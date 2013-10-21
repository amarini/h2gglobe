#!/usr/bin/python
import os,sys,array
from optparse import OptionParser
import re

def print_line_except_word(parts,N,f):
	for i in range(0,len(parts)):
		if i!=N:
			if "\n" in parts[i]:
				f.write(parts[i])
			else:
				f.write(parts[i]+" ")


##PARSE OPTIONS
usage = "usage: %prog [options] arg1 arg2"
parser = OptionParser(usage=usage)
parser.add_option("-f","--fileName"  ,dest='fileName' ,type='string',help="fileName",default="hgg.txt")
parser.add_option("-c","--catName"  ,dest='catName' ,type='string',help="cat Name",default="cat0")
parser.add_option("-p","--procName"  ,dest='procName' ,type='string',help="process Name",default="ggH")
parser.add_option("-o","--outName"  ,dest='outName' ,type='string',help="cat Name",default="stdout")

(options,args)=parser.parse_args()
##
try:
	f=open(options.fileName,"r")
except IOError:
	print >>sys.stderr, "File "+options.fileName+" does not exists"


lines= f.readlines()

bincount=0
proccount=0
binline=""
procline=""

for ll in lines:
	l2=re.sub(' +',' ',ll)
	parts=l2.split(' ')
	if parts[0] == "bin":
		bincount+=1
		if bincount == 2:
			binline=l2
	if parts[0] == "process":
		proccount+=1
		if proccount == 1:
			procline=l2
# I got binline and procline stripped of extra white spaces
#search for catName and typeName
binparts=binline.split(' ')
procparts=procline.split(' ')

if len(binparts) != len(procparts):
	print >>sys.stderr, "bin and proc does not have the same number of words"
	exit
N=-1
for i in range(0,len(binparts)):
	if binparts[i]==options.catName and procparts[i]==options.procName:
		N=i
if N<0:
	print >>sys.stderr, "Not found cat "+options.catName+" and proc "+options.procName
	print >>sys.stderr, "--> Bin  Line: \""+binline +"\" BinCount="+str(bincount)
	print >>sys.stderr, "--> Proc Line: \""+procline+"\" ProcCount=\""+str(proccount)
	exit	


bincount=0
proccount=0
#Loop again removing unwanted cols and printing
try:
	if options.outName=="stdout":
		out=open("/dev/stdout","w")
	else:
		out=open(options.outName,"w")
except IOERROR:
	print "file "+options.outName+" error"
	exit

for ll in lines:
	l2=re.sub(' +',' ',ll)
	parts=l2.split(' ')
	if parts[0]=="bin":
		bincount+=1
		if bincount==2:
			print_line_except_word(parts,N,out)
		else :
			print_line_except_word(parts,-1,out)
	elif "process" == parts[0]:
		print_line_except_word(parts,N,out)
	elif "rate" == parts[0]:
		print_line_except_word(parts,N,out)
	elif "QCDscale" in parts[0]:
		print_line_except_word(parts,N+1,out)
	elif "pdf" in parts[0]:
		print_line_except_word(parts,N+1,out)
	elif "lumi" in parts[0]:
		print_line_except_word(parts,N+1,out)
	elif "E_" in parts[0]:
		print_line_except_word(parts,N+1,out)
	elif "Eff" in parts[0]:
		print_line_except_word(parts,N+1,out)
	elif "phoIdMva" == parts[0]:
		print_line_except_word(parts,N+1,out)
	elif "regSig" == parts[0]:
		print_line_except_word(parts,N+1,out)
	#general case print all
	else:
		print_line_except_word(parts,-1,out)
			


