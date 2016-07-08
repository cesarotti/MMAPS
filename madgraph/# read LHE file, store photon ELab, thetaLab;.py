# read LHE file, store photon ELab, thetaLab;
# to run:
# python processLHDfile.py 2gam 02


import sys,os,re
from math import *
import numpy as np
import ROOT as rt


def isign(ipdgID):
	if ipdgID > 0: return -1
	if ipdgID < 0: return +1
	return 0



print os.getcwd()


filename="/Users/carissacesarotti/DarkCode/Dark-Photons/madgraph/LHEtoProcess/unweighted_events.lhe"
outfilename="data_radBhabha.lhe"
itype=22
print "radiative Bhabha sample"


	
getline=open(filename).xreadlines()
outfile=open(outfilename,"w")


# Lorentz parameters gamma and beta
sqrts=0.070
Ebeam=5.000
me=0.000511
gammabeam=((sqrts/me)**2)/2 -1.0
print gammabeam
betaCM=sqrt((gammabeam-1)/(1+gammabeam))
gammaCM=1/sqrt(1-betaCM**2)
print "betaCM and gammaCM = ", betaCM, gammaCM
naccepted=0
ntry=0



status="ready"
ievt=0
for line in getline:

	# start of event
	if "<event>" in line: 
		status="InEvent"
		ievt+=1
		continue  # get next line from file
		
		
	# end of event: process for future use
	if "</event>" in line or "<mgrwt>" in line:  
		status="NotInEvent"
		

	# read in LHE data and store		
	if status=="InEvent":
	
		if line[1].isdigit(): continue
		elements=map(lambda x: x.strip(),  filter(lambda q: q!="", line[:-1].split(" "))  )
		iparticleType=int(elements[0])	
		iq=isign(iparticleType) # sign of charge
		if (abs(iparticleType) != itype ): continue  # skip anything not a photon (or whatever itype is)
		(px,py,pz,E,m)=map(lambda x: float(x),elements[6:11])
		if px==0.0: continue  # skip incoming e+ and target e- when itype=11
		ntry+=1


		pt=sqrt(px**2 + py**2)
		costhCM=cos(atan2(pt,pz))
		b=betaCM
		g=gammaCM
		costhLab=(costhCM+betaCM)/(1+betaCM*costhCM)
		angleLab=acos(costhLab)
		ELab= gammaCM*(E + betaCM*pz)
		pzLab=gammaCM*(pz+ betaCM*E)
		m2=ELab**2 - pzLab**2 - pt**2

		if (angleLab < 2.0*pi/180. or angleLab > 5.0*pi/180.): continue # keep only if in detector acceptance		
		naccepted +=1		
		data = "%12.6e %12.6e %12.6e"%(ELab, pzLab, angleLab)
		#data = "%12.6e %12.6e %12.6e, &i"%(ELab, pzLab, angleLab, iq)
		outfile.write(data+"\n")
		
		
		
print "nAccepted=",naccepted, " nphotons=",ntry, " nEvents=",ievt," Acceptance=",float(naccepted)/float(ievt)	
outfile.close()
print "Closed ",outfilename