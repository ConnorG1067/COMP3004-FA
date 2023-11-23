#ifndef NORMALSINUSRHYTHM_H
#define NORMALSINUSRHYTHM_H

#include <QString>
#include "CardiacArrhythmias.h"

class NormalSinusRhythm : public CardiacArrhythmias {
    public:
        NormalSinusRhythm(){};

        void treatmentProcedure() override {};
        QString getConditionName() override { return this->conditionName; }
    private:
        QString conditionName = "Normal Sinus Rhythm";
};

#endif // NORMALSINUSRHYTHM_H
