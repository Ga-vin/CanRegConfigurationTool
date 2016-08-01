#include <QtGui>
#include <QtCore>
#include <QTextCodec>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QtXml/QDomNode>

#include "canregdlg.h"

CanRegDlg::CanRegDlg(QWidget *parent)
    :QDialog(parent),
      file_name("")
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    this->initWidgets();

    this->setWindowTitle(QObject::tr("CAN总线寄存器配置工具 --- By Gaivn.Bai"));
    this->resize(1000, 800);
    this->setWindowIcon(QIcon(":/images/main.png"));

    this->openFile();
    this->loadFile();
}

CanRegDlg::~CanRegDlg()
{
    delete this->p_tab_can_mode;
    delete this->p_tab_can_regs;
    delete this->p_tab_can_sub_items;

    delete this->p_txt_can_mode;
    delete this->p_txt_can_regs;
    delete this->p_txt_can_sub_items;

    delete this->p_grp_can_mode;
    delete this->p_grp_can_regs;
    delete this->p_grp_can_sub_items;

    delete this->p_com_bit_value;
}

bool CanRegDlg::openFile()
{
    QString file_name = QFileDialog::getOpenFileName(0,
                                                     QObject::tr("选择打开的文件"),
                                                     QObject::tr("请选择一个文件来打开"),
                                                     QString(QObject::tr("Xml文件(*.xml)")));
    if ( file_name.isEmpty()) {
        QMessageBox::warning(0,
                             QObject::tr("错误提示"),
                             QObject::tr("选择的文件为空"));

        return (false);
    } else {
        this->setFileName(file_name);

        return (true);
    }
}

bool CanRegDlg::loadFile()
{
    if ( !this->getFileName().isEmpty()) {
        QFile file(this->getFileName());
        if ( !file.open(QIODevice::Text | QIODevice::ReadOnly)) {
            QMessageBox::warning(0,
                                 QObject::tr("错误提示"),
                                 QObject::tr("无法打开文件:%1 -- %2").arg(this->getFileName()).arg(file.errorString()));

            return (false);
        }

        if ( !this->parseXml(file)) {
            QMessageBox::warning(0,
                                 QObject::tr("错误提示"),
                                 QObject::tr("无法解析XML文件"));

            return (false);
        }
    } else {
        QMessageBox::warning(0,
                             QObject::tr("错误提示"),
                             QObject::tr("文件名为空"));

        return (false);
    }

    return (false);
}

bool CanRegDlg::parseXml(QFile &file)
{
    if ( !file.isOpen()) {
        QMessageBox::warning(0,
                             QObject::tr("错误提示"),
                             QObject::tr("文件还没有被打开"));

        return (false);
    }

    QDomDocument document;
    int          row;
    int          col;
    QString      error;
    if ( !document.setContent(&file, false, &error, &row, &col)) {
        QMessageBox::warning(0,
                             QObject::tr("错误提示"),
                             QObject::tr("解析XML文件错误发生于%1行%2列").arg(row).arg(col));

        return (false);
    }

    /* 从XML文件中获取相应每个节点的具体细节 */
    /* 获取各个模式 */
    QStringList mode_names = this->getCanModeLists(document);
    if ( mode_names.count() > 0) {
        for (int i = 0; i != mode_names.count(); ++i) {
            CanRegNode mode(mode_names.at(i));
            QList<CanReg> lists = this->getCanRegLists(document, mode_names.at(i));
            if ( lists.count() > 0) {
                for (int j = 0; j != lists.count(); ++j) {
                    mode.addRegNode(lists.at(j));
                }
            }
            this->can_reg_nodes.append(mode);
        }

        this->displayCanMode(mode_names);
        return (true);
    } else {
        return (false);
    }

    return (false);
}

QString CanRegDlg::getFileName() const
{
    return (this->file_name);
}

void CanRegDlg::setFileName(const QString &file_name)
{
    if ( this->getFileName() != file_name) {
        this->file_name = file_name;
    }
}

QStringList CanRegDlg::getCanModeLists(QDomDocument &document)
{
    QStringList mode_names;

    if ( document.isNull()) {
        QMessageBox::warning(0,
                             QObject::tr("错误提示"),
                             QObject::tr("该XML文件为空"));

        return (mode_names);
    }

    QDomElement  root = document.documentElement();
    QDomNodeList node_list = root.childNodes();
    for (int i = 0; i != node_list.count(); ++i) {
        QDomNode item = node_list.at(i);
        qDebug() << "Tag: " << item.toElement().attribute("mode");
        mode_names.append(item.toElement().attribute("mode"));
    }

    return (mode_names);
}

QList<CanReg> CanRegDlg::getCanRegLists(QDomDocument &document, const QString &mode_name)
{
    QList<CanReg> reg_list;

    if ( !document.isNull()) {
        QDomElement root = document.documentElement();
        /* 获取各种模式 */
        QDomNodeList top_node_list = root.childNodes();
        if ( top_node_list.count() > 0) {
            for ( int i = 0; i != top_node_list.count(); ++i) {
                //qDebug() << "Get Reg Lists: " << top_node_list.at(i).toElement().tagName() << " Mode name: " << mode_name;
                if ( mode_name == top_node_list.at(i).toElement().attribute("mode")) {
                    if ( top_node_list.at(i).hasChildNodes()) {
                        /* 获取特定模式下的各个寄存器 */
                        QDomNodeList sub_node_list = top_node_list.at(i).childNodes();
                        //qDebug() << "Mode: " << mode_name << "Sub_Node Count: " << sub_node_list.count();
                        if ( sub_node_list.count() > 0) {
                            CanReg sub_reg;
                            for (int j = 0; j != sub_node_list.count(); ++j) {
                                QDomNode sub_node = sub_node_list.at(j);    /* 寄存器节点 */
                                //qDebug() << sub_node.toElement().attribute("name");

                                /* 获取对应该寄存器下的相应特性 */
                                sub_reg = this->getCanReg(sub_node.childNodes());
                                sub_reg.setRegName(sub_node.toElement().attribute("name"));
                                this->dispalyReg(sub_reg);
                            }
                            reg_list.append(sub_reg);
                        }
                    }
                }
            }
        }
    }

    return (reg_list);
}

bool CanRegDlg::addRowItem(QTableWidget *p_object, int row, int col, const QString &contents)
{
    if ( row > p_object->rowCount()) {
        QMessageBox::warning(0,
                             QObject::tr("错误提示"),
                             QObject::tr("行数已经超过最大行数"));

        return (false);
    }

    if ( !contents.isEmpty()) {
        p_object->setItem(row, col, new QTableWidgetItem(contents));

        return (true);
    } else {
        return (false);
    }
}

void CanRegDlg::displayCanMode(const QStringList &mode_lists)
{
    this->p_tab_can_mode->setRowCount(mode_lists.count());
    for (int i = 0; i != mode_lists.count(); ++i) {
        this->addRowItem(this->p_tab_can_mode, i, 0, mode_lists.at(i));
    }
}

void CanRegDlg::displayCanRegs(const QStringList &reg_lists)
{

}

CanRegNode CanRegDlg::getCanRegNodeByMode(const QString &mode_name)
{
    CanRegNode reg_node;
    for (QList<CanRegNode>::const_iterator iter = this->can_reg_nodes.begin(); iter != this->can_reg_nodes.end(); ++iter) {
        reg_node = *iter;
        if ( mode_name == reg_node.getCurrentMode()) {
            return (reg_node);
        }
    }

    return (reg_node);
}

CanReg CanRegDlg::getCanReg(const QDomNodeList &nodes)
{
    CanReg reg;
    bool   ok = false;

    if ( nodes.count() > 0) {
        for (int i = 0; i != nodes.count(); ++i) {
            QDomElement element = nodes.at(i).toElement();
            if ( "OFFSET" == element.tagName()) {
                reg.setRegOffset(element.text().toInt(&ok, 16));
                //qDebug() << "Convert: " << element.text().toInt(&ok, 16);
            } else if ( "PROPERTY" == element.tagName()) {
                reg.setRegRdWrAttr(reg.convertStrToAttr(element.text()));
                //qDebug() << "Attr: " << element.text();
            } else if ( "WORK" == element.tagName()) {
                /* 解析工作模式下该寄存器各个位的含义 */
                /* Todo here */

            } else if ( "RESET" == element.tagName()) {
                /* 解析复位模式下该寄存器各个位的含义 */
                /* Todo here */

            }
        }
    }

    return reg;
}

bool CanRegDlg::addCanRegNode(const CanRegNode &node)
{
    if ( !node.getCurrentMode().isEmpty()) {
        this->can_reg_nodes.append(node);

        return (true);
    } else {
        return (false);
    }
}

void CanRegDlg::dispalyReg(const CanReg &reg)
{
    qDebug() << "Name: " << reg.getRegName();
    qDebug() << "Offset: " << reg.getRegOffset();
    qDebug() << "Attr: " << reg.getRegRdWrAttr();
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
