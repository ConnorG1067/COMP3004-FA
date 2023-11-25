#include "AED.h"

AED::AED() {
    this->electrodePads = new ElectrodePadPair(new AdultElectrode(), new AdultElectrode());
    this->voiceSystem = new VoiceSystem();
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

void AED::setIsReadyForShock(bool isReady){
    if(isReady){
        this->voiceSystem->initiateAudioAndTextIntruction("qrc:/audios/src/audios/shockAdvisedChargingStandClear.mp3", ":/images/src/img/analyzing.png", "Administering first shock to patient");
        emit this->flashShockButtonSignal();
    }

    this->readyForShock = isReady;
}

void AED::shock() {
    emit this->shockSignal();
}
