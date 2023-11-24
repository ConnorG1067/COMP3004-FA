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
#include "AED.h"
#include "Victim.h"
#include "CardiacArrhythmias.h"
#include "NormalSinusRhythm.h"
#include "VentricularFibrillation.h"
#include "VentricularTachycardia.h"
#include "ChildElectrode.h"
#include "AdultElectrode.h"



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
    // function to setup connections-
    void initializeBtns();
    void initializeStartingUI();
    void selfCheckUI(bool);
    void displayDummy();
    void displayIllustration();

    // Helpers
    void placeImage(QGraphicsScene*, QString, int, int, int, int);
    QString determineCondition();
    CardiacArrhythmias* imgPathToCardiac(QString);
    void updateVictimInfo();
    void placePadsUI(bool);
    ElectrodePadPair* generateElectrodePadPair(bool);

private slots:  
    void powerBtn();
    void failAEDSetupBtn();
    void displayTextInstruction(QString);
    void placeAdultElectrodeBtn();
    void placeChildElectrodeBtn();

};
#endif // MAINWINDOW_H
