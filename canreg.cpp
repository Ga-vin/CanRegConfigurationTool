#include <QString>
#include "canreg.h"


CanReg::CanReg(const QString &reg_name, const QString &attr)
{
    this->setRegName(reg_name);
    this->setRegRdWrAttr(this->convertStrToAttr(attr));
}

CanReg::~CanReg()
{

}

void CanReg::setRegName(const QString &reg_name)
{
    if ( !reg_name.isEmpty() && this->getRegName() != reg_name) {
        this->reg_name = reg_name;
    }
}

QString CanReg::getRegName() const
{
    return (this->reg_name);
}

void CanReg::setRegRdWrAttr(const CanReg::RegRDWDAttr &attr)
{
    switch (attr) {
    case RDONLY:
    case WRONLY:
    case RDWR:
        this->rdwr_attr = attr;
        break;
    default:
        break;
    }
}

CanReg::RegRDWDAttr CanReg::getRegRdWrAttr() const
{
    return (this->rdwr_attr);
}

CanReg::RegRDWDAttr CanReg::convertStrToAttr(const QString &attr)
{
    if ( "rdonly" == attr.toLower()) {
        return (RDONLY);
    } else if ( "wronly" == attr.toLower()) {
        return (WRONLY);
    } else if ( "rdwr" == attr.toLower()) {
        return (RDWR);
    } else {
        return (RDWR);
    }
}
