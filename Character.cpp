#include "Character.h"
#include <iostream>

Character::Character(string description) {
    this->description = description;
    health = 100; // Initialize health to 100
    hunger = 0; // Initialize hunger to 0
}

void Character::addItems(Item* item) {
    itemsInCharacter.push_back(*item);
}

void Character::putItems(Item* item) {
    int location = getItemIndex(item);
    if (location == -1) {
        cout << "Item is not here" << endl;
    }
    else {
        itemsInCharacter.erase(itemsInCharacter.begin() + location);
    }
}

int Character::getItemIndex(Item* item) {
    string name = item->getShortDescription();
    int size = itemsInCharacter.size();
    for (int i = 0; i < size; i++) {
        if (itemsInCharacter[i].getShortDescription().compare(name) == 0)
            return i;
    }
    return -1;
}

Item Character::hasItem(string name) {
    for (Item i : itemsInCharacter) {
        if (i.getShortDescription().compare(name) == 0)
            return i;
    }
    Item* temp = new Item("Nothing");
    return *temp;
}

void Character::increaseHunger(int amount) {
    hunger += amount;
}

void Character::decreaseHunger(int amount) {
    hunger -= amount;
    if (hunger < 0)
        hunger = 0;
}

void Character::decreaseHealth(int amount) {
    health -= amount;
}

string Character::shortDescription() {
    return description;
}

string Character::printInventory() {
    string returnString;
    for (Item i : itemsInCharacter) {
        returnString = returnString + (i).getShortDescription() + " ";
    }
    return "\nInventory: " + returnString;
}


