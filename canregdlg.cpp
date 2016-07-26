#include <QtGui>
#include <QtCore>
#include <QTextCodec>

#include "canregdlg.h"

CanRegDlg::CanRegDlg(QWidget *parent)
    :QDialog(parent)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    this->initWidgets();

    this->setWindowTitle(QObject::tr("CAN总线寄存器配置工具 --- By Gaivn.Bai"));
    this->resize(1000, 800);
}

CanRegDlg::~CanRegDlg()
{

}

void CanRegDlg::initWidgets()
{
    p_grp_can_mode = new QGroupBox(QObject::tr("Can模式显示"));
    p_grp_can_regs = new QGroupBox(QObject::tr("Can寄存器显示"));
    p_grp_can_sub_items = new QGroupBox(QObject::tr("子项目"));

    /* Can 模式设置 */
    p_tab_can_mode = new QTableWidget(0, 1);
    p_tab_can_mode->setHorizontalHeaderItem(0, new QTableWidgetItem(QObject::tr("模式名称")));
    p_txt_can_mode = new QTextEdit;
    p_txt_can_mode->setReadOnly(true);

    QVBoxLayout *p_layout_mode = new QVBoxLayout;
    p_layout_mode->addWidget(p_tab_can_mode);
    p_layout_mode->addWidget(p_txt_can_mode);
    p_grp_can_mode->setLayout(p_layout_mode);

    /* Can寄存器设置 */
    p_tab_can_regs = new QTableWidget(0, 2);
    p_tab_can_regs->setHorizontalHeaderItem(0, new QTableWidgetItem(QObject::tr("寄存器名称")));
    p_tab_can_regs->setHorizontalHeaderItem(1, new QTableWidgetItem(QObject::tr("读写方式")));
    p_txt_can_regs = new QTextEdit;
    p_txt_can_regs->setReadOnly(true);

    QVBoxLayout *p_layout_regs = new QVBoxLayout;
    p_layout_regs->addWidget(p_tab_can_regs);
    p_layout_regs->addWidget(p_txt_can_regs);
    p_grp_can_regs->setLayout(p_layout_regs);

    /* Can子项设置 */
    p_tab_can_sub_items = new QTableWidget(0, 2);
    p_tab_can_sub_items->setHorizontalHeaderItem(0, new QTableWidgetItem(QObject::tr("子项")));
    p_tab_can_sub_items->setHorizontalHeaderItem(1, new QTableWidgetItem(QObject::tr("子项值")));

    QVBoxLayout *p_layout_sub_items = new QVBoxLayout;
    p_layout_sub_items->addWidget(p_tab_can_sub_items);
    p_grp_can_sub_items->setLayout(p_layout_sub_items);

    QLabel *p_lab_bit_value = new QLabel(QObject::tr("值:"));
    p_com_bit_value = new QComboBox;
    QHBoxLayout *p_layout_value = new QHBoxLayout;
    p_layout_value->addWidget(p_lab_bit_value);
    p_layout_value->addWidget(p_com_bit_value);

    p_txt_can_sub_items = new QTextEdit;
    p_txt_can_sub_items->setReadOnly(true);

    QVBoxLayout *p_layout_left = new QVBoxLayout;
    p_layout_left->addWidget(p_grp_can_mode);
    p_layout_left->addWidget(p_grp_can_regs);

    QVBoxLayout *p_layout_right = new QVBoxLayout;
    p_layout_right->addWidget(p_grp_can_sub_items);
    p_layout_right->addLayout(p_layout_value);
    p_layout_right->addWidget(p_txt_can_sub_items);

    QHBoxLayout *p_layout = new QHBoxLayout;
    p_layout->addLayout(p_layout_left);
    p_layout->addLayout(p_layout_right);

    this->setLayout(p_layout);
}
