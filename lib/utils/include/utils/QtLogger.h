#ifndef QTLOGGER_H
#define QTLOGGER_H

#include "Log.h"

class QtLogger: public Logger

{
public: 
    void processLog(const Log& log) override;
    ~QtLogger();

};

#endif // QTLOGGER_H
