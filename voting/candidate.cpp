#include "candidate.h"

Candidate::Candidate(QString party, QString name, int number) :
    m_party(party),
    m_name(name),
    m_number(number)
{
}

QString Candidate::getName(){
    return m_name;
}

QString Candidate::getParty(){
    return m_party;
}

int Candidate::getNumber(){
    return m_number;
}
