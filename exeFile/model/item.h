#ifndef __ITEM_H_
#define __ITEM_H_

#include <string>
#include "model.h"
#include "SerializedInput.h"

using namespace std;

class item : public model {
public:
   string id;
   int a;
   int b;
   string c;
   short d;
   float e;
   bool f;
   map<int,int> g;
   vector<string> h;


    virtual bool resolveData(SerializedInput *input){  
            
    //id
    this->id = input->readStringUTF();
    
    //a
    this->a = input->readInt32BE();
    
    //b
    this->b = input->readInt32BE();
    
    //c
    this->c = input->readStringUTF();
    
    //d
    this->d = input->readInt16BE();
    
    //e
    this->e = input->readFloatBE();
    
    //f
    this->f = input->readBoolean();

    //map
    short size = input->readInt16BE();
    for(int i=0;i<size; ++i){
        int first = input->readInt32BE();
        int second = input->readInt32BE();
        this->g[first] = second;
    }

    //vertor
    short vSize = input->readInt16BE();
    for(int i=0; i<vSize; ++i){
        string str = input->readStringUTF();
        this->h.push_back(str);
    }

        return true;
    }
};
#endif