#include "mainwindow.h"
#include "ui_mainwindow.h"

QString MainWindow::yellowRBIndicator = "QRadioButton {color:black;}QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:yellow;border:2px solid black;}";
QString MainWindow::redRBIndicator = "QRadioButton {color:black;}QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:red;border:2px solid black;}";
QString MainWindow::greenRBIndicator = "QRadioButton {color:black;}QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:green;border:2px solid black;}";
QString MainWindow::blackUnfilledRBIndicator = "QRadioButton {color:black;}QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:unchecked {border:2px solid black;}";


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->aed = new AED();

    flashTimer = new QTimer();
    this->flashTimer->setInterval(100);

    this->instructionScene = new QGraphicsScene();
    this->imageInstructionScene = new QGraphicsScene();
    this->waveFormScene = new QGraphicsScene();
    ui->instructionGraphics->setScene(this->instructionScene);
    ui->imageInstructionGraphics->setScene(this->imageInstructionScene);
    ui->waveFormGraphics->setScene(this->waveFormScene);
    ui->normalSinusRhythmRB->setChecked(true);

    // Initialize Buttons
    initializeBtns();
    initializeStartingUI();
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

    // Connect shock button to the shock function
    connect(ui->shock, &QPushButton::released, this, [this](){this->aed->shock();});

    // Connect flash shock button timer to timer function
    QObject::connect(flashTimer, SIGNAL(timeout()), this, SLOT(flashShockButton()));

    // Connect aed to flashShockButton function so that the aed may update the ui with the flashing shock button
    connect(this->aed, &AED::flashShockButtonSignal, this, [this](){
        flashTimer->start();
    });

    // TODO: This may be redundant, could do this code in aed.cpp
    connect(this->aed, &AED::shockSignal, this, [this](){this->aed->setShockAdministered(true);});

    connect(ui->shock, &QPushButton::released, this, [this](){this->aed->shock();});
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

    ui->checkPads->setAutoExclusive(false);
    ui->doNotTouchPatient->setAutoExclusive(false);
    ui->analyzing->setAutoExclusive(false);
    ui->shockableRhythm->setAutoExclusive(false);

    ui->checkPads->setDisabled(true);
    ui->doNotTouchPatient->setDisabled(true);
    ui->analyzing->setDisabled(true);
    ui->shockableRhythm->setDisabled(true);
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

        resetRadioBtns();

        ui->placeAdultElectrodes->setEnabled(false);
        ui->placeChildElectrodes->setEnabled(false);
    }

    this->aed->setIsOn(!this->aed->getIsOn());
}

void MainWindow::resetRadioBtns(){
    ui->checkPads->setStyleSheet(MainWindow::blackUnfilledRBIndicator);
    ui->doNotTouchPatient->setStyleSheet(MainWindow::blackUnfilledRBIndicator);
    ui->analyzing->setStyleSheet(MainWindow::blackUnfilledRBIndicator);
    ui->shockableRhythm->setStyleSheet(MainWindow::blackUnfilledRBIndicator);

    //Uncheck all radio btns
    ui->checkPads->setChecked(false);
    ui->doNotTouchPatient->setChecked(false);
    ui->analyzing->setChecked(false);
    ui->shockableRhythm->setChecked(false);
}


// Add a random error the to aed errorVector
void MainWindow::failAEDSetupBtn() {
    // Ensure the AED is not functional
    this->aed->setIsFunctional(false);
}

// Add a random error the to aed errorVector
void MainWindow::displayTextInstruction(QString message) {
    this->ui->textInstructions->append(message);
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

void MainWindow::placeImage(QGraphicsScene* scene, QString path, int xSize, int ySize, int xPos, int yPos) {
    // Clear the scene
    scene->clear();

    // Create an image and scale it
    QPixmap image(path);
    image = image.scaled(QSize(xSize, ySize), Qt::KeepAspectRatio);

    // Add the pixmapItem and set its positions
    QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(image);
    pixmapItem->setPos(xPos, yPos);
    scene->addItem(pixmapItem);
}

// Determines the condition of the patient
QString MainWindow::determineCondition() {
    if(ui->normalSinusRhythmRB->isChecked()){
        return ":/images/src/img/nsr_ecg.png";
    }else if(ui->VentricularFibrillationRB->isChecked()){
        return ":/images/src/img/ventricular_fibrillation_ecg.png";
    }else{
        return ":/images/src/img/ventricular_teachycardia_ecg.png";
    }
    return "";
}

CardiacArrhythmias* MainWindow::imgPathToCardiac(QString imgPath) {
    if(imgPath == ":/images/src/img/ventricular_teachycardia_ecg.png"){
        return new VentricularTachycardia();
    }else if(imgPath == ":/images/src/img/ventricular_fibrillation_ecg.png"){
        return new VentricularFibrillation();
    }else{
        return new NormalSinusRhythm();
    }
}

void MainWindow::indiciatorSwitch(QRadioButton* radioBtn, std::function<void()> performOperations, std::function<void()> audioOperations, bool isSuccess) {
    if(this->aed->getIsOn()){
        // Check the btn
        radioBtn->setChecked(true);
        // Set the style sheet of the button to yellow
        radioBtn->setStyleSheet(MainWindow::yellowRBIndicator);
    }

    // Create a timer
    QTimer* timer = new QTimer(this);
    // Create a step pointer
    int* step = new int(0);
    audioOperations();

    QObject::connect(timer, &QTimer::timeout, [this, step, timer, isSuccess, radioBtn, performOperations, audioOperations]() {

        // Stop the timer after 3 iterations
        if ((*step) == 3 || !this->aed->getIsOn()) {
            // Stop and delete timer
            timer->stop();
            timer->deleteLater();

            if(this->aed->getIsOn()) radioBtn->setStyleSheet((isSuccess) ? MainWindow::greenRBIndicator : MainWindow::redRBIndicator);
            // preform operations after awaiting
            performOperations();
            // Delete the step
            delete step;
        } else {

            if(!(this->aed->getVoiceSystem()->getAudioInstructions()->state() == QMediaPlayer::PlayingState)){
                (*step)++;
            }
        }
    });

    timer->setInterval(1000);
    timer->start();
}

void MainWindow::flashShockButton(){
    if(!this->aed->getShockAdministered()){
        ui->shock->setStyleSheet(ui->shock->styleSheet() == "" ? "background-color: red" : "");
    }else{
        ui->shock->setStyleSheet("");
        this->aed->setShockAdministered(false);
        this->flashTimer->stop();
        this->flashTimer->deleteLater();
    }
}

void MainWindow::placeAdultElectrodeBtn() {
    resetRadioBtns();
    QString patientCondition = determineCondition();
    placeImage(this->waveFormScene, patientCondition, 800, 224, 35, 0);

    // Set the aed to a victim aged from 19-100, with a random condition
    this->aed->setVictim(new Victim(QRandomGenerator::global()->bounded(19, 101), imgPathToCardiac(patientCondition)));
    updateVictimInfo();
    placePadsUI(false);

    callIndicatorSwitchLambdas();
}

void MainWindow::placeChildElectrodeBtn() {
    QString patientCondition = determineCondition();
    placeImage(this->waveFormScene, patientCondition, 800, 224, 35, 0);

    // Set the aed to a victim aged from 5-18, with a random condition
    this->aed->setVictim(new Victim(QRandomGenerator::global()->bounded(5, 19), imgPathToCardiac(patientCondition)));
    updateVictimInfo();
    placePadsUI(true);

    callIndicatorSwitchLambdas();
}

void MainWindow::callIndicatorSwitchLambdas() {
    indiciatorSwitch(ui->checkPads, [this] () {
        if(!this->aed->getFaultyPadPlacment()) {
            indiciatorSwitch(ui->doNotTouchPatient, [this] () {
                indiciatorSwitch(ui->analyzing, [this] () {
                    indiciatorSwitch(ui->shockableRhythm, [this] () {
                        this->aed->setIsReadyForShock((this->aed->getVictim()->getCondition()->getConditionName() != "Normal Sinus Rhythm"));
                    }, [this] () { this->aed->getVoiceSystem()->initiateAudioAndTextIntruction(((this->aed->getVictim()->getCondition()->getConditionName() != "Normal Sinus Rhythm")) ? "qrc:/audios/src/audios/ShockableHeartRhythmFound.mp3" : "qrc:/audios/src/audios/NoShockableHeartRhythm.mp3", ":/images/src/img/analyzing.png", "Analyzing"); }, (this->aed->getVictim()->getCondition()->getConditionName() != "Normal Sinus Rhythm"));
                }, [this] () { this->aed->getVoiceSystem()->initiateAudioAndTextIntruction("qrc:/audios/src/audios/AnalyzingHR.mp3", ":/images/src/img/analyzing.png", "Analyzing"); }, true);
            }, [this] () { this->aed->getVoiceSystem()->initiateAudioAndTextIntruction("qrc:/audios/src/audios/DoNotTouch.mp3", ":/images/src/img/analyzing.png", "Do not touch"); }, true);
        }
        this->aed->setFaultyPadPlacement(false);
    }, [this] () { this->aed->getVoiceSystem()->initiateAudioAndTextIntruction((!this->aed->getFaultyPadPlacment()) ? "qrc:/audios/src/audios/PadCheckSuccess.mp3" : "qrc:/audios/src/audios/PadCheckFailed.mp3", ":/images/src/img/attachPads.png", "Apply Pads"); }, !this->aed->getFaultyPadPlacment());
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
