#ifndef VENTRICULARTACHYCARDIA_H
#define VENTRICULARTACHYCARDIA_H

#include "CardiacArrhythmias.h"

// VentricularTachycardia class inherits from CardiacArrhythmias
class VentricularTachycardia : public CardiacArrhythmias{
    // Public functions
    public:
        // Empty constructor
        VentricularTachycardia() {};
        // Treatment process override
        void treatmentProcedure() override {};
        // Getter override
        QString getConditionName() override { return this->conditionName; }
    // Private member variables
    private:
        QString conditionName = "Ventricular Tachycardia";
};

#endif // VENTRICULARTACHYCARDIA_H
