#!/bin/env python
import os,sys
from optparse import OptionParser

if __name__=="__main__":
	usage = "usage: %prog [options]"
	parser=OptionParser(usage=usage)
	parser.add_option("-f","--file" ,dest='file',type='string',help="postfit file. Default=%default",default="cms-hgg.root")
	parser.add_option("-d","--debug" ,dest='debug',action='store_true',help="DEBUG. Default=%default",default=False)
	(opts,args)=parser.parse_args()

import ROOT

#load combine
ROOT.gSystem.Load("libHiggsAnalysisCombinedLimit.so");

f=ROOT.TFile.Open(opts.file)

if f==None: 
	print "Give me a file!!! "
	exit(0)

ws=f.Get("w")

cat=0
Bin=0

while True: # loop on cat
   nominal = 0
   JESup   = 0
   JESdn   = 0
   while True: # integrate over bins
	if opts.debug: print "executing bin%d cat %d"%(Bin,cat) #DEBUG
	ws.var("CMS_hgg_JES").setVal(0)
	n	=ws.function("n_exp_bincat%(cat)d_8TeV_proc_Bin%(bin)d"%{"cat":cat,"bin":Bin})
	norm	=ws.function("shapeSig_Bin%(bin)d_cat%(cat)d_8TeV__norm"%{"cat":cat,"bin":Bin})
	if n == None or norm == None: break;
	nominal += n.getVal()*norm.getVal()
	ws.var("CMS_hgg_JES").setVal(1)
	JESup += n.getVal()*norm.getVal()
	ws.var("CMS_hgg_JES").setVal(-1)
	JESdn += n.getVal()*norm.getVal()

	Bin+=1
   if nominal == 0 and JESup == 0 and JESdn == 0 : break;	
   print "CAT %(cat)d nBins=%(nBins)d JESUP = %(jup)f JESDN = %(jdn)f"%{"cat":cat,"nBins":Bin,"jup":JESup/nominal,"jdn":JESdn/nominal}
   Bin=0
   cat+=1

#root [33] ws::n_exp_bincat0_8TeV_proc_Bin0->Print()
#ProcessNormalization::n_exp_bincat0_8TeV_proc_Bin0[ thetaList=(lumi_8TeV,CMS_hgg_n_trig_eff) asymmThetaList=(CMS_hgg_n_id_eff,CMS_hgg_JES,CMS_hgg_n_sigmae) otherFactorList=(r_Bin0) ] = 19715
#root [34]  ws::shapeSig_Bin0_cat0_8TeV__norm->Print()
