#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include "item.h"
using namespace std;
using std::vector;

class Room {

private:
	string description;
	map<string, Room*> exits;
	string exitString();
    vector <Item> itemsInRoom;

    friend class ZorkUL;


public:
    int numberOfItems();
    Room(string description, string image);
    void setExits(Room *north, Room *east, Room *south, Room *west, Room *up, Room *down);
	string shortDescription();
    string image;
	string longDescription();
	Room* nextRoom(string direction);
    void addItem(Item *inItem);
    string displayItem();
    Item* isItemInRoom(string inString);
    void removeItem(Item* itemRemoved);
    string getImagePath();
    string getFirstItem();
};

#endif
