#include "AED.h"

AED::AED() {
    this->errorVector = new vector<Error*>;
}

bool AED::selfCheck() {
    if(this->batteryLevel > 0 && this->errorVector->empty()) {
        return true;
    }else{
        return false;
    }
}

bool AED::powerOn() {
    if(this->batteryLevel > 0) {
        this->isOn = true;
        return true;
    }else{
       return false;
    }
}
