
#ifndef __OUTPUT_H__
#define __OUTPUT_H__
#include "cocos2d.h"
#include "stdio.h"

using namespace cocos2d;

typedef unsigned char byte;

class SerializedOutput {

	
public: 
	FILE *m_fp;
    char *m_beginBuf;
	char *m_buf;
	int m_curPos;

	void createFile(const char *name);
	void closeFile();

	void writeInt8(char n);
	void writeUInt8(unsigned char n);
	void writeInt16BE(short n);
	void writeUInt16BE(unsigned short n);
	void writeInt32BE(int n);
	void writeInt64BE(long long n);
	void writeFloatBE(float f);		
	void writeStringUTF(std::string str);
	void writeBoolean(bool b);
	void writeUUID(std::string str);
	long getWriteSize();

	void init(int size);
	char* getBuf();
	void finalize();
};

#endif
