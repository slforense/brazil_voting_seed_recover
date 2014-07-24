#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),  m_lcdValue(0)
{

    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(finishedSlot(QNetworkReply*)));

    QUrl url("http://localhost:3000/candidates");
    nam->get(QNetworkRequest(url));

    setupUi(this);

    connect(ui_pb_0, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));
    connect(ui_pb_1, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));
    connect(ui_pb_2, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));
    connect(ui_pb_3, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));
    connect(ui_pb_4, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));
    connect(ui_pb_5, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));
    connect(ui_pb_6, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));
    connect(ui_pb_7, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));
    connect(ui_pb_8, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));
    connect(ui_pb_9, SIGNAL(clicked()), this, SLOT(btnClickerSlot()));

    m_numpad = new QMap<int, QPushButton *>();
    m_numpad->insert(0,ui_pb_0);
    m_numpad->insert(1,ui_pb_1);
    m_numpad->insert(2,ui_pb_2);
    m_numpad->insert(3,ui_pb_3);
    m_numpad->insert(4,ui_pb_4);
    m_numpad->insert(5,ui_pb_5);
    m_numpad->insert(6,ui_pb_6);
    m_numpad->insert(7,ui_pb_7);
    m_numpad->insert(8,ui_pb_8);
    m_numpad->insert(9,ui_pb_9);


    connect(ui_pb_corrige, SIGNAL(clicked()), this, SLOT(clearTextSlot()));
    connect(ui_pb_confirma, SIGNAL(clicked()), this, SLOT(confirmVoteSlot()));
    connect(ui_pb_branco, SIGNAL(clicked()), this, SLOT(voteWhiteSlot()));

    connect(ui_menu_start, SIGNAL(triggered()), this, SLOT(startVoting()));
    connect(ui_menu_stop, SIGNAL(triggered()), this, SLOT(stopVoting()));
    connect(ui_menu_new, SIGNAL(triggered()), this, SLOT(newUserSlot()));

    connect(ui_menu_sim_gerar, SIGNAL(triggered()), this, SLOT(generateVotesSlot()));
    connect(ui_menu_sim_aplicar, SIGNAL(triggered()), this, SLOT(applyVotesSlot()));

    m_roles = (Role **) calloc (sizeof(Role *), MAX_VOTE_PER_USER);

    m_roles[0] = new Role(5,"Deputado Distrital");
    m_roles[1] = new Role(4,"Deputado Federal");
    m_roles[2] = new Role(3,"Senador 1");
    m_roles[3] = new Role(3,"Senador 2");
    m_roles[4] = new Role(2,"Governador");
    m_roles[5] = new Role(2,"Presidente");

    ui_menu_new->setEnabled(false);
    ui_menu_stop->setEnabled(false);
    ui_menu_start->setEnabled(true);

    ui_menu_sim_gerar->setEnabled(true);
    ui_menu_sim_aplicar->setEnabled(false);

    for (int i = 0; i < MAX_VOTES; i++){
        for (int j = 0; j < MAX_VOTE_PER_USER; j++){
            m_ordervotes[i][j] = -2;
        }
    }

    m_file.setFileName("result.log");
    m_file.open(QIODevice::WriteOnly | QIODevice::Text);

    m_order.setFileName("result_order.sort");
    m_order.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&m_file);
    out << "Iniciando aplicação de urna\n\n";
}

MainWindow::~MainWindow(){

}

void MainWindow::applyVotesSlot(){
    if (m_ordervotes[0][0] == -2){
        return;
    }

    QTextStream out(&m_order);

    out << "Votos em Ordem:\n";
    QString report = "";
    for (int i = 0; i < MAX_VOTES; i++){
        newUserSlot();
        report = QString::number(i) + ". {";

        for (int j = 0; j < MAX_VOTE_PER_USER; j++){
            m_vote[j] = m_ordervotes[i][j];

            report +=  QString::number(m_ordervotes[i][j]);
            if (j != MAX_VOTE_PER_USER - 1){
                report += ",";
            }
        }

        report += "}\n";
        out << report;

        finishUser();
    }

    stopVoting();
    m_order.close();
}

void MainWindow::generateVotesSlot(){
    srand(QDateTime::currentDateTime().toTime_t());

    int max;
    int index;
    QList<int> keys;

    for (int i = 0; i < MAX_VOTES; i++){
        for (int j = 0; j < MAX_VOTE_PER_USER; j++){
            max = m_candidates[j].size();
            keys = m_candidates[j].keys();

            index  = rand() % max;
            m_ordervotes[i][j] = keys.at(index);
        }
    }
}

void MainWindow::stopVoting(){
    ui_menu_new->setEnabled(false);
    ui_menu_stop->setEnabled(false);
    ui_menu_start->setEnabled(true);
    ui_grid_main->setEnabled(false);

    //random can be used againd
    ui_menu_sim_gerar->setEnabled(true);
    ui_menu_sim_aplicar->setEnabled(false);

    QTextStream out(&m_file);

    out << "Final Report\n";

    QString report = "";
    for (int i = 0; i < MAX_VOTES; i++){
        report.append(QString::number(i));
        report.append(". {");
        for (int j = 0; j < MAX_VOTE_PER_USER; j++){            
            report.append(QString::number(m_votes[i][j]));

            if (j != MAX_VOTE_PER_USER - 1){
                report.append(",");
            }
        }
        report.append("}\n");
        out << report;
        report = "";
    }

    m_file.close();
}

void MainWindow::startVoting(){
    QTextStream out(&m_file);
    int seed = QDateTime::currentDateTime().toTime_t();
    out << "Zeressima\n" << QDateTime::fromTime_t(seed).toString("MM dd hh:mm:ss yyyy") << "\n\n";

    srand(seed);
    ui_menu_new->setEnabled(true);
    ui_menu_stop->setEnabled(true);
    ui_menu_start->setEnabled(false);

    //random already created can used to fill votes
    ui_menu_sim_gerar->setEnabled(false);
    ui_menu_sim_aplicar->setEnabled(true);

    /*
     *   pg 16 https://1996ce7e-a-62cb3a1a-s-sites.googlegroups.com/site/dfaranha/projects/report-voting.pdf
     *   DRV Initialization.
     *   Algorithm 3.1 DRV Initialization.
     *   Input: Table T representing the DRV, total of m electors.
     *   Output: Table T initialized and pseudo-random number generator seeded
     *   with a timestamp.
     *       1: srand(time(NULL));
     *       2: for i ← 0 to m do
     *       3: T[i] ← EMPTY
     *       4: end for
     */

    for (int i = 0; i < MAX_VOTES; i++){
        for (int j = 0; j < MAX_VOTE_PER_USER; j++){
            m_votes[i][j] = -2;
        }
    }
}

void MainWindow::finishUser(){
    m_index = 0;

    ui_lb_role->clear();
    clearTextSlot();

    ui_grid_main->setEnabled(false);
    /*
     *  Algorithm 3.2 Storage of a vote in the DRV.
     *  Input: Table T representing the DRV, i-th vote V , with 0 ≤ i < n.
     *  Output: Table T updated with vote V stored.
     *      1: j ← rand() mod m
     *      2: if T[j] != EMPTY then
     *      3: {Collision found!}
     *      4: Increment or decrement j until a new free position is found
     *      5: end if
     *      6: T[j] ← V
     */
    int j;

    for (int i = 0; i < MAX_VOTE_PER_USER; i++){
        j = getFreePos(rand() % MAX_VOTES, i);
        m_votes[j][i] = m_vote[i];
    }

}

int MainWindow::getFreePos(int userindex, int voteindex){

    for (int i = userindex; i < MAX_VOTES; i++){
        if (m_votes[i][voteindex] == -2)
            return i;
    }

    for (int i = userindex - 1; i >= 0; i--){
        if (m_votes[i][voteindex] == -2)
            return i;
    }

    //Chegou no final
    return -1;
}

void MainWindow::newUserSlot(){
    m_index = 0;
    ui_lb_role->setText(m_roles[m_index]->getName());

    ui_grid_main->setEnabled(true);
    ui_pb_confirma->setEnabled(false);
    setNumpadEnabled(true);
}

void MainWindow::voteWhiteSlot(){
    clearTextSlot();
    setNumpadEnabled(false);
    ui_lb_vote->setText("Branco");
}

void MainWindow::confirmVoteSlot(){
    m_vote[m_index] = m_lcdValue;
    m_index++;

    if (m_index < MAX_VOTE_PER_USER){
        clearTextSlot();
        ui_lb_role->setText(m_roles[m_index]->getName());
    }else{
        finishUser();
    }
}

void MainWindow::clearTextSlot(){
    m_lcdValue = 0;
    ui_lb_vote->clear();

    ui_lb_name->clear();
    ui_lb_party->clear();

    setNumpadEnabled(true);
}

void MainWindow::btnClickerSlot(){
    QString object = sender()->objectName();
    int length = object.length();

    QString strValue = object.remove(0, length - 1);
    int value = strValue.toInt();

    m_lcdValue = m_lcdValue*10 + value;

    ui_lb_vote->setText(ui_lb_vote->text().append(QString::number(value)));  

    if (ui_lb_vote->text().length() == m_roles[m_index]->getQuantity()){
        setNumpadEnabled(false);

        if (m_candidates[m_index].contains(m_lcdValue)){
            Candidate *candidate = m_candidates[m_index].value(m_lcdValue, 0);

            ui_lb_name->setText(candidate->getName());
            ui_lb_party->setText(candidate->getParty());
        }else{
            ui_lb_name->setText(QString("Voto Nulo"));
            ui_lb_party->setText(QString("Voto Nulo"));

            m_lcdValue = -1;
        }
    }
}

void MainWindow::setNumpadEnabled(bool enabled){
    ui_pb_0->setEnabled(enabled);
    ui_pb_1->setEnabled(enabled);
    ui_pb_2->setEnabled(enabled);
    ui_pb_3->setEnabled(enabled);
    ui_pb_4->setEnabled(enabled);
    ui_pb_5->setEnabled(enabled);
    ui_pb_6->setEnabled(enabled);
    ui_pb_7->setEnabled(enabled);
    ui_pb_8->setEnabled(enabled);
    ui_pb_9->setEnabled(enabled);

     ui_pb_confirma->setEnabled(!enabled);
}

void MainWindow::finishedSlot(QNetworkReply* reply)
{

    QByteArray bytes = reply->readAll();
    QJsonDocument jdoc= QJsonDocument::fromJson(bytes);
    QJsonArray candidates = jdoc.array();

    QJsonObject candidate;
    QString party, name;
    int number, role;

    for(auto&& item: candidates){
        candidate = item.toObject();

        number = candidate["number"].toString().toInt();
        role = candidate["role"].toInt();
        party = candidate["party"].toString();
        name = candidate["name"].toString();

        m_candidates[role].insert(number,new Candidate(party, name, number));
    }

    for (int i=0; i < MAX_VOTE_PER_USER; i++){
        qDebug() << m_candidates[i].size() << " candidatos para a vaga " << i;
    }

    delete reply;
}
