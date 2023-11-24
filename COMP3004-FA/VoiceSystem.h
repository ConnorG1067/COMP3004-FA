#ifndef VOICESYSTEM_H
#define VOICESYSTEM_H

#include <QObject>
#include <QString>
#include <QMediaPlayer>

// In VoiceSystem.h
class AED; // Forward declaration

class VoiceSystem : public QObject {
    Q_OBJECT;

    private:
        QString currentInstruction;
        AED *aed;
        QMediaPlayer* audioInstructions;

    public:
        explicit VoiceSystem();
        explicit VoiceSystem(QObject*);

        QString getCurrentInstruction();
        void setCurrentInstruction(QString);

        // Message functions
        void initiateAudioAndTextIntruction(QString, QString);

    signals:
        void textInstructionUpdatedForDisplay();
};

#endif // VOICESYSTEM_H
