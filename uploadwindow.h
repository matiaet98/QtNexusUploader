#ifndef UPLOADWINDOW_H
#define UPLOADWINDOW_H

#include <QDialog>
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
    bool VerSiExiste();
    bool generarMD5();
    bool generarSHA1();
    bool Subir();
    std::string usuario;
    std::string password;
    std::string archivo;
    std::string url;
    std::string repositorio;
    std::string carpeta;
};

#endif // UPLOADWINDOW_H
