#ifndef VICTIM_H
#define VICTIM_H

#include <stdlib.h>
#include "CardiacArrhythmias.h"
#include <vector>

using namespace std;


// Victim class
class Victim{
    // Public functions
    public:
        // Constructor
        Victim(int, CardiacArrhythmias*);

        // Getters
        int getVictimId() { return this->victimId; }
        int getAge() { return this->age; }
        string getName() { return this->name; }
        CardiacArrhythmias* getCondition() { return this->condition; }

        // Random name generator
        static string generateRandomName();
    // Private member variables
    private:
        // Static victim Id
        static int victimStaticId;
        // Name of victim
        string name;
        // Id the the victim
        int victimId;
        // Age of victim
        int age;
        // Condition of the victim
        CardiacArrhythmias* condition;
        // Is adult
        bool isAdult;
};

#endif // VICTIM_H
