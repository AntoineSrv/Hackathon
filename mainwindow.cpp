#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init_port(); //initiation of the port
    ui->setupUi(this);
//    connect(ui->dial, SIGNAL(sliderMoved(int)), this, SLOT(transmitCmd(int)));
    // On connecte le mouvement du bouton a l'envoi de la commande
//    connect(ui->slider, SIGNAL(sliderMoved(int)), this, SLOT(transmitCmd(int)));
    // On connecte le mouvement du slider a l'envoi de la commande
    //transmitCmd(90);
    // On initialise le servo à 90°

    connect(ui->LedButton, SIGNAL(released()), this, SLOT(envoyerLed()));
    connect(ui->testButton, SIGNAL(released()), this, SLOT(envoyerTest()));
    connect(ui->InfoButton, SIGNAL(released()), this, SLOT(recupInfos()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init_port(){

    QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();

    qDebug() << "Liste des ports série disponibles : ";
    foreach(const QSerialPortInfo &serialPortInfo, serialPortInfos) {
        qDebug() << "Nom : " << serialPortInfo.portName();
        qDebug() << "Description : " << serialPortInfo.description();
        qDebug() << "Fabricant : " << serialPortInfo.manufacturer();
        qDebug() << "Identifiant du fournisseur : " << serialPortInfo.vendorIdentifier();
        qDebug() << "Identifiant du produit : " << serialPortInfo.productIdentifier();
        qDebug() << "--------------------------------------";
    }
    foreach(const QSerialPortInfo &serialPortInfo, serialPortInfos) {
        if(serialPortInfo.portName() == "COM8") { // Remplacez "STM32 Serial Port" par la description correcte du port série STM32
            serialPort.setPort(serialPortInfo);
            break;
        }
    }

    if(serialPort.open(QIODevice::ReadWrite)) {
        qDebug() << "Port série ouvert avec succès.";
        serialPort.setBaudRate(QSerialPort::Baud115200);
        // Boucle pour la lecture continue des données
        /*while(serialPort.isOpen()) {
                if(serialPort.waitForReadyRead(500)) { // Attendre jusqu'à ce que des données soient disponibles pendant 1 seconde
                    QByteArray data = serialPort.readAll();
                    qDebug() << "Données reçues :" << data;
                }
            }*/
    } else {
        qDebug() << "Impossible d'ouvrir le port série.";
    }

}
/*void MainWindow::transmitCmd(int value){
    QByteArray byte; //byte a envoyer
    qint64 bw = 0; //bytes really writen
    ui->lcdNumber->display(value);
    byte.clear(); // on efface le contenu de byte
    byte.append(value); // on ajoute "value" a byte

    if(port != NULL){ // on vérifie que le port existe toujours
        bw = port->write(byte); // on écrit les byte
        //(bw récupere le nombre de byte écris)
        qDebug() << bw << "byte(s) written | Value sent:" << value << "(dec)";
        port->flush(); // on attend la fin de la transmission
    }

}
*/

int colorLed = 1;
void MainWindow::envoyerLed(){
    serialPort.clear();
    QString message = "LED\r"; // Message à envoyer
    serialPort.write(message.toUtf8()); // Convertir la chaîne en tableau de bytes et envoyer

    qDebug() << message.toUtf8();
    if(serialPort.waitForReadyRead(2000)) { // Attendre jusqu'à ce que des données soient disponibles pendant 1 seconde
        QByteArray data = serialPort.readLine();
        qDebug() << "Données reçues :" << data;
    }
    if(colorLed==1){
        ui->LedButton->setStyleSheet("background-color: green;");
        colorLed = 0;
    } else {
        ui->LedButton->setStyleSheet("background-color: red;");
        colorLed =1;
    }

}

void MainWindow::envoyerTest(){
    //    if(serialPort.waitForReadyRead(500)) { // Attendre jusqu'à ce que des données soient disponibles pendant 1 seconde
    //        QByteArray data = serialPort.readAll();
    //        qDebug() << "Données reçues :" << data;
    //    }
    QString message = "test\r"; // Message à envoyer
    serialPort.write(message.toUtf8()); // Convertir la chaîne en tableau de bytes et envoyer
    qDebug() << message.toUtf8();
}

void MainWindow::recupInfos(){
    //if(serialPort.waitForReadyRead(100)) { // Attendre jusqu'à ce que des données soient disponibles pendant 1 seconde
    QByteArray data = serialPort.readLine();
    qDebug() << "Données reçues :" << data;
    //}
    //    QString message = "Hello, COM8!\r\n"; // Message à envoyer
    //    serialPort.write(message.toUtf8()); // Convertir la chaîne en tableau de bytes et envoyer
    qDebug() << "coucou2";
}
