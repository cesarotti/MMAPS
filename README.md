# MMAP-Magnet-Sim
Simulation for the Cornell MMAP experiment including the adjustment magnet.
# MMAPS
To use batch mode, if the code needs to be recompiled, use compile.sh, then batchMode.sh
To use interface mode, use builddarkphotonCLASSE.sh

#SIMULATION STUDIES

If you are going to change parameters, DO NOT GO INTO THE CODE. Instead, open the file in the MMAPS folder called "parameters.txt". In this file, the labels on the variables should be easily understood. If the quantity is dimensionful, the units you should use are included in the name. Modify and save this file, then can run batch mode once the issues with the madgraph events are sorted out. Use "builddarkphotonCLASSE.sh buildscript. As always with build scripts, open and adjust pathways. 

To remember all parameters, in the output folder, there will be a text file called "output.txt" which will save all the variables such that one can remember what this run was in the future. 