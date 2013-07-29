
import commands,sys,os, json
import array
import ROOT
from optparse import OptionParser

# Local python imports
from datBlocks import *
from makeFilelist import *
from getTreeEntry import *

PYDEBUG=True

#dir='/store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/Summer12_DR53X-PU_RD1_START53_V7N/DiPhotonJetsBox_M60_8TeV-sherpa_Summer12_DR53X-PU_RD1_START53_V7N-v1'

ROOT.gROOT.ProcessLine( \
	"struct Entry{ \
	    float w; \
	};" 
	)
from ROOT import Entry

Sw=0.0;
nT=0;

from optparse import OptionParser

parser = OptionParser()
parser.add_option("-j","--jobId",dest="jobId",type='int',default=0)
parser.add_option("-n","--nJobs",dest="nJobs",type='int',default=-1)
parser.add_option("-p","--path",dest="Path",type='string',default="/store/group/phys_higgs/cmshgg/processed/V15_00_08/mc/Summer12_DR53X-PU_RD1_START53_V7N/DiPhotonJetsBox_M60_8TeV-sherpa_Summer12_DR53X-PU_RD1_START53_V7N-v1")

(options,args)=parser.parse_args()

if PYDEBUG:
	print >>sys.stderr, "nJobs="+str(options.nJobs)+" jobId="+str(options.jobId)

ca_files=makeCaFiles(options.Path,options.nJobs,options.jobId);
for file_s in ca_files:
	if not file_s[1]:
		continue
	if PYDEBUG:
		print >> sys.stderr, str(len(file_s)) + " " + file_s[0] + " " + str(file_s[1]) 
	newFile = ROOT.TFile.Open(file_s[0]);
	tree = newFile.Get("event"); 
	brnch= tree.GetBranch("weight");
	valueStruct = Entry();
	brnch.SetAddress(ROOT.AddressOf(valueStruct,'w'));
	entries=tree.GetEntries();
	for iEntry in range(0,entries):
		if PYDEBUG and (iEntry%1000 == 0):
			print >> sys.stderr,"iEntry = " + str(iEntry) + "/" + str(entries)
		tree.GetEntry(iEntry)
		Sw+=valueStruct.w
		nT+=1

print "ScaleFactor="+str(nT/Sw);
print "Sw=" + str(Sw) 
print "nT=" + str(nT)

