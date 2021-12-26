#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonGeneratePrimes_clicked();

    void on_buttonInject_clicked();

    void on_buttonHelp_clicked();

private:
    Ui::MainWindow *ui;
    int *primesArray;
    int primesLength;
    int *injectedArray;
    int injectedLength;
};
#endif // MAINWINDOW_H
