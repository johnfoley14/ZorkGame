#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "item.h"
#include <string>
#include <vector>

using namespace std;

class Character {
private:
    string description;
    vector<Item> itemsInCharacter;


public:
    Character(string description);
    void addItems(Item* item);
    void putItems(Item* item);
    Item hasItem(string name);
    int getItemIndex(Item* item);
    void increaseHunger(int amount);
    void decreaseHunger(int amount);
    void decreaseHealth(int amount);
    string shortDescription();
    string printInventory();
    int health;
    int hunger;
};

#endif /* CHARACTER_H_ */
