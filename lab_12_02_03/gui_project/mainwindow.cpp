#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "primes.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    primesArray = nullptr;
    injectedArray = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonGeneratePrimes_clicked()
{
    primesLength = ui->inputPrimesAmount->value();

    delete[]primesArray;
    primesArray = new int[primesLength];

    gen_prime_array(primesArray, primesLength);

    QString displayText("");

    for (int i = 0; i < primesLength; i++)
    {
        displayText.append(QString::number(primesArray[i]) + QString(" "));
    }

    ui->outputPrimes->setText(displayText);
}

void MainWindow::on_buttonInject_clicked()
{
    injectedLength = primesLength << 1;

    delete[]injectedArray;
    injectedArray = new int[injectedLength];

    inject_number(primesArray, primesLength, ui->inputInjectNumber->value(), injectedArray);

    QString displayText("");

    for (int i = 0; i < injectedLength; i++)
    {
        displayText.append(QString::number(injectedArray[i]) + QString(" "));
    }

    ui->outputInjected->setText(displayText);
}


void MainWindow::on_buttonHelp_clicked()
{
    QMessageBox::information(
                this,
                "Помощь",
                "В поле \"Primes Amount\" введите число простых чисел, которое вы желаете сгенерировать, "
                "после чего, нажмите кнопку \"Generate Primes\". "
                "В первой строке появится получившийся массив простых чисел.\n"
                "Введите в поле \"Number to inject\" число, которое вы хотите вставить в промежутки между "
                "другими числами в первой строке. По нажатии кнопки \"Inject Number\" вы увидите результат.");
}

