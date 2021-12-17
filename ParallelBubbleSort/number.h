#ifndef __number__
#define __number__

//------------------------------------------------------------------------------
// number.h - �������� �������� ����������� �����,
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

class number {
public:
    virtual double ConvertToReal() {
        return 0;
    }

    virtual char* ToString() {
        return nullptr;
    }
};


#include "fraction.h"
#include "coordinates.h"
#include "complexnumber.h"

#endif
