#ifndef AED_H
#define AED_H

#include <QObject>
#include <ElectrodePad.h>
#include <vector>
#include <QTimer>
#include <QElapsedTimer>
#include <thread>
#include <QRandomGenerator>
#include <functional>


#include "VoiceSystem.h"
#include "Victim.h"
#include "ElectrodePadPair.h"
#include "AdultElectrode.h"
#include "ChildElectrode.h"

// AED inherits from QObject to send signals to mainwindow.h
class AED : public QObject {
    Q_OBJECT;

    // Private member variables
    private:
        // Custom classes
        ElectrodePadPair* electrodePads;
        Victim* victim;
        VoiceSystem* voiceSystem;

        QTimer* batteryTimer;
        QTimer* CPRTimer;
        QElapsedTimer* CPRElapsedTimer;
        QElapsedTimer* CPRElapsedIterationTimer;

        std::function<void()> mainWindowResetCallback;

        // Ints
        int batteryLevel = 100;
        int batteryAlpha = 2;

        // Bools
        bool isOn = false;
        bool correctPadPos = false;
        bool isFunctional = true;
        bool faultyPadPlacement = false;
        bool readyForShock = false;
        bool shockAdministered = false;
        bool patientDisturbed = false;

        int CPRCompressions[5] = {0,0,0,0,0};
        int CPRCompressionTimings[5] = {0,0,0,0,0};

    // Public member variables
    public:
        // explicit constructor
        explicit AED();

        // Shock btn functionality
        void shock();

        // Power on the aed
        bool powerOn();

        // Self Check
        bool selfCheck();

        // CPR iterations
        int cprIterations;

        // Await Audio
        void awaitAudio(QString, QString, QString, std::function<void()>);

        // Perform Compression
        void performCompression(int compressionType);

        void readyForShockFunctionality();

        // Getters
        bool getIsOn() { return this->isOn; }
        bool getPatientDisturbed() { return this->patientDisturbed; }
        bool getIsReadyForShock() { return this->readyForShock; }
        int getBatteryLevel() { return this->batteryLevel; }
        bool getCorrectPadPos() { return this->correctPadPos; }
        bool getIsFunctional() { return this->isFunctional; }
        bool getFaultyPadPlacment() { return this->faultyPadPlacement; }
        ElectrodePadPair* getElectrodePadPair() { return this->electrodePads; }
        bool getShockAdministered() { return this->shockAdministered; }
        Victim* getVictim() { return this->victim; }
        VoiceSystem* getVoiceSystem() { return this->voiceSystem; }
        QTimer* getBatteryTimer() { return this->batteryTimer; }
        QTimer* getCPRTimer() { return this->CPRTimer; }
        QElapsedTimer* getCPRElapsedTimer() { return this->CPRElapsedTimer; }
        QElapsedTimer* getCPRElapsedIterationTimer() { return this->CPRElapsedIterationTimer; }

        // Setters
        void setPatientDisturbed(bool isDisturbed) { this->patientDisturbed = isDisturbed; }
        void setIsReadyForShock(bool shockVal) { this->readyForShock = shockVal; }
        void setBatteryLevel(int newBatteryLevel) { this->batteryLevel = newBatteryLevel; }
        void setBatteryAlpha(int newBatteryAlpha) { this->batteryAlpha = newBatteryAlpha; }
        void setIsOn(bool newIsOn) { this->isOn = newIsOn; }
        void setCorrectPadPos(bool padPositioning) { this->correctPadPos = padPositioning; }
        void setIsFunctional(bool newIsFunctional) { this->isFunctional = newIsFunctional; }
        void setFaultyPadPlacement(bool faulty) { this->faultyPadPlacement = faulty; }
        void setVictim(Victim *newVictim) { this->victim = newVictim; };
        void setElectrodePadPair(ElectrodePadPair* newPair) { this->electrodePads = newPair; }
        void setShockAdministered(bool newShockAdministered) { this->shockAdministered = newShockAdministered; }
        void setCprIterations(int newIteration) { this->cprIterations = newIteration; }
        void setMainWindowResetCallback(std::function<void()> newFunc) { this->mainWindowResetCallback = newFunc; }

        void startCPR();

    // Signals for the aed
    signals:
        void arythmiaDetected();
        void flashShockButtonSignal();
        void shockSignal();
        void updateBatteryLevel();

    private slots:
        void CPRTimerFn();
};

#endif // AED_H
