#ifndef AED_H
#define AED_H

#include <QObject>
#include <ElectrodePad.h>
#include <vector>
#include "VoiceSystem.h"
#include "Victim.h"

using namespace std;

class AED : QObject{
    private:
        vector<ElectrodePad*>* pads;
        VoiceSystem *voiceSystem;
        Victim *victim;

        int batteryLevel = 100;
        bool isOn = false;
        bool correctPadPos = false;
        bool isFunctional = true;
    public:
        AED();
        bool powerOn();
        void monitorLoop();
        void shock();

        void setVictim(Victim *victim);
        void setVoice(QString *msg);
        // I imagine the UI will be much more complex, and that this function will ultimately get eliminated
        // When the UI comes in, we'll be able to add the change.
        // TODO: Change this func so it suits the real UI
        void setDisplay(QString *msg);
        void addPad(ElectrodePad *pad);
        void delPad();
        void delAllPads();
        void setPads(QVector<ElectrodePad> *pads);

        // Self Check
        bool selfCheck();


        // Getters & Setters
        bool getIsOn() { return this->isOn; }
        int getBatteryLevel() { return this->batteryLevel; }
        bool getCorrectPadPos() { return this->correctPadPos; }
        bool getIsFunctional() { return this->isFunctional; }

        void setBatteryLevel(int newBatteryLevel) { this->batteryLevel = newBatteryLevel; }
        void setGetIsOn(bool newIsOn) { this->batteryLevel = newIsOn; }
        void setCorrectPadPos(bool padPositioning) { this->correctPadPos = padPositioning; }
        void setIsFunctional(bool newIsFunctional) { this->isFunctional = newIsFunctional; }

    signals:
        void arythmiaDetected();
};

#endif // AED_H
