#include "Victim.h"

// Victim static Id
int Victim::victimStaticId = 0;

// Victim Constructor
Victim::Victim(int age, CardiacArrhythmias* condition) {
    // Set the age, condition, victim id and some random name
    this->age = age;
    this->condition = condition;
    this->victimId = (victimStaticId)++;
    this->name = generateRandomName();
}

// Generates a random name
string Victim::generateRandomName(){
    vector<string> names = {"Alice", "Bob", "Charlie", "David", "Eva", "Frank", "Grace", "Hank", "Ivy", "Jack"};
    return names[rand() % names.size()];
}
