import sys,re
from math import *
import numpy as np

def isign(ipdgID):
	if ipdgID > 0: return -1
	if ipdgID < 0: return +1
	return 0

print("Hello World!")

status = ""

filename="/Users/carissacesarotti/DarkCode/Dark-Photons/madgraph/LHEtoProcess/unweighted_events.lhe"
getline=open(filename).xreadlines()
outName="unweighted_events_hit.lhe"

outfile=open(outName,'w')
itype=22

#Set up the header of LHE
for line in getline:
    
    if "<event>" not in line: 
        outfile.write(line)
    else:
        break

for line in getline:

    if "<event>" in line:
        status="InEvent"
        continue
        
    if status=="InEvent":

        if line[1].isdigit(): continue
        elements=map(lambda x: x.strip(),  filter(lambda q: q!="", line[:-1].split(" "))  )
        iparticleType=int(elements[0])
        iq=isign(iparticleType) # sign of charge
        if (abs(iparticleType) != itype ): continue  # skip anything not a photon (or whatever itype is)
        (px,py,pz,E,m)=map(lambda x: float(x),elements[6:11])

        print "X Momentum"
        print px
        print py
        print px
        print E
        print m
        print "Done"



outfile.close()
   




