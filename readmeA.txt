Ŀ¼:
createClass : �Զ�����ģ�����(c++)
 - model     ����ģ�͵Ĵ�Ŵ�
 - template  ģ���ļ�(ԭʼ�ļ�,py��ȡ��.���鲻���޸�)
 - config.json   ���������ļ�
 - createClass.py   ����c++ģ�����python�ű�
createData : �Զ��������л�����
 - readValue.py ����zl.data��python�ű�
 - writeData.so  ��ȡ�ļ���c++�����so��.
test.xlsx : ����

���ô���
std::string DPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("zl.data");
    TXData::shareData()->readData("zl.data");