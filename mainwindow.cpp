
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <string>
#include <chrono>
#include <thread>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ZorkUL temp;

    closeWindowLambda = [this]() {

        this->close();


    };

    closeTimer = new QTimer(this);
    closeTimer->setSingleShot(true);
    connect(closeTimer, &QTimer::timeout, this, closeWindowLambda);

    QSize labelSize3 = ui->mapLabel3->size();
    pixmap.load("C:/Users/johnm/Downloads/map.png");
    ui->mapLabel3->setPixmap(pixmap.scaled(labelSize3, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//    connect("reference to button", &MainWindow::pressed, this, &MainWindow::onButtonPressed)
}

MainWindow::~MainWindow()
{
    delete ui;
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //    temp.play(false);
    //    return 0;
    return a.exec();
}



void MainWindow::on_pushButton_clicked()
{
    // Get the text from the line edit
    QString text = ui->lineEdit->text();

    // Store the text in the variable
    storedText = text.toStdString();

    // Clear the line edit
    ui->lineEdit->clear();
    CommandController(storedText);
}



void MainWindow::on_lineEdit_returnPressed()
{
    QString text = ui->lineEdit->text();
    storedText = text.toStdString();
    ui->lineEdit->clear();
    CommandController(storedText);
}

void MainWindow::setOutputText(string outputText){
    setEnabled(false);

    if(outputText=="Game is completed"){
        gameWon = true;
        QString qstrOutputText = QString::fromStdString(outputText);
        ui->textBrowser->append(qstrOutputText);
        ui->textBrowser_2->append(qstrOutputText);
        std::this_thread::sleep_for(std::chrono::seconds(5));
        closeWindowLambda();
    }
    else if(outputText=="dead"){
        QString qstrOutputText = QString::fromStdString(outputText);
        ui->textBrowser->append(qstrOutputText);
        ui->textBrowser_2->append(qstrOutputText);
        closeTimer->start(5000);
    }
    else{
        QString qstrOutputText = QString::fromStdString(outputText);
        ui->textBrowser->append(qstrOutputText);
        ui->textBrowser_2->append(qstrOutputText);
        setEnabled(true);
    }
    // check to see if the string back is "Game is completed" if it is then end game after by setting gamewon to true,
    // but also send a output text to the UI
}

void MainWindow::CommandController(string inputText){
    parser.getInput(inputText);
    if(!gameWon){
        if(inputText.compare("map")==0){
            showMapView();
    }
    else{
        Command* command = parser.getCommand();
        // Pass dereferenced command and check for end of game.
        string response = temp.processCommand(*command);
        setOutputText(response);
    }
    }
}

//Gui based controls

void MainWindow::on_northButton_clicked()
{
    CommandController("go north");
}


void MainWindow::on_westButton_clicked()
{
    CommandController("go west");
}


void MainWindow::on_southButton_clicked()
{
    CommandController("go south");
}


void MainWindow::on_eastButton_clicked()
{
    CommandController("go east");
}


void MainWindow::on_upButton_clicked()
{
    CommandController("go up");
}


void MainWindow::on_downButton_clicked()
{
    CommandController("go down");
}


void MainWindow::on_mapButton_clicked()
{
//    QSize labelSize = ui->mapLabel->size();

//    pixmap.load("C:/Users/johnm/Downloads/map.png");

//    if(showMap%2 ==0){
//        ui->mapLabel->setPixmap(pixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));

//    }else{
//        ui->mapLabel->clear();
//    }
//    showMap = showMap +1;
    showMapView();

}

void MainWindow::showMapView(){

    QSize labelSize1 = ui->mapLabel->size();
    QSize labelSize2 = ui->mapLabel2->size();

    pixmap.load("C:/Users/johnm/Downloads/map.png");

    if(showMap%2 ==0){
        ui->mapLabel->setPixmap(pixmap.scaled(labelSize1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->mapLabel2->setPixmap(pixmap.scaled(labelSize2, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    }else{
        ui->mapLabel->clear();
        ui->mapLabel2->clear();
    }
    showMap = showMap +1;

}

