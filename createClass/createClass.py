# coding: utf-8

import os, json
import xlrd
from sys import exit, argv
import string
#from string import Template

fileConfigMain = "../configMain.json"
preFileName = "ZL"
OUT_PATH = "model/"
EXCEL_FILE_NAME = "../test.xlsx"
MODELH_FILE_NAME = "template/modelNormal.h"
ALLH_FILE_NAME = "template/modelH_normal.h"
ALLH_FILE_NAME_save = "model/modelH.h"
TXData_cpp_Path = "template/TXData.cpp"
TXData_h_Path = "template/TXData.h"
TXData_cpp_Path_save = "model/TXData.cpp"
TXData_h_Path_save = "model/TXData.h"
row_startNum = 2
col_valueName = 1
col_valueType = 2
col_valueStart = 9

str_map = """
    //map
    short size = input->readInt16BE();
    for(int i=0;i<size; ++i){
        $FirstType first = input->$FirstElementRead();
        $secondType second = input->$SecondElementRead();
        this->$value[first] = second;
    }
"""

str_vector = """
    //vertor
    short vSize = input->readInt16BE();
    for(int i=0; i<vSize; ++i){
        $ElementType str = input->$ElementRead();
        this->$value.push_back(str);
    }
"""

str_base = """
    //$value
    this->$value = input->$ElementRead();
"""
str_mapValueDefine = """
    //$ValueType
    std::map<std::string, $ValueType*>  $Value;
"""

str_mapValueRead = """
        else if(c=="$ValueType")
        {
            std::string className(c);
            $ValueType *t = new $ValueType;
            modelControl<$ValueType> a;    
            a.resolveData(&input, t, className);
            $Value[t->id] = t;
        }
"""

def toUnicode(v):
    return unicode(v, "utf-8")

#config文件
global configData
global configDataBase

def loadConfig():
    global configData
    global configDataBase
    
    readFile = open("config.json", "r")
    buf = readFile.read()
    readFile.close()

    print buf
    pData = json.loads(buf)
    configData = pData
    configDataBase = configData["readBaseCon"]
    #print pData["readBaseCon"]

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
    

def getMapFirstAndSecond(v):
    a = v.find("<")
    b = v.find(">")
    con = v[a+1:b]
    c = con.split(",")
    return c[0],c[1]

def createMapReadCode(v, vValue):
    global configDataBase
    
    f,s = getMapFirstAndSecond(v)
    tempMap = string.Template(str_map)
    strF = configDataBase[f]
    strS = configDataBase[s]
    temp = tempMap.substitute(FirstType=f, secondType=s, value=vValue, FirstElementRead=strF, SecondElementRead=strS)
    return temp

def getVectorValue(v):
    a = v.find("<")
    b = v.find(">")
    con = v[a+1:b]
    return con

def createVectorReadCode(v, vValue):
    global configDataBase

    f = getVectorValue(v)
    tempVector = string.Template(str_vector)
    strV = configDataBase[f]
    temp = tempVector.substitute( value=vValue, ElementType=f, ElementRead=strV)
    return temp

def createBaseValue(v, vValue):
    strV = configDataBase[v]
    assert (strV!="") , "type error"

    tempBase = string.Template(str_base)
    
    temp = tempBase.substitute( value=vValue,ElementRead=strV)
    return temp

def getBufOfFile(fileName):
    readFile = open(fileName, "r")
    buf = readFile.read()
    readFile.close()
    #file = os.open(fileName, os.O_RDWR)
    #buf = file.read()
    #file.close()
    return buf

def saveBufOfFile(fileName, buf):
    writeFile = open(fileName, "w")
    writeFile.write(buf)
    writeFile.close()
    #file = os.open(fileName, os.O_RDWR)
    #file.write(buf)
    #file.close()
    
def readExcel_classMember(path):
    global configDataBase

    valueStr = ""
    readValueStr = ""
    workbook = xlrd.open_workbook(path)

    modelBuf_H = getBufOfFile(ALLH_FILE_NAME)
    TXDataCppBuf = getBufOfFile(TXData_cpp_Path)
    TXDataHBuf = getBufOfFile(TXData_h_Path)
    
    ALLH = ""
    all_map_value=""
    all_map_read=""
   
    sheet_num = len(workbook.sheets())
    for sheet in xrange(0, sheet_num):        
        oneSheet = workbook.sheets()[sheet]
        print "sheet name = "+oneSheet.name
        fileName = oneSheet.name
        rowNum = oneSheet.nrows
        colNum = oneSheet.ncols
        if(rowNum<1):
            continue
        rowValueName = oneSheet.row(col_valueName)
        rowValueType = oneSheet.row(col_valueType)

        readValueStr = ""
        valueStr = ""
 
        for j in xrange(row_startNum, colNum):
            valueStr += '   %s %s;\n' %(rowValueType[j].value, rowValueName[j].value)
            
            vType = rowValueType[j].value
            vValue = rowValueName[j].value
            if vType.find("map")!=-1:
                print "sheet = ",fileName,"row=",j,"vtype=",vType,"vValue=",vValue
                code = createMapReadCode(vType, vValue)
                readValueStr += code
                #print "map code ="+code
            elif vType.find("vector")!=-1:
                print "sheet = ",fileName,"row=",j,"vtype=",vType,"vValue=",vValue
                code = createVectorReadCode(vType, vValue)
                #print "vector ="+code
                readValueStr += code
            else:
                print "sheet = ",fileName,"row=",j,"vtype=",vType,"vValue=",vValue
                code = createBaseValue(vType, vValue)
                #print "strType = "+code
                readValueStr += "    "+code

        #item.h
        modelBuf = getBufOfFile(MODELH_FILE_NAME)
        tempBuf = string.Template(modelBuf)
        buf = tempBuf.substitute(CLASSNAMEUP="__"+fileName.upper()+"_H_", CLASSNAME=fileName, CLASSVALUE=valueStr, CLASSREADE=readValueStr)
        #print buf
        saveBufOfFile(OUT_PATH+fileName+".h", buf)
        #modelH.h
        ALLH += '#include \"'+fileName+'.h\"\n'
        #TXData.h
        valueName = "tx_"+fileName+"S"
        tempBuf_data = string.Template(str_mapValueDefine)
        buf_data = tempBuf_data.substitute(ValueType=fileName, Value=valueName)
        all_map_value += buf_data
        #print "buf_data:",buf_data
        #TXData.cpp
        tempBuf_Read = string.Template(str_mapValueRead)
        buf_Read = tempBuf_Read.substitute(ValueType=fileName, Value=valueName)
        all_map_read += buf_Read
        #print "buf_Read:",buf_Read

        #clear
        

    tempBufH = string.Template(modelBuf_H)
    bufH = tempBufH.substitute(EXTFILENAME=ALLH)    
    saveBufOfFile(ALLH_FILE_NAME_save, bufH)
    #print bufH

    DataHBufH = string.Template(TXDataHBuf)
    dataH = DataHBufH.substitute(ALLMAPVALUE=all_map_value)    
    saveBufOfFile(TXData_h_Path_save, dataH)
    #print "TXData.h"
    #print dataH
    
    DataCppBufH = string.Template(TXDataCppBuf)
    dataCpp = DataCppBufH.substitute(MAPVALUEREAD=all_map_read)    
    saveBufOfFile(TXData_cpp_Path_save, dataCpp)
    #print "TXData.cpp"
    #print dataCpp


loadConfig()
loadConfigMain()
readExcel_classMember("../"+configDataMain["inputFile"])
