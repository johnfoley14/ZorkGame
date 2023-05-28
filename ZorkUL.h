#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
#include "player.h"
#include "Character.h"
using namespace std;

class ZorkUL {
private:
	Parser parser;
	Room *currentRoom;
	void createRooms();
	void printWelcome();
	void printHelp();
    string goRoom(Command command);
    void createItems();
    void displayItems();
    void createUserCharacter();
    Character *player;

public:
	ZorkUL();
    void play(bool newCommand);
	string go(string direction);
    bool isNewCommand;
    void setCommandTrue();
    string processCommand(Command command);
};

#endif /*ZORKUL_H_*/
