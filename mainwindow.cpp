
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <string>
#include <chrono>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ZorkUL temp;
    ui->textBrowser->append("Welcome to the Pyramids!!\nToday you will be on a dangerous quest to escape\n"
                            "Make sure to eat and defend yourself against the monsters! \nBest of luck and enter info for help\n");
    ui->textBrowser_2->append("Welcome to the Pyramids!!\nToday you will be on a dangerous quest to escape\n"
                              "Make sure to eat and defend yourself against the monsters! \nBest of luck and enter info for help\n");
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
//    player *usersplayer = new player("your avergae character");
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
    if(outputText=="Game is completed"){
        gameWon = true;
        QString qstrOutputText = QString::fromStdString(outputText);
        ui->textBrowser->append(qstrOutputText);
//        std::this_thread::sleep_for(std::chrono::seconds(5));
//        w.close();
    }
    else{
        QString qstrOutputText = QString::fromStdString(outputText);
        ui->textBrowser->append(qstrOutputText);
        ui->textBrowser_2->append(qstrOutputText);
    }
    // check to see if the string back is "Game is completed" if it is then end game after by setting gamewon to true,
    // but also send a output text to the UI
}

void MainWindow::CommandController(string inputText){
    parser.getInput(inputText);
    if(!gameWon){
        Command* command = parser.getCommand();
        // Pass dereferenced command and check for end of game.
        string response = temp.processCommand(*command);
        setOutputText(response);
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

