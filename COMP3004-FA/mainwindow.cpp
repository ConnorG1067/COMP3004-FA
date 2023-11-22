#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize Buttons
    initializeBtns();
    initializeStartingUI();

    this->aed = new AED();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeBtns(){

        // TODO generate slots
//    connect(ui->placeAdultElectrodes, SIGNAL(released()), this, SLOT());
//    connect(ui->placeChildElectrodes, SIGNAL(released()), this, SLOT());

    connect(ui->onOffBtn, SIGNAL(released()), this, SLOT(powerBtn()));
//    connect(ui->disturbPatientBtn, SIGNAL(released()), this, SLOT());

}

// Function that is ran on the UI contructor to update UI
void MainWindow::initializeStartingUI() {

    // Setting up active and battery indicator DON'T TOUCH!
    ui->batteryIndicator->setDisabled(true);
    ui->activeIndicator->setDisabled(true);

    ui->batteryIndicator->setCheckable(true);
    ui->activeIndicator->setCheckable(true);

    ui->batteryIndicator->setAutoExclusive(false);
    ui->activeIndicator->setAutoExclusive(false);
}

// Toggles the on and off buttons
void MainWindow::powerBtn() {
    // If we can power the aed on update the UI
    if(this->aed->powerOn()){
        ui->activeIndicator->setChecked(!ui->activeIndicator->isChecked());
        ui->batteryIndicator->setChecked(!ui->batteryIndicator->isChecked());
    }

    if(this->aed->selfCheck()){
        selfCheckUI();
    }

}

void MainWindow::selfCheckUI() {

}





