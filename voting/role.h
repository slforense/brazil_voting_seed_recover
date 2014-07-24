#ifndef ROLE_H
#define ROLE_H

#include <QString>

class Role
{

public:
    Role(int nQnt, QString name);

    int getQuantity();
    QString getName();

private:
    int m_numberQnt;
    QString m_roleName;
};

#endif // ROLE_H
