#ifndef CARDIACARRHYTHMIAS_H
#define CARDIACARRHYTHMIAS_H

#include <QString>

class CardiacArrhythmias {
    public:
        CardiacArrhythmias() {};
        virtual void treatmentProcedure() = 0;
        virtual QString getConditionName() = 0;
    private:
        QString conditionName;
};


#endif // CARDIACARRHYTHMIAS_H
