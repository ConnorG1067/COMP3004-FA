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

void AED::shock() {
    if(this->getIsReadyForShock()) {
        this->voiceSystem->initiateAudioAndTextIntruction("qrc:/audios/src/audios/shockAdvisedChargingStandClear.mp3", ":/images/src/img/analyzing.png", "Administering first shock to patient");

        /*
        // Create timer for flashing shock button
        QTimer* flashTimer = new QTimer(this);
        // Create step pointer
        int* step = new int(0);

        QObject::connect(flashTimer, &QTimer::timeout [this, step, flashTimer](){
            this->
        });*/


    }else{
        qDebug() << "patient not shockable";
    }
}
