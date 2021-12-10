#include "number.h"

#ifndef __fraction__
#define __fraction__

class fraction : public number {
public:
    double ConvertToReal() {
        return numenator / denominator;
    }

    fraction(double givennominator, double givendenominator) {
        numenator = givennominator;
        denominator = givendenominator;
    }

    virtual char* ToString() {
        char* outstr = new char[100];
        snprintf(outstr, 99, "Fraction %f/%f - %f", numenator, denominator, ConvertToReal());
        return outstr;
    }

private:
    double numenator, denominator;
};

#endif