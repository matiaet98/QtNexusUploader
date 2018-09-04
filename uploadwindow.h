#ifndef UPLOADWINDOW_H
#define UPLOADWINDOW_H

#include <QDialog>
#include <QUrl>
#include "mainwindow.h"

namespace Ui {
class uploadWindow;
}

class uploadWindow : public QDialog
{
    Q_OBJECT

public:
    explicit uploadWindow(MainWindow *parent = nullptr);
    ~uploadWindow();

private slots:
    void on_salirBoton_clicked();


private:
    Ui::uploadWindow *ui;
    bool VerSiExiste(std::string url);
    bool generarMD5();
    bool generarSHA1();
    bool Subir();
    void buildLinks();
    std::string usuario;
    std::string password;
    std::string archivo;
    std::string url;
    std::string repositorio;
    std::string carpeta;
    QString filename;
    std::string link;
    std::string linkMD5;
    std::string linkSHA1;
};

#endif // UPLOADWINDOW_H
