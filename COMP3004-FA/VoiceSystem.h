#ifndef VOICESYSTEM_H
#define VOICESYSTEM_H

#include <QObject>
#include <QString>

// In VoiceSystem.h
class AED; // Forward declaration

class VoiceSystem : QObject {
    Q_OBJECT;

    private:
        QString msg;
        AED *aed;
    public:
        VoiceSystem();
        VoiceSystem(QString msg);
        QString getMessage();
        void setMessage(QString *msg);
    signals:
        void voiceUpdate(QString msg);
};

#endif // VOICESYSTEM_H
