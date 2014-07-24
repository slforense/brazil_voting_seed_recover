#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <QString>

class Candidate
{
public:
    Candidate(QString party, QString name, int number);

    QString getName();
    QString getParty();
    int getNumber();

private:
    QString m_party;
    QString m_name;
    int m_number;
};

#endif // CANDIDATE_H
