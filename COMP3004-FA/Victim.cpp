#include "Victim.h"

int Victim::victimStaticId = 0;

Victim::Victim(int age) {
    this->age = age;

    this->victimId = (victimStaticId)++;
    this->isAdult = (this->age >= 18);
}
