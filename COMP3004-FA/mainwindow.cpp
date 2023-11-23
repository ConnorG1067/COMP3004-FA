#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Initialize Buttons
    initializeBtns();
    initializeStartingUI();

    this->instructionScene = new QGraphicsScene();
    this->waveFormScene = new QGraphicsScene();
    ui->instructionGraphics->setScene(this->instructionScene);
    ui->waveFormGraphics->setScene(this->waveFormScene);

    this->aed = new AED();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initializeBtns(){
    connect(ui->placeAdultElectrodes, SIGNAL(released()), this, SLOT(placeAdultElectrodeBtn()));
    connect(ui->placeChildElectrodes, SIGNAL(released()), this, SLOT(placeChildElectrodeBtn()));
    connect(ui->onOffBtn, SIGNAL(released()), this, SLOT(powerBtn()));
    connect(ui->misPlacePad, &QPushButton::released, this, [this] () {
        this->aed->setFaultyPadPlacement(true);
    });

    connect(ui->failSetUpBtn, SIGNAL(released()), this, SLOT(failAEDSetupBtn()));
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
    ui->activeIndicator->setChecked(!ui->activeIndicator->isChecked());
    ui->batteryIndicator->setChecked(!ui->batteryIndicator->isChecked());

    if(!this->aed->getIsOn()) {
        selfCheckUI(this->aed->selfCheck());
    }else{
        this->instructionScene->clear();
        this->waveFormScene->clear();
        ui->placeAdultElectrodes->setEnabled(false);
        ui->placeChildElectrodes->setEnabled(false);
    }

    this->aed->setIsOn(!this->aed->getIsOn());
}

// Add a random error the to aed errorVector
void MainWindow::failAEDSetupBtn() {
    // Ensure the AED is not functional
    this->aed->setIsFunctional(false);
}

// Generates the AI during a self check
void MainWindow::selfCheckUI(bool isSuccessful) {

    // Make a progress bar and a textItem
    QProgressBar *progressBar = new QProgressBar();
    QGraphicsTextItem *textItem = new QGraphicsTextItem("Preforming Self Check");
    // Set the position of the text item to be centered and above the progress bar
    textItem->setPos(25, -30);

    // Set the range and current value of the progress bar
    progressBar->setRange(0, 100);
    progressBar->setValue(0);

    // Create a QGraphicsProxyWidget so we can add the progress bar on the QGraphicsView
    QGraphicsProxyWidget *proxyWidget = new QGraphicsProxyWidget();
    // Set the widet of the proxyWidget to the progress bar
    proxyWidget->setWidget(progressBar);
    // Add the items to the scene
    this->instructionScene->addItem(proxyWidget);
    this->instructionScene->addItem(textItem);

    // Create and animation
    QPropertyAnimation *animation = new QPropertyAnimation(progressBar, "value");
    animation->setDuration(3000); // Animation duration in milliseconds
    animation->setStartValue(0);
    animation->setEndValue(100);

    // Generate a random stop value
    int randomStopValue = QRandomGenerator::global()->bounded(100);
    QObject::connect(animation, &QPropertyAnimation::finished, [this]() {
        if(this->aed->getIsFunctional()){
            displayDummy();
        }
    });


    // When the value is changed check if we need to stop the animation
    QObject::connect(animation, &QPropertyAnimation::valueChanged, [this, animation, randomStopValue, isSuccessful](const QVariant &value) {
        // Check if the current value is greater than or equal to the randomStop value and we want a failure
        if(value.toInt() >= randomStopValue && !isSuccessful) {
            // Switch the is functional back to true
            this->aed->setIsFunctional(true);
            animation->stop();
        }
    });

    // Start the animation
    animation->start();
}


void MainWindow::displayDummy() {
    placeImage(this->instructionScene, ":/images/src/img/dummy.jpg", 186, 220, 35, 0);

    // Make the electrodes button enabled
    ui->placeAdultElectrodes->setEnabled(true);
    ui->placeChildElectrodes->setEnabled(true);
}


void MainWindow::placeImage(QGraphicsScene* scene, string path, int xSize, int ySize, int xPos, int yPos) {
    // Clear the scene
    scene->clear();

    // Create an image and scale it
    QPixmap image(QString::fromStdString(path));
    image = image.scaled(QSize(xSize, ySize), Qt::KeepAspectRatio);

    // Add the pixmapItem and set its positions
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(image);
    pixmapItem->setPos(xPos, yPos);
    scene->addItem(pixmapItem);
}

// Determines the condition of the patient
string MainWindow::determineCondition() {
    // Generates a random number from 0 to 9
    int randomNumber = QRandomGenerator::global()->bounded(10);
    // 0 - 5 NSR 60%
    // 6 - 7 VT 20% Inclusive
    // 8 - 9 VF 20% Inclusive
    if(randomNumber < 6){
        return ":/images/src/img/nsr_ecg.png";
    }else if(randomNumber >= 6 && randomNumber <= 7){
        return ":/images/src/img/ventricular_fibrillation_ecg.png";
    }else{
        return ":/images/src/img/ventricular_teachycardia_ecg.png";
    }

    return "";
}

CardiacArrhythmias* MainWindow::imgPathToCardiac(string imgPath) {
    if(imgPath == ":/images/src/img/ventricular_teachycardia_ecg.png"){
        return new VentricularTachycardia();
    }else if(imgPath == ":/images/src/img/ventricular_fibrillation_ecg.png"){
        return new VentricularFibrillation();
    }else{
        return new NormalSinusRhythm();
    }
}

void MainWindow::placeAdultElectrodeBtn() {
    string patientCondition = determineCondition();
    placeImage(this->waveFormScene, patientCondition, 800, 224, 35, 0);

    // Set the aed to a victim aged from 19-100, with a random condition
    this->aed->setVictim(new Victim(QRandomGenerator::global()->bounded(19, 101), imgPathToCardiac(patientCondition)));
    updateVictimInfo();
    placePadsUI(false);
}

void MainWindow::placeChildElectrodeBtn() {
    string patientCondition = determineCondition();
    placeImage(this->waveFormScene, patientCondition, 800, 224, 35, 0);

    // Set the aed to a victim aged from 5-18, with a random condition
    this->aed->setVictim(new Victim(QRandomGenerator::global()->bounded(5, 19), imgPathToCardiac(patientCondition)));
    updateVictimInfo();
    placePadsUI(true);
}


void MainWindow::updateVictimInfo() {
    ui->nameLabel->setText(QString::fromStdString(this->aed->getVictim()->getName()));
    ui->ageLabel->setText(QString::number(this->aed->getVictim()->getAge()));
    ui->conditionLabel->setText(this->aed->getVictim()->getCondition()->getConditionName());
}

ElectrodePadPair* MainWindow::generateElectrodePadPair(bool isChild){
    ElectrodePadPair* currentPair;
    if(isChild){
        if(this->aed->getFaultyPadPlacment()){
            currentPair = new ElectrodePadPair(
                        new ChildElectrode(QRandomGenerator::global()->bounded(70, 101), QRandomGenerator::global()->bounded(80, 121)),
                        new ChildElectrode(QRandomGenerator::global()->bounded(70, 101), QRandomGenerator::global()->bounded(80, 121))
                    );
        }else{
            currentPair = new ElectrodePadPair(new ChildElectrode(60, 70), new ChildElectrode(114, 131));
        }
    }else{
        if(this->aed->getFaultyPadPlacment()){
            currentPair = new ElectrodePadPair(
                        new AdultElectrode(QRandomGenerator::global()->bounded(70, 101), QRandomGenerator::global()->bounded(80, 121)),
                        new AdultElectrode(QRandomGenerator::global()->bounded(70, 101), QRandomGenerator::global()->bounded(80, 121))
                    );
        }else{
            currentPair = new ElectrodePadPair(new AdultElectrode(60, 70), new AdultElectrode(114, 131));
        }
    }

    return currentPair;
}

void MainWindow::placePadsUI(bool isChild) {
    if(this->instructionScene->items().contains(this->aed->getElectrodePadPair()->getUpperPad()->getPadRect())){
        this->instructionScene->removeItem(this->aed->getElectrodePadPair()->getUpperPad()->getPadRect());
    }
    if(this->instructionScene->items().contains(this->aed->getElectrodePadPair()->getLowerPad()->getPadRect())){
        this->instructionScene->removeItem(this->aed->getElectrodePadPair()->getLowerPad()->getPadRect());
    }
    // Create an electrode pair
    ElectrodePadPair* currentPair = generateElectrodePadPair(isChild);

    // Set the aed pair to the pair made above
    this->aed->setElectrodePadPair(currentPair);

    // Add the box to the scene
    this->instructionScene->addItem(currentPair->getUpperPad()->getPadRect());
    this->instructionScene->addItem(currentPair->getLowerPad()->getPadRect());
}





