#ifndef _TXDATA_H__
#define _TXDATA_H__

#include <string>
#include <map>

#include "modelH.h"

class TXData {
public:
    //std::map<std::string, item*>  m_items;
    
    //item
    std::map<std::string, item*>  tx_itemS;

    //leiTest1
    std::map<std::string, leiTest1*>  tx_leiTest1S;


    static TXData *shareData();
    void readData(const char *dataFilePath);
    
};
#endif