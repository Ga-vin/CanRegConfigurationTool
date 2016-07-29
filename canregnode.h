#ifndef CANREGNODE_H
#define CANREGNODE_H

#include <QList>
#include "canreg.h"
class QString;

class CanRegNode
{
public:
    CanRegNode();
    CanRegNode(const QString &mode_name);
    ~CanRegNode();

    void    changeWorkMode(const QString &new_mode_name);
    void    setCurrentMode(const QString &new_mode_name);
    QString getCurrentMode() const;

    QString getRegName() const;
    void    setRegName(const QString &name);

    CanReg  getRegByName(const QString &reg_name);
    CanReg  getRegByOffset(qint32 offset);

    bool    addRegNode(const CanReg reg);

private:
    QString       can_work_mode;
    QList<CanReg> can_reg_lists;
    CanReg        can_reg;
};

#endif // CANREGNODE_H
