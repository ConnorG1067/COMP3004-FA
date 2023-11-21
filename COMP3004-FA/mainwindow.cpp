#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set up connections-
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections(){
    //connect Battery button click signal to BatteryStatus slot
    connect(ui->batteryIndicator, SIGNAL(released()), this, SLOT(batteryStatus()));

    //connect Electrode button click signal to OnElectrodesBtnPressed slot
    connect(ui->batteryIndicator_2, SIGNAL(released()), this, SLOT(onElectrodesBtnPressed()));

    //connect Cardiac Arrhythmia button click signal to OnCardiacArrhythmiaBtnPressed slot
    connect(ui->electrode...indicator, SIGNAL(released()), this, SLOT(onCardiacArrhythmiaBtnPressed()));

    //connect Place Electrodes button click signal to PlaceElectrodes slot
    connect(ui->placeElectrodes, SIGNAL(released()), this, SLOT(placeElectrodes()));
}

void MainWindow::batteryStatus(){
    qInfo("Shows remaining battery percentage");
}

void MainWindow::onElectrodesBtnPressed(){
    qInfo("Connect Electrodes");
}

void MainWindow::onCardiacArrhythmiaBtnPressed(){
    qInfo("Cardiac Arrhythmia");
}

void MainWindow::placeElectrodes(){
    qInfo("Place Electrodes");
}


