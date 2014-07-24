#include "report.h"

#include <Qtime>
#include <QDebug>
#include <QJsonDocument>

Report::Report()
{
}

void Report::generateZeresima(){
    QDateTime date =  QDateTime::currentDateTime();
    qDebug() << date.toString();
}
