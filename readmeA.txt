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

调用代码
std::string DPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("zl.data");
    TXData::shareData()->readData("zl.data");