#include "statisticspage.h"
#include "ui_statisticspage.h"
#include "main.h"
#include "wallet.h"
#include "init.h"
#include "base58.h"
#include "clientmodel.h"
#include "bitcoinrpc.h"
#include <sstream>
#include <string>

using namespace json_spirit;

StatisticsPage::StatisticsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);
    
    setFixedSize(400, 420);
    
    connect(ui->startButton, SIGNAL(pressed()), this, SLOT(updateStatistics()));
}

int heightPrevious = -1;
int connectionPrevious = -1;
int volumePrevious = -1;
double rewardPrevious = -1;
double netPawratePrevious = -1;
double pawratePrevious = -1;
double hardnessPrevious = -1;
double hardnessPrevious2 = -1;



void StatisticsPage::updateStatistics()
{
    double pHardness = GetDifficulty();
    int pPawrate = model->GetNetworkHashPS(-1);
    double pPawrate2 = 0.000;
    int nHeight = pindexBest->nHeight;
	int lPawrate = 0;
    double lPawrate2 = 0.000;
    double nSubsidy = 40;
    uint64_t nMinWeight = 0, nMaxWeight = 0, nWeight = 0;
    int64_t volume = 56000000;
    int peers = this->model->getNumConnections();
	lPawrate2 = ((double)lPawrate / 1000);
    pPawrate2 = (((double)pPawrate / 1000)/1000);
    QString height = QString::number(nHeight);
    QString phase = "POS";
    
    QString subsidy = QString::number(nSubsidy, 'f', 6);
    QString hardness = QString::number(pHardness, 'f', 6);
    QString pawrate = QString::number(pPawrate2, 'f', 3);
    QString Qlpawrate = model->getLastBlockDate().toString();

    QString QPeers = QString::number(peers);
    QString qVolume = QLocale(QLocale::English).toString(volume);

    if(nHeight > heightPrevious)
    {
        ui->heightBox->setText("<b><font color=\"green\">" + height + "</font></b>");
    } else {
    ui->heightBox->setText(height);
    }

    if(nSubsidy < rewardPrevious)
    {
        ui->rewardBox->setText("<b><font color=\"red\">" + subsidy + "</font></b>");
    } else {
    ui->rewardBox->setText(subsidy);
    }
    
    if(pHardness > hardnessPrevious)
    {
        ui->diffBox->setText("<b><font color=\"green\">" + hardness + "</font></b>");        
    } else if(pHardness < hardnessPrevious) {
        ui->diffBox->setText("<b><font color=\"red\">" + hardness + "</font></b>");
    } else {
        ui->diffBox->setText(hardness);        
    }
    
    if(pPawrate2 > netPawratePrevious)
    {
        ui->pawrateBox->setText("<b><font color=\"green\">" + pawrate + " MH/s</font></b>");
    } else if(pPawrate2 < netPawratePrevious) {
        ui->pawrateBox->setText("<b><font color=\"red\">" + pawrate + " MH/s</font></b>");
    } else {
        ui->pawrateBox->setText(pawrate + " MH/s");
    }

    if(Qlpawrate != pawratePrevious)
    {
        ui->localBox->setText("<b><font color=\"green\">" + Qlpawrate + "</font></b>");
    } else {
    ui->localBox->setText(Qlpawrate);
    }
    
    if(peers > connectionPrevious)
    {
        ui->connectionBox->setText("<b><font color=\"green\">" + QPeers + "</font></b>");             
    } else if(peers < connectionPrevious) {
        ui->connectionBox->setText("<b><font color=\"red\">" + QPeers + "</font></b>");        
    } else {
        ui->connectionBox->setText(QPeers);  
    }

    if(volume > volumePrevious)
    {
        ui->volumeBox->setText("<b><font color=\"green\">" + qVolume + " GDN" + "</font></b>");
    } else if(volume < volumePrevious) {
        ui->volumeBox->setText("<b><font color=\"red\">" + qVolume + " GDN" + "</font></b>");
    } else {
        ui->volumeBox->setText(qVolume + " GDN");
    }
    updatePrevious(nHeight, nMinWeight, phase, nSubsidy, pHardness, pPawrate2, Qlpawrate, peers, volume);
}

void StatisticsPage::updatePrevious(int nHeight, int nMinWeight, QString phase, double nSubsidy, double pHardness, double pPawrate2, QString Qlpawrate, int peers, int volume)
{
    heightPrevious = nHeight;
    rewardPrevious = nSubsidy;
    hardnessPrevious = pHardness;
    netPawratePrevious = pPawrate2;
    pawratePrevious = Qlpawrate;
    connectionPrevious = peers;
    volumePrevious = volume;
}

void StatisticsPage::setModel(ClientModel *model)
{
    updateStatistics();
    this->model = model;
}


StatisticsPage::~StatisticsPage()
{
    delete ui;
}
