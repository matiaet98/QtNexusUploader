#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"

using json = nlohmann::json;

bool checkConfig(){

    std::ifstream ifile("config.json");
    return ifile.good();
}

void createConfig(){

    json config;

    config["usuarioSUA"] = "Uxxxxx";
    config["passwordSUA"] = "";
    config["nexusURL"] = "http://localhost:8081/repository/";
    config["repositorios"] = {
            "fisca-analisis-sectoriales-raw",
            "fisca-scoring-raw",
            "fisca-etl-raw",
            "fisca-devoluciones-raw",
            "fisca-facturacion-registracion-raw",
            "fisca-seguimiento-acciones-raw",
            "fisca-infraestructura-raw",
            "fisca-seleccion-casos-raw",
            "fisca-internacional-raw"
    };
    config["carpetas"] = {
            "efisco/efisco-backend-sql",
            "efisco/efisco-application-sql"
    };

    //Guardo archivo
    std::ofstream o("config.json");
    o << std::setw(4) << config << std::endl;
    o.close();
}

int main(int argc, char *argv[])
{
    if(!checkConfig()){
        createConfig();
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
