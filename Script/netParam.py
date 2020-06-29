from typing import List,Dict
from copy import copy

class CVar:
    def __init__(self,typ,name,value):
        self.typ = typ
        self.isList = isinstance(value,list)
        self.isConfig = (not self.isList) and "Config" in typ
        self.isDict = (not self.isList) and "dict" in typ
        self.name = name 
        self.value = value
    #def __str__(self)->str:
    #    return "({},{}:{})".format(self.typ,self.name,str(self.value))
    def __repr__(self)->str:
        return "({},{}:{})".format(self.typ,self.name,str(self.value))

class Config: 
    typ = ""

    '''@staticmethod
    def dict_get_dict_cvar(dic:Dict,typ :str = "",list:List=[],name = "")->Tuple[Dict,List[CVar] ]:

        _child_cnt = 0
        value = dict()

        for k,v in dic.items():

            if( '_' == k[0]): #跳过内部变量
                continue

            elif( isinstance(v,List) ): #数组必须通过间接引用
                v_name = "{}_{}".format(name,k)
                _child_cnt += 1

                inner_list = []
                cnt = 0

                if( isinstance(v[0],List) ): #仅支持一维数组
                    assert(False)

                for vv in v:
                    assert( type(v[0]) == type(vv) ) #单类型数组
                    if( isinstance(vv,Config) ):

                        vv_cvar_list = vv.get_cvar_list(list=[], name = vv._name if vv._name != "" else "{}_{}".format(v_name,cnt) )

                        list.extend( vv_cvar_list[0:-1] )
                        vv_cvar = vv_cvar_list[-1]
                        inner_list.append( vv_cvar )
                    else:
                        inner_list.append(vv)
                    cnt +=1
                
                if( isinstance(v[0],Config) ):
                    v_type = v[0].typ
                elif( isinstance(v[0],int) ):
                    v_type = "uint32_t"
                elif( isinstance(v[0],str)):
                    v_type = "char"
                else:
                    assert(False)

                v_cvar = CVar( v_type,v_name,inner_list )
                list.append(v_cvar)

                value[k] = "&{}".format(v_name)
            else:
                if( isinstance(v,Config)):
                    v_cvar_list = v.get_cvar_list(list=[] , name = v._name if v._name != "" else "{}_{}".format(name,k))
                    v_cvar = v_cvar_list[-1]
                    value[k] = v_cvar
                    list.extend(v_cvar_list[0:-1])
                elif( isinstance(v,dict) ):
                    ret = Config.dict_get_dict_cvar(v,typ= "",list = [])
                    value[k] = ret[0]
                    list.extend(ret[])
                else:
                    assert(False)
                
        cvar = CVar(typ,name,value)
        
        list.append(cvar)  

        return list
        '''

    @staticmethod
    def dict_get_cvar_list(dic:Dict,typ:str = "",list:List=[] , name = "")->List[CVar]:

        _child_cnt = 0

        value = dict()
        for k,v in dic.items():

            if( '_' == k[0]): #跳过内部变量
                continue

            elif( isinstance(v,List) ): #数组必须通过间接引用
                v_name = "{}_{}".format(name,k)
                _child_cnt += 1

                inner_list = []
                cnt = 0

                if( isinstance(v[0],List) ): #仅支持一维数组
                    assert(False)

                for vv in v:
                    assert( type(v[0]) == type(vv) ) #单类型数组
                    if( isinstance(vv,Config) ):

                        vv_cvar_list = vv.get_cvar_list(list=[], name = vv._name if vv._name != "" else "{}_{}".format(v_name,cnt) )

                        list.extend( vv_cvar_list[0:-1] )
                        vv_cvar = vv_cvar_list[-1]
                        inner_list.append( vv_cvar )
                    else:
                        inner_list.append(vv)
                    cnt +=1
                
                if( isinstance(v[0],Config) ):
                    v_type = v[0].typ
                elif( isinstance(v[0],int) ):
                    v_type = "uint32_t"
                elif( isinstance(v[0],str)):
                    v_type = "char"
                else:
                    assert(False)

                v_cvar = CVar( v_type,v_name,inner_list )
                list.append(v_cvar)

                value[k] = "&{}".format(v_name)
            else:
                if( isinstance(v,Config)):
                    v_cvar_list = v.get_cvar_list(list=[] , name = v._name if v._name != "" else "{}_{}".format(name,k))

                    v_cvar = v_cvar_list[-1]
                    value[k] = v_cvar
                    list.extend(v_cvar_list[0:-1])
                elif( isinstance(v,dict)):
                    v_cvar_list = Config.dict_get_cvar_list(v,typ="dict",list =[],name = "{}_{}".format(name,k) )

                    v_cvar = v_cvar_list[-1]
                    value[k] = v_cvar
                    list.extend(v_cvar_list[0:-1])
                else:
                    value[k] = v
                
        cvar = CVar(typ,name,value)
        
        list.append(cvar)  

        return list




    def __init__(self,name):
        self._name = name
        self._child_cnt = 0
    
    def get_cvar_list(self,list:List=[],name = "")->List[CVar]:
        d_self = copy(self.__dict__)

        if( name == ""):
            name = self._name

        '''value = dict()
        for k,v in d_self.items():

            if( '_' == k[0]): #跳过内部变量
                continue

            elif( isinstance(v,List) ): #数组必须通过间接引用
                v_name = "{}_{}".format(name,k)
                self._child_cnt += 1

                inner_list = []
                cnt = 0;

                if( isinstance(v[0],List) ): #仅支持一维数组
                    assert(False)

                for vv in v:
                    assert( type(v[0]) == type(vv) ) #单类型数组
                    if( isinstance(vv,Config) ):

                        vv_cvar_list = vv.get_cvar_list(list=[], name = vv._name if vv._name != "" else "{}_{}".format(v_name,cnt) )

                        list.extend( vv_cvar_list[0:-1] )
                        vv_cvar = vv_cvar_list[-1]
                        inner_list.append( vv_cvar )
                    else:
                        inner_list.append(vv)
                    cnt +=1
                
                if( isinstance(v[0],Config) ):
                    v_type = v[0].typ
                elif( isinstance(v[0],int) ):
                    v_type = "uint32_t"
                elif( isinstance(v[0],str)):
                    v_type = "char"
                else:
                    assert(False)

                v_cvar = CVar( v_type,v_name,inner_list )
                list.append(v_cvar)

                value[k] = "&{}".format(v_name)
            else:
                if( isinstance(v,Config)):
                    v_cvar_list = v.get_cvar_list(list=[] , name = v._name if v._name != "" else "{}_{}".format(name,k))
                    v_cvar = v_cvar_list[-1]
                    value[k] = v_cvar
                    list.extend(v_cvar_list[0:-1])
                else:
                    value[k] = v
                
        cvar = CVar(self.typ,name,value)
        
        list.append(cvar)  
        '''

        return Config.dict_get_cvar_list(d_self,self.typ,list,name)

        #return list


class DMAConfig(Config):

    typ = "DMAConfig"

    def __init__(self,rd_addr,wr_addr,size,name = ""):
        super().__init__(name)
        #self.start_addr = start_addr
        #self.size = size
        self.rd_addr = rd_addr
        self.wr_addr = wr_addr
        self.size = size


class DMAGroupConfig(Config):

    typ = "DMAGroupConfig"

    def __init__(self,dma_configs,name = ""):
        super().__init__(name)
        self.dma_length = len(dma_configs)
        self.dma = dma_configs

class FMDMAConfig(Config):

    typ = "FMDMAConfig"

    def __init__(self,rd_addr,wr_addr,size,step,loop,name = ""):
        super().__init__(name)
        self.wr_addr= wr_addr
        self.rd_addr= rd_addr
        self.size = size
        self.step = step
        self.loop = loop

class PEConfig(Config):
    
    typ = "_PEConfig"

    def __init__(self,fsign:bool,kernel:int,stride:int,comp_en = bool,name = ""):
        super().__init__(name)
        self.pe = { "fsign" : fsign}
        self.ce = { "kernel" : kernel,"stride":stride}
        self.comp = { "en":comp_en }

'''class CEConfig(Config):

    typ = "_CEConfig"
    
    def __init__(self,kernel:int,stride:int,name = ""):
        super().__init__(name)
        self.kernel = kernel
        self.stride = stride

class CompConfig(Config):
    typ = "_CompConfig"

    def __init__(self,en,name = ""):
        super().__init__(name)
        self.en = en

class PESubConfig(Config):

    typ = "PEConfig"
    def __init__(self,pe,ce,comp):
        self.pe = pe
        self.ce = ce
        self.comp = comp

'''

    
class WMConfig(Config):
    typ = "WMConfig"

    def __init__(self,loop:int,dma_group:DMAGroupConfig,name = ""):
        super().__init__(name)
        self.loop = loop
        self.dma = dma_group


class FMRoundConfig(Config):
    typ = "FMRoundConfig"
    def __init__(self,shape:Dict,kernel:int,stride:int,pooling:int,padding:Dict,dma_group:FMDMAConfig,
            round_read_times:int=0, round_read_sig:int=0,name = ""):
        super().__init__(name)
        self.shape = shape

        self.kernel = kernel
        self.stride = stride
        self.pooling = pooling

        self.padding = padding

        self.round_read_times = round_read_times
        self.round_read_sig = round_read_sig

        self.dma = dma_group

class FMConfig(Config):
    typ = "FMConfig"

    def __init__(self,fmround_group:List[FMRoundConfig],name = ""):
        super().__init__(name)
        self.config_length = len(fmround_group)
        self.config = fmround_group

class BBQSConfig(Config):
    typ = "BBQConfig"

    def __init__(self,sc_sign:bool,sc_en:bool,loop:int,bfdma:DMAGroupConfig,bmloop:int,bmdma:DMAGroupConfig,name = ""):
        super().__init__(name)
        self.sc_sign = sc_sign
        self.sc_en = sc_en
        self.loop = loop
        
        self.bf = { "dma": bfdma }
        self.bm = { "loop":bmloop,"dma":bmdma }

class PPUConfig(Config):
    typ = "PPUConfig"

    def __init__(self,bbqs:BBQSConfig,act_en:bool,pool_en:bool,pool_sign:bool,pool_kernel:int,dc_size:int,dc_step:int,wbdma:DMAGroupConfig,name = ""):
        super().__init__(name)
        self.bbqs = bbqs
        self.act = { "en":act_en}
        self.pool = { "en":pool_en, "sign":pool_sign, "kernel":pool_kernel }
        self.dc = { "size":dc_size,"step":dc_step }

        self.wb = { "dma": wbdma }
    

class LayerConfig(Config):
    typ = "LayerConfig"

    def __init__(self,pe:PEConfig,wm:WMConfig,fm:FMConfig,ppu:PPUConfig,name = ""):
        super().__init__(name)
        self.pe = pe
        self.wm = wm
        self.fm = fm
        self.ppu = ppu

class NetConfig(Config):
    typ = "NetConfig"

    def __init__(self,layers:List[LayerConfig],name = ""):
        super().__init__(name)
        self.layer_length = len(layers)
        self.layer = layers


class IOConfig(Config):
    typ =  "IOConfig"

    def __init__(self,net_load:DMAGroupConfig,feature_load:DMAGroupConfig,feature_store:DMAGroupConfig,name= ""):
        super().__init__(name)

        self.net_load = net_load
        self.feature_load = feature_load
        self.feature_store = feature_store
    