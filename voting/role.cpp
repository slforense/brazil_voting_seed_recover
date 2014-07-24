#include "role.h"

Role::Role(int nQnt, QString name) : m_numberQnt(nQnt), m_roleName(name){}

int Role::getQuantity(){
    return m_numberQnt;
}

QString Role::getName(){
    return m_roleName;
}


