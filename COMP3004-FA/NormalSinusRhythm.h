#ifndef NORMALSINUSRHYTHM_H
#define NORMALSINUSRHYTHM_H

#include <QString>
#include "CardiacArrhythmias.h"

// NormalSinusRhythm class inherits from CardiacArrhythmias
class NormalSinusRhythm : public CardiacArrhythmias {
    // Public functions
    public:
        // Empty constructor
        NormalSinusRhythm(){};
        // Treatment process override
        void treatmentProcedure() override {};
        // Getter override
        QString getConditionName() override { return this->conditionName; }
    // Private member variables
    private:
        QString conditionName = "Normal Sinus Rhythm";
};

#endif // NORMALSINUSRHYTHM_H
