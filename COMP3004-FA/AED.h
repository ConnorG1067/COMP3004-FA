#ifndef AED_H
#define AED_H

#include <QObject>
#include <ElectrodePad.h>
#include <vector>

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

        // Ints
        int batteryLevel = 100;

        // Bools
        bool isOn = false;
        bool correctPadPos = false;
        bool isFunctional = true;
        bool faultyPadPlacement = false;
        bool readyForShock = false;
        bool shockAdministered = false;
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

        // Getters
        bool getIsOn() { return this->isOn; }
        bool getIsReadyForShock() { return this->readyForShock; }
        int getBatteryLevel() { return this->batteryLevel; }
        bool getCorrectPadPos() { return this->correctPadPos; }
        bool getIsFunctional() { return this->isFunctional; }
        bool getFaultyPadPlacment() { return this->faultyPadPlacement; }
        ElectrodePadPair* getElectrodePadPair() { return this->electrodePads; }
        bool getShockAdministered() { return this->shockAdministered; }
        Victim* getVictim() { return this->victim; }
        VoiceSystem* getVoiceSystem() { return this->voiceSystem; }

        // Setters
        void setIsReadyForShock(bool isReady);
        void setBatteryLevel(int newBatteryLevel) { this->batteryLevel = newBatteryLevel; }
        void setIsOn(bool newIsOn) { this->isOn = newIsOn; }
        void setCorrectPadPos(bool padPositioning) { this->correctPadPos = padPositioning; }
        void setIsFunctional(bool newIsFunctional) { this->isFunctional = newIsFunctional; }
        void setFaultyPadPlacement(bool faulty) { this->faultyPadPlacement = faulty; }
        void setVictim(Victim *newVictim) { this->victim = newVictim; };
        void setElectrodePadPair(ElectrodePadPair* newPair) { this->electrodePads = newPair; }
        void setShockAdministered(bool newShockAdministered) { this->shockAdministered = newShockAdministered; }
    // Signals for the aed
    signals:
        void arythmiaDetected();
        void flashShockButtonSignal();
        void shockSignal();
};

#endif // AED_H
