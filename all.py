import os

os.chdir("createData")
execfile('readValue.py')
os.chdir("../createClass")
execfile('createClass.py')
raw_input("raw_input: ")
