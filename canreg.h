#ifndef CANREG_H
#define CANREG_H

class QString;

enum REG_BITS {
    BIT_0    = 0x0,
    BIT_1    = 0x1,
    BIT_2    = 0x2,
    BIT_3    = 0x3,
    BIT_4    = 0x4,
    BIT_5    = 0x5,
    BIT_6    = 0x6,
    BIT_7    = 0x7,
    MAX_BITS = 0x8
};

struct CanRegBits {
    QString bits[MAX_BITS];
};

class CanReg {
public:
    CanReg();
    CanReg(const QString &reg_name, const QString &reg_attr = "RDWR");
    ~CanReg();

    void        setRegName(const QString &reg_name);
    QString     getRegName() const;

    enum RegRDWDAttr {
        RDONLY  = 0x1,
        WRONLY  = 0x2,
        RDWR    = 0x3
    };
    enum RegMode {
        WORK    = 0x1,
        RESET   = 0x2,
        DEFAULT = 0x3
    };

    void        setRegRdWrAttr(const RegRDWDAttr &attr);
    RegRDWDAttr getRegRdWrAttr() const;
    RegRDWDAttr convertStrToAttr(const QString &attr);

    QString     getRegBit(const REG_BITS bit);
    void        setRegBit();
    void        setRegBit(const REG_BITS bit, const QString &bit_contents);

    RegMode     getRegMode() const;
    void        setRegMode(const RegMode &mode);
    QString     convertModeToString(const RegMode &mode);
    RegMode     convertStringToMode(const QString &mode);

    qint32      getRegOffset() const;
    void        setRegOffset(qint32 offset);

private:
    QString     reg_name;
    RegRDWDAttr rdwr_attr;
    CanRegBits  reg_bits;
    RegMode     reg_mode;
    qint32      reg_offset;
};

#endif // CANREG_H
