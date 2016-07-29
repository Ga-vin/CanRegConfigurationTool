#include <cstdlib>
#include <QString>
#include "canregnode.h"


CanRegNode::CanRegNode()
    :can_reg("")
{
    this->can_work_mode = QString("Default");
}

CanRegNode::CanRegNode(const QString &mode_name)
    :can_reg("")
{
    this->setCurrentMode(mode_name);
}

CanRegNode::~CanRegNode()
{

}

void CanRegNode::changeWorkMode(const QString &new_mode_name)
{
    if ( (!new_mode_name.isEmpty()) && (new_mode_name != this->getCurrentMode())) {
        this->can_work_mode = new_mode_name;

        return ;
    }
}

void CanRegNode::setCurrentMode(const QString &new_mode_name)
{
    this->can_work_mode = new_mode_name;
}

QString CanRegNode::getCurrentMode() const
{
    return (this->can_work_mode);
}

QString CanRegNode::getRegName() const
{
    return (this->can_reg.getRegName());
}

void CanRegNode::setRegName(const QString &name)
{
    if ( (!name.isEmpty()) && (this->can_reg.getRegName() != name)) {
        this->can_reg.setRegName(name);
    }
}

CanReg CanRegNode::getRegByName(const QString &reg_name)
{
    CanReg can_node;
    for (QList<CanReg>::const_iterator iter = this->can_reg_lists.begin(); iter != this->can_reg_lists.end(); ++iter) {
        can_node = *iter;
        if ( reg_name == can_node.getRegName()) {
            return (can_node);
        }
    }

    return (can_node);
}

CanReg CanRegNode::getRegByOffset(qint32 offset)
{
    CanReg reg_node;
    if ( offset >= 0) {
        for (QList<CanReg>::const_iterator iter= this->can_reg_lists.begin(); iter != this->can_reg_lists.end(); ++iter) {
            reg_node = *iter;
            if ( offset == reg_node.getRegOffset()) {
                return (reg_node);
            }
        }
    }

    return (reg_node);
}

bool CanRegNode::addRegNode(const CanReg reg)
{
    if ( !reg.getRegName().isEmpty()) {
        this->can_reg_lists.append(reg);

        return (true);
    } else {
        return (false);
    }
}
