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


exeFile�ǿ�ִ�е��ļ���Ŀ¼.���������ļ������ɵ�.
 -createClass.exe   ������class��Ŀ�ִ���ļ�.(modelĿ¼�µ�)
 -readValue.exe     �����������ļ��Ŀ�ִ���ļ�.(zl.data)


����:
1:��дtest.xlsx,
ÿ��sheet��һ����,�ڶ�������ĳ�Ա����,���������������, ��ʮ�п�ʼ������. �������ݴ�c�п�ʼ,�����ط�����������;.��ʱû��.
��֧������:string,int,short,bool,map,vector.
2:�޸�"configMain.json"
inputFile: xlsx�ļ���
outputFile:���������.
3:ִ��exeFile/createClass.exe ��model���������е�class�ļ�.
4:ִ��exeFile/readValue.exe ������zl.data.
5:����model�ļ��к�zl.data����Ӧ��Ŀ¼��.
6:���ô���
std::string DPath = CCFileUtils::sharedFileUtils()->fullPathForFilename("zl.data");
TXData::shareData()->readData("zl.data");
�Ϳ���ֱ����TXData::shareData()�����б�����.