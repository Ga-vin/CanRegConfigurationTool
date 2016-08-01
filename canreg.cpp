#include <QString>
#include "canreg.h"


CanReg::CanReg()
{
    this->setRegName("None");
    this->setRegRdWrAttr(RDWR);
}

CanReg::CanReg(const QString &reg_name, const QString &attr)
{
    this->setRegName(reg_name);
    this->setRegRdWrAttr(this->convertStrToAttr(attr));
    this->setRegMode(DEFAULT);
    this->setRegBit();
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

QString CanReg::getRegBit(REG_BITS bit) const
{
    switch (bit) {
    case BIT_0:
    case BIT_1:
    case BIT_2:
    case BIT_3:
    case BIT_4:
    case BIT_5:
    case BIT_6:
    case BIT_7:
        return (this->reg_bits.bits[bit]);
    default:
        return QString("");
    }
}

void CanReg::setRegBit()
{
    for (int i = 0; i != MAX_BITS; ++i) {
        this->reg_bits.bits[i] = QString("");
    }
}

void CanReg::setRegBit(const REG_BITS bit, const QString &bit_contents)
{
    switch (bit) {
    case BIT_0:
    case BIT_1:
    case BIT_2:
    case BIT_3:
    case BIT_4:
    case BIT_5:
    case BIT_6:
    case BIT_7:
        this->reg_bits.bits[bit] = bit_contents;
        break;
    default:
        return ;
    }
}

CanReg::RegMode CanReg::getRegMode() const
{
    return (this->reg_mode);
}

void CanReg::setRegMode(const CanReg::RegMode &mode)
{
    switch (mode) {
    case WORK:
    case RESET:
    case DEFAULT:
        if ( this->reg_mode != mode) {
            this->reg_mode = mode;
        }
        break;
    default:
        return ;
    }
}

QString CanReg::convertModeToString(const CanReg::RegMode &mode)
{
    switch (mode) {
    case WORK:
        return (QString("WORK"));

    case RESET:
        return (QString("RESET"));

    default:
        return (QString(""));
    }
}

CanReg::RegMode CanReg::convertStringToMode(const QString &mode)
{
    if ( !mode.isEmpty()) {
        if ( "WORK" == mode.toUpper()) {
            return (WORK);
        } else if ( "RESET" == mode.toUpper()) {
            return (RESET);
        }
    } else {
        return (DEFAULT);
    }
}

qint32 CanReg::getRegOffset() const
{
    return (this->reg_offset);
}

void CanReg::setRegOffset(qint32 offset)
{
    if ( (offset >= 0) && (this->getRegOffset() != offset)) {
        this->reg_offset = offset;
    }
}

CanReg& CanReg::operator =(const CanReg &reg)
{
    if ( this != &reg) {
        this->setRegName(reg.getRegName());
        this->setRegOffset(reg.getRegOffset());
        for (int i = 0; i != MAX_BITS; ++i) {
            this->setRegBit(REG_BITS(i), reg.getRegBit(REG_BITS(i)));
        }
        this->setRegMode(reg.getRegMode());
        this->setRegRdWrAttr(reg.getRegRdWrAttr());

        return (*this);
    } else {
        return (*this);
    }
}
