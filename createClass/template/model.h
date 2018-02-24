#ifndef __MODEL_H__
#define __MODEL_H__

#include <string>
#include "SerializedInput.h"

using namespace std;

class model{
public:
    std::string className;
    int size;
    //std::string  id;

    virtual bool resolveData(SerializedInput *input){
        return false;
    }


};

template<class T>
class modelControl{
public:
    static std::string getModelClassName(SerializedInput *input){
        //std::string _className = input->readStringUTF();
        //char *n = (char *)_className.c_str();
        return input->readStringUTF();
        //m->className = input->readStringUTF();
    }

    void resolveData(SerializedInput *input, T*m, std::string &_name){
        //m->className = input->readStringUTF();
        m->className = _name;
        m->size = input->readInt16BE();
        if(!m->resolveData(input)){
            //skip size;
            int r = getSize(m->className)+getSize(m->size);
            //int r = m->className.size()+sizeof(short)+sizeof(int);
            int left = m->size-r;
            input->skipBytes(left);
        }
    };
};


//***********得到各个类型的size
int getSize(string str){
    return str.size()+sizeof(short);
}
template<class T>
int getSize(T t){
    return sizeof(t);
}
template<class T>
int getSize(vector<T> t){
    int s = t.size();
    auto vecSize = std::for_each(t.begin(), t.end(), getSizeForEach<T, int>());
    return vecSize.size+sizeof(short);
}

template<class T1, class T2>
int getSize(map<T1, T2> t){
    int s = t.size();
    auto vecSize = std::for_each(t.begin(), t.end(), getSizeForEach<T1, T2>());
    return vecSize.size+sizeof(short);
};

template<class T, class T1>
class getSizeForEach{
public:
    int size;
    getSizeForEach(){
        size = 0;
    };

    void operator()(T v){
        size += getSize(v);
        //return size;
    };
    void operator()(std::pair<T, T1> v){
        size += getSize(v.first);
        size += getSize(v.second);
    };
};

#endif // !__MODEL_H__
