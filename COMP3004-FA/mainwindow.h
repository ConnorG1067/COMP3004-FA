#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QGraphicsProxyWidget>
#include <QTimer>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QGraphicsOpacityEffect>
#include <QThread>
#include <QRadioButton>
#include "AED.h"
#include "Victim.h"
#include "CardiacArrhythmias.h"
#include "NormalSinusRhythm.h"
#include "VentricularFibrillation.h"
#include "VentricularTachycardia.h"
#include "ChildElectrode.h"
#include "AdultElectrode.h"
#include <functional>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* instructionScene;
    QGraphicsScene* imageInstructionScene;
    QGraphicsScene* waveFormScene;

    AED* aed;
    VoiceSystem* vs;

    // Timers
    QTimer* flashTimer;

    // QRadioButton Colors
    static QString yellowRBIndicator;
    static QString greenRBIndicator;
    static QString redRBIndicator;
    static QString blackUnfilledRBIndicator;

    // function to setup connections-
    void initializeBtns();
    void initializeStartingUI();
    void selfCheckUI(bool);
    void displayDummy();

    // Helpers
    void placeImage(QGraphicsScene*, QString, int, int, int, int);
    QString determineCondition();
    CardiacArrhythmias* imgPathToCardiac(QString);
    void updateVictimInfo();
    void placePadsUI(bool);
    ElectrodePadPair* generateElectrodePadPair(bool);
    void indiciatorSwitch(QRadioButton*, std::function<void()>, bool);

private slots:  
    void powerBtn();
    void failAEDSetupBtn();
    void displayTextInstruction(QString);
    void placeAdultElectrodeBtn();
    void placeChildElectrodeBtn();
    void flashShockButton();

};
#endif // MAINWINDOW_H
