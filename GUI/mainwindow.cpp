#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    arduino = new QSerialPort(this);

    arduino->setPortName("COM3");
    arduino->open(QSerialPort::ReadWrite);
    arduino->setBaudRate(QSerialPort::Baud9600);
    arduino->setDataBits(QSerialPort::Data8);
    arduino->setFlowControl(QSerialPort::NoFlowControl);
    arduino->setParity(QSerialPort::NoParity);
    arduino->setStopBits(QSerialPort::OneStop);
    QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));

    if(!arduino->isOpen())
    {
        QMessageBox::warning(this, "port error", "Serial Port not Opened!");
        ui->statusLabel->setText("Not Connected!");
    }
    else
    {
         QMessageBox::information(this, "Serial Port OK", "Connected.");
         ui->statusLabel->setText("Connected Successfully");
    }



}

MainWindow::~MainWindow()
{
    delete ui;
    arduino->close();
}



//*************************************  SERIAL COMMANDS


void MainWindow::on_push_pal1_clicked()
{
    arduino->write("1");
}

void MainWindow::on_push_pal1_2_clicked()
{
    arduino->write("2");
}

void MainWindow::on_push_pal1_3_clicked()
{
    arduino->write("3");
}

void MainWindow::on_push_pal1_4_clicked()
{
    arduino->write("4");
}

void MainWindow::on_push_pal1_5_clicked()
{
    arduino->write("5");
}

void MainWindow::on_push_pal1_6_clicked()
{
    arduino->write("6");
}

void MainWindow::on_push_pal1_7_clicked()
{
    arduino->write("7");
}

void MainWindow::on_push_pal1_8_clicked()
{
    arduino->write("8");
}
