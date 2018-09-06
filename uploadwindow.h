#ifndef UPLOADWINDOW_H
#define UPLOADWINDOW_H

#include <QDialog>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
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
    void managerFinished(QNetworkReply *reply);
    void on_salirBoton_clicked();


private:
    Ui::uploadWindow *ui;
    bool VerSiExiste(QUrl url);
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
    QUrl link;
    QUrl linkMD5;
    QUrl linkSHA1;
    QNetworkAccessManager *manager;
    QNetworkRequest request;

};

#endif // UPLOADWINDOW_H
