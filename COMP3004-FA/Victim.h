#ifndef VICTIM_H
#define VICTIM_H

#include <stdlib.h>

class Victim{
    public:
        Victim(int);

        int getVictimId() { return victimId; }
    private:
        // Static victim Id
        static int victimStaticId;
        // Id the the victim
        int victimId;
        // Age of victim
        int age;
        // Is adult
        bool isAdult;
};

#endif // VICTIM_H
