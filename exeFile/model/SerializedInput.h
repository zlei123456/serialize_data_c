
#ifndef __INPUT_H__
#define __INPUT_H__
#include "cocos2d.h"
#include "stdio.h"

using namespace cocos2d;
class SerializedInput {

public: 
	//FILE *m_fp;
	char *buffer;
	char *cur_buf;
	
	void createFile(const char* fn);
	void closeFile();

	void setBuffer(char *buf);
	void BufRead(void *buf,int size);

	int skipBytes(int n);
	char readInt8();			//********���Թ���*******
	unsigned char readUInt8();			//*********���Թ���*******
	short readInt16BE();		//*********���Թ���*******
	unsigned short readUInt16BE();		//*********���Թ���*******
	int readInt32BE();				//*********���Թ���*******
	long long readInt64BE();
	float readFloatBE();			//*********������**********
	std::string readStringUTF();
	bool readBoolean();
	std::string readUUIDAsStr();
	long getReadSize();

	void closeFile(FILE *fp);
};

#endif
