#include "AED.h"

AED::AED() {}

bool AED::powerOn() {
    if(this->batteryLevel > 0) {
        this->isOn = true;
        return true;
    }else{
       return false;
    }

}
