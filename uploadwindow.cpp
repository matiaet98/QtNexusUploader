#include "uploadwindow.h"
#include "ui_uploadwindow.h"
#include "mainwindow.h"
#include <QCryptographicHash>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QStringListModel>

uploadWindow::uploadWindow(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::uploadWindow)
{
    ui->setupUi(this);
    parent->getUploadParams(
        &this->usuario,
        &this->password,
        &this->archivo,
        &this->url,
        &this->repositorio,
        &this->carpeta);

    //qDebug()<< QString::fromStdString(this->usuario);

    QStringListModel *model = new QStringListModel(this);
    QStringList lst;
    lst.push_back(QString::fromStdString(this->carpeta));
    model->setStringList(lst);
    ui->listaProgreso->setModel(model);
}

uploadWindow::~uploadWindow()
{
    delete ui;
}

bool uploadWindow::VerSiExiste(){
    return true;
}
bool uploadWindow::generarMD5(){

    QFile file("");
    file.open(QIODevice::ReadOnly);
    QByteArray hashData = QCryptographicHash::hash(file.readAll(),QCryptographicHash::Md5);
    qDebug() << hashData.toHex();
    //QString md5Hash = QString(QCryptographicHash::hash(("myPassword"),QCryptographicHash::Md5).toHex());
    return true;

}
bool uploadWindow::generarSHA1(){
    return true;

}
bool uploadWindow::Subir(){
    return true;
}

void uploadWindow::on_salirBoton_clicked()
{

}

