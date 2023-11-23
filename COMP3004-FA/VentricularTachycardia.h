#ifndef VENTRICULARTACHYCARDIA_H
#define VENTRICULARTACHYCARDIA_H

#include "CardiacArrhythmias.h"

class VentricularTachycardia : public CardiacArrhythmias{
    public:
        VentricularTachycardia() {};
        void treatmentProcedure() override {};
        QString getConditionName() override { return this->conditionName; }
    private:
        QString conditionName = "Ventricular Tachycardia";
};

#endif // VENTRICULARTACHYCARDIA_H
