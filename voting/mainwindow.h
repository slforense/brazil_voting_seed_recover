#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QToolBar>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QThread>
#include <time.h>
#include <random>

#include "candidate.h"
#include "role.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, Ui_MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void finishedSlot(QNetworkReply* reply);
    void btnClickerSlot();
    void clearTextSlot();
    void confirmVoteSlot();
    void voteWhiteSlot();
    void startVoting();
    void stopVoting();
    void newUserSlot();
    void generateVotesSlot();
    void applyVotesSlot();

private:
    static const int MAX_VOTES = 1000;
    static const int MAX_VOTE_PER_USER = 6;

    void setNumpadEnabled(bool enabled);
    int getFreePos(int userindex, int voteindex);
    void finishUser();
    int m_index;
    int m_votesIndex;

    int m_lcdValue;
    QMap<int, Candidate *> m_candidates[MAX_VOTE_PER_USER];
    QMap<int, QPushButton *> *m_numpad;
    Role **m_roles;
    QFile m_file;
    QFile m_order;

    int m_vote[MAX_VOTE_PER_USER];
    int m_votes[MAX_VOTES][MAX_VOTE_PER_USER];
    int m_ordervotes[MAX_VOTES][MAX_VOTE_PER_USER];
};

#endif // MAINWINDOW_H
