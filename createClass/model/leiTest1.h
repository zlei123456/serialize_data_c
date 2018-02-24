#ifndef __LEITEST1_H_
#define __LEITEST1_H_

#include <string>
#include "model.h"
#include "SerializedInput.h"

using namespace std;

class leiTest1 : public model {
public:
   string id;
   string fadsf;
   int sdfs;
   bool fasdd;
   std::map<string,string> add;


    virtual bool resolveData(SerializedInput *input){  
            
    //id
    this->id = input->readStringUTF();
    
    //fadsf
    this->fadsf = input->readStringUTF();
    
    //sdfs
    this->sdfs = input->readInt32BE();
    
    //fasdd
    this->fasdd = input->readBoolean();

    //map
    short size = input->readInt16BE();
    for(int i=0;i<size; ++i){
        string first = input->readStringUTF();
        string second = input->readStringUTF();
        this->add[first] = second;
    }

        return true;
    }
};
#endif