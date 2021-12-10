#ifndef __coordinates__
#define __coordinates__

class coordinates : public number {
public:
    double ConvertToReal() {
        return value;
    }

    coordinates(double givenangle, double givenvalue) {
        angle = givenangle;
        value = givenvalue;
    }

    virtual char* ToString() {
        char* outstr = new char[100];
        snprintf(outstr, 99, "Coordinates (%f; %f) - %f", angle, value, ConvertToReal());
        return outstr;
    }

private:
    double angle, value;
};

#endif