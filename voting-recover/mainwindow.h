#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    static const int MAX_VOTES = 6;
    static const int MAX_VOTE = 1000;

    Ui::MainWindow *ui;
    QDateTime m_zeressima;
    int m_votes[MAX_VOTE][MAX_VOTES];
    int m_auxVotes[MAX_VOTE][MAX_VOTES];


    void findMatches(int vote[MAX_VOTES], int pos);
    int getFreePos(int votes[MAX_VOTE][MAX_VOTES], int userindex, int voteindex);
    void resetAuxVotes();
    void fillAuxVotes(int pos);

private slots:
    void btCheckSlot();
    void loadResultSlot();
};

#endif // MAINWINDOW_H
