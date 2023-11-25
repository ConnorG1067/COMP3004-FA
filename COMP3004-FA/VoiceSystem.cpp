#include <QString>
#include "VoiceSystem.h"

// VoiceSystem constructor
VoiceSystem::VoiceSystem() {
    // Set the instruction to empty and initalize a media player
    this->setCurrentInstruction("");
    this->audioInstructions = new QMediaPlayer();
}

// Get the currentInstruction
QString VoiceSystem::getCurrentInstruction(){
    return this->currentInstruction;
}

// Set the current instruction
void VoiceSystem::setCurrentInstruction(QString newInstruction){
    this->currentInstruction = newInstruction;
}

// Get the current illustrationPath
QString VoiceSystem::getCurrentIllustrationPath(){
    return this->currentIllustrationPath;
}

// Set the currentIllustrationPath
void VoiceSystem::setCurrentIllustrationPath(QString newIllustrationPath){
    this->currentIllustrationPath = newIllustrationPath;
}

// TTS/Images/Text
void VoiceSystem::initiateAudioAndTextIntruction(QString audioPath, QString illustrationPath, QString currentInstruction){
    // Set the audio to the audio path
    this->audioInstructions->setMedia(QUrl(audioPath));
    // Play the media
    this->audioInstructions->play();
    // Set the IllustrationPath and currentInstruction to the corressponding values
    this->setCurrentIllustrationPath(illustrationPath);
    this->setCurrentInstruction(currentInstruction);

    // emit the display update for mainwindow.h
    emit this->textInstructionUpdatedForDisplay();
}
