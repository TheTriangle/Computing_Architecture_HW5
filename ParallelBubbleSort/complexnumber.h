#ifndef __complexnumber__
#define __complexnumber__

class complexnumber : public number {
public:
    virtual double ConvertToReal() {
        return sqrt(real * real + imaginary * imaginary);
    }

    complexnumber(double givenreal, double givenimaginary) {
        real = givenreal;
        imaginary = givenimaginary;
    }

    virtual char* ToString() {
        char* outstr = new char[100];
        snprintf(outstr, 99, "Complex number (%f; %f) - %f", real, imaginary, ConvertToReal());
        return outstr;
    }

private:
    double real, imaginary;
};

#endif