#include "SerializedOutput.h"

using namespace cocos2d;

#define S_BIGENDAIN

void SerializedOutput::createFile(const char *name){
	m_fp = fopen(name,"wb+");
}

void SerializedOutput::closeFile(){
    m_buf[0]='\0';
    fwrite(m_beginBuf, m_curPos+1, 1, m_fp);
	fclose(m_fp);
}

void SerializedOutput::init(int size)
{
	//int n =100;
	m_buf = new char[size]; 
    m_beginBuf = m_buf;
	m_curPos = 0;
    //writeInt16BE(12);
}

void SerializedOutput::writeInt8(char n){
    m_buf[0] = n;
	m_buf++;
	m_curPos++;
}

void SerializedOutput::writeUInt8(unsigned char n){
    m_buf[0] = n;
	m_buf++;
	m_curPos++;
}

void SerializedOutput::writeInt16BE(short n){
#ifdef S_BIGENDAIN
    short x = n;
    size_t LEN = sizeof(n);
    for (size_t i = 0; i < LEN; i++) {
        unsigned char b = x & 0xFF;
        m_buf[LEN-i-1] = b;
        x = x >> 8;
    }
#else
    short x = n;
    size_t LEN = sizeof(n);
    for (size_t i = 0; i < LEN; i++) {
        unsigned char b = x & 0xFF;
        m_buf[i] = b;
        x = x >> 8;
    }
#endif
	m_buf+=LEN;
	m_curPos+=LEN;
}

void SerializedOutput::writeUInt16BE(unsigned short n){
#ifdef S_BIGENDAIN
    unsigned short x = n;
    size_t LEN = sizeof(n);
    for (size_t i = 0; i < LEN; i++) {
        unsigned char b = x & 0xFF;
        m_buf[LEN-i-1] = b;
        x = x >> 8;
    }
#else
    unsigned short x = n;
    size_t LEN = sizeof(n);
    for (size_t i = 0; i < LEN; i++) {
        unsigned char b = x & 0xFF;
        m_buf[i] = b;
        x = x >> 8;
    }
#endif
	m_buf+=LEN;
	m_curPos+=LEN;
}

void SerializedOutput::writeInt32BE(int n){

#ifdef S_BIGENDAIN
    long x = n;
    size_t LEN = sizeof(n);
    for (size_t i = 0; i < LEN; i++) {
        unsigned char b = x & 0xFF;
        m_buf[LEN-i-1] = b;
        x = x >> 8;
    }
#else
    long x = n;
    size_t LEN = sizeof(n);
    for (size_t i = 0; i < LEN; i++) {
        unsigned char b = x & 0xFF;
        m_buf[i] = b;
        x = x >> 8;
    }
#endif
	m_buf+=LEN;
	m_curPos+=LEN;
}

void SerializedOutput::writeInt64BE(long long n){

#ifdef S_BIGENDAIN
    long long x = n;
    size_t LEN = sizeof(n);
    for (size_t i = 0; i < LEN; i++) {
        unsigned char b = x & 0xFF;
        m_buf[LEN-i-1] = b;
        x = x >> 8;
    }
#else
    long long x = n;
    size_t LEN = sizeof(n);
    for (size_t i = 0; i < LEN; i++) {
        unsigned char b = x & 0xFF;
        m_buf[i] = b;
        x = x >> 8;
    }
#endif
	m_buf+=LEN;
	m_curPos+=LEN;
}

void SerializedOutput::writeFloatBE(float f){
    union {
        int x;
        float y;
    } u;
    u.y = f;
    writeInt32BE(u.x);
}

void SerializedOutput::writeStringUTF(std::string str){

	writeInt16BE(str.size());
	memcpy(m_buf, str.c_str(), str.size());
	m_buf+=str.size();
	m_curPos+=str.size();
}

void SerializedOutput::writeBoolean(bool b){
	memcpy(m_buf, (char*)&b, 1);
	m_buf+=1;
	m_curPos+=1;
}

void SerializedOutput::writeUUID(std::string str){
	writeStringUTF(str);
}

long SerializedOutput::getWriteSize()
{
	return m_curPos;
}

char* SerializedOutput::getBuf()
{
	m_buf -= m_curPos;
	return m_buf;
}

void SerializedOutput::finalize()
{
	delete m_buf;
}
