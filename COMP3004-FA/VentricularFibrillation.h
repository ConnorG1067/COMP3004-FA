#ifndef VENTRICULARFIBRILLATION_H
#define VENTRICULARFIBRILLATION_H

#include "CardiacArrhythmias.h"

class VentricularFibrillation : public CardiacArrhythmias{
    public:
        VentricularFibrillation() {};
        void treatmentProcedure() override {};
        QString getConditionName() override { return this->conditionName; }
    private:
        QString conditionName = "Ventricular Fibrillation";

};

#endif // VENTRICULARFIBRILLATION_H
