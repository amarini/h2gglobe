#!env python

import sys,os
import array
import ROOT
import time
import math

import decimal

def float_to_decimal(f):
    # http://docs.python.org/library/decimal.html#decimal-faq
    "Convert a floating point number to a Decimal with no loss of information"
    n, d = f.as_integer_ratio()
    numerator, denominator = decimal.Decimal(n), decimal.Decimal(d)
    ctx = decimal.Context(prec=60)
    result = ctx.divide(numerator, denominator)
    while ctx.flags[decimal.Inexact]:
        ctx.flags[decimal.Inexact] = False
        ctx.prec *= 2
        result = ctx.divide(numerator, denominator)
    return result 

def float_to_string(number, sigfig):
    '''This function should convert a number to a string according to the significat digit precision requested'''
    # http://stackoverflow.com/questions/2663612/nicely-representing-a-floating-point-number-in-python/2663623#2663623
    assert(sigfig>0)
    try:
        d=decimal.Decimal(number)
    except TypeError:
        d=float_to_decimal(float(number))
    sign,digits,exponent=d.as_tuple()
    if len(digits) < sigfig:
        digits = list(digits)
        digits.extend([0] * (sigfig - len(digits)))    
    shift=d.adjusted()
    result=int(''.join(map(str,digits[:sigfig])))
    # Round the result
    if len(digits)>sigfig and digits[sigfig]>=5: result+=1
    result=list(str(result))
    # Rounding can change the length of result
    # If so, adjust shift
    shift+=len(result)-sigfig
    # reset len of result to sigfig
    result=result[:sigfig]
    if shift >= sigfig-1:
        # Tack more zeros on the end
        result+=['0']*(shift-sigfig+1)
    elif 0<=shift:
        # Place the decimal point in between digits
        result.insert(shift+1,'.')
    else:
        # Tack zeros on the front
        assert(shift<0)
        result=['0.']+['0']*(-shift-1)+result
    if sign:
        result.insert(0,'-')
    return ''.join(result)

from optparse import OptionParser
usage = "usage: %prog [options] arg1 arg2"
parser=OptionParser(usage=usage)
parser.add_option("-i","--inputFile" ,dest='inputFile',type='string',help="Input file",default="xSec_%(var)s.root")
parser.add_option("-o","--outputFile" ,dest='outputFile',type='string',help="Output file",default="")
parser.add_option("-a","--all" ,dest='all',action='store_true',help="Do all variables. Default naming",default=False)
parser.add_option("-x","--binbybin" ,dest='BbB',action='store_true',help="Print bin-by-bin",default=False)
(opts,args)=parser.parse_args()

allvars=['Fiducial','pToMscaled','CosThetaStar','Ygg','dPhi','Njets',
	'LeadJetpT','dRapidityHiggsJet',
	'dPhiggjjExtended','dEtajjExtended','dPhijjExtended','MjjExtended','ZeppExtended']
#  KEY: TH1F	data;1	Data
#  KEY: TH1F	Expected;1	Expected
#  KEY: TH1F	error;1	Error
#  KEY: TH1F	BbBerror;1	Error BbB
#  KEY: TH1F	BbB;1	BbB
#  KEY: TH1F	HExp_ggh;1	HExpected ggh
#  KEY: TH1F	HExp_vbf;1	HExpected vbf
#  KEY: TH1F	HExp_wh;1	HExpected wh
#  KEY: TH1F	HExp_zh;1	HExpected zh
#  KEY: TH1F	HExp_tth;1	HExpected tth
#  KEY: TNamed	mh;1	124.374
#  KEY: TNamed	all_mh_over_125_bin0;1	1.008955
#  KEY: TNamed	ggh_mh_over_125_bin0;1	1.008888
#  KEY: TNamed	vbf_mh_over_125_bin0;1	1.005115
#  KEY: TNamed	wh_mh_over_125_bin0;1	1.015864
#  KEY: TNamed	zh_mh_over_125_bin0;1	1.016053
#  KEY: TNamed	tth_mh_over_125_bin0;1	1.014860

#construct list of input
fileList=[opts.inputFile]
if opts.all:
	fileList=[opts.inputFile % { "var": x} for x in allvars ] 

#open outputfile
out = open(opts.outputFile,'w')

for idx,file in enumerate(fileList):
	fRoot=ROOT.TFile.Open(file)	
	if fRoot == None:
		print 'Error: File',file,'does not exist: ignore'
	else:
		print 'Doing file',file
	data = fRoot.Get('data')
	err  = fRoot.Get('error')
	exp  = fRoot.Get('Expected')
	
	BbB  = fRoot.Get('BbB')
	BbBerr = fRoot.Get('BbBerror')
	
	mh   = fRoot.Get('mh')
	
	### Print informations	
	nBins = data.GetNbinsX()

	print >> out, "\\begin{table}[bp]"
	print >> out, "\\centering"
	#
	print >> out, "\\begin{tabular}{ccc",
	if opts.BbB: print >>out, "c",
	print >> out, "}"
	#
	print >> out, "\\toprule"
	#
	print >> out, "\\textbf{Bin} & \\textbf{$\\sigma$} &" ,
	if opts.BbB: print >>out, "\\textbf{bin-by-bin} & ",
	print >> out, "{\\scshape Powheg}  \\\\"
	#
	print >> out, "\\midrule"
	for iBin in range(0,nBins): ## should be offset by 1
		#print >> out, " $%3f$--$%3f$ & "%(data.GetBinLowEdge(iBin+1),data.GetBinLowEdge(iBin+2)), ## boundaries
		print >> out, " $"+ \
				float_to_string(data.GetBinLowEdge(iBin+1),3)+ \
				"$--$"+ \
				float_to_string(data.GetBinLowEdge(iBin+2),3) + \
				"$ & ", ## boundaries
		### DATA ###
		sigma=data.GetBinContent(iBin+1)*data.GetBinWidth(iBin+1)
		up=(err.GetBinContent(iBin+1)+ err.GetBinError(iBin+1))*err.GetBinWidth(iBin+1)
		dn=(err.GetBinContent(iBin+1)- err.GetBinError(iBin+1))*err.GetBinWidth(iBin+1)
		print >> out, " $%.1f^{+%.1f}_{-%.1f}$ & " % ( sigma, up-sigma, sigma-dn ),
		### BbB ###
		if opts.BbB:
			sigma=BbB.GetBinContent(iBin+1)*BbB.GetBinWidth(iBin+1)
			up=(BbBerr.GetBinContent(iBin+1)+ BbBerr.GetBinError(iBin+1))*BbBerr.GetBinWidth(iBin+1)
			dn=(BbBerr.GetBinContent(iBin+1)- BbBerr.GetBinError(iBin+1))*BbBerr.GetBinWidth(iBin+1)
			print >> out, " $%.1f^{+%.1f}_{-%.1f}$ & " % ( sigma, up-sigma, sigma-dn ),
		### EXP ###
		expSigma=exp.GetBinContent(iBin+1)*exp.GetBinWidth(iBin+1)
		print >> out, " $%.1f$" % (expSigma),
		### ENDL ###
		print >> out, "\\\\"
	print >> out, "\\bottomrule"
	print >> out, "\\end{tabular}"
	print >> out, "\\caption{Differential cross section for",
	if opts.all:
		print >>out, allvars[idx] + '.',
	else: 
		print >>out, opts.inputFile + '.',
	print >> out, "The best fit mass is $",mh.GetTitle() + "\,\\textup{GeV}$.",
	print >> out, "}"
	print >> out, "\\label{tab:",
	if opts.all:
		print >>out, allvars[idx] ,
	else:
		print >>out, opts.inputFile,
	print >> out, "}"
	print >> out, "\\end{table}"
	if opts.all:
		print >>out,"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"
