#include <iostream>
#include <QApplication>
#include "mainwindow.h"
using namespace std;
#include "ZorkUL.h"
#include <QString>
#include <string>

//int main(int argc, char *argv[]) {
//    QApplication a(argc, argv);
//    ZorkUL temp;
//    MainWindow w;
//    w.show();
////    temp.play(false);
////    return 0;
//    return a.exec();
//}

ZorkUL::ZorkUL() {
    createRooms();
}

void ZorkUL::createRooms()  {
    Room *escape, *souterrain, *finalboss, *exit, *foodstore, *kitchen, *cor1, *cor2, *cor3, *cor4, *cor5, *cor6, *cor7, *cor8, *cor9,
         *cell, *surpriseroom, *scribesroom, *toilet, *freefood, *noentry, *start, *armoury, *tomb1, *treasury, *documents,
         *cell2, *cell3, *cell4, *tomb2, *cor10, *mummystomb, *boss, *sphynx, *wizardsroom, *kingstomb;

    escape = new Room("escape");
    souterrain = new Room("souterrain");
        souterrain->addItem(new Item("x", 1, 11));
        souterrain->addItem(new Item("y", 2, 22));
    finalboss = new Room("finalboss");
    exit = new Room("exit");
    foodstore = new Room("foodstore");
    kitchen = new Room("kitchen");
    cell = new Room("cell");
    surpriseroom = new Room("surpriseroom");
    scribesroom = new Room("scribesroom");
    toilet = new Room("toilet");
    freefood = new Room("freefood");
    noentry = new Room("noentry");
    start = new Room("start");
    armoury = new Room("armoury");
        armoury->addItem(new Item("sword",20,20));
    tomb1 = new Room("tomb1");
    treasury = new Room("treasury");
    documents = new Room("documents");
    cell = new Room("cell");
    cell2  = new Room("cell2");
    cell3  = new Room("cell3");
    cell4   = new Room("cell4");
    tomb2   = new Room("tomb2");
    cor10 = new Room("cor10");
    mummystomb = new Room("mummystomb");
    boss = new Room("boss");
    sphynx = new Room("sphynx");
    wizardsroom   = new Room("wizardsroom");
    kingstomb = new Room("kingstomb");

    cor1 = new Room("cor1");
    cor2 = new Room("cor2");
    cor3 = new Room("cor3");
    cor4 = new Room("cor4");
    cor5 = new Room("cor5");
    cor6 = new Room("cor6");
    cor7 = new Room("cor7");
    cor8 = new Room("cor8");
    cor9 = new Room("cor9");

//             (N, E, S, W, U, D)
    start->setExits(NULL, NULL, armoury, cell, NULL, NULL);
    souterrain->setExits(NULL, cor5, finalboss, NULL, NULL, NULL);
    escape->setExits(NULL, NULL, NULL,NULL,NULL, NULL);
    finalboss->setExits(souterrain, cor4, exit, NULL, NULL, NULL);
    exit->setExits(finalboss, cor3, foodstore, escape, NULL, NULL);
    kitchen->setExits(cell, NULL, NULL, cell, NULL, NULL);
    cor1->setExits(NULL, cell, cell, cell, NULL, NULL);
    cor2->setExits(NULL, NULL, NULL, cell, NULL, NULL);
    cor3->setExits(NULL, cell, NULL, NULL, NULL, NULL);
    cor4->setExits(NULL, cell, NULL, NULL, NULL, NULL);

        currentRoom = start;
}

/**
 *  Main play routine.  Loops until end of play.
 */
//void ZorkUL::play(bool newCommand) {
////	printWelcome();

//    // Enter the main command loop.  Here we repeatedly read commands and
//    // execute them until the ZorkUL game is over.

//    bool finished = false;
//    while (!finished) {
//        if(newCommand){
//            // Create pointer to command and give it a command.
//            Command* command = parser.getCommand();
//            // Pass dereferenced command and check for end of game.
//            finished = processCommand(*command);
//            // Free the memory allocated by "parser.getCommand()"
//            //   with ("return new Command(...)")
//            delete command;
//            newCommand = false;
//        }

//    }
////    cout << endl;
////    cout << "end" << endl;
//}

void ZorkUL::setCommandTrue(){
    isNewCommand = true;
}

void ZorkUL::printWelcome() {
    cout << "start"<< endl;
    cout << "info for help"<< endl;
    cout << endl;
    cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
string ZorkUL::processCommand(Command command) {
    if (command.isUnknown()) {
     //   cout << "invalid input"<< endl;

        return "invalid input";
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        return std::string("valid inputs are: ") + parser.showCommands();

    else if (commandWord.compare("map") == 0)
        {
        cout << "          [cell] --- [documents] ---    [start]   --->   [sphynx] --- [surprise]  "<< endl;
        cout << "                |                            |                          |                |            |         |"<< endl;
        cout << "                |                            |                          |                |            |         |"<< endl;
        cout << "[escape] ---- [exit] ----- [treasury] --- [scribes room]  ---> [mummystomb] -- [boss] ---> [kings tomb]"<< endl;
        cout << "                |                           |                           |                |            |         |"<< endl;
        cout << "                |                           |                           |                |            |         |"<< endl;
        cout << "          [food store] --- [souterrain] ---- [armoury] "<< endl;
        cout << "                |                           |                           | "<< endl;
        }//

    else if (commandWord.compare("go") == 0)
//        string response = goRoom(command);
//        if(response.compare())
        return goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
        //cout << "incomplete input"<< endl;
            return "incomplete input: please specify item to take";
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            return "item is not in this room";
        else
           /* cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl*/;
        return "you have picked up the item successfully";
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }
/*
    {
    if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
        else if (commandWord.compare("quit") == 0) {
            if (command.hasSecondWord())
                cout << "overdefined input"<< endl;
            else
                return "hwko"; /**signal to quit*/
        }
        return "false";
}
/** COMMANDS **/
void ZorkUL::printHelp() {
    cout << "valid inputs are; " << endl;
    parser.showCommands();

}

string ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
    //    cout << "incomplete input"<< endl;
        return "incomplete input";
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        return "no room in this direction";
    else {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}

string ZorkUL::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else
    {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}
