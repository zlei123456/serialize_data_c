#include "TXData.h"
#include "SerializedInput.h"

using namespace std;
static TXData* _TXShareData= NULL;

TXData* TXData::shareData(){
    if(!_TXShareData){
        _TXShareData = new TXData();
    }
    return _TXShareData;
}
void TXData::readData(const char *dataFilePath){
    SerializedInput input;
    input.createFile(dataFilePath);

    std::string c;
    for(c=modelControl<model>::getModelClassName(&input); c!=""; c=(modelControl<model>::getModelClassName(&input))){
        if(c=="dataEnd"){
            break;
        }
        
        else if(c=="item")
        {
            std::string className(c);
            item *t = new item;
            modelControl<item> a;    
            a.resolveData(&input, t, className);
            tx_itemS[t->id] = t;
        }

        else if(c=="leiTest1")
        {
            std::string className(c);
            leiTest1 *t = new leiTest1;
            modelControl<leiTest1> a;    
            a.resolveData(&input, t, className);
            tx_leiTest1S[t->id] = t;
        }


    }

    input.closeFile();

}