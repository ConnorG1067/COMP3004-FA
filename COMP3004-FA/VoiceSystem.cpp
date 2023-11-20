#include <QString>
#include "VoiceSystem.h"

VoiceSystem::VoiceSystem() { this->msg = nullptr; }

VoiceSystem::VoiceSystem(QString msg)
    : msg(msg) {};

void VoiceSystem::setMessage(QString *msg) {
    this->msg = *msg;
    emit this->voiceUpdate(*msg);
}

QString VoiceSystem::getMessage() { return this->msg; }