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
#include "AED.h"

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
    AED* aed;
    VoiceSystem* vs;
    // function to setup connections-
    void initializeBtns();
    void initializeStartingUI();
    void selfCheckUI(bool);

private slots:  
    void powerBtn();
    void failAEDSetupBtn();
    void displayTextInstruction(QString);

};
#endif // MAINWINDOW_H
