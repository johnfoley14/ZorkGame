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
    createCharacter();
}

void ZorkUL::createRooms()  {
    Room *escape, *souterrain, *exit, *foodstore, *cell, *surpriseroom, *scribesroom, *start, *armoury,
        *mummystomb, *boss, *sphynx, *kingstomb, *treasury, *documents, *dungeon;
    // escape, cell, documents, start, exit, treasury, scribes room, food store, souterrain, armoury
    // sphynx, mummystomb, surprise, boss, kings tomb
    escape = new Room("escape");
    dungeon = new Room("dungeon");
    souterrain = new Room("souterrain");
    souterrain->addItem(new Item("dagger", 1, 11, false, true));
    souterrain->addItem(new Item("y", 2, 22, false, false));
    exit = new Room("exit");
    foodstore = new Room("foodstore");
    cell = new Room("cell");
    surpriseroom = new Room("surpriseroom");
    scribesroom = new Room("scribesroom");
    start = new Room("start");
    armoury = new Room("armoury");
    armoury->addItem(new Item("sword",20,20, false, true));
    treasury = new Room("treasury");
    documents = new Room("documents");
    mummystomb = new Room("mummystomb");
    boss = new Room("boss");
    sphynx = new Room("sphynx");
    kingstomb = new Room("kingstomb");

//             (N, E, S, W, U, D)
    start->setExits(NULL, NULL, scribesroom, documents, NULL, NULL);
    souterrain->setExits(treasury, armoury, NULL, foodstore, boss, dungeon);
    escape->setExits(NULL, NULL, NULL,NULL,NULL, NULL);
    boss->setExits(NULL, surpriseroom, NULL,  mummystomb, kingstomb, souterrain);
    exit->setExits(cell, treasury, foodstore, escape, mummystomb, NULL);
    foodstore->setExits(exit, souterrain, NULL, NULL, NULL, NULL);
    cell->setExits(NULL, documents, exit, NULL, NULL, NULL);
    surpriseroom->setExits(sphynx, NULL, boss, NULL, NULL, NULL);
    scribesroom->setExits(start, NULL, armoury, treasury, surpriseroom, NULL);
    armoury->setExits(scribesroom, NULL, NULL, souterrain, NULL, NULL);
    treasury->setExits(documents, scribesroom, souterrain, exit, NULL, NULL);
    documents->setExits(NULL, start, treasury, cell, sphynx, NULL);
    mummystomb->setExits(sphynx, NULL, boss, NULL, NULL, exit);
    sphynx->setExits(NULL, surpriseroom, NULL, mummystomb, NULL, documents);
    kingstomb->setExits(NULL, NULL, NULL, NULL,NULL, boss);

        currentRoom = start;
}

void ZorkUL::createCharacter(){
        Character *player;
        player = new Character("the avergae player character");
        character = player;
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

        return "invalid input\n";
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        return std::string("valid inputs are: ") + parser.showCommands()+"\n";

    else if (commandWord.compare("go") == 0)
//        string response = goRoom(command);
//        if(response.compare())
        return goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
        //cout << "incomplete input"<< endl;
            return "incomplete input: please specify item to take\n";
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            return "item is not in this room\n";
        else
           /* cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl*/;
        return "you have picked up the item successfully"+character->printInventory()+"\n";
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
        return "incomplete input\n";
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        return "no room in this direction\n";
    else {
        currentRoom = nextRoom;
        int i = currentRoom->shortDescription().compare("boss");
        if(i == 0){
            character->decreaseHealth(30);

            if(character->health<0){
                return "dead\n";
            }
            return "You have entered a room with a boss monster\nHe hits you with a sword and you lose 30 health\n";
        }
        currentRoom = nextRoom;

        return currentRoom->longDescription()+"\n";
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
