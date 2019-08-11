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
// serial commands are sent as ASCII code, so Arduino
// will read them as integers ranging from 97-106

void MainWindow::on_push_pal1_clicked()
{
    arduino->write("a");
}

void MainWindow::on_push_pal1_2_clicked()
{
    arduino->write("b");
}

void MainWindow::on_push_pal1_3_clicked()
{
    arduino->write("c");
}

void MainWindow::on_push_pal1_4_clicked()
{
    arduino->write("d");
}

void MainWindow::on_push_pal1_5_clicked()
{
    arduino->write("e");
}


void MainWindow::on_pushButton_clicked()
{
    arduino->write("0");
}

void MainWindow::on_pushButton_2_clicked()
{
   arduino->write("1");
}

void MainWindow::on_pushButton_3_clicked(bool disconnect)
{
   if(disconnect==false)
   {
       disconnect=true;
       arduino->close();
   }
}

void MainWindow::on_push_pal1_10_clicked()
{
    arduino->write("f");
}

void MainWindow::on_push_pal1_9_clicked()
{
    arduino->write("g");
}

void MainWindow::on_push_pal1_7_clicked()
{
    arduino->write("h");
}

void MainWindow::on_push_pal1_8_clicked()
{
    arduino->write("i");
}

void MainWindow::on_push_pal1_6_clicked()
{
    arduino->write("j");
}

void MainWindow::on_push_pal1_11_clicked()
{
    arduino->write("k");
}


