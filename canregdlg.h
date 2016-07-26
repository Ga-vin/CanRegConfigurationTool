#ifndef CANREGDLG_H
#define CANREGDLG_H


#include <QDialog>

class QWidget;
class QTableWidget;
class QGroupBox;
class QTextEdit;
class QComboBox;
class QString;
class QFile;

class CanRegDlg : public QDialog
{
    Q_OBJECT

public:
    CanRegDlg(QWidget *parent = 0);
    ~CanRegDlg();

    bool openFile();
    bool loadFile();
    bool parseXml(const QFile &file);

    QString getFileName() const;
    void setFileName(const QString &file_name);

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
};

#endif // CANREGDLG_H
