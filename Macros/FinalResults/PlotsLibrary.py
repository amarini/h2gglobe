#!/usr/bin/python
import os,sys
import array
from glob import glob
from subprocess import call
from optparse import OptionParser

##### CONFIGURATION ######
colors_=[632,416,600,800,432,400+2,416+2,632+2,58]
##########################


print "Importing ROOT"
sys.argv=[]
import ROOT
ROOT.gROOT.SetBatch()

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

#from makeCombinePlots import cleanSpikes1D
def cleanSpikes1D(rfix):

 # cindex is where deltaNLL = 0 (pre anything)
 MAXDER = 1.0
 for i,r in enumerate(rfix):
   if abs(r[1]) <0.001: cindex = i

 lhs = rfix[0:cindex]; lhs.reverse()
 rhs= rfix[cindex:-1]
 keeplhs = []
 keeprhs = []

 for i,lr in enumerate(lhs): 
   if i==0: 
   	prev = lr[1]
	idiff = 1
   if abs(lr[1]-prev) > MAXDER :
   	idiff+=1
   	continue 
   keeplhs.append(lr)
   prev = lr[1]
   idiff=1
 keeplhs.reverse()

 for i,rr in enumerate(rhs):
   if i==0: 
   	prev = rr[1]
	idiff = 1
   if abs(rr[1]-prev) > MAXDER : 
   	idiff+=1
   	continue 
   keeprhs.append(rr)
   prev = rr[1]
   idiff=1
 
 rfix = keeplhs+keeprhs
 
 rkeep = []
 #now try to remove small jagged spikes
 for i,r in enumerate(rfix):
   if i==0 or i==len(rfix)-1: 
   	rkeep.append(r)
   	continue
   tres = [rfix[i-1][1],r[1],rfix[i+1][1]]
   mean = float(sum(tres))/3.
   mdiff = abs(max(tres)-min(tres))
   if abs(tres[1] - mean) > 0.6*mdiff :continue
   rkeep.append(r)
 return rkeep

#from makeCombinePlots Palette
def set_palette(ncontours=999,style=4):
    ''' Set Palette to a specific style:
	ncontours = number of gradient points
	style:
	\t 1) default palette
	\t 2) blue palette
	\t 3) 
	\t 4) Hgg
    '''
    if (style==1):
     # default palette, looks cool
     stops = [0.00, 0.34, 0.61, 0.84, 1.00]
     red   = [0.00, 0.00, 0.77, 0.85, 0.90]
     green = [0.00, 0.81, 1.00, 0.20, 0.00]
     blue  = [0.51, 1.00, 0.12, 0.00, 0.00]

    elif (style==3):
     
     red   = [ 0.00, 0.90, 1.00] 
     blue  = [ 1.00, 0.50, 0.00] 
     green = [ 0.00, 0.00, 0.00] 
     stops = [ 0.00, 0.50, 1.00] 

    elif (style==2):
     # blue palette, looks cool
     stops = [0.00, 0.14, 0.34, 0.61, 0.84, 1.00]
     red   = [0.00, 0.00, 0.00, 0.05, 0.30, 1.00]
     green = [0.00, 0.00, 0.00, 0.00, 0.00, 0.00]
     blue  = [1.00, 0.80, 0.6, 0.4, 0.2, 0.0]

    elif (style==4):
     stops = [0.00, 1.00]
     red   = [1.00, 48./255.]
     green = [1.00, 48./255.]
     blue  = [1.00, 131./255.]
    ###############
    st = array.array('d', stops)
    re = array.array('d', red)
    gr = array.array('d', green)
    bl = array.array('d', blue)

    npoints = len(st)
    ROOT.TColor.CreateGradientColorTable(npoints, st, re, gr, bl, ncontours)
    ROOT.gStyle.SetNumberContours(ncontours)

def findPath():
	#figure out globe name
	globe_name = "h2gglobe"
	mypath = os.path.abspath(os.getcwd())
	while mypath != "":
	    if "h2gglobe" in os.path.basename(mypath):
	        globe_name = os.path.basename(mypath)
	        break
	    mypath = os.path.dirname(mypath)
	return (mypath,globe_name)

def getDet(x=[],y=[],z=[]):
	'''Return determinant of
	 | x[0] y[0] z[0] |
	 | x[1] y[1] z[1] |
	 | x[2] y[2] z[2] |
	'''
	return x[0]*y[1]*z[2] + y[0]*z[1]*x[2] + z[0]*x[1]*y[2] - x[2]*y[1]*z[0] - y[2]*z[1]*x[0] -z[2]*x[1]*y[0] 

import math
def getInterpolation(x=[1,2,3],y=[1,2,3],type='min',value=0.5):
	'''type=min, value'''
	type=type.lower()
	# y= a x**2 + b x + c
	## Cramer
	##  a11 a12 a13 
	##  a21 a22 a23
	##  a31 a32 a33
	Unity=[1,1,1]

	epsilon=0.001
	if abs(x[0]-x[1])<epsilon or abs(x[0]-x[2])<epsilon or abs(x[1]-x[2])<epsilon: 
		print "Interpolation: two x are closer than",epsilon
		raise "Degenerate Error"
	xSquare=[ xx*xx for xx in x ] 

	# | x 1 y | / | x**2 + x + 1 |
	a=  getDet(y,x,Unity)       / getDet(xSquare,x,Unity)
	b=  getDet(xSquare,y,Unity) / getDet(xSquare,x,Unity)
	c=  getDet(xSquare,x,y)     / getDet(xSquare,x,Unity)
	#print "--------------------"
	#print "(",x[0],",",y[0],")"
	#print "(",x[1],",",y[1],")"
	#print "(",x[2],",",y[2],")"
	#print "a=",a
	#print "b=",b
	#print "c=",c
	#print "val=",value
	#print "--------------------"
	
	if type=='min':
		xmin=-b/(2.*a)
		return [ -b/(2.*a), a*(xmin**2)+b*xmin + c ]
	elif type=='val' or type=='value':
		return [ ( -b - math.sqrt(b**2 - 4*a*(c-value) ) ) / (2*a) ,
		  	 ( -b + math.sqrt(b**2 - 4*a*(c-value) ) ) / (2*a) ]
	else: return -9999.



def getMu(nBins=6,dir="jobs",File="UnfoldScanExp",sigma=1,Interpolate=False,mh=-1):
	''' Get Mu for Differential. Mh is considered for mh scans only if >0'''
	Mu=[]
	Graphs=[] ## keep them otherwise destroyed too soon
	print "Going to Scan Bins"
	for iBin in range(0,nBins):
		if mh> 0:
			mhStr=("%.2f"%mh).replace('.','_')
			print "Going to open","%s/%sBin%d_mh%s/%sBin%d_mh%s.root"%(dir,File,iBin,mhStr,File,iBin,mhStr)
			f=ROOT.TFile.Open("%s/%sBin%d_mh%s/%sBin%d_mh%s.root"%(dir,File,iBin,mhStr,File,iBin,mhStr))
		else:
			print "Going to open","%s/%sBin%d/%sBin%d.root"%(dir,File,iBin,File,iBin)
			f=ROOT.TFile.Open("%s/%sBin%d/%sBin%d.root"%(dir,File,iBin,File,iBin))
		t=f.Get("limit")
		A=ROOT.entry()
		t.SetBranchAddress("r_Bin%d"%iBin,ROOT.AddressOf(A,'var'))
		t.SetBranchAddress("deltaNLL",ROOT.AddressOf(A,"nll"))
		
		values=[]
		valuesForErrors=[]
		for iEntry in range(0,t.GetEntries()):
			t.GetEntry(iEntry)
			values.append( (A.var,A.nll) )
		values.sort()
		values=cleanSpikes1D(values)
		#Get Minimum and errors
		(x,y)=values[0] #var,nll
		for (x1,y1) in values:
			if y1<y: (x,y)=(x1,y1)

		valuesForErrors=[ x1 for (x1,y1) in values if y1<y+0.5*(sigma**2) ] 

		try:
			e1= min(valuesForErrors)
			e2= max(valuesForErrors)
		except ValueError: e1=e2=-1

		if Interpolate:	
			#remove duplicates
			values=list(set(values))
			values.sort()
			##get minimum
			(xmin,ymin) =values[0]
			for i in range(0, len(values) ):
				(xi,yi)=values[i]
				if yi<ymin:
					ymin=yi
					#assuming i-1,i+1 exists, and sorted otherwise far from min
					try:
					   xI=(values[i][0],values[i-1][0],values[i+1][0])
					   yI=(values[i][1],values[i-1][1],values[i+1][1])
					except:
					   print "i-1 or i+1 does not exist"
					   xI=None # this will raise an exception in interpolation
					   yI=None
					#print "i=",i,"xI=",xI,"yI=",yI
			#print "Min: xI=",xI ##DEBUG
			#print "Min: yI=",yI ##DEBUG
			#print "--- min ---"
			try:
				(x,y)=getInterpolation(xI,yI,'min')
			except:
				print "MINIMUM INTERP ERR: Switching off interpolation",xI,yI
				return getMu(nBins,dir,File,sigma,Interpolate=False)

			#1 -> if i_min>1 use the  -1 i +1, otherwise use the first three
			e1=values[0][0]
			e2=values[-1][0]

			Ifailed=False
			for i in reversed(range(1, len(values)-1 ) ):
				(xi,yi)=values[i]
				if yi < y + 0.5*sigma**2:
					xI=(values[i][0],values[i-1][0],values[i+1][0])
					yI=(values[i][1],values[i-1][1],values[i+1][1])
					try:
					   #print "--- e1 ---"
					   e1=getInterpolation(xI,yI,'val',y+ 0.5*sigma**2)[0]
					   Ifailed=False
					except:
					   Ifailed=True
			#print "E1: xI=",xI ##DEBUG
			#print "E1: yI=",yI ##DEBUG
			if Ifailed:
				print "->Interpolation failed"
			Ifailed=False
			for i in range(1, len(values)-1 ) :
				(xi,yi)=values[i]
				if yi < y + 0.5*sigma**2:
					xI=(values[i][0],values[i-1][0],values[i+1][0])
					yI=(values[i][1],values[i-1][1],values[i+1][1])
					try:
					   #print "--- e2 ---"
					   e2=getInterpolation(xI,yI,'val',y+ 0.5*sigma**2)[1]
					   Ifailed=False
					except:
					   Ifailed=True
			#print "E2: xI=",xI ##DEBUG
			#print "E2: yI=",yI ##DEBUG

			if Ifailed:
				print "->Interpolation failed"
				return getMu(nBins,dir,File,sigma,Interpolate=False)

		#print "I -> (",x,",",y," - ",e1,",",e2,")" ##DEBUG
		
		#######
		Mu.append( (x,e1,e2) )
		#######
	
		g=ROOT.TGraph()
		g.SetName("Bin%d"%iBin)
		g.SetLineColor(colors_[iBin])
		g.SetFillColor(ROOT.kWhite)
		g.SetLineWidth(2)
		for (x1,y1) in values:
			g.SetPoint(g.GetN(),x1,y1)
		Graphs.append(g)
	
		f.Close()

	return (Mu,Graphs)


def DrawNLL(dir="jobs",nBins=6,File="UnfoldScanExp"):
	C=ROOT.TCanvas("c","c")
	L=ROOT.TLegend(.65,.65,.89,.89)
	(Mu,Graphs) = getMu(nBins,dir,File)
	for iG in range(0,len(Graphs)):
		g=Graphs[iG]
		if(iG==0): 
			g.Draw("AL")	
			g.GetYaxis().SetTitle("#Delta NNL");
			g.GetXaxis().SetTitle("#mu");
			g.GetYaxis().SetRangeUser(0,5)
		else: g.Draw("L SAME")
		L.AddEntry(g,"Bin%d"%iG,"F")
	
	L.Draw()
	line=ROOT.TGraph()
	line.SetName("1sigma")
	line.SetPoint(0,-10,0.5)
	line.SetPoint(1,10,0.5)
	line.Draw("L SAME")
	line2=ROOT.TGraph()
	line2.SetName("2sigma")
	line2.SetPoint(0,-10,2)
	line2.SetPoint(1,10,2)
	line2.Draw("L SAME")

	#vertical lines
	obj=[]
	for iBin in range(0,nBins):
		l_e0=ROOT.TGraph()
		l_e0.SetName("e0_Bin%d"%iBin)
		l_e0.SetPoint(0,Mu[iBin][0],0)
		l_e0.SetPoint(1,Mu[iBin][0],2)

		l_e1=ROOT.TGraph()
		l_e1.SetName("e1_Bin%d"%iBin)
		l_e1.SetPoint(0,Mu[iBin][1],0)
		l_e1.SetPoint(1,Mu[iBin][1],2)

		l_e2=ROOT.TGraph()
		l_e2.SetName("e2_Bin%d"%iBin)
		l_e2.SetPoint(0,Mu[iBin][2],0)
		l_e2.SetPoint(1,Mu[iBin][2],2)

		l_e0.SetLineColor(Graphs[iBin].GetLineColor())
		l_e1.SetLineColor(Graphs[iBin].GetLineColor())
		l_e2.SetLineColor(Graphs[iBin].GetLineColor())

		l_e0.Draw("L SAME")
		l_e1.Draw("L SAME")
		l_e2.Draw("L SAME")
		obj.extend([l_e0,l_e1,l_e2])

	extraString=""
	if not 'Unfold' in File:
		extraString+="reco"
	if 'Stat' in File:
		extraString+="_Stat"
	C.SaveAs("plots_nll"+extraString+"_"+dir.replace("/","")+".pdf")
	C.SaveAs("plots_nll"+extraString+"_"+dir.replace("/","")+".root")
	C.SaveAs("plots_nll"+extraString+"_"+dir.replace("/","")+".png")

def GetXsecSplines():
	#load LoopAll -> Normalization
	(mypath,globe_name)=findPath()

	try:
		l=ROOT.LoopAll()
	except:
		print "Loading Globe: ",mypath+"/"+"/"+"libLoopAll.so"
		ROOT.gSystem.Load(mypath+"/"+"libLoopAll.so")
	
	#didn't found a more elegant way
	ROOT.gROOT.ProcessLine("struct array { \
			double val[1023]; } ; ")
	
	sqrts_=8
	norm = ROOT.Normalization_8TeV();
	norm.Init(sqrts_);
	brGraph = norm.GetBrGraph(); # TGraph
	brSpline=ROOT.TSpline3("brSpline",brGraph)
	
	procs = [ "ggh","vbf","wh","zh","tth" ]
	xsGraphs = {}
	for proc in procs:
		xsGraph = norm.GetSigmaGraph(proc);
		xsGraphs[proc]=xsGraph
	
	xsGraphs["tot"] = xsGraphs["ggh"].Clone("tot")
	for proc in procs:
		if proc=="ggh": continue # it is cloned in the initialization
	        nPoints=xsGraphs["tot"].GetN()
	        for iP in range(0,nPoints):
			x=ROOT.array()
			y=ROOT.array()
			xsGraphs["tot"].GetPoint(iP,x.val,y.val);
			y.val[0]+=xsGraphs[proc].Eval(x.val[0]);
			xsGraphs["tot"].SetPoint(iP,x.val[0],y.val[0]);
	
	xsSpline=ROOT.TSpline3("xsSpline",xsGraphs["tot"])
	return (xsGraphs,xsSpline,brGraph,brSpline)

def GetXsec(ws,mh,nBins,Lumi,extra=""):
	(xsGraphs,xsSpline,brGraph,brSpline) = GetXsecSplines()
	nEvents={}
	Xsec=[]
	masses=[120,125,130]
	for iBin in range(0,nBins):
	   eaGraph=ROOT.TGraph()
	   eaGraph.SetName("effAcc")
	   for m in masses:
		nEvents[ (m,iBin)]= ws.data("sig_gen_Bin%d%s_mass_m%d_cat0"%(iBin,extra,m)).sumEntries();
		xSec=xsGraphs["tot"].Eval(m,xsSpline) *1000.  #pb->fb 
		br=brGraph.Eval(m,brSpline)
		effAcc= ( nEvents[ (m,iBin)]/ ( Lumi* xSec * br )  );
		eaGraph.SetPoint(eaGraph.GetN(), m , effAcc)
	   eaSpline=ROOT.TSpline3("eaSpline",eaGraph)

	   Xsec.append( xsGraphs["tot"].Eval(mh,xsSpline)*1000. * brGraph.Eval(mh,brSpline) * eaGraph.Eval(mh,eaSpline))
	return Xsec

# -----------------------------------------------------------------------------------------------------------

#sys.path.insert(0,os.getcwd())
# Pasquale's Macros
mypath = os.path.dirname(__file__)
sys.path.insert(0, mypath + '/hgg_legacy_plots/macros/')

from  adjustStyle import makeContours,loadRootStyle,getAllPrims
# -----------------------------------------------------------------------------------------------------------

def CMS(canv,hist=None):
  ''' Write CMS and set a bit of style'''
  canv.SetLeftMargin(.1)  
  canv.SetRightMargin(.15)  
  canv.SetBottomMargin(.15)  
  canv.SetTopMargin(.1)  
  ## write CMS
  latex=ROOT.TLatex()
  latex.SetNDC()
  latex.SetTextFont(43)
  latex.SetTextSize(34)
  latex.SetTextAlign(13)
  latex.SetTextColor(ROOT.kBlack)
  latex.DrawLatex(.12,.88,"#bf{CMS}")

  latex.SetTextColor(ROOT.kBlack)
  latex.SetTextSize(24)
  latex.SetTextAlign(31)
  latex.DrawLatex(0.90,.91,"19.7 fb^{-1} (8 TeV)")
  ##
  if hist:
  	hist.GetYaxis().SetTitleOffset(1.2)
  	hist.GetXaxis().SetTitleOffset(1.2)
  	hist.GetXaxis().SetNdivisions(504)
  	hist.GetYaxis().SetNdivisions(504)
  #Get Palette
  palette = hist.GetListOfFunctions().FindObject("palette");
  if palette:
  	palette.SetX1NDC(0.9);
  	palette.SetX2NDC(0.95);
  	palette.SetY1NDC(0.2);
  	palette.SetY2NDC(0.8);
  #
  #Tell ROOT that canvas has been modified
  canv.Modified();
  canv.Update();


def plot2DNLL(infile,ws,xvar="MH",yvar="r_Bin0",xtitle="M_{H} [GeV]",ytitle="#sigma [fb]",Lumi=19.7):
  ''' This macro is taken from makeCombinePlots, and implement the xSec mult:
  	ws is the sig ws
  	infile is the combine output
  '''
  
  #from Pasquale
  #loadRootStyle()

  BFgrs		= []
  CONT1grs	= []
  CONT2grs 	= []
  COLgrs	= []
  
  leg = ROOT.TLegend(0.7,0.7,0.88,0.88)
  #else: leg = ROOT.TLegend(float(options.legend.split(',')[0]),float(options.legend.split(',')[1]),float(options.legend.split(',')[2]),float(options.legend.split(',')[3]))
  #leg.SetFillColor(10)

  smmarker = ROOT.TMarker(1,1,33)
  smmarker.SetMarkerColor(97)
  smmarker.SetMarkerSize(2.5)
  smmarker2 = ROOT.TMarker(1,1,33)
  smmarker2.SetMarkerColor(89)
  smmarker2.SetMarkerSize(1.4)
  smmarker_leg = smmarker.Clone("smmarker_leg")
  #smmarker_leg.SetMarkerStyle(27)
  smmarker_leg.SetMarkerSize(2.5)

  addBFtoLeg = False

  mems = []
  th2s = []

  tf = ROOT.TFile(infile)
  mems.append(tf)
  tree = tf.Get('limit')

  ROOT.gROOT.ProcessLine("struct limEntry {\
		  float mh ; \
		  float mu ; \
		  float z; \
		  };" )
  from ROOT import limEntry

  E=ROOT.limEntry()
  #print "Check E:mh ",E.mh
  #print "Check E:mu ",E.mu
  #print "Check E:z ",E.z
  tree.SetBranchAddress( xvar, ROOT.AddressOf(E,"mh") );
  tree.SetBranchAddress( yvar, ROOT.AddressOf(E,"mu") );
  tree.SetBranchAddress( "deltaNLL",ROOT .AddressOf(E,"z") ) ;

  xmin=123.
  xmax=126.5
  ymin=5
  ymax=60

  th2= ROOT.TH2D("xSecVsMH","#sigma vs M_{H}",1000,xmin,xmax,1000,ymin,ymax)
  tg2= ROOT.TGraph2D() ## th2 is too sparse
  tg2_unique_point={}

  th2.GetXaxis().SetTitle(xtitle)
  th2.GetYaxis().SetTitle(ytitle)
  th2.GetZaxis().SetTitle("2#DeltaNLL")

  gBF = ROOT.TGraph()

  mytree={} ## vs mh

  for iEntry in range (0, tree.GetEntries() ) :
  	tree.GetEntry(iEntry)
	if E.z<0 : continue;
	if E.mh not in mytree: mytree[E.mh]=[]
	mytree[E.mh].append( (E.mu,E.z *2)  )   # 2DeltaNLL
	#if iEntry >100: break; ## FAST

  for E.mh in mytree:
    xsBare=GetXsec(ws,E.mh,1,Lumi,extra="")[0] 
    for (E.mu,E.z) in mytree[E.mh]:
	# set best fit
	xs=xsBare*E.mu
	if E.z== 0:
		gBF.SetPoint(0, E.mh,xs);
	# set th2d
	th2bin=th2.FindBin(E.mh,xs)
	#print " BIN ASSIGNMENT:",th2bin," mh=",E.mh,"xs=",xs,"mu=",E.mu
	if th2.GetBinContent(th2bin) > 0 and th2.GetBinError(th2bin) > 0: 
		if abs( th2.GetBinContent(th2bin) - E.z )>0.01  and not (E.mh<xmax or E.mh> xmax) and not (xs<ymin or xs>ymax): 
			print "[WARNING]: content is already set for bin (",E.mh,",",xs,"-",E.mu,") and differs:",th2.GetBinContent(th2bin)," != ", E.z 
		continue

	th2.SetBinContent(th2bin, E.z)
	th2.SetBinError(th2bin, 1)
	#if  (E.mh<xmin or E.mh> xmax) or (xs<ymin or xs>ymax) : continue
	if (E.mh,xs) not in tg2_unique_point:
		tg2_unique_point[ (E.mh,xs) ] = 1
		tg2.SetPoint(tg2.GetN(), E.mh, xs, E.z )

  print "INTERPOLATION",tg2.GetN()
  ## CHECK
  for i in range(0,tg2.GetN() ):
  	print "x=", tg2.GetX()[i] ,"y=",tg2.GetY()[i],"z=",tg2.GetZ()[i]
  print "INTERPOLATE CHECK:",tg2.Interpolate( 124.8, 32.)

  ### BEGIN NICK INTERPOLATION
  ### ROOT.gSystem.Load("libHiggsAnalysisCombinedLimit.so");

  ### roo_mh = ROOT.RooRealVar("mh","mh",0.)
  ### roo_xsec = ROOT.RooRealVar("xsec","xsec",0.)
  ### roo_dnll = ROOT.RooRealVar("dnll","dnll",0.)

  ### ROOT.gROOT.ProcessLine("struct Entry2 {\
  ###       	  double mh ; \
  ###       	  double xsec ; \
  ###       	  double z; \
  ###       	  };" )
  ### from ROOT import Entry2
  ### E=ROOT.Entry2()

  ### treeInt = ROOT.TTree("mytree","mytree")
  ### treeInt.Branch( "mh"  , ROOT.AddressOf(E,"mh") ,"mh/D");
  ### treeInt.Branch( "xsec", ROOT.AddressOf(E,"xsec") ,"xsec/D");
  ### treeInt.Branch( "dnll", ROOT.AddressOf(E,"z") ,"dnll/D") ;

  ### for i in range(0,tg2.GetN() ) :
  ###       E.mh=tg2.GetX()[i] 
  ###       E.mu=tg2.GetY()[i]
  ###       E.z =tg2.GetZ()[i]
  ###       treeInt.Fill();

  ### interpolator = ROOT.RooSplineND( "interpolator", "interpolator", ROOT.RooArgList(roo_mh,roo_xsec), treeInt , "dnll",0.2 )
  ### for xBin in range(0,th2.GetXaxis().GetNbins() ):
  ###   for yBin in range(0,th2.GetYaxis().GetNbins() ):
  ###           roo_mh.setVal(th2.GetXaxis().GetBinCenter(xBin+1) )
  ###           roo_xsec.setVal(th2.GetYaxis().GetBinCenter(yBin+1) )
  ###           th2.SetBinContent(xBin+1,yBin+1,  interpolator.getVal()  ) ;

  ########### OLD INTERP
  for xBin in range(0,th2.GetXaxis().GetNbins() ):
    for yBin in range(0,th2.GetYaxis().GetNbins() ):
            x=th2.GetXaxis().GetBinCenter(xBin+1) 
            y=th2.GetYaxis().GetBinCenter(yBin+1) 
            th2.SetBinContent(xBin+1,yBin+1,  tg2.Interpolate( x,y) ) ;
  print
  ########### OLD INTERP END

  #cont_1sig.SetContour(2)
  #cont_1sig.SetContourLevel(1,2.3)
  #cont_1sig.SetLineColor( ROOT.kBlack)
  #cont_1sig.SetLineWidth(3)
  #cont_1sig.SetLineStyle(1)

  #cont_2sig = th2.Clone('cont_2_sig')
  #cont_2sig.SetContour(2)
  #cont_2sig.SetContourLevel(1,6.18)
  #cont_2sig.SetLineColor( ROOT.kBlack)
  #cont_2sig.SetLineWidth(3)
  #cont_2sig.SetLineStyle(2)

  set_palette(ncontours=255);

  gBF.SetMarkerStyle(34)
  gBF.SetMarkerSize(1.8)
  gBF.SetMarkerColor(ROOT.kBlack)
  gBF.SetLineColor( ROOT.kBlack)

  ROOT.gStyle.SetOptStat(0)
  ROOT.gStyle.SetOptTitle(0)


  #cont_1sig.Draw("cont3,list same")
  
  ## NICE CONTOURS -----------------------
  tmp=ROOT.TCanvas()
  cont_1sig = th2.Clone('cont_1_sig')
  cont_1sig.SetContour(2, array.array( 'd', [2.3,6.18 ]) )
  cont_1sig.Draw("cont,list")
  tmp.Update()
  ROOT.gROOT.GetListOfSpecials().Print()
  contours = ROOT.gROOT.GetListOfSpecials().FindObject("contours")
  ###   contours is  a TList of contours
  print "COUNTOURS=",contours
  clones=[]
  for ic in range(0,2):
        cnts= contours.At(ic)
	print "cnts[",ic,"]",cnts
  	for idx,c in enumerate(cnts):
		print "c=",c
  		if ic==0: 
			c.SetLineStyle(1)
			c.SetLineWidth(2)
  		if ic==1: 
			c.SetLineStyle(7)
			c.SetLineWidth(2)
		if ic>1: continue;
        	clone= c.Clone("ic_%d_idx_%d"%(ic,idx))
        	clones.append(clone)
        	#canv.GetListOfPrimitives().Add(clone)
  cont_1sig.Delete()
  ROOT.gROOT.GetListOfSpecials().Delete()
  ## END CONTOURS ---------------------
  ### DRAW ######
  canv = ROOT.TCanvas("%s_%s"%(xvar,yvar),"%s_%s"%(xvar,yvar),750,750)
  canv.cd()
  th2.Draw("colz")
  th2.GetXaxis().SetRangeUser(123.,125.7)
  th2.GetYaxis().SetRangeUser(0,60-0.001)

  gBF_underlay = gBF.Clone()
  gBF_underlay.SetMarkerColor(ROOT.kRed)
  gBF_underlay.SetMarkerSize(2.6)
  gBF_underlay.Draw("P same")
  gBF.Draw("P same")

  for c in clones : 
	  print "Drawing", c.GetName()
	  c.Draw("LSAME")

  CMS(canv,th2)

  canv.Print("xSecVsMH_col.pdf")
  canv.Print("xSecVsMH_col.png")
  canv.Print("xSecVsMH_col.root")
