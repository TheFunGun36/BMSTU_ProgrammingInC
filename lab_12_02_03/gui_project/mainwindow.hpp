#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    int *primesArray;
    int primesLength;
    int *injectedArray;
    int injectedLength;

    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *inputPrimesAmount;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *buttonGeneratePrimes;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *outputPrimes;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *inputInjectNumber;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *buttonInject;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *outputInjected;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonHelp;
};
#endif // MAINWINDOW_H
