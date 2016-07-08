import sys, os, re
from math import *
import numpy as np

print os.getcwd()

filename="/nfs/cms/mc1/cjc359/Dark-Photons/madgraph/parse/data_3gamma1.lhe"
filename2="/nfs/cms/mc1/cjc359/Dark-Photons/madgraph/parse/data_3gamma4.lhe"

getline=open(filename2).xreadlines()

all_lines=[]
check=False


for line in getline:
    if '<event>' in line: check = True
    if check: all_lines.append(line)


outfile=open(filename,"a")
for line in all_lines: outfile.write(line)
outfile.close()

