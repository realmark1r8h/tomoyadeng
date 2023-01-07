#encoding=utf-8
# -*- coding: UTF-8 -*-

import sys
import re
import os
import fnmatch
import os.path
from optparse import OptionParser
import posixpath
import string
import time


reload(sys)
sys.setdefaultencoding('utf8') # 允许中文字符串
 
 

ConfigType= "Debug"
lenght = len(sys.argv)
if lenght > 1:
    if sys.argv[1] == "r" or sys.argv[1] == "release" or sys.argv[1] == "Release":
        ConfigType = "Release"

def IsValidFile(file, ext):
	if ext == ".*":
		return True
	elif file.endswith(ext):
		return True
	else:
		return False

def CopyTo(srcFile, dstFile):
	print("CopyTo: ")
	print("src: " +  srcFile)
	print("dst: " + dstFile)
	dstPath= os.path.dirname( dstFile) 
	if os.path.exists(dstPath) == False:
		os.makedirs(dstPath)  
	os.system ("copy %s %s" % (srcFile, dstFile))
	
def transfer(srcDir, dstDir,  ext, currentDir = ""):  
  if currentDir == "":
	currentDir = srcDir
  print("current: " + os.path.abspath(currentDir)) 
  for file in os.listdir( currentDir): 
	path = os.path.join( currentDir,file)
	if os.path.isdir(path) == False: 
		if IsValidFile(file, ext): 
			dstFile = path.replace(srcDir, dstDir)
			srcFile = os.path.abspath(path)
			dstFile = os.path.abspath(dstFile)
			CopyTo(srcFile, dstFile) 
	else: 
		dstSubDir = path.replace(srcDir, dstDir)
		dstSubDir = os.path.abspath(dstSubDir ) 
		transfer(srcDir, dstDir, ext, path)
		
 
nodePath = "../NCUI-Library/node/"
cefPath = "../NCUI-Library/cef/"
srcPath = "./"
		 
dstDir = "../NCUI-Out/Binary.UR32/"
if  ConfigType == "Debug":
	dstDir = "../NCUI-Out/Binary.UD32/"
	
transfer(cefPath  + ConfigType , dstDir, '.dll')
transfer(cefPath  + ConfigType , dstDir, '.bin')
transfer(cefPath  + "Resources", dstDir, '.*')
transfer(nodePath +  ConfigType , dstDir, '.dll')
transfer(nodePath +  ConfigType , dstDir, '.exe')
transfer(srcPath + "resources", dstDir, '.*')