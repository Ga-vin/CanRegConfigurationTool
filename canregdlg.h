#ifndef CANREGDLG_H
#define CANREGDLG_H


#include <QDialog>
#include <QList>

#include "canregnode.h"

class QWidget;
class QTableWidget;
class QGroupBox;
class QTextEdit;
class QComboBox;
class QString;
class QFile;
class QStringList;
class QDomDocument;

class CanRegDlg : public QDialog
{
    Q_OBJECT

public:
    CanRegDlg(QWidget *parent = 0);
    ~CanRegDlg();

    bool openFile();
    bool loadFile();
    bool parseXml(QFile &file);

    QString getFileName() const;
    void setFileName(const QString &file_name);

    QStringList getCanModeLists(QDomDocument &document);

    bool addRowItem(QTableWidget *p_object, int row, int col, const QString &contents);

    void displayCanMode(const QStringList &mode_lists);
    void displayCanRegs(const QStringList &reg_lists);

public slots:
    //

private:
    void initWidgets();

    QGroupBox    *p_grp_can_mode;
    QGroupBox    *p_grp_can_regs;
    QGroupBox    *p_grp_can_sub_items;

    QTableWidget *p_tab_can_mode;
    QTableWidget *p_tab_can_regs;
    QTableWidget *p_tab_can_sub_items;

    QTextEdit    *p_txt_can_mode;
    QTextEdit    *p_txt_can_regs;
    QTextEdit    *p_txt_can_sub_items;

    QComboBox    *p_com_bit_value;

    QString       file_name;

    QList<CanRegNode> can_reg_nodes;
};

#endif // CANREGDLG_H
