#include "AED.h"

// AED constructor
AED::AED() {
    // Create an electrodePadPair
    this->electrodePads = new ElectrodePadPair(new AdultElectrode(), new AdultElectrode());
    // Voice system
    this->voiceSystem = new VoiceSystem();
}

// Power on the aed
bool AED::powerOn() {
    // If the battery is not 0
    if(this->batteryLevel > 0) {
        // turn on the aed and return true
        this->isOn = true;
        return true;
    // Otherwise return false
    }else{
       return false;
    }
}

// Set is ready for shock
void AED::setIsReadyForShock(bool isReady){
    // If it is ready
    if(isReady) {
        // Play the shock advised audio
        this->voiceSystem->initiateAudioAndTextIntruction("qrc:/audios/src/audios/shockAdvisedChargingStandClear.mp3", ":/images/src/img/analyzing.png", "Administering first shock to patient");
        // emit the flashShockBtn
        emit this->flashShockButtonSignal();
    }
    // Set the variable is ready for shock
    this->readyForShock = isReady;
}

// Shock function
void AED::shock() {
    this->getVoiceSystem()->initiateAudioAndTextIntruction("qrc:/audios/src/audios/shockOneDeliveredBeginCPR.mp3", ":/images/src/img/analyzingHeart.png", "Shock one administered");
    emit this->shockSignal();
}
