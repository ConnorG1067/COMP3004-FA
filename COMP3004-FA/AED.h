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


class AED : public QObject {
    Q_OBJECT;

    private:
        ElectrodePadPair* electrodePads;
        Victim* victim;
        VoiceSystem* voiceSystem;

        int batteryLevel = 100;
        bool isOn = false;
        bool correctPadPos = false;
        bool isFunctional = true;
        bool faultyPadPlacement = false;
        bool readyForShock = false;
        bool shockAdministered = false;

    public:
        explicit AED();
        void shock();

        bool powerOn();
        void monitorLoop();

        // Self Check
        bool selfCheck();

        // Getters & Setters
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

        void setIsReadyForShock(bool isReady);

        void setBatteryLevel(int newBatteryLevel) { this->batteryLevel = newBatteryLevel; }
        void setIsOn(bool newIsOn) { this->isOn = newIsOn; }
        void setCorrectPadPos(bool padPositioning) { this->correctPadPos = padPositioning; }
        void setIsFunctional(bool newIsFunctional) { this->isFunctional = newIsFunctional; }
        void setFaultyPadPlacement(bool faulty) { this->faultyPadPlacement = faulty; }
        void setVictim(Victim *newVictim) { this->victim = newVictim; };
        void setElectrodePadPair(ElectrodePadPair* newPair) { this->electrodePads = newPair; }
        void setShockAdministered(bool newShockAdministered) { this->shockAdministered = newShockAdministered; }

    signals:
        void arythmiaDetected();
        void flashShockButtonSignal();
        void shockSignal();
};

#endif // AED_H
