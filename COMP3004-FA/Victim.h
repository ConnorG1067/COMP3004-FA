#ifndef VICTIM_H
#define VICTIM_H

#include <stdlib.h>
#include "CardiacArrhythmias.h"
#include <vector>

using namespace std;



class Victim{
    public:
        Victim(int, CardiacArrhythmias*);

        int getVictimId() { return this->victimId; }
        int getAge() { return this->age; }
        string getName() { return this->name; }
        CardiacArrhythmias* getCondition() { return this->condition; }

        static string generateRandomName();
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
