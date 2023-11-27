#include "AED.h"

// AED constructor
AED::AED() {
    // Create an electrodePadPair
    this->electrodePads = new ElectrodePadPair(new AdultElectrode(), new AdultElectrode());
    // Voice system
    this->voiceSystem = new VoiceSystem();

    this->CPRTimer = new QTimer();
    this->CPRTimer->setInterval(600);

    this->CPRElapsedTimer = new QElapsedTimer();

    // Connect flash shock button timer to timer function
    QObject::connect(CPRTimer, SIGNAL(timeout()), this, SLOT(CPRTimerFn()));
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

// CPR start function
void AED::startCPR(){
    this->CPRElapsedTimer->start();
    this->getCPRTimer()->start();
}

// CPR Timer function
void AED::CPRTimerFn(){
    this->voiceSystem->initiateSound("qrc:/audios/src/audios/CPRTick.mp3");
}

// Power on the aed
void AED::performCompression(int compressionType = 0){
    bool goodCompressions = true;
    bool enoughElapsedTimeDataPresent = [=](){for(int i = 0; i < 5; i++){if(this->CPRCompressionTimings[i] == 0) return false;} return true;}();

    long long compressionTiming = this->CPRElapsedTimer->elapsed();
    this->CPRElapsedTimer->restart();

    qDebug() << compressionTiming;

    for(int i = 0; i < 4; i++){
        this->CPRCompressions[i] = this->CPRCompressions[i+1];
        this->CPRCompressionTimings[i] = this->CPRCompressionTimings[i+1];
    }

    this->CPRCompressions[4] = compressionType;
    this->CPRCompressionTimings[4] = compressionTiming;

    // keeps track of overall quality of compressions
    int sumType = 0;

    // keeps track of overall quality of compression timings
    int sumQuality = 0;

    for(int i = 0; i < 5; i++){
        sumType += this->CPRCompressions[i];
        sumQuality += this->CPRCompressionTimings[i];
        if(this->CPRCompressionTimings[i] > 0 && (this->CPRCompressionTimings[i] < 400 || this->CPRCompressionTimings[i] > 800)){
            goodCompressions = false;	// Not all compressions are correctly timed
        }
    }

    if(enoughElapsedTimeDataPresent){
        if(goodCompressions && sumType == 5){
            this->voiceSystem->initiateTextIntruction("Good Compressions");
            for(int i = 0; i < 5; i++) this->CPRCompressions[i] = 0;
        }else if(sumType == 5){
            ((sumQuality / 6) < 400) ? this->voiceSystem->initiateTextIntruction("Decrease Speed") : this->voiceSystem->initiateTextIntruction("Increase Speed");
            for(int i = 0; i < 5; i++) this->CPRCompressions[i] = 0;
        }else if(sumType == -5){
            this->voiceSystem->initiateTextIntruction("Push harder");
        }
    }
}

// Set is ready for shock
void AED::setIsReadyForShock(bool isReady){
    // If it is ready
    if(isReady) {
        // Play the shock advised audio
        this->voiceSystem->initiateAudioAndTextIntruction("qrc:/audios/src/audios/shockAdvisedChargingStandClear.mp3", ":/images/src/img/analyzing.png", "Administering first shock to patient");
        // emit the flashShockBtn
        this->startCPR();
    }else{
        this->voiceSystem->initiateAudioAndTextIntruction("qrc:/audios/src/audios/shockOneDeliveredBeginCPR.mp3", ":/images/src/img/analyzing.png", "Shock not advised. Begin CPR");
    }
    // Set the variable is ready for shock
    this->readyForShock = isReady;
}

// Shock function
void AED::shock() {
    emit this->shockSignal();

    this->voiceSystem->initiateAudioAndTextIntruction("qrc:/audios/src/audios/shockOneDeliveredBeginCPR.mp3", ":/images/src/img/analyzingHeart.png", "Start CPR");
    this->startCPR();
}

