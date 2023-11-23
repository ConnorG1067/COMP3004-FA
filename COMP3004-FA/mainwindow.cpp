#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    vs = new VoiceSystem();

    // Initialize Buttons
    initializeBtns();
    initializeStartingUI();

    this->aed = new AED();


    vs->analyzingHeartRhythmDoNotTouch();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::initializeBtns(){
    connect(ui->onOffBtn, SIGNAL(released()), this, SLOT(powerBtn()));
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

    connect(this->vs, &VoiceSystem::textInstructionUpdatedForDisplay, this, [=](){this->ui->textInstructions->append(this->vs->getCurrentInstruction());});
}

// Toggles the on and off buttons
void MainWindow::powerBtn() {
    // If we can power the aed on update the UI
    if(this->aed->powerOn()){
        ui->activeIndicator->setChecked(!ui->activeIndicator->isChecked());
        ui->batteryIndicator->setChecked(!ui->batteryIndicator->isChecked());
    }

    selfCheckUI(this->aed->selfCheck());
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
    // Create a scene and add it to the instructionGraphicsView
    QGraphicsScene* scene = new QGraphicsScene();
    ui->instructionGraphics->setScene(scene);

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
    scene->addItem(proxyWidget);
    scene->addItem(textItem);

    // Create and animation
    QPropertyAnimation *animation = new QPropertyAnimation(progressBar, "value");
    animation->setDuration(3000); // Animation duration in milliseconds
    animation->setStartValue(0);
    animation->setEndValue(100);

    // Generate a random stop value
    int randomStopValue = QRandomGenerator::global()->bounded(100);

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





