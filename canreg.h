#ifndef CANREG_H
#define CANREG_H


class CanReg {
public:
    CanReg(const QString &reg_name, const QString &reg_attr = "RDWR");
    ~CanReg();

    void setRegName(const QString &reg_name);
    QString getRegName() const;

    enum RegRDWDAttr {
        RDONLY = 0x1,
        WRONLY = 0x2,
        RDWR   = 0x3
    };
    void setRegRdWrAttr(const RegRDWDAttr &attr);
    RegRDWDAttr getRegRdWrAttr() const;
    RegRDWDAttr convertStrToAttr(const QString &attr);

private:
    QString     reg_name;
    RegRDWDAttr rdwr_attr;
};

#endif // CANREG_H
