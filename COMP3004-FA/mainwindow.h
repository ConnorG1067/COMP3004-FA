#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

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
    // function to setup connections-
    void initializeBtns();
    void initializeStartingUI();
    void selfCheckUI();

private slots:  
    void powerBtn();

};
#endif // MAINWINDOW_H
