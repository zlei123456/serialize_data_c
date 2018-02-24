#ifndef _TXDATA_H__
#define _TXDATA_H__

#include <string>
#include <map>

#include "modelH.h"

class TXData {
public:
    //std::map<std::string, item*>  m_items;
    $ALLMAPVALUE

    static TXData *shareData();
    void readData(const char *dataFilePath);
    
};
#endif