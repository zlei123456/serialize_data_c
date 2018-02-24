# mysetup.py 
#setup(console=["createClass.py"]) 


from distutils.core import setup
import py2exe
import sys

pyName = "readValue"

options = {"py2exe":   { "bundle_files": 1, "dist_dir":"../exeFile" }  
                } 
setup(options = options,
	  zipfile=None, 
	  console = [{"script":pyName+".py"}])