#ifndef VOICESYSTEM_H
#define VOICESYSTEM_H

#include <QObject>
#include <QString>
#include <QMediaPlayer>

// In VoiceSystem.h
class AED; // Forward declaration

// Voice system class
class VoiceSystem : public QObject {
    Q_OBJECT;

    // Private member variables
    private:
        // Text Instructions
        QString currentInstruction;
        // Illustration Path
        QString currentIllustrationPath;
        // AED assoicated with the voice system
        AED *aed;
        // Media player for the VoiceSystem
        QMediaPlayer* audioInstructions;
    // Public functions
    public:
        // Constructors
        explicit VoiceSystem();
        explicit VoiceSystem(QObject*);

        // Getters
        QString getCurrentInstruction() { return this->currentInstruction; };
        QString getCurrentIllustrationPath() { return this->currentIllustrationPath; };
        QMediaPlayer* getAudioInstructions() { return this->audioInstructions; }

        // Setters
        void setCurrentInstruction(QString);
        void setCurrentIllustrationPath(QString);


        // Message function
        void initiateAudioAndTextIntruction(QString, QString, QString);

    // Signals
    signals:
        void textInstructionUpdatedForDisplay();
};

#endif // VOICESYSTEM_H
