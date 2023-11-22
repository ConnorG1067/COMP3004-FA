#ifndef ERROR_H
#define ERROR_H

#include <QString>

class Error {
    public:
        virtual void errorProcedure() = 0;
    private:
        QString errorMessage;
};

#endif // ERROR_H
