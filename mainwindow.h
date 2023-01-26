#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtBluetooth>
#include <QJsonDocument>

#include <QBluetoothSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define DEVICE "24:6F:28:AA:B6:B6"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QBluetoothSocket *serial;

    bool isConnected;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

void on_update();

void connectionEstablished();

void disconnected();

void pair();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
