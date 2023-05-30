
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <string>
#include <chrono>
#include <thread>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textBrowser->append("Welcome to the Pyramids!!\nToday you will be on a dangerous quest to escape\n"
                            "Make sure to eat and defend yourself against the monsters! \nBest of luck and enter info for help\n");
    ui->textBrowser_2->append("Welcome to the Pyramids!!\nToday you will be on a dangerous quest to escape\n"
                              "Make sure to eat and defend yourself against the monsters! \nBest of luck and enter info for help\n");
    ZorkUL temp;

    ui->turnButton->setVisible(false);



    closeWindowLambda = [this]() {

        this->close();


    };

    closeTimer = new QTimer(this);
    closeTimer->setSingleShot(true);
    connect(closeTimer, &QTimer::timeout, this, closeWindowLambda);

    QSize labelSizeRoom = ui->roomLabel->size();

    pixmap.load("C:/Users/johnm/Downloads/RoomImages/Pyramid.png");

    ui->roomLabel->setPixmap(pixmap.scaled(labelSizeRoom, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QSize labelSize3 = ui->mapLabel3->size();
    pixmap.load("C:/Users/johnm/Downloads/RoomImages/map.png");
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
        showWinningMessage();
        std::this_thread::sleep_for(std::chrono::seconds(5));
        closeWindowLambda();
    }
    else if(outputText=="Quiting game"){
        QString qstrOutputText = QString::fromStdString(outputText);
        ui->textBrowser->append(qstrOutputText);
        ui->textBrowser_2->append(qstrOutputText);
        closeTimer->start(5000);
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

void MainWindow::showWinningMessage()
{

    QMessageBox::information(this, "Congratulations", "You have won! Well done\nGo tell your friends of your achievement");
}

Command* command;

void MainWindow::CommandController(string inputText){
    if(inputText.compare("take key")==0){
        setVisible();
    }
    parser.getInput(inputText);
    if(!gameWon){
        if(inputText.compare("map")==0){
            showMapView();
        }
        else{
            command = parser.getCommand();

            // Pass dereferenced command and check for end of game.
            string response = temp.processCommand(*command);
            setOutputText(response);
            if(command->getCommandWord().compare("go")==0){
                setRoomImage(temp.currentRoom);
            }
        }
    }
}

void MainWindow::setRoomImage(Room* roomDescription){
    QSize labelSizeRoom = ui->roomLabel->size();

    string imagePath = roomDescription->getImagePath();
    QString qstrOutputText = QString::fromStdString(imagePath);

    QPixmap newImagePixmap(qstrOutputText);


    newImagePixmap.load(qstrOutputText);

    ui->roomLabel->setPixmap(newImagePixmap.scaled(labelSizeRoom, Qt::KeepAspectRatio, Qt::SmoothTransformation));

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
    showMapView();

}

void MainWindow::showMapView(){

    QSize labelSize1 = ui->mapLabel->size();
    QSize labelSize2 = ui->mapLabel2->size();

    pixmap.load("C:/Users/johnm/Downloads/RoomImages/map.png");

    if(showMap%2 ==0){
        ui->mapLabel->setPixmap(pixmap.scaled(labelSize1, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        ui->mapLabel2->setPixmap(pixmap.scaled(labelSize2, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    }else{
        ui->mapLabel->clear();
        ui->mapLabel2->clear();
    }
    showMap = showMap +1;

}


void MainWindow::on_infoButton_clicked()
{
    CommandController("info");
}


void MainWindow::on_InventoryButton_clicked()
{
    CommandController("inventory");
}


void MainWindow::on_hitButton_clicked()
{
    CommandController("hit Medusa");

}


void MainWindow::on_clearButton_clicked()
{
    ui->textBrowser->clear();
    ui->textBrowser_2->clear();
}

void MainWindow::setVisible(){
    ui->turnButton->setVisible(true);
}

void MainWindow::on_turnButton_clicked()
{
    CommandController("turn key");
}


void MainWindow::on_takeButton_clicked()
{
    if(temp.currentRoom->numberOfItems()==0){
        ui->textBrowser->append("No item to take in this room\n");
        ui->textBrowser_2->append("No item to take in this room\n");
    }
    else{
    string itemString = temp.currentRoom->getFirstItem();
    CommandController("take "+itemString);
    }
}


void MainWindow::on_putButton_clicked()
{
    if(temp.character->hasEmptyInventory()){
    ui->textBrowser->append("Inventory empty. Nothing to put down\n");
    ui->textBrowser_2->append("Inventory empty. Nothing to put down\n");
    }
    else{
    string itemString = temp.character->getFirstItem();
    CommandController("put "+itemString);
    }
}

