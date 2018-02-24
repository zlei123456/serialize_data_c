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
        $MAPVALUEREAD

    }

    input.closeFile();

}