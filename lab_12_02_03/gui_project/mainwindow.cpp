#include "mainwindow.hpp"
#include "primes.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
    resize(800, 600);
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setText(QString("Количество простых:"));

    horizontalLayout->addWidget(label);

    inputPrimesAmount = new QSpinBox(centralwidget);
    inputPrimesAmount->setObjectName(QString::fromUtf8("inputPrimesAmount"));
    inputPrimesAmount->setMinimum(1);

    horizontalLayout->addWidget(inputPrimesAmount);

    buttonGeneratePrimes = new QPushButton(centralwidget);
    buttonGeneratePrimes->setObjectName(QString::fromUtf8("buttonGeneratePrimes"));
    buttonGeneratePrimes->setText(QString("Сгенерировать числа"));
    QObject::connect(buttonGeneratePrimes,
                     &QPushButton::clicked,
                     this,
                     &MainWindow::on_buttonGeneratePrimes_clicked);

    horizontalLayout->addWidget(buttonGeneratePrimes);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_3);

    verticalLayout->addLayout(horizontalLayout);

    outputPrimes = new QLineEdit(centralwidget);
    outputPrimes->setObjectName(QString::fromUtf8("outputPrimes"));
    outputPrimes->setReadOnly(true);

    verticalLayout->addWidget(outputPrimes);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
    label_2 = new QLabel(centralwidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setText(QString("Число для вставки:"));

    horizontalLayout_2->addWidget(label_2);

    inputInjectNumber = new QSpinBox(centralwidget);
    inputInjectNumber->setObjectName(QString::fromUtf8("inputInjectNumber"));
    inputInjectNumber->setMinimum(-99);

    horizontalLayout_2->addWidget(inputInjectNumber);

    horizontalSpacer_5 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_5);

    buttonInject = new QPushButton(centralwidget);
    buttonInject->setObjectName(QString::fromUtf8("buttonInject"));
    buttonInject->setText(QString("Вставить число"));
    connect(buttonInject, &QPushButton::clicked, this, &MainWindow::on_buttonInject_clicked);

    horizontalLayout_2->addWidget(buttonInject);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);

    verticalLayout->addLayout(horizontalLayout_2);

    outputInjected = new QLineEdit(centralwidget);
    outputInjected->setObjectName(QString::fromUtf8("outputInjected"));
    outputInjected->setReadOnly(true);

    verticalLayout->addWidget(outputInjected);

    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout->addItem(verticalSpacer);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer);

    buttonHelp = new QPushButton(centralwidget);
    buttonHelp->setObjectName(QString::fromUtf8("buttonHelp"));
    buttonHelp->setText(QString("Помощь"));
    connect(buttonHelp, &QPushButton::clicked, this, &MainWindow::on_buttonHelp_clicked);

    horizontalLayout_3->addWidget(buttonHelp);

    verticalLayout->addLayout(horizontalLayout_3);

    setCentralWidget(centralwidget);

    primesArray = nullptr;
    injectedArray = nullptr;
}

MainWindow::~MainWindow() {}

void MainWindow::on_buttonGeneratePrimes_clicked()
{
    primesLength = inputPrimesAmount->value();

    delete[]primesArray;
    primesArray = new int[primesLength];

    gen_prime_array(primesArray, primesLength);

    QString displayText("");

    for (int i = 0; i < primesLength; i++)
    {
        displayText.append(QString::number(primesArray[i]) + QString(" "));
    }

    outputPrimes->setText(displayText);
}

void MainWindow::on_buttonInject_clicked()
{
    injectedLength = primesLength << 1;

    delete[]injectedArray;
    injectedArray = new int[injectedLength];

    inject_number(primesArray, primesLength, inputInjectNumber->value(), injectedArray);

    QString displayText("");

    for (int i = 0; i < injectedLength; i++)
    {
        displayText.append(QString::number(injectedArray[i]) + QString(" "));
    }

    outputInjected->setText(displayText);
}


void MainWindow::on_buttonHelp_clicked()
{
    QMessageBox::information(
        this,
        "Помощь",
        "В поле \"Количество простых\" введите число простых чисел, которое вы желаете "
        "сгенерировать, после чего, нажмите кнопку \"Сгенерировать числа\". "
        "В первой строке появится получившийся массив простых чисел.\n"
        "Введите в поле \"Число для вставки\" число, которое вы хотите вставить в после каждого "
        "простого числа из первой строки. По нажатии кнопки \"Вставить число \" вы увидите "
        "результат.");
}

