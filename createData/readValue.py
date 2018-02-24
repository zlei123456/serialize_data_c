# coding: utf-8

import os, json
import xlrd
from sys import exit, argv
import string
#from string import Template
import ctypes
from ctypes import *

fileConfigMain = "../configMain.json"
preFileName = "ZL" 
EXCEL_FILE_NAME = "../test.xlsx"
MODELH_FILE_NAME = "test.h"
row_startNum = 2
col_valueName = 1
col_valueType = 2
col_valueStart = 9

 
ll = ctypes.cdll.LoadLibrary 
lib = ll("./writeData.so")


global configDataMain
def loadConfigMain():
    global configDataMain
    
    readFile = open(fileConfigMain, "r")
    buf = readFile.read()
    readFile.close()

    print buf
    pData = json.loads(buf)
    configDataMain = pData
    #print pData["readBaseCon"]
    
def readValue(path):
    
    valueStr = ""
    readValueStr = ""
    workbook = xlrd.open_workbook(path)
   
    sheet_num = len(workbook.sheets())
    for sheet in xrange(0, sheet_num):        
        oneSheet = workbook.sheets()[sheet]
        print "sheet name = "+oneSheet.name
        fileName = oneSheet.name
        #总列号
        rowNum = oneSheet.nrows
        #总行号
        colNum = oneSheet.ncols
        if(colNum<col_valueType):
            continue;
        #rowValueName = oneSheet.row(col_valueName)
        rowValueType = oneSheet.row(col_valueType)

        for i in xrange(col_valueStart, rowNum):            
            rowValue = oneSheet.row(i)
            lib.pClassBegin(str(fileName))
            for j in xrange(row_startNum, colNum):
                #type
                vType = rowValueType[j].value
                #value
                vValue = rowValue[j].value
                cType = oneSheet.cell_type(i,j)
                cValue = oneSheet.cell_value(i,j)                

                print "sheet = ",fileName,"row=",j,"vtype=",vType,"vValue=",vValue
                if vType.find("map")!=-1:
                    pr = lib.pWriteMapData(str(vType), str(vValue))
                    #print "map code ="+vValue+"vtype="+vType
                    #print str(pr)
                elif vType.find("vector")!=-1:
                    #print "vector code ="+vValue+"vtype="+vType
                    lib.pWriteVectorData(str(vType), str(vValue))                    
                    #lib.
                elif vType.lower()=="int":
                    lib.pWriteIntData(int(vValue))
                elif vType.lower()=="short":                    
                    lib.pWriteShortData(int(vValue))
                elif vType.lower()=="bool":
                    lib.pWriteBoolData(int(vValue))
                elif vType.lower()=="float":
                    print type(vValue)
                    lib.pWriteFloatData(c_float(vValue))
                elif vType.lower()=="string":
                    #print "string:",type(vValue)
                    if(type(vValue)==float):
                        if(vValue==int(vValue)):                            
                            val = int(vValue)
                            #print "int:",str(val)
                            lib.pWriteStringData(str(val))
                        else:
                            lib.pWriteStringData(str(vValue))
                    else:
                        lib.pWriteStringData(str(vValue))
                    

            lib.pClassEnd()

   
        #print valueStr
        #print readValueStr

    lib.pWriteStringData("dataEnd")


loadConfigMain()
print configDataMain["outputFile"]
lib.pOpenFile(str(configDataMain["outputFile"]), 10*1024*1024)
readValue("../"+configDataMain["inputFile"])
lib.pCloseWFile()
