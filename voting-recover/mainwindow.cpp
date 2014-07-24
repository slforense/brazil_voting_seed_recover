#include <QFileDialog>
#include <QFile>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->ui_pb_check, SIGNAL(clicked()), this, SLOT(btCheckSlot()));
    connect(ui->ui_pb_file, SIGNAL(clicked()), this, SLOT(loadResultSlot()));

    ui->ui_sp_time_margin->setMinimum(0);
    ui->ui_sp_time_margin->setMaximum(3600);

    ui->ui_sp_time_margin->setValue(100);
    ui->ui_pb_check->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btCheckSlot(){
    ui->ui_pb_check->setEnabled(false);
    int vote[MAX_VOTES];

    //Existe documento
    vote[0] = ui->ui_le_dep_dis->text().toInt();
    vote[1] = ui->ui_le_dep_fed->text().toInt();
    vote[2] = ui->ui_le_senador1->text().toInt();
    vote[3] = ui->ui_le_senador2->text().toInt();
    vote[4] = ui->ui_le_governador->text().toInt();
    vote[5] = ui->ui_le_presidente->text().toInt();

    int pos = ui->ui_le_pos->text().toInt();
    findMatches(vote, pos);

    ui->ui_pb_check->setEnabled(true);
}

void MainWindow::resetAuxVotes(){
    for (int i = 0; i < MAX_VOTE; i++)
        for (int j = 0; j < MAX_VOTES; j++)
            m_auxVotes[i][j] = -2;

}

void MainWindow::fillAuxVotes(int pos){
    int index;

    for (int i = 0; i < pos; i++) {
        for (int j = 0; j < MAX_VOTES; j++){
            index = getFreePos(m_auxVotes, rand() % MAX_VOTE, j);
            m_auxVotes[index][j] = 0;
        }
    }
}


void MainWindow::findMatches(int vote[MAX_VOTES], int pos){
    int index;
    int seed;

    int margin = ui->ui_sp_time_margin->value();
    for (int i = (margin * -1); i <= margin; i++ ){
        seed = m_zeressima.toTime_t() + i;
        srand(seed);

        resetAuxVotes();
        fillAuxVotes(pos);

        int j;

        for (j = 0; j < MAX_VOTES; j++){
            index = getFreePos(m_auxVotes, rand() % MAX_VOTE, j);

            if (m_votes[index][j] != vote[j])
                break;
        }

        if (j == MAX_VOTES){ //Found one
            qDebug() << "Possível semente encontrada: " <<  seed;
        }

    }
}

int MainWindow::getFreePos(int votes[MAX_VOTE][MAX_VOTES], int userindex, int voteindex){
    int i = userindex;

    for (i = userindex; i < MAX_VOTE; i++){
        if (votes[i][voteindex] == -2)
            return i;
    }

    for (i = userindex - 1; i >= 0; i--){
        if (votes[i][voteindex] == -2)
            return i;
    }

    //Chegou no final
    return -1;
}


void MainWindow::loadResultSlot(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Result Log"), "C:", tr("Result Log (*.log)"));

    if (fileName == NULL || fileName.isEmpty())
        return;

    QFile result(fileName);
    result.open(QIODevice::ReadOnly);
    QByteArray data;

    //Load File
    data = result.readLine(); // Iniciando aplicação de urna
    data = result.readLine(); // Empty line
    data = result.readLine(); // Zeressima

    data = result.readLine(); // 07 23 09:43:50 2014
    m_zeressima = QDateTime::fromString(QString(data), "MM dd hh:mm:ss yyyy\r\n");
    ui->ui_le_zeressima->setText(m_zeressima.toString());

    data = result.readLine(); //Empty line
    data = result.readLine(); //Final Report

    QString vote;
    QStringList votes;
    int begin, end;

    for (int i = 0; i < MAX_VOTE; i++){
        // Data index. {0,0,0,0,0,0}
        data = result.readLine();
        vote = "";
        vote.append(data);

        begin = vote.indexOf("{");
        end = vote.indexOf("}");

        vote = vote.remove(end, vote.length() - end);
        vote = vote.remove(0, begin + 1);

        votes = vote.split(",");

        m_votes[i][0] = votes.at(0).toInt();
        m_votes[i][1] = votes.at(1).toInt();
        m_votes[i][2] = votes.at(2).toInt();
        m_votes[i][3] = votes.at(3).toInt();
        m_votes[i][4] = votes.at(4).toInt();
        m_votes[i][5] = votes.at(5).toInt();
    }

    ui->ui_pb_check->setEnabled(true);

    result.close();
}

