#ifndef CANREGNODE_H
#define CANREGNODE_H

#include "canreg.h"
class QString;

class CanRegNode
{
public:
    CanRegNode();
    CanRegNode(const QString &mode_name);
    ~CanRegNode();

    void changeWorkMode(const QString &new_mode_name);
    void setCurrentMode(const QString &new_mode_name);
    QString getCurrentMode() const;

    QString getRegName() const;
    void    setRegName(const QString &name);

private:
    //
    QString can_work_mode;
    CanReg  can_reg;
};

#endif // CANREGNODE_H
