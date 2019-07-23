#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_push_pal1_clicked();

    void on_push_pal1_2_clicked();

    void on_push_pal1_3_clicked();

    void on_push_pal1_4_clicked();

    void on_push_pal1_5_clicked();

    void on_push_pal1_6_clicked();

    void on_push_pal1_7_clicked();

    void on_push_pal1_8_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    static const quint16 arduino_uno_vendor_id = 9025;
    static const quint16 arduino_uno_product_id = 67;
};

#endif // MAINWINDOW_H
