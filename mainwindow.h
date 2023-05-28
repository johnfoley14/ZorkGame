
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "Parser.h"
#include "ZorkUL.h"
#include "Character.h"
#include "ZorkUL.h"
#include <QTimer>
#include <QMainWindow>
#include <Qlabel>
#include <QPushButton>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    ZorkUL temp;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    string storedText = "";
    Parser parser;
    string outputTextBrowser;
    void setOutputText(string outputText);
    void CommandController(string inputText);
    bool gameWon;


private slots:
    void on_pushButton_clicked();

    void on_lineEdit_returnPressed();

    void on_northButton_clicked();

    void on_westButton_clicked();

    void on_southButton_clicked();

    void on_eastButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_mapButton_clicked();

private:
    Ui::MainWindow *ui;
    std::function<void()> closeWindowLambda;
    QTimer* closeTimer;
    int showMap = 0;
    QPushButton *button;
    QPixmap pixmap;
    bool isPixmapVisible;
    void showMapView();

};

#endif // MAINWINDOW_H
