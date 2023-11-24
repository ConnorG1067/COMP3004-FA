#include <QString>
#include "VoiceSystem.h"

VoiceSystem::VoiceSystem() {
    this->setCurrentInstruction("");
    this->audioInstructions = new QMediaPlayer();
}

QString VoiceSystem::getCurrentInstruction(){
    return this->currentInstruction;
}

void VoiceSystem::setCurrentInstruction(QString newInstruction){
    this->currentInstruction = newInstruction;
}

QString VoiceSystem::getCurrentIllustrationPath(){
    return this->currentIllustrationPath;
}

void VoiceSystem::setCurrentIllustrationPath(QString newIllustrationPath){
    this->currentIllustrationPath = newIllustrationPath;
}

void VoiceSystem::initiateAudioAndTextIntruction(QString audioPath, QString illustrationPath, QString currentInstruction){
    this->audioInstructions->setMedia(QUrl(audioPath));
    this->audioInstructions->play();

    this->setCurrentIllustrationPath(illustrationPath);
    this->setCurrentInstruction(currentInstruction);

    emit this->textInstructionUpdatedForDisplay();
}
