#include "AED.h"

AED::AED() {
    this->electrodePads = new ElectrodePadPair(new AdultElectrode(), new AdultElectrode());
}

bool AED::selfCheck() {
    if(this->isFunctional) {
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
