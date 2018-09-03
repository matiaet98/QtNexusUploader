#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "json.hpp"

using json = nlohmann::json;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    json getConfig();
    void setConfig();
    void saveConfig();
    void getUploadParams(std::string *user,std::string *password,std::string *arch,std::string *url,std::string *repo,std::string *folders);


private slots:
    void on_selectArtifactButton_clicked();

    void on_uploadButton_clicked();

private:
    Ui::MainWindow *ui;
    json config;
};

#endif // MAINWINDOW_H
