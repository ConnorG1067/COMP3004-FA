#include "Victim.h"

int Victim::victimStaticId = 0;

Victim::Victim(int age, CardiacArrhythmias* condition) {
    this->age = age;
    this->condition = condition;
    this->victimId = (victimStaticId)++;
    this->isAdult = (this->age >= 19);
    this->name = generateRandomName();
}


string Victim::generateRandomName(){
    vector<string> names = {"Alice", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Hank", "Ivy", "Jack"};
    return names[rand() % names.size()];
}
