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
    this->CPRElapsedIterationTimer = new QElapsedTimer();

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
    this->CPRElapsedIterationTimer->start();
}

// CPR Timer function
void AED::CPRTimerFn(){
    // 10 seconds of cpr
    if(this->CPRElapsedIterationTimer->elapsed() <= 10000){
        // Play tick sound
        this->voiceSystem->initiateSound("qrc:/audios/src/audios/CPRTick.mp3");
    // Greater than 10 seconds
    }else{
        // Stop the timers
        this->CPRElapsedIterationTimer->invalidate();
        this->getCPRTimer()->stop();

        // Decrement the cpr iterations
        (this->cprIterations)--;
        // If we still have iterations
        if(this->cprIterations > 0) {
            // Check for a shock
            if(this->getIsReadyForShock()){
                this->readyForShockFunctionality();
            // Perform more cpr
            }else{
                this->startCPR();
            }
        }else{
            int responsiveProbability = QRandomGenerator::global()->bounded(0, 9);

            awaitAudio((responsiveProbability < 3) ? "qrc:/audios/src/audios/unresponsive.mp3" : "qrc:/audios/src/audios/responsive.mp3", ":/images/src/img/ems_arrival.png", "Await EMS", [this] () {
                this->mainWindowResetCallback();
            });

            this->readyForShock = false;
        }
    }
}

void AED::awaitAudio(QString audioPath, QString imgPath, QString textInstructions, std::function<void()> operationAfterAudio) {
    QTimer* timer = new QTimer;
    bool* isPlayed = new bool(false);
    QObject::connect(timer, &QTimer::timeout, [this, timer, operationAfterAudio, textInstructions, imgPath, audioPath, isPlayed]() {
        if(!(*isPlayed)){
            (*isPlayed) = true;
            this->voiceSystem->initiateAudioAndTextIntruction(audioPath, imgPath, textInstructions);
        }else if(this->voiceSystem->getAudioInstructions()->state() == QMediaPlayer::StoppedState && isPlayed){
            operationAfterAudio();
            timer->stop();
            timer->deleteLater();
        }
    });
    timer->setInterval(1000);
    timer->start();
}

// Power on the aed
void AED::performCompression(int compressionType = 0){
    bool goodCompressions = true;
    bool enoughElapsedTimeDataPresent = [=](){for(int i = 0; i < 5; i++){if(this->CPRCompressionTimings[i] == 0) return false;} return true;}();

    long long compressionTiming = this->CPRElapsedTimer->elapsed();
    this->CPRElapsedTimer->restart();

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
void AED::readyForShockFunctionality(){
    // If it is ready
    if(this->readyForShock) {
        // Play the shock advised audio
        this->voiceSystem->initiateAudioAndTextIntruction("qrc:/audios/src/audios/shockAdvisedChargingStandClear.mp3", ":/images/src/img/analyzing.png", "Administering first shock to patient");
        emit flashShockButtonSignal();
    }else{
        awaitAudio("qrc:/audios/src/audios/ShockNotAdvisedBeginCPR.mp3", ":/images/src/img/analyzingHeart.png", "Start CPR", [this] () { this->startCPR(); });
    }
}

// Shock function
void AED::shock() {
    if(this->readyForShock){
        emit this->shockSignal();
        awaitAudio("qrc:/audios/src/audios/ShockDeliveredCPR.mp3", ":/images/src/img/analyzingHeart.png", "Start CPR", [this] () { this->startCPR(); });
    }
}

