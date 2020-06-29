from jinja2 import Environment,PackageLoader,Template

from  netParam import * 

#env = Environment(loader=PackageLoader('python_project','.'))



pe = PEConfig(True,3,1,True)

wmdma = [ DMAConfig(0,0,100), DMAConfig(100,100,200),DMAConfig(200,200,300) ]

wm = WMConfig(1024,DMAGroupConfig(wmdma) )

fmdma0 = FMDMAConfig( 0,0,100,200,2 )
fmdma1 = FMDMAConfig( 200,200,100,200,3)

fmround0 = FMRoundConfig( shape = {'height':10,'width':10,'channel':10,},kernel = 3,stride = 1,pooling = 1,padding =  {'top':1,'bottom':2,'left':3,'right':4,} ,dma_group=fmdma0)
fmround1 = FMRoundConfig( shape = {'height':10,'width':10,'channel':10,},kernel = 3,stride = 1,pooling = 1,padding =  {'top':1,'bottom':2,'left':3,'right':4,} ,dma_group=fmdma1)

fm = FMConfig( [fmround0,fmround1] )

ppu = PPUConfig( BBQSConfig(True,False,1024,DMAGroupConfig(wmdma),1024,DMAGroupConfig(wmdma) ),act_en = True,pool_en = True,pool_sign = True,pool_kernel = 0,dc_size = 1,dc_step = 1,wbdma= DMAGroupConfig(wmdma) )

layer  = LayerConfig(pe,wm,fm,ppu)

net = NetConfig( [layer] ,"testnet")


for i in net.get_cvar_list(name = 'test_net'):
    print (i)
#print(net.get_cvar_list(name = 'net')[0])

with open( "./base_cvar.template","r") as f:
    template = Template(f.read() )

print( template.render(var = net.get_cvar_list(list = [],name='test_net') ) )
#print( template.render(var = PEConfig( True).get_cvar_list(name="testpe") ) )


