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
wsFile_="CMS-HGG.root"
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
	parser.add_option("-D","--dir" ,dest='dir',type='string',help="Directory. Default=%default",default=dir_)
	parser.add_option("-s","" ,dest='sig',type='string',help="Ws Sig not fitted. Default=%default",default=wsFile_)
	parser.add_option("-v","--var" ,dest='var',type='string',help="Variable. If non null read bins from the var file. Default=%default",default="")
	parser.add_option("-k","--split" ,dest='split',action='store_true',help="Add split info for root files for Nicolas (>v5). Default=%default",default=True)
	parser.add_option("-K","--nosplit" ,dest='split',action='store_false',help="Dont split info for root files.")
	parser.add_option("","--unblind" ,dest='unblind',action='store_true',help="Unblind Plots. Default=%default",default=False)
	(options,args)=parser.parse_args()
	dir_=options.dir
        wsFile_=options.sig

print "Importing ROOT"
sys.argv=[]
import ROOT
if options.batch: ROOT.gROOT.SetBatch()
ROOT.gROOT.ProcessLine(
		'struct entry{\
		Float_t var;\
		Float_t nll;\
		};'
		)
from ROOT import entry

ROOT.gROOT.ProcessLine("Float_t histBins[100];");
from ROOT import histBins;
import math
from glob import glob

from PlotsLibrary import findPath,getMu,DrawNLL,GetXsec
(mypath,globe_name)=findPath()

#from globe_name.Macros.FinalResults.combineHarvester import getVariableBins 
sys.path.append(mypath+"/Macros/FinalResults")
from combineHarvester import getVariableBins,getVariableBinsFromWs

#take from the file
if options.var == "":
	nBins_=6
	histBins[0]=0
	histBins[1]=20
	histBins[2]=35
	histBins[3]=60
	histBins[4]=130
	histBins[5]=400
else:
	(nBins_,boundaries,jooa)=getVariableBinsFromWs(options.var,wsFile_,verbose=True)
	#(nBins_,boundaries,jooa) = getVariableBins(options.var,verbose=True)
	#nBins_ += 1
	for iBin in range(0,len(boundaries)):
		histBins[iBin] = boundaries[iBin]

## Draw Canvas nll##


for mh in mhpoints_:
	ExpStr="Exp"
	if options.unblind: ExpStr=""
	try:	DrawNLL(dir_,nBins_,("UnfoldScan%s_mh%.2f"%(ExpStr,mh)).replace('.','_'))
	except ReferenceError: pass ## no file
	try:	DrawNLL(dir_,nBins_,("RecoScan%s_mh%.2f"%(ExpStr, mh)).replace('.','_'))
	except ReferenceError: pass ## no file
	try:	DrawNLL(dir_,nBins_,("RecoScanStat%s_mh%.2f"%(ExpStr,mh) ).replace('.','_'))
	except ReferenceError: pass ## no file
	try:	DrawNLL(dir_,nBins_,("UnfoldScanStat%s_mh%.2f"%(ExpStr,mh)).replace('.','_'))
	except ReferenceError: pass ## no file

# load combine
ROOT.gSystem.Load("libHiggsAnalysisCombinedLimit.so")
f=ROOT.TFile.Open(wsFile_)
ws=f.Get("cms_hgg_workspace")

xSecVsMh={}
xSecSplitVsMh={}
for mh in mhpoints_:
	xSecPerBin=GetXsec(ws,mh,nBins_,Lumi)
	xSecVsMh[mh] = xSecPerBin

	if options.split:
		xSecSplit={}
		#HSplit={}
		procs=["ggh","vbf","wh","zh","tth"]
		for p in procs:
			xSecSplit[p]=GetXsec(ws,mass_,nBins_,Lumi,"_"+p)
			#HSplit[p]=ROOT.TH1F("HExp_"+p,"HExpected "+p,nBins_,histBins)
		xSecSplitVsMh[mh]=xSecSplit

ROOT.gStyle.SetErrorX(0)
ROOT.gStyle.SetOptStat(0)
C=ROOT.TCanvas("c","c")

G=ROOT.TGraphAsymmErrors(); G.SetName("tgraph_data");
GExp=ROOT.TGraphAsymmErrors(); GExp.SetName("tgraph_expected")
GBbB=ROOT.TGraphAsymmErrors(); GBbB.SetName("tgraph_BbB")

for mh in mhpoints_:
	if options.unblind:(Mu,Graphs) = getMu(nBins_,dir_,'UnfoldScan',mh=mh)
	else: (Mu,Graphs) = getMu(nBins_,dir_,'UnfoldScanExp',mh=mh)
	
	try: 	MuU=getMu(nBins_,dir_,"UnfoldScan%s"%ExpStr,1,mh=mh)[0]
	except: MuU=None
	try:	MuUS=getMu(nBins_,dir_,"UnfoldScanStat%s"%ExpStr,1,mh=mh)[0]
	except: MuUS=None
	try:	MuR=getMu(nBins_,dir_,"RecoScan%s"%ExpStr,1,mh=mh)[0]
	except: MuR=None
	try:	MuRS=getMu(nBins_,dir_,"RecoScanStat%s"%ExpStr,1,mh=mh)[0]
	except: MuRS=None

	print "ONLY BIN 0 -- ONLY FIDUCIAL"
	iBin=0;
	print "Mu ",MuU[iBin][0], "+-", MuU[iBin][1],MuU[iBin][2]

	iPoint=G.GetN();

	y=xSecVsMh[mh][iBin] * MuU[iBin][0]
	ylow=xSecVsMh[mh][iBin] * MuU[iBin][1]
	yhigh=xSecVsMh[mh][iBin] * MuU[iBin][2]

	G.SetPoint(iPoint, mh, y);
	G.SetPointEXhigh(iPoint, 0);
	G.SetPointEXlow(iPoint, 0);
	G.SetPointEYhigh(iPoint, yhigh-y);
	G.SetPointEYlow(iPoint, y-ylow);
	
	##use Exp
	print "TODO"
	y=xSecVsMh[mh][iBin]
	ylow=xSecVsMh[mh][iBin] 
	yhigh=xSecVsMh[mh][iBin]

	GExp.SetPoint(iPoint, mh, y)
	GExp.SetPointError(iPoint,0,0,0,0);

G.SetMarkerStyle(20)
G.Draw("AP")
G.GetYaxis().SetTitle("#sigma [fb]")
G.GetXaxis().SetTitle("m_{H} [GeV]")

GExp.SetLineColor(ROOT.kRed)
GExp.Draw("LSAME")

fileName="xSecMHScan_"+dir_.replace("/","")

C.SaveAs(fileName+".pdf")
C.SaveAs(fileName+".png")
C.SaveAs(fileName+".root") #will be deleted by the next line if split

f=ROOT.TFile(fileName+".root","UPDATE")

f.cd()
G.Write()
GExp.Write()
#GBbB.Write()
f.Close()
