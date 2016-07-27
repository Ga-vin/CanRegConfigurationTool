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
