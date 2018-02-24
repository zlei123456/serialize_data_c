#ifndef $CLASSNAMEUP
#define $CLASSNAMEUP

#include <string>
#include "model.h"
#include "SerializedInput.h"

using namespace std;

class $CLASSNAME : public model {
public:
$CLASSVALUE

    virtual bool resolveData(SerializedInput *input){  
        $CLASSREADE
        return true;
    }
};
#endif