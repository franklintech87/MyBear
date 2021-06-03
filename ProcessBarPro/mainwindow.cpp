#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* process bar */
    ui->processbar->setTitleText(tr("Remain"));
    connect(ui->slider, &QSlider::valueChanged,
            ui->processbar, &ProcessBar::updateValue_slot);

    /* auto display */
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout,
            this, &MainWindow::autoDisplay_slot);
    m_timer->start(20);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::autoDisplay_slot()
{
    static int value = 0;
    ui->slider->setValue(value++);
    if (value > 100) {
        m_timer->stop();
    }
}
