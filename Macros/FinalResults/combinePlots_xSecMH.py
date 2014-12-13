#!/usr/bin/python
import os,sys
import array
from glob import glob
from subprocess import call
from optparse import OptionParser

##### CONFIGURATION ######
nBins_=6 # later figured out
mass_=125
sigma_=1
wsFile_="input_ws/CMS-HGG_Fiducial_Sig.root"
###      red green, blue, orange,cyan, yelow
colors_=[632,416,600,800,432,400+2,416+2,632+2,58]
dir_='jobs'
Lumi=19.7
mhpoints_=[124.30,124.35,124.40,124.45,124.50,124.55,124.60,124.65,124.70,124.75,124.80,124.85,124.90,124.95,125.00,125.05,125.10,125.15,125.20]
##########################

############ PARSER 
if __name__=="__main__":
	usage = "usage: %prog [options]"
	parser=OptionParser(usage=usage)
	parser.add_option("-b","--batch" ,dest='batch',action='store_true',help="Batch Mode. Default=%default",default=False)
	#parser.add_option("-D","--dir" ,dest='dir',type='string',help="Directory. Default=%default",default=dir_)
	parser.add_option("-s","" ,dest='sig',type='string',help="Ws Sig not fitted. Default=%default",default=wsFile_)
	#parser.add_option("-v","--var" ,dest='var',type='string',help="Variable. If non null read bins from the var file. Default=%default",default="")
	#parser.add_option("","--unblind" ,dest='unblind',action='store_true',help="Unblind Plots. Default=%default",default=False)
	(options,args)=parser.parse_args()
	#dir_=options.dir
        wsFile_=options.sig

print "Importing ROOT"
sys.argv=[]
import ROOT
if options.batch: ROOT.gROOT.SetBatch()

import math
from glob import glob

from PlotsLibrary import findPath,getMu,DrawNLL,GetXsec,plot2DNLL
(mypath,globe_name)=findPath()

#from globe_name.Macros.FinalResults.combineHarvester import getVariableBins 
sys.path.append(mypath+"/Macros/FinalResults")
from combineHarvester import getVariableBins,getVariableBinsFromWs

#take from the file
#if options.var == "":
#	nBins_=6
#else:
#	(nBins_,boundaries,jooa)=getVariableBinsFromWs(options.var,wsFile_,verbose=True)

# load combine
ROOT.gSystem.Load("libHiggsAnalysisCombinedLimit.so")
f=ROOT.TFile.Open(wsFile_)
ws=f.Get("cms_hgg_workspace")

plot2DNLL("MuMH/MuMH_Unfold_Fiducial/MuMH_Unfold_Fiducial.root",ws )
