import sys
import os
import binascii
import struct

path = sys.argv[2]
if os.path.exists(path): 
    os.remove(path)  
else:
    print('no such file')

filepath= sys.argv[1]

f = open(path, "w") 
fb = open(filepath, "rb")

print >> f,"MEMORY_INITIALIZATION_RADIX=16;"
print >> f,"MEMORY_INITIALIZATION_VECTOR="


one_line = 16

databuffer = ["0"]*(one_line*2) #["0","0","0","0","0","0","0","0"]

size = os.path.getsize(filepath)
for i in range(size//one_line):
	
  for j in range(one_line):
    datab = fb.read(1) 
    datah =  str(binascii.b2a_hex(datab))[0]
    databuffer[(one_line-1-j)*2] = datah
    datah =  str(binascii.b2a_hex(datab))[1]
    databuffer[(one_line-1-j)*2+1] = datah

  for n in range(one_line*2):
    f.write(databuffer[n])
  
  if i < (size//one_line)-1:
    print >> f,","
  else :
    print >> f,";"

fb.close()
f.close()
