#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "uploadwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>


using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setConfig();
    std::ifstream i("config.json");
    std::string usr = "";
    std::string pwd = "";

    if(ui->recordarCheck->isChecked()){
        usr = this->getConfig().at("usuarioSUA").get<std::string>();
        pwd = this->getConfig().at("passwordSUA").get<std::string>();
    }
    ui->usuarioLineEdit->setText( QString::fromStdString(usr));
    ui->passwordLineEdit->setText( QString::fromStdString(pwd));

    std::vector<std::string> vec = this->getConfig().at("repositorios");
    for(std::size_t i=0 ; i < vec.size(); ++i){
        ui->repositorioComboBox->addItem(QString::fromStdString(vec[i]));
    }

    std::vector<std::string> folders = this->getConfig().at("carpetas");
    for(std::size_t j=0 ; j < folders.size(); ++j){
        ui->CarpetaComboBox->addItem(QString::fromStdString(folders[j]));
    }
}

MainWindow::~MainWindow()
{
    this->saveConfig();
    delete ui;
}

void MainWindow::setConfig(){
    std::ifstream i("config.json");
    i >> this->config;
    i.close();
}

json MainWindow::getConfig(){
    return this->config;
}

void MainWindow::saveConfig(){
    if(ui->recordarCheck->isChecked()){
        this->config["usuarioSUA"] = ui->usuarioLineEdit->text().toStdString();
        this->config["passwordSUA"] = ui->passwordLineEdit->text().toStdString();
    }
    else{
        this->config["usuarioSUA"] = "";
        this->config["passwordSUA"] = "";
    }

    std::list<std::string> carpetas;

    for(int index = 0; index < ui->CarpetaComboBox->count(); index++){
        carpetas.push_back(ui->CarpetaComboBox->itemText(index).toStdString());
    }
    this->config["carpetas"] = carpetas;

    std::ofstream o("config.json");
    o << std::setw(4) << config << std::endl;
    o.close();
}

void MainWindow::on_selectArtifactButton_clicked()
{
    QString artefacto = QFileDialog::getOpenFileName(this,"Seleccione artefacto",ui->artefactoLineEdit->text(),"Artefactos (*.zip)");

    if(!artefacto.isEmpty()){
        ui->artefactoLineEdit->setText(artefacto);
    }
}

void MainWindow::getUploadParams(std::string *user,std::string *password,std::string *arch,std::string *url,std::string *repo,std::string *folders){
    std::string fixFolder = this->ui->CarpetaComboBox->currentText().toStdString();
    if(fixFolder.at(0) == '/') fixFolder.erase(0,1);
    if(fixFolder.back() == '/') fixFolder.erase(fixFolder.end()-1,fixFolder.end());
    *user = ui->usuarioLineEdit->text().toStdString();
    *password = ui->passwordLineEdit->text().toStdString();
    *arch = ui->artefactoLineEdit->text().toStdString();
    *url = this->getConfig().at("nexusURL").get<std::string>();
    *repo = this->ui->repositorioComboBox->currentText().toStdString();
    *folders = fixFolder;
}

void MainWindow::on_uploadButton_clicked()
{
    if(ui->usuarioLineEdit->text().toStdString() == ""){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","El usuario no puede estar incompleto");
        messageBox.setFixedSize(500,200);
        return;
    }

    if(ui->passwordLineEdit->text().toStdString() == ""){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","La password no puede estar incompleto");
        messageBox.setFixedSize(500,200);
        return;
    }

    if(ui->artefactoLineEdit->text().toStdString() == ""){
        QMessageBox messageBox;
        messageBox.critical(nullptr,"Error","Debe seleccionar un archivo");
        messageBox.setFixedSize(500,200);
        return;
    }

    this->saveConfig();

    uploadWindow uw(this);
    uw.setModal(true);
    uw.exec();
}
