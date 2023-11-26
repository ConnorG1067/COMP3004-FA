#ifndef CARDIACARRHYTHMIAS_H
#define CARDIACARRHYTHMIAS_H

#include <QString>

// CardiacArrhythmias class
class CardiacArrhythmias {
    // Public functions
    public:
        // Constructor
        CardiacArrhythmias() {};
        // Virtual void functions
        virtual void treatmentProcedure() = 0;
        virtual QString getConditionName() = 0;
    // Private member variables
    private:
        QString conditionName;
};


#endif // CARDIACARRHYTHMIAS_H
