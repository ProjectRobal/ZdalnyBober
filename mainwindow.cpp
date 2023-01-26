#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_AcceptTouchEvents, true);

    QObject::connect(ui->stick,&Joystick::updated,this,&MainWindow::on_update);

    this->serial=new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol,this);

    QObject::connect(this->serial,&QBluetoothSocket::connected,this,&MainWindow::connectionEstablished);

    QObject::connect(this->serial,&QBluetoothSocket::disconnected,this,&MainWindow::disconnected);

    isConnected=false;

    ui->label->setText("Disconnected!!");

    ui->info->setText("No nima połączenia");

    ui->connect->setText("Disconnected!!");

    QObject::connect(ui->connect,&QPushButton::clicked,this,&MainWindow::pair);

    pair();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString Trans_Direction(Joystick::Direction dir)
{
    switch(dir)
    {
    case Joystick::Direction::FORWARD:
            return "Forward";
        break;

    case Joystick::Direction::BACKWARD:
            return "Backward";
        break;
    }
}

void MainWindow::on_update()
{
    if(!isConnected && !this->serial->isOpen())
    {
        ui->label->setText("Disconnected!!");
        return;
    }

    ui->label->setText("Angel: "+QString::number(ui->stick->Angel()));

    ui->info->setText(" Dir: "+Trans_Direction(ui->stick->GetDirection()));

    QJsonObject object;

    object["angel"]=ui->stick->Angel();

    object["speed"]=ui->stick->Speed();

    object["mode"]=ui->stick->GetDirection();

    qDebug()<<QJsonDocument(object).toJson();
    qDebug()<<QJsonDocument(object).toJson().size();

    serial->write(QJsonDocument(object).toJson());
}

void MainWindow::connectionEstablished()
{
    isConnected=true;
    ui->connect->setText("Connected!!");
}

void MainWindow::disconnected()
{
    isConnected=false;
    ui->connect->setText("Disconnected!!");
    ui->info->setText("No nima połączenia");
}

void MainWindow::pair()
{
    const QString uuid=QStringLiteral("00001101-0000-1000-8000-00805F9B34FB");
    this->serial->connectToService(QBluetoothAddress(DEVICE),QBluetoothUuid(uuid),QIODevice::WriteOnly);
}

