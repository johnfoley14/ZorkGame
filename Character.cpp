#include "Character.h"
#include <iostream>

Character::Character(string description) {
    this->description = description;
    health = 100; // Initialize health to 100
    hunger = 100; // Initialize hunger to 0
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

bool Character::hasThisItem(string name) {
    for (Item i : itemsInCharacter) {
        if (i.getShortDescription().compare(name) == 0)
            return true;
    }

    return false;
}

void Character::increaseHunger(int amount) {
    hunger += amount;
}

void Character::decreaseHunger(int amount) {
    hunger -= amount;
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
    return "Inventory: " + returnString+"\n";
}

bool Character::hasWeapon() {
    for (Item i : itemsInCharacter) {
        if (i.isAWeapon()) {
            return true;
        }
    }
    return false;
}

bool Character::hasEmptyInventory(){
    if(itemsInCharacter.size()==0){
        return true;
    }
    else{
        return false;
    }
}

string Character::getFirstItem(){
    return itemsInCharacter[0].getShortDescription();
}
