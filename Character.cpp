//#include "Character.h"
//#include <iostream>
//#include <string>
//using namespace std;
//#include <vector>


//Character::Character(string description) {
//    this->description = description;
//}
//const int MAX_ITEMS = 10;
//vector<string> inventory;
//inventory.reserve(max_length);

//void Character::addItem(Item &item) {
//    itemsInCharacter.push_back(item);
//}
//void Character::addItem(Item *item) {
//    itemsInCharacter.push_back(*item);
//    delete item;
//}
//string Character::longDescription()
//{
//  string ret = this->description;
//  ret += "\n Item list:\n";
//  for (vector<Item>::iterator i = itemsInCharacter.begin(); i != itemsInCharacter.end(); i++)
//    ret += "\t"+ (*i).getLongDescription() + "\n";
//  return ret;
//}


////Character::Character(string description){
////    this->description = description;
////}

////int health = 100;

#include "Character.h"

Character::Character(string description) {
  this->description = description;
}

void Character::addItems(Item *item) {
  itemsInCharacter.push_back(*item);
}

void Character::putItems(Item *item) {
  int location = getItemIndex(item);
  if (location == -1){
    cout << "item is not here" << endl;
  }
  else{ // Removing choosen item from character
    itemsInCharacter.erase(itemsInCharacter.begin()+location);
  }
}

int Character::getItemIndex(Item *item){
  string name = item->getShortDescription();
  int size = itemsInCharacter.size();
  for (int i = 0; i < size; i++){
    if(itemsInCharacter[i].getShortDescription().compare(name) == 0)
        return i;
  }
  return -1;
}

// Character having an Item
Item Character::hasItem(string name){
  for (Item i : itemsInCharacter)
    if(i.getShortDescription().compare(name) == 0)
        return i;
  Item* temp = new Item("Nothing");
  return *temp;
}

string Character::printInventory()
{
  string returnString;
  for (Item i : itemsInCharacter){
    returnString = returnString + (i).getShortDescription() + " ";
  }
  return "\nInventory: " + returnString;
}


