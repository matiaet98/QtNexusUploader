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
    config["nexusURL"] = "https://nexus.cloudint.afip.gob.ar/nexus/repository/";
    config["repositorios"] = {
            "fisca-analisis-sectoriales-raw",
            "fisca-controles-raw",
            "fisca-devoluciones-raw",
            "fisca-etl-raw",
            "fisca-facturacion-registracion-raw",
            "fisca-infraestructura-raw",
            "fisca-internacional-raw",
            "fisca-scoring-raw",
            "fisca-seguimiento-acciones-raw",
            "fisca-seleccion-casos-raw",
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
