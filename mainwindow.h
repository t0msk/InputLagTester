#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Click_clicked();

    void on_pushButton_State_clicked();

    void toggleState();

    void redButton();

    void setButtonClass(QString);

    void measure(QString);

    void wait(int);

    void setUI(QString, int, bool);

    void on_lineEdit_textChanged();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
