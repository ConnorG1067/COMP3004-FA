#ifndef ELECTRODEPADPAIR_H
#define ELECTRODEPADPAIR_H

#include <vector>
#include "ElectrodePad.h"

using namespace std;

class ElectrodePadPair {
    public:
        ElectrodePadPair(ElectrodePad*, ElectrodePad*);

        ElectrodePad* getUpperPad() { return this->upperPad; }
        ElectrodePad* getLowerPad() { return this->lowerPad; }


    private:
        ElectrodePad* upperPad;
        ElectrodePad* lowerPad;
};
#endif // ELECTODEPADPAIR_H
