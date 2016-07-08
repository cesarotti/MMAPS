# read LHE file, store photon ELab, thetaLab;
# to run:
# python processLHDfile.py 2gam 02


import sys,os,re
from math import *
import numpy as np
#import ROOT as rt

print os.getcwd()

#filename="/Users/carissacesarotti/DarkCode/Dark-Photons/madgraph/LHEtoProcess/unweighted_events.lhe" # CHANGE TO YOUR PATHWAY
filename="/nfs/cms/mc1/cjc359/Dark-Photons/madgraph/parse/3gamma4.lhe"
outfilename="data_3gamma4.lhe"
print "3gamma sample"


	
getline=open(filename).xreadlines()


# metadata of whole run
me=0.000511
sqrts=0.070   # be careful!  We might change these beam-conditions parameters in some runs! Better to take value from LHE file.
Ebeam=5.000
EbeamTrueInMeV=((sqrts**2/(2*me))-me)*1000
print "Note sqrt(s) = ",sqrts*1000," MeV,  and Ebeam = ",EbeamTrueInMeV," MeV.  "

# Lorentz parameters gamma and beta
gammabeam=((sqrts/me)**2)/2 -1.0
betaCM=sqrt((gammabeam-1)/(1+gammabeam))
gammaCM=1/sqrt(1-betaCM**2)
b=betaCM    # shorter names for same thing
g=gammaCM
print gammabeam
print "betaCM and gammaCM = ", betaCM, gammaCM



naccepted=0
ntry=0
status="NotInEvent"
ievt=0
all_lines=[]  # this will be the whole lhe file, minus unaccepted events
nnn=0
ngoodparticle=0
nacc=0
for line in getline:
	nnn+=1

	# start of event
	if "<event>" in line: 
		status="InEvent"
		ievt+=1
		nAcceptedParticles=0
		event_lines=[]  # start empty list to write lhe lines into for each event
		event_lines.append(line)
		ngoodparticle=0
		continue  # get next line from file
		
		
	# end of event: process for future use
	if "</event>" in line:  
		status="NotInEvent"
		event_lines.append(line)
		# Now check if any particles from this event were in the acceptance; if so, transfer whole event_lines to all_lines
		if ngoodparticle>0:
			for eline in event_lines: 
				all_lines.append(eline)
				print "xxx ",eline[:-1]
				nacc+=1
			del event_lines  # get rid of the event lines list now
		ngoodparticle=0
		continue
		

	# read in LHE data and store 
	if status=="InEvent":
	
		if line[0]=="<":
			event_lines.append(line)
			continue
			
		if line[1].isdigit(): 
			event_lines.append(line)  # event metadata
			continue
			
		elements=map(lambda x: x.strip(),  filter(lambda q: q!="", line[:-1].split(" "))  )
		
		istate=elements[1] # istate = -1 for initial state particles, +1 for final state particles#
		print "istate=",istate, line[:-1]
		if int(istate) == -1: 
			event_lines.append(line)
			continue  # no need to check for acceptance -- this one isn't in the final state anyway
		

		# now we have a particle in the final state: check whether in acceptance or not before adding to event_lines
		(px,py,pz,E,m)=map(lambda x: float(x),elements[6:11])
		ntry+=1
		pt=sqrt(px**2 + py**2)
		costhCM=cos(atan2(pt,pz))
		costhLab=(costhCM+betaCM)/(1+betaCM*costhCM)
		angleLab=acos(costhLab)
		if (angleLab > 2.0*pi/180. and angleLab < 5.0*pi/180.):  ngoodparticle+=1				
		event_lines.append(line)
		
		
	# any lines not associated with an event get transferred to all_lines
	#print "any line: ",line[:-1]
	if status != "InEvent": all_lines.append(line)
	
		
print "number of accepted events written to output file: ",nacc

outfile=open(outfilename,"w")
for line in all_lines: outfile.write(line)
outfile.close()
print "Closed ",outfilename
