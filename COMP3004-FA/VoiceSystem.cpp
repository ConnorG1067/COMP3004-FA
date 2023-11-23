#include <QString>
#include "VoiceSystem.h"

VoiceSystem::VoiceSystem() {
    this->setCurrentInstruction("beans");
    this->audioInstructions = new QMediaPlayer();
}

QString VoiceSystem::getCurrentInstruction(){
    return this->currentInstruction;
}

void VoiceSystem::setCurrentInstruction(QString newInstruction){
    this->currentInstruction = newInstruction;
}

void VoiceSystem::analyzingHeartRhythmDoNotTouch(){
    this->audioInstructions->setMedia(QUrl("qrc:/src/audios/analyzingHeartRhythmDoNotTouch.mp3"));
    this->audioInstructions->play();
    this->setCurrentInstruction("Analyzing Heart Rhythm. Do not touch patient.");
    emit this->textInstructionUpdatedForDisplay();
}
void VoiceSystem::applyPadsToPatientsBareChest(){
    this->audioInstructions->setMedia(QUrl("qrc:/src/audios/applyPadsToPatientsBareChest.mp3"));
    this->audioInstructions->play();
    this->setCurrentInstruction("Analyzing Heart Rhythm. Do not touch patient.");
    emit this->textInstructionUpdatedForDisplay();
}

void VoiceSystem::shockAdvisedChargingStandClear(){
    this->audioInstructions->setMedia(QUrl("qrc:/src/audios/shockAdvisedChargingStandClear.mp3"));
    this->audioInstructions->play();
    this->setCurrentInstruction("Analyzing Heart Rhythm. Do not touch patient.");
    emit this->textInstructionUpdatedForDisplay();
}

void VoiceSystem::shockOneDeliveredBeginCPR(){
    this->audioInstructions->setMedia(QUrl("qrc:/src/audios/shockOneDeliveredBeginCPR.mp3"));
    this->audioInstructions->play();
    this->setCurrentInstruction("Analyzing Heart Rhythm. Do not touch patient.");
    emit this->textInstructionUpdatedForDisplay();
}
