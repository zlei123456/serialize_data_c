这段时间有时间了,自己写了一个c++代码数据自动生成的工具,附源码(python的)
目录:
createClass : 自动生成模板代码(c++)
- model     生成模型的存放处
- template  模板文件(原始文件,py读取的.建议不做修改)
- config.json   部分配置文件
- createClass.py   生成c++模型类的python脚本
createData : 自动生成序列化数据
- readValue.py 生成zl.data的python脚本
- writeData.so  读取文件的c++编译的so库.
test.xlsx : 数据


exeFile是可执行的文件的目录.是有其他文件夹生成的.
-createClass.exe   是生成class类的可执行文件.(model目录下的)
-readValue.exe     是生成数据文件的可执行文件.(zl.data)


使用步骤:
1:填写test.xlsx,
每个sheet是一个类,第二行填类的成员变量,第三行填变量类型, 第十行开始填数据. 所有数据从c列开始,其他地方留作其他用途.暂时没有.
现支持类型:string,int,short,bool,map,vector.
2:修改"configMain.json"
inputFile: xlsx文件名
outputFile:数据输出名.
3:执行exeFile/createClass.exe 在model下生成所有的class文件.
4:执行exeFile/readValue.exe 会生成zl.data.
5:拷贝model文件夹和zl.data到相应的目录下.
6:调用代码
std::string DPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("zl.data");
TXData::shareData()->readData("zl.data");
就可以直接用TXData::shareData()的所有变量了.

