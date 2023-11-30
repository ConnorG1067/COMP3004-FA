#include "mainwindow.h"
#include "ui_mainwindow.h"

// Default Indicator Style Sheets
QString MainWindow::yellowRBIndicator = "QRadioButton {color:black;}QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:yellow;border:2px solid black;}";
QString MainWindow::redRBIndicator = "QRadioButton {color:black;}QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:red;border:2px solid black;}";
QString MainWindow::greenRBIndicator = "QRadioButton {color:black;}QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:checked {background-color:green;border:2px solid black;}";
QString MainWindow::blackUnfilledRBIndicator = "QRadioButton {color:black;}QRadioButton::indicator {width:10px;height:10px;border-radius:7px;}QRadioButton::indicator:unchecked {border:2px solid black;}";

// MainWindow Constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Allocating memory for an AED
    this->aed = new AED();
    this->aed->setCprIterations(ui->iterationComboBox->currentText().toInt());
    this->aed->setMainWindowResetCallback([this] () {
        // Clear Scenes and text boxes
        this->instructionScene->clear();
        placeImage(this->instructionScene, ":/images/src/img/dummy.jpg", 186, 220, 35, 0);
        this->waveFormScene->clear();
        this->imageInstructionScene->clear();
        ui->textInstructions->clear();

        resetRadioBtns();
        initializeStartingUI();

        ui->nameLabel->clear();
        ui->ageLabel->clear();
        ui->conditionLabel->clear();
    });

    // Initializing timers
    this->flashTimer = new QTimer();
    this->flashTimer->setInterval(100);

    // Creating multiple scenes from the class definition
    this->instructionScene = new QGraphicsScene();
    this->imageInstructionScene = new QGraphicsScene();
    this->waveFormScene = new QGraphicsScene();

    // Set the scene of each QGraphicsScene
    ui->instructionGraphics->setScene(this->instructionScene);
    ui->imageInstructionGraphics->setScene(this->imageInstructionScene);
    ui->waveFormGraphics->setScene(this->waveFormScene);

    // Set the default victim condition to NSR
    ui->normalSinusRhythmRB->setChecked(true);

    // Initialize Buttons & Starting UI
    initializeBtns();
    initializeStartingUI();
}

// Deconstructor for MainWindow
MainWindow::~MainWindow() {
    delete ui;
}

// Initalize all buttons
void MainWindow::initializeBtns(){
    // Place child and adult electrodes
    connect(ui->placeElectrodesBtn, SIGNAL(released()), this, SLOT(determineElectrodes()));
    // On and off btn
    connect(ui->onOffBtn, SIGNAL(released()), this, SLOT(powerBtn()));
    connect(ui->onOffAedBtn, SIGNAL(released()), this, SLOT(powerBtn()));
    // Sets the next pad placement to the incorrect position
    connect(ui->misPlacePad, &QPushButton::released, this, [this] () {
        this->aed->setFaultyPadPlacement(true);
        determineElectrodes();
    });
    // Sets the next setup to a fail
    connect(ui->failSetUpBtn, SIGNAL(released()), this, SLOT(failAEDSetupBtn()));
    // Connect shock button to the shock function
    connect(ui->shock, &QPushButton::released, this, [this](){this->aed->shock();});
    // Disturb the patient
    connect(ui->disturbPatientBtn, &QPushButton::released, this, [this](){this->aed->setPatientDisturbed(true);});

    // Connect flash shock button timer to timer function
    connect(flashTimer, SIGNAL(timeout()), this, SLOT(flashShockButton()));

    // Connect CPR compression
    connect(ui->compression, &QPushButton::released, this, [this](){this->aed->performCompression(1);});

    // Connect poor CPR compression
    connect(ui->poorCompression, &QPushButton::released, this, [this](){this->aed->performCompression(-1);});

    // Connect aed to flashShockButton function so that the aed may update the ui with the flashing shock button
    connect(this->aed, &AED::flashShockButtonSignal, this, [this](){ flashTimer->start(); });

    // TODO: This may be redundant, could do this code in aed.cpp
    connect(this->aed, &AED::shockSignal, this, [this](){this->aed->setShockAdministered(true);});

    // Toggle the is child btn from the aed
    connect(ui->childAedBtn, &QPushButton::released, this, [this](){ ui->childTogglePads->setChecked(!ui->childTogglePads->isChecked()); });

    connect(ui->iterationComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int index) { this->aed->setCprIterations(ui->iterationComboBox->itemText(index).toInt()); });

    // Initalize voice system
    connect(this->aed->getVoiceSystem(), &VoiceSystem::textInstructionUpdatedForDisplay, this, [=](){this->ui->textInstructions->append(this->aed->getVoiceSystem()->getCurrentInstruction());});
    connect(this->aed->getVoiceSystem(), &VoiceSystem::textInstructionUpdatedForDisplay, this, [=](){placeImage(this->imageInstructionScene, QString(this->aed->getVoiceSystem()->getCurrentIllustrationPath()), 160, 80, 35, 0); });
}

// Function that is ran on the UI contructor to update UI
void MainWindow::initializeStartingUI() {

    // Setting up active and battery indicator
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

    // Set the process radio buttons to disabled
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

    // If it is not on
    if(!this->aed->getIsOn()) {
        // Do a self check and pass the value into the selfCheckUI function
        selfCheckUI(this->aed->getIsFunctional());
    }else{
        // Clear both scenes
        this->instructionScene->clear();
        this->waveFormScene->clear();
        this->imageInstructionScene->clear();
        ui->textInstructions->clear();

        this->aed->getCPRTimer()->stop();
        this->aed->getCPRElapsedTimer()->invalidate();
        this->aed->getCPRElapsedTimer()->invalidate();


        // Reset the radio btns to their default values
        resetRadioBtns();

        // Disable the adult and child electrode btns
        ui->placeElectrodesBtn->setEnabled(false);
        // Disable the misplace pad btn
        ui->misPlacePad->setEnabled(false);
    }
    // Set us on to the negation of itself
    this->aed->setIsOn(!this->aed->getIsOn());
}

// Resets the radio btns to their original state
void MainWindow::resetRadioBtns(){
    // Set the stylesheets to the defualt blackUnfilledRBIndicator
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
    animation->setDuration(3000);
    animation->setStartValue(0);
    animation->setEndValue(100);

    // Generate a random stop value
    int randomStopValue = QRandomGenerator::global()->bounded(100);
    QObject::connect(animation, &QPropertyAnimation::finished, [this]() {
        if(this->aed->getIsFunctional()){
            displayDummy();
            this->aed->getVoiceSystem()->initiateAudioAndTextIntruction("qrc:/audios/src/audios/UnitOkay.mp3", ":/images/src/img/check_mark_img.png", "Unit okay. Call 911");
        }
    });


    // When the value is changed check if we need to stop the animation
    QObject::connect(animation, &QPropertyAnimation::valueChanged, [this, animation, randomStopValue, isSuccessful](const QVariant &value) {
        // Check if the current value is greater than or equal to the randomStop value and we want a failure
        if(value.toInt() >= randomStopValue && !isSuccessful) {
            this->aed->getVoiceSystem()->initiateAudioAndTextIntruction("qrc:/audios/src/audios/UnitNotOkay.mp3", ":/images/src/img/not_okay_img.png", "Unit not okay. Call 911");
            // Switch the is functional back to true
            this->aed->setIsFunctional(true);
            animation->stop();
        }
    });

    // Start the animation
    animation->start();
}

// Displays the dummy
void MainWindow::displayDummy() {
    // Place the dummy.jpg image on the instruction scene
    placeImage(this->instructionScene, ":/images/src/img/dummy.jpg", 186, 220, 35, 0);

    // Make the electrodes button enabled
    ui->placeElectrodesBtn->setEnabled(true);
    // Make the misplace electrodes button enabled
    ui->misPlacePad->setEnabled(true);
}

// Place btn function
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
    // If the normalSinusRhythmRB is checked then return the img path
    if(ui->normalSinusRhythmRB->isChecked()){
        return ":/images/src/img/nsr_ecg.png";
    // If the VentricularFibrillationRB is checked then return the img path
    }else if(ui->ventricularFibrillationRB->isChecked()){
        return ":/images/src/img/ventricular_fibrillation_ecg.png";
    // Otherwise return the ventricular teachycardia path
    }else{
        return ":/images/src/img/ventricular_teachycardia_ecg.png";
    }
}

// Based on an image path return a child class of CardiacArrhythmias
CardiacArrhythmias* MainWindow::imgPathToCardiac(QString imgPath) {
    if(imgPath == ":/images/src/img/ventricular_teachycardia_ecg.png"){
        return new VentricularTachycardia();
    }else if(imgPath == ":/images/src/img/ventricular_fibrillation_ecg.png"){
        return new VentricularFibrillation();
    }else{
        return new NormalSinusRhythm();
    }
}

// Takes in a radio button, two functions, boolean
void MainWindow::indiciatorSwitch(QRadioButton* radioBtn, std::function<void()> performOperations, std::function<void()> audioOperations, bool isSuccess) {
    // If the aed is on
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

        // Stop the timer after 3 iterations or the aed is turned off
        if ((*step) == 3 || !this->aed->getIsOn()) {
            // Stop and delete timer
            timer->stop();
            timer->deleteLater();
            // Only if the aed is still on determine success or failure
            if(this->aed->getIsOn()) radioBtn->setStyleSheet((isSuccess) ? MainWindow::greenRBIndicator : MainWindow::redRBIndicator);
            // preform operations after awaiting
            performOperations();
            // Delete the step
            delete step;
        } else {
            // Only increment the step value while the audio system is not playing
            // This ensures that the full audio file is read until the next one is requested
            if(!(this->aed->getVoiceSystem()->getAudioInstructions()->state() == QMediaPlayer::PlayingState)){
                (*step)++;
            }
        }
    });

    // Start the timer with an interval of 1000ms
    timer->setInterval(1000);
    timer->start();
}

// Flash the shock btn
void MainWindow::flashShockButton(){
    // If there is not a shock to administer set it to red if not red and not to red if red
    if(!this->aed->getShockAdministered()){
        ui->shock->setStyleSheet(ui->shock->styleSheet() == "" ? "background-color: red" : "");
    // Otherwise
    }else{
        // Set the style sheet to empty
        ui->shock->setStyleSheet("");
        // Set the shock to false
        this->aed->setShockAdministered(false);
        // Delete and stop the timer
        this->flashTimer->stop();
//        this->flashTimer->deleteLater();
    }
}

// Place the adult electrode
void MainWindow::placeAdultElectrodeBtn() {
    // Reset all btn states
    resetRadioBtns();
    // Determine the patient condition
    QString patientCondition = determineCondition();
    // Place the condition image on the waveFormScene
    placeImage(this->waveFormScene, patientCondition, 800, 224, 35, 0);

    // Set the aed to a victim aged from 19-100, with a random condition
    this->aed->setVictim(new Victim(QRandomGenerator::global()->bounded(19, 101), imgPathToCardiac(patientCondition)));
    // Updates the victim info UI
    updateVictimInfo();
    // Place the pads with false for the parameter isChild
    placePadsUI(false);
    // Calls the progress indicators with lambdas
    callIndicatorSwitchLambdas();
}

// Place the child electrodes
void MainWindow::placeChildElectrodeBtn() {
    // Determine the patient condition
    QString patientCondition = determineCondition();
    // Place the condition image on the waveFormScene
    placeImage(this->waveFormScene, patientCondition, 800, 224, 35, 0);

    // Set the aed to a victim aged from 5-18, with a random condition
    this->aed->setVictim(new Victim(QRandomGenerator::global()->bounded(5, 19), imgPathToCardiac(patientCondition)));
    // Updates the victim info UI
    updateVictimInfo();
    // Place the pads with false for the parameter isChild
    placePadsUI(true);
    // Calls the progress indicators with lambdas
    callIndicatorSwitchLambdas();
}

// Call the indicator progress
void MainWindow::callIndicatorSwitchLambdas() {
    qDebug() << this->aed->getPatientDisturbed();
    indiciatorSwitch(ui->checkPads, [this] () {
        // If the pads are not faulty then proced
        if(!this->aed->getFaultyPadPlacment()) {
            // Don't touch the patient
            indiciatorSwitch(ui->doNotTouchPatient, [this] () {
                if(!this->aed->getPatientDisturbed()) {
                    // Analyze the patient
                    indiciatorSwitch(ui->analyzing, [this] () {
                        // Determine a shockable rhythm if the condition is not Normal Sinus Rhythm
                        indiciatorSwitch(ui->shockableRhythm, [this] () {
                            this->ui->compression->setEnabled(true);
                            this->ui->poorCompression->setEnabled(true);
                            this->aed->setIsReadyForShock(this->aed->getVictim()->getCondition()->getConditionName() != "Normal Sinus Rhythm");
                            this->aed->readyForShockFunctionality();
                        }, [this] () { if(this->aed->getVictim()->getCondition()->getConditionName() != "Normal Sinus Rhythm")this->aed->getVoiceSystem()->initiateAudioAndTextIntruction("qrc:/audios/src/audios/ShockableHeartRhythmFound.mp3", (this->aed->getVictim()->getCondition()->getConditionName() != "Normal Sinus Rhythm") ?  ":/images/src/img/shockadvised_img.png" : ":/images/src/img/noShockAdvised.png", "Attempting to detect shockable heart rhythm"); }, (this->aed->getVictim()->getCondition()->getConditionName() != "Normal Sinus Rhythm"));
                    }, [this] () { this->aed->getVoiceSystem()->initiateAudioAndTextIntruction("qrc:/audios/src/audios/AnalyzingHR.mp3", ":/images/src/img/analyzingHeart.png", "Analyzing heart rhythm. Do not touch patient"); }, true);
                }
                this->aed->setPatientDisturbed(false);
            }, [this] () { this->aed->getVoiceSystem()->initiateAudioAndTextIntruction("qrc:/audios/src/audios/DoNotTouch.mp3", ":/images/src/img/analyzing.png", "Do not touch patient"); }, !(this->aed->getPatientDisturbed()));
        }
        // Set the faulty pad placement to false
        this->aed->setFaultyPadPlacement(false);
    }, [this] () { this->aed->getVoiceSystem()->initiateAudioAndTextIntruction((!this->aed->getFaultyPadPlacment()) ? "qrc:/audios/src/audios/PadCheckSuccess.mp3" : "qrc:/audios/src/audios/PadCheckFailed.mp3", ":/images/src/img/attachPads.png", "Apply pads to patient"); }, !this->aed->getFaultyPadPlacment());
}

// Updates the UI for the victim info
void MainWindow::updateVictimInfo() {
    // Set the name, age, and condition labels
    ui->nameLabel->setText(QString::fromStdString(this->aed->getVictim()->getName()));
    ui->ageLabel->setText(QString::number(this->aed->getVictim()->getAge()));
    ui->conditionLabel->setText(this->aed->getVictim()->getCondition()->getConditionName());
}

// Generate and ElectrodePadPair
ElectrodePadPair* MainWindow::generateElectrodePadPair(bool isChild){
    ElectrodePadPair* currentPair;
    // If the call is for a child
    if(isChild){
        // If the pad placement is faulty
        if(this->aed->getFaultyPadPlacment()){
            // Set the Pair to two child electrodes with random incorrect positions
            currentPair = new ElectrodePadPair(
                        new ChildElectrode(QRandomGenerator::global()->bounded(70, 101), QRandomGenerator::global()->bounded(80, 121)),
                        new ChildElectrode(QRandomGenerator::global()->bounded(70, 101), QRandomGenerator::global()->bounded(80, 121))
                    );
        // Otherwise get correct child pad placement
        }else{
            currentPair = new ElectrodePadPair(new ChildElectrode(60, 70), new ChildElectrode(114, 131));
        }
    // If it is an adult
    }else{
        // Check if the pad placement is faulty
        if(this->aed->getFaultyPadPlacment()){
            // Place faulty adult pads as the ElectrodePadPair
            currentPair = new ElectrodePadPair(
                        new AdultElectrode(QRandomGenerator::global()->bounded(70, 101), QRandomGenerator::global()->bounded(80, 121)),
                        new AdultElectrode(QRandomGenerator::global()->bounded(70, 101), QRandomGenerator::global()->bounded(80, 121))
                    );
        // Give the correct position
        }else{
            // Set the pair to the correct position with two adult electrode pad pairs
            currentPair = new ElectrodePadPair(new AdultElectrode(60, 70), new AdultElectrode(114, 131));
        }
    }

    // Return the currentPair
    return currentPair;
}

// Place the pads on the victim
void MainWindow::placePadsUI(bool isChild) {
    // If the upper pad is on the scene remove it
    if(this->instructionScene->items().contains(this->aed->getElectrodePadPair()->getUpperPad()->getPadRect())){
        this->instructionScene->removeItem(this->aed->getElectrodePadPair()->getUpperPad()->getPadRect());
    }
    // If the lower pad is on the scene remove it
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

void MainWindow::determineElectrodes() {
    (ui->childTogglePads->isChecked()) ? placeChildElectrodeBtn() : placeAdultElectrodeBtn();
}
