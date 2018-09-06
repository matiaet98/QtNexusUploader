#include "uploadwindow.h"
#include "ui_uploadwindow.h"
#include "mainwindow.h"
#include <QCryptographicHash>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QStringListModel>
#include <QFileInfo>
#include <QUrl>

uploadWindow::uploadWindow(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::uploadWindow)
{
    ui->setupUi(this);

    this->ui->barraProgreso->setMinimum(0);
    this->ui->barraProgreso->setMaximum(100);

    parent->getUploadParams(
        &this->usuario,
        &this->password,
        &this->archivo,
        &this->url,
        &this->repositorio,
        &this->carpeta);

    QStringListModel *model = new QStringListModel(this);
    QStringList lst;
    ui->listaProgreso->setModel(model);

    lst.push_back("Generando MD5...");
    model->setStringList(lst);

    if(!this->generarMD5()){
        lst.push_back("fallo al generar MD5");
        model->setStringList(lst);
        return;
    }

    lst.push_back("MD5 generado");
    model->setStringList(lst);
    this->ui->barraProgreso->setValue(10);

    lst.push_back("Generando SHA1...");
    model->setStringList(lst);
    this->generarSHA1();

    if(!this->generarSHA1()){
        lst.push_back("fallo al generar SHA1");
        model->setStringList(lst);
        return;
    }

    lst.push_back("SHA1 generado");
    model->setStringList(lst);
    this->ui->barraProgreso->setValue(20);

    lst.push_back("Creando links");
    QFile file(QString::fromStdString(this->archivo));
    file.open(QIODevice::ReadOnly);
    QFileInfo fileInfo(file.fileName());
    this->filename = QString(fileInfo.fileName());
    this->buildLinks();
    model->setStringList(lst);
    this->ui->barraProgreso->setValue(50);

    lst.push_back("Chequeando si ya existen en Nexus");
    manager = new QNetworkAccessManager();
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(managerFinished(QNetworkReply*)));

    model->setStringList(lst);
    if(this->VerSiExiste(this->link)){
        lst.push_back("El archivo ZIP ya existe");
        model->setStringList(lst);
        return;
    }
    this->ui->barraProgreso->setValue(60);

}

uploadWindow::~uploadWindow()
{
    delete ui;
    delete manager;
}

bool uploadWindow::generarMD5(){
    try {
        QFile file(QString::fromStdString(this->archivo));
        if(!file.exists()){
            return false;
        }
        file.open(QIODevice::ReadOnly);
        QByteArray md5Hash = QCryptographicHash::hash(file.readAll(),QCryptographicHash::Md5);
        QFileInfo fileInfo(file.fileName());
        QString filenameMD5(fileInfo.fileName()+".md5");
        QString pathMD5 = fileInfo.path();
        file.close();
        QString fullNameMD5;
        #ifdef Q_OS_WIN
            fullNameMD5 = pathMD5+"\\"+filenameMD5;
        #else
            fullNameMD5 = pathMD5+"/"+filenameMD5;
        #endif
        QFile fileMD5(fullNameMD5);
        fileMD5.open(QIODevice::WriteOnly);
        QTextStream stream(&fileMD5);
        stream << md5Hash.toHex() << endl;
        fileMD5.close();
        return true;
    } catch (int e) {
        qDebug()<< "Excepcion: " << e;
        return false;
    }
}

bool uploadWindow::generarSHA1(){
    try {
        QFile file(QString::fromStdString(this->archivo));
        if(!file.exists()){
            return false;
        }
        file.open(QIODevice::ReadOnly);
        QByteArray sha1Hash = QCryptographicHash::hash(file.readAll(),QCryptographicHash::Sha1);
        QFileInfo fileInfo(file.fileName());
        QString filenameSha1(fileInfo.fileName()+".sha1");
        QString pathSha1 = fileInfo.path();
        file.close();
        QString fullNameSha1;
        #ifdef Q_OS_WIN
            fullNameSha1 = pathSha1+"\\"+filenameSha1;
        #else
            fullNameSha1 = pathSha1+"/"+filenameSha1;
        #endif
        QFile fileSha1(fullNameSha1);
        fileSha1.open(QIODevice::WriteOnly);
        QTextStream stream(&fileSha1);
        stream << sha1Hash.toHex() << endl;
        fileSha1.close();
        return true;
    } catch (int e) {
        qDebug()<< "Excepcion: " << e;
        return false;
    }
}

void uploadWindow::buildLinks(){
    this->link = QUrl(QString::fromStdString(this->url)+QString::fromStdString(this->repositorio)+"/"+QString::fromStdString(this->carpeta)+"/"+ this->filename);
    this->linkMD5 = QUrl(QString::fromStdString(this->url)+QString::fromStdString(this->repositorio)+"/"+QString::fromStdString(this->carpeta)+"/"+this->filename+".md5");
    this->linkSHA1 = QUrl(QString::fromStdString(this->url)+QString::fromStdString(this->repositorio)+"/"+QString::fromStdString(this->carpeta)+"/"+this->filename+".sha1");
}

bool uploadWindow::Subir(){
    return true;
}

bool uploadWindow::VerSiExiste(QUrl url){

    return true;
}
void uploadWindow::on_salirBoton_clicked()
{

}

void uploadWindow::managerFinished(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << reply->errorString();
        return;
    }

    QString answer = reply->readAll();

    qDebug() << answer;
}
