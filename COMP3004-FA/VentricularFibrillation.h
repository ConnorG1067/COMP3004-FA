#ifndef VENTRICULARFIBRILLATION_H
#define VENTRICULARFIBRILLATION_H

#include "CardiacArrhythmias.h"

// VentricularFibrillation class inherits from CardiacArrhythmias
class VentricularFibrillation : public CardiacArrhythmias{
    // Public functions
    public:
        // Empty constructor
        VentricularFibrillation() {};
        // Treatment process override
        void treatmentProcedure() override {};
        // Getter override
        QString getConditionName() override { return this->conditionName; }
    // Private member variables
    private:
        QString conditionName = "Ventricular Fibrillation";

};

#endif // VENTRICULARFIBRILLATION_H
