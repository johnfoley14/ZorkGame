#include <iostream>
#include <QApplication>
#include "mainwindow.h"
using namespace std;
#include "ZorkUL.h"
#include <QString>
#include <string>


ZorkUL::ZorkUL() {
    createRooms();
    createCharacter();
}

void ZorkUL::createRooms()  {
    Room *escape, *souterrain, *exit, *foodstore, *cell, *surpriseroom, *scribesroom, *start, *armoury,
        *mummystomb, *boss, *sphynx, *kingstomb, *treasury, *documents, *dungeon;

    start = new Room("start", "C:/Users/johnm/Downloads/RoomImages/Pyramid.png");
    souterrain = new Room("souterrain", "C:/Users/johnm/Downloads/RoomImages/souterrain.jpg");
    escape = new Room("escape", "C:/Users/johnm/Downloads/RoomImages/exit.jpg");
    boss = new Room("boss", "C:/Users/johnm/Downloads/RoomImages/boss.jpg");
    exit = new Room("exit", "C:/Users/johnm/Downloads/RoomImages/exit.jpg");
    foodstore = new Room("foodstore", "C:/Users/johnm/Downloads/RoomImages/foodstore.png");
    cell = new Room("cell", "C:/Users/johnm/Downloads/RoomImages/dungeoncell.png");
    surpriseroom = new Room("surpriseroom", "C:/Users/johnm/Downloads/RoomImages/barImageSurprise.jpg");
    scribesroom = new Room("scribesroom", "C:/Users/johnm/Downloads/RoomImages/scribesroom.png");
    armoury = new Room("armoury", "C:/Users/johnm/Downloads/RoomImages/armory.jpg");
    treasury = new Room("treasury", "C:/Users/johnm/Downloads/RoomImages/treasure.jpg");
    documents = new Room("documents", "C:/Users/johnm/Downloads/RoomImages/writersroom.jpg");
    mummystomb = new Room("mummystomb", "C:/Users/johnm/Downloads/RoomImages/mummyroom.png");
    sphynx = new Room("sphynx", "C:/Users/johnm/Downloads/RoomImages/churchroom.jpg");
    kingstomb = new Room("kingstomb", "C:/Users/johnm/Downloads/RoomImages/kingstomb.jpg");



    souterrain->addItem(new Item("dagger", 1, 11, false, true));
    foodstore->addItem(new Item("apple", 1, 11, true, false));
    cell->addItem(new Item("broken axe", 1, 20, false, false));
    surpriseroom->addItem(new Item("beer", 1, 20, true, false));
    scribesroom->addItem(new Item("parchment", 1, 10, false, false));
    documents->addItem(new Item("scroll", 1, 20, false, false));
    kingstomb->addItem(new Item("key", 1, 0, 0, 0));
    foodstore->addItem(new Item("bread", 1, 50, true , false));
    armoury->addItem(new Item("sword",20,20, false, true));
    treasury->addItem(new Item("coins", 1, 1, false, false));

//             (N, E, S, W, U, D)
    start->setExits(NULL, NULL, scribesroom, documents, NULL, NULL);
    souterrain->setExits(treasury, armoury, NULL, foodstore, boss, dungeon);
    escape->setExits(NULL, NULL, NULL,NULL,NULL, NULL);
    boss->setExits(NULL, surpriseroom, NULL,  mummystomb, kingstomb, souterrain);
    exit->setExits(cell, treasury, foodstore, escape, mummystomb, NULL);
    foodstore->setExits(exit, souterrain, NULL, NULL, NULL, NULL);
    cell->setExits(NULL, documents, exit, NULL, NULL, NULL);
    surpriseroom->setExits(sphynx, NULL, boss, NULL, NULL, scribesroom);
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
        Monster *monster;
        monster = new Monster("Medusa");
        boss = monster;
}


void ZorkUL::setCommandTrue(){
    isNewCommand = true;
}


/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
string ZorkUL::processCommand(Command command) {
    if (command.isUnknown()) {

        return "invalid input\n";
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        return std::string("valid inputs are: ") + parser.showCommands()+"\n";

    else if (commandWord.compare("go") == 0){
        return goRoom(command);
    }
    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
            return "incomplete input: please specify item to take\n";
        }
        else if (command.hasSecondWord()) {

            // location indicates the position in the array of the room that the item is.
        Item* location = currentRoom->isItemInRoom(command.getSecondWord());

            if (location == 0 ){
            return "item is not in this room\n";
        }
        else{
            character->addItems(location);
            currentRoom->removeItem(location);

            return "you have picked up the item successfully\n"+character->printInventory();
        }
        }
    }

    else if (commandWord.compare("room")==0){
        return currentRoom->shortDescription()+"\n";
    }

    else if (commandWord.compare("read")==0){

        if (!command.hasSecondWord()) {
        return "incomplete input\n";
        }
        else if(command.getSecondWord().compare("letMeWin")==0){
        return "Game is completed";
        }
        else if ((command.getSecondWord().compare("scroll")==0) && (character->hasThisItem("scroll"))){
              return "Unveil the map, seek the king's tomb with care,\n"
               "Beware the boss, a challenge to bear.\n"
               "Conquer it all, and glory shall be your share.\n";
        }
        else if ((command.getSecondWord().compare("parchment")==0) && (character->hasThisItem("parchment"))){
        return "In shadows deep, where darkness thrives,\n"
                   "Unsheath thy sword, as courage arrives.\n"
                   "Face the boss, with valor ignited,\n"
                   "Strike true and fierce, until it is smited\n";
        }
        else if ((command.getSecondWord().compare("hieroglyphics")==0) && (currentRoom->shortDescription().compare("kingstomb")==0)){
        return "If you want to complete, then go learn leet!\nT4k3 7h3 1<3y 4nd g0 w357 fr0m 7h3 3x17";
        }
        else{
        return "Make sure the item you are trying to read is in your inventory\n";
        }

    }

    else if (commandWord.compare("eat")==0){
        if(character->hasThisItem(command.getSecondWord())){
        Item food = character->hasItem(command.getSecondWord());
        if(food.isAFood()){
        character->increaseHunger(food.getInValue());
        return "Hunger increased by " + std::to_string(food.getInValue())+"\n";
        }else{
        return "Item is not a food\n";
        }

        }
        else{
        return "Character does not have this item\n";
        }
    }


    else if (commandWord.compare("put") == 0)
    {
        if (!command.hasSecondWord()) {
                return "incomplete input: please specify item to put down\n";
                }
        else if (command.hasSecondWord()){

                Item putItem = character->hasItem(command.getSecondWord());
                Item* putItemAddress = &putItem;
                currentRoom->addItem(putItemAddress);
                character->putItems(putItemAddress);
                return "You have put down " + command.getSecondWord()+"\n";

        }

    }

    else if(commandWord.compare("turn")==0){
        if((command.getSecondWord().compare("key")==0) && (currentRoom->shortDescription().compare("exit")==0)){
                if(character->hasThisItem("key")){
        return "Game is completed";
                }
                else{
        return "You need to find the key first\n";
                }
        }
        else{
                return "Invalid input: make sure you are in the correct room\n";
        }
    }

    else if(commandWord.compare("hit")==0){
        if(!(currentRoom->shortDescription().compare("boss")==0)){
                return "There is no monster to hit in this room\n";
        }
        else{
                if(character->hasWeapon()){

        if(boss->health<=0){
            return "Medusa is already dead. No need anymore\n";
        }
        boss->decreaseHealth(20);

        if(boss->health<=0){
            return "Medusa is dead\n";
        }

        return "You have hit Medusa\nHer health is now "+std::to_string(boss->health)+"\n";

                }else{
        return "You must have a weapon to hit the monster\n";
                }
        }
    }

    else if (commandWord.compare("inventory")==0){
        return character->printInventory();
    }

        else if (commandWord.compare("quit") == 0) {
            if (command.hasSecondWord())
                cout << "overdefined input"<< endl;
            else
                return "Quiting game"; /**signal to quit*/
        }
        return "invalid input";
}
/** COMMANDS **/
void ZorkUL::printHelp() {
    cout << "valid inputs are; " << endl;
    parser.showCommands();

}

string ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        return "incomplete input\n";
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        return "no room in this direction\n";
    else {
        currentRoom = nextRoom;
        character->decreaseHunger(5);
        if(character->hunger<1){
                return "dead";
        }
        if(currentRoom->shortDescription().compare("boss") == 0){
            character->decreaseHealth(30);

            if(character->health<0){
                return "dead";
            }
            return "You have entered a room with a monster called Medusa\nShe hits you with a sword and you lose 30 health\n"+currentRoom->longDescription()+"\nHunger: "+
                   std::to_string(character->hunger)+"\nHealth"+ std::to_string(character->health)+"\n";
        }
        if(currentRoom->shortDescription().compare("kingstomb")==0){
            return "You enter the kings burial tomb and there is ancient hieroglyphics on the way.\nMaybe this could be a clue to escape?\n"+
            currentRoom->longDescription()+"\nHunger: "+ std::to_string(character->hunger)+"\nHealth:"+ std::to_string(character->health)+"\n";
        }


        return currentRoom->longDescription()+"\nHunger: "+ std::to_string(character->hunger)+"\nHealth:"+ std::to_string(character->health)+"\n";
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

// Operator Overloading

//class Vector {
//private:
//    double x, y;

//public:
//    Vector(double x = 0.0, double y = 0.0) : x(x), y(y) {}

//    Vector operator+(const Vector& other) const {
//        return Vector(x + other.x, y + other.y);
//    }

//    void display() const {
//        cout << "(" << x << ", " << y << ")";
//    }
//};

//int main() {
//    Vector v1(2.5, 3.8);
//    Vector v2(1.2, 0.7);
//    Vector sum = v1 + v2;

//    sum.display();  // Output: (3.7, 4.5)

//    return 0;
//}

