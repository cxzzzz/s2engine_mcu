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
databuffer = ["0","0","0","0","0","0","0","0"]

print >> f,"MEMORY_INITIALIZATION_RADIX=16;"
print >> f,"MEMORY_INITIALIZATION_VECTOR="

size = os.path.getsize(filepath)
for i in range(size/4):
	
  for j in range(4):
    datab = fb.read(1) 
    datah =  str(binascii.b2a_hex(datab))[0]
    databuffer[(3-j)*2] = datah
    datah =  str(binascii.b2a_hex(datab))[1]
    databuffer[(3-j)*2+1] = datah

  for n in range(8):
    f.write(databuffer[n])
  
  if i < (size/4)-1:
    print >> f,","
  else :
    print >> f,";"

fb.close()
f.close()
