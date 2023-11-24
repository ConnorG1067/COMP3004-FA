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


using namespace std;

class AED : public QObject{
    private:
        ElectrodePadPair* electrodePads;
        Victim* victim;

        int batteryLevel = 100;
        bool isOn = false;
        bool correctPadPos = false;
        bool isFunctional = true;
        bool faultyPadPlacement = false;
        bool shockable = false;

    public:
        AED();

        void setShockable(bool);
        bool getShockable();

        void shock();

        bool powerOn();
        void monitorLoop();

        // Self Check
        bool selfCheck();

        VoiceSystem* voiceSystem;

        // Getters & Setters
        bool getIsOn() { return this->isOn; }
        int getBatteryLevel() { return this->batteryLevel; }
        bool getCorrectPadPos() { return this->correctPadPos; }
        bool getIsFunctional() { return this->isFunctional; }
        bool getFaultyPadPlacment() { return this->faultyPadPlacement; }
        ElectrodePadPair* getElectrodePadPair() { return this->electrodePads; }

        Victim* getVictim() { return this->victim; }

        void setBatteryLevel(int newBatteryLevel) { this->batteryLevel = newBatteryLevel; }
        void setIsOn(bool newIsOn) { this->isOn = newIsOn; }
        void setCorrectPadPos(bool padPositioning) { this->correctPadPos = padPositioning; }
        void setIsFunctional(bool newIsFunctional) { this->isFunctional = newIsFunctional; }
        void setFaultyPadPlacement(bool faulty) { this->faultyPadPlacement = faulty; }
        void setVictim(Victim *newVictim) { this->victim = newVictim; };
        void setElectrodePadPair(ElectrodePadPair* newPair) { this->electrodePads = newPair; }

    signals:
        void arythmiaDetected();
};

#endif // AED_H
