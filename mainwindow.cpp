/*******************************************************
* Name: InputLagTester								   *
* Create date: 29.12.2018                              *
* Author:  Tomáš "tomsk" Sabo                          *
* Purpose:  Test Input Lag / reflexes      			   *
* Usage: Runs the program, click START and click big   *
* button, when red.							  		   *
*******************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"

#include "QTimer"
#include "QElapsedTimer"
#include "QString"

QElapsedTimer timer;
int state = 1;
bool measuring = false;
int rows = 0;
int totalDuration = 0;

/*
 * States:
 *      1 - start
 *      2 - stop - running
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Click_clicked()
{
    measure("Mouse");
}

void MainWindow::on_lineEdit_textChanged()
{
    measure("Keyboard");
}

void MainWindow::on_pushButton_State_clicked()
{
    toggleState();
}

void MainWindow::toggleState()
{
    if(state == 1) { //START
        ui->pushButton_State->setText("STOP");
        state = 2;
        MainWindow::setUI("", 0, true);
        MainWindow::wait(5000);
    } else if(state == 2) { //STOP
        ui->pushButton_State->setText("START AGAIN");
        state = 1;
        MainWindow::setButtonClass("");
        measuring = false;
    }
}

void MainWindow::redButton()
{
    if(state == 1) {
        return;
    }

    MainWindow::setButtonClass("active");

    measuring = true;
    timer.restart();
}

void MainWindow::setButtonClass(QString value)
{
    ui->pushButton_Click->setProperty("class", value);
    ui->pushButton_Click->style()->unpolish(ui->pushButton_Click);
    ui->pushButton_Click->style()->polish(ui->pushButton_Click);
}

void MainWindow::measure(QString device)
{
    int elapsed = timer.elapsed();

    if(!measuring){
        return;
    }

    totalDuration += elapsed;
    rows++;

    MainWindow::setUI(device, elapsed, false);

    MainWindow::wait(0);
}

void MainWindow::setUI(QString device, int elapsed, bool reset)
{
    MainWindow::setButtonClass("");

    if(reset){
        ui->listWidget->clear();
        ui->label_Count->setText("Count: N/A");
        ui->label_Average->setText("Average: N/A ms");
        rows = 0;
        totalDuration = 0;
    } else {
        ui->listWidget->addItem("#" + QString::number(rows) + "  Device: " + device + "  Time: " + QString::number(elapsed) + " ms");
        ui->label_Count->setText("Count: " + QString::number(rows));
        ui->label_Average->setText("Average: " + QString::number(totalDuration / rows) + " ms");
    }

    measuring = false;
}

void MainWindow::wait(int lenght)
{
    srand(time(NULL));
    int randnumber = (rand() % 41 + 10) * 100; //min 1 sec, max 5 sec
    QTimer::singleShot(lenght + randnumber, this, SLOT(redButton()));
}

