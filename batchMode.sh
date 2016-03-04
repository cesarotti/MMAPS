#!/bin/bash                                                                     
# Run annihilation                                                              

source /opt/rh/devtoolset-3/enable
source /nfs/opt/root/bin/thisroot.sh
export CXX="/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/bin/c++"; export CC="/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/bin/cc"
export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/lib/:/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/gcc/4.9.1-cms/lib64/"
export G4LEDATA="/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/geant4-G4EMLOW/6.35/data/G4EMLOW6.35/"
export G4LEVELGAMMADATA="/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/geant4-G4PhotonEvaporation/3.0/data/PhotonEvaporation3.0/"
export G4SAIDXSDATA="/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/geant4-G4SAIDDATA/1.1/data/G4SAIDDATA1.1/"
export G4NEUTRONXSDATA="/cvmfs/cms.cern.ch/slc6_amd64_gcc491/external/geant4-G4NEUTRONXS/1.4/data/G4NEUTRONXS1.4/"



#cd /nfs/cms/mc1/cjc359/MMAPS/darkPhotonBuild2

cd /nfs/cms/mc1/cjc359/MMAPS_Sim/darkPhotonBuild2

currentfolder=$(date +%Y:%m:%d#%H:%M:%S)
echo "Today's date is " >> output.txt
date +%Y:%m:%d#%H:%M:%S >> output.txt


# export G4LIB_USE_GDML=0
# export XERCESCROOT=/build/dmendezl/CMSSW_7_2_0_pre4-build/slc6_amd64_gcc491/external/xerces-c/2.8.0-cms
# export G4LIB_BUILD_SHARED=1



./darkPhoton /nfs/cms/mc1/cjc359/MMAPS_Sim/runBatch2.mac


mkdir ../$currentfolder
mv *.root  ../$currentfolder
rm -rf *.root
cd ../$currentfolder
mv /nfs/cms/mc1/cjc359/MMAPS_Sim/darkPhotonBuild2/output.txt ./
hadd complete.root *.root
mkdir threadfiles
mv *.root threadfiles
cd threadfiles
mv complete.root ../
