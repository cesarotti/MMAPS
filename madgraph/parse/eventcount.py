import sys,os,re
from math import *
import numpy as np

print os.getcwd()

filename="/nfs/cms/mc1/cjc359/Dark-Photons/madgraph/parse/data_3gamma1.lhe"

getline=open(filename).xreadlines()
linecount=0

for line in getline:
    if "<event>" in line:
        linecount=linecount+1

print linecount