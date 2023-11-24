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

void VoiceSystem::initiateAudioAndTextIntruction(QString audioPath, QString imagePath, QString currentInstruction){
    this->audioInstructions->setMedia(QUrl(audioPath));
    this->audioInstructions->play();
    this->setCurrentInstruction(currentInstruction);
    emit this->textInstructionUpdatedForDisplay();
}
