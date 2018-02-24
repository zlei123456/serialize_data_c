#include "SerializedInput.h"
#include "platform/CCFileUtils.h"

#define S_BIGENDIAN

using namespace cocos2d;

void SerializedInput::createFile(const char* fn)
{
	unsigned long file_size = 0;
	setBuffer((char*)CCFileUtils::sharedFileUtils()->getFileData(fn, "rb", &file_size));

	//CCFileUtils::getFileData
	//FILE *fp = fopen(fn ,"rb");
	//if (!fp) return;

	//fseek(fp,0,SEEK_END);
	//int size = ftell(fp);
	//fseek(fp, 0, SEEK_SET);

	//char * buf = (char*)malloc(size);
	//fread(buf, 1, size, fp);
	//fclose(fp);
	//setBuffer(buf);
}

void SerializedInput::closeFile()
{
	free(buffer);
}

void SerializedInput::setBuffer(char *buf){
	cur_buf = buffer = buf;

}

int SerializedInput::skipBytes(int n){
	//return fseek(m_fp,n,SEEK_CUR);
	cur_buf += n;
	return n;

}
char SerializedInput::readInt8(){

	char m;
	//fread((byte*)&m, 1, 1, m_fp);
	m = *cur_buf;
	cur_buf ++;
		
	return m;
	
}
unsigned char SerializedInput::readUInt8(){
	unsigned char n;
	//fread((byte*)&n, 1, 1, m_fp);
	n = (unsigned char)*cur_buf;
	cur_buf ++;
	return n;
}
short SerializedInput::readInt16BE(){

	short n=0;
	//short *p = (short *)cur_buf;
	//cur_buf += 2;
	//n = *p;

	unsigned char *p = (unsigned char*)cur_buf;
	cur_buf += 2;

	for (int i = 1; i >= 0; i--) {
		n = (n<<8) + *(p+i);
	}

#ifdef S_BIGENDIAN
	int m = n;
	n = ((m & 0xFF) << 8) + ((m >> 8) & 0xFF);
#endif
	return n;
}
unsigned short SerializedInput::readUInt16BE(){

	unsigned short n = 0;
	//fread((void *)&n,1,2,m_fp);

	//unsigned short *p = (unsigned short *)cur_buf;
	//cur_buf += 2;
	//n = *p;

	unsigned char *p = (unsigned char*)cur_buf;
	cur_buf += 2;

	for (int i = 1; i >= 0; i--) {
		n = (n<<8) + *(p+i);
	}

	//char c1,c2;
	//c1= *cur_buf++;
	//c2 = *cur_buf++;
	//n = (c2&0xFF)<<8;
	//n += c1;

#ifdef S_BIGENDIAN
	int m = n;
	n = ((m & 0xFF) << 8) + ((m >> 8) & 0xFF);
#endif
	return (unsigned short)n;
}
int SerializedInput::readInt32BE(){
	int n =0;
	//fread((void *)&n,1,4,m_fp);
	unsigned char *p = (unsigned char*)cur_buf;
	cur_buf += 4;

	for (int i = 3; i >= 0; i--) {
		n = (n<<8) + *(p+i);
	}

#ifdef S_BIGENDIAN
	int m = n;
	n = ((m & 0xFF) << 24) + (((m >> 8) & 0xFF) << 16) + (((m >> 16) & 0xFF) << 8) + ((m >> 24) & 0xFF);
#endif
	return n;
}
long long SerializedInput::readInt64BE(){

	long long n = 0;

	unsigned char *p = (unsigned char*)cur_buf;
	cur_buf += 8;

#ifdef S_BIGENDIAN
	for (int i = 0; i < 8; i++) {
		n = (n<<8) + *(p+i);
	}
#else
	for (int i = 7; i >= 0; i--) {
		n = (n<<8) + *(p+i);
	}
#endif

	return n;
}
float SerializedInput::readFloatBE(){

    union {
        int I;
        float F;
    } C;

	int n = 0;
	unsigned char *p = (unsigned char*)cur_buf;
	cur_buf += 4;

#ifdef S_BIGENDIAN
	for (int i = 0; i < 4; i++) {
		n = (n<<8) + *(p+i);
	}
#else
	for (int i = 3; i >= 0; i--) {
		n = (n<<8) + *(p+i);
	}
#endif

    C.I = n;
    return C.F;
}

std::string SerializedInput::readStringUTF(){
	short size = readInt16BE();

	std::string n ;
	n.resize(size);
	n.assign(cur_buf, size);
	cur_buf+=size;

	//char* m = (char*)malloc(size+1);
	//memcpy(m, cur_buf, size);
	//cur_buf+=size;
	//m[size] = 0;
	//std::string n(m);
	//free(m);
	return n;
}

bool SerializedInput::readBoolean(){
	bool n;
	//fread((void *)&n,1,1,m_fp);
	n = *cur_buf != 0;
	cur_buf ++;
	return n;
}

std::string SerializedInput::readUUIDAsStr(){
	return readStringUTF();
}


long SerializedInput::getReadSize()
{
	//fseek(m_fp, 0L,SEEK_CUR);
	//return ftell(m_fp);
    //return (long)(buffer-cur_buf);
    return (long)(cur_buf-buffer);
}
