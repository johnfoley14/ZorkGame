//#ifndef CHARACTER_H_
//#define CHARACTER_H_
//#include "ZorkUL.h"
//#include <vector>
//#include <string>
//using namespace std;
//#include <vector>
//using std::vector;


//class Character {
//private:
//    string description;
//    vector < Item > itemsInCharacter;

//public:
//    Character(string description);
//    string shortDescription();
//    string longDescription();
//    void addItems(Item &item);
//    int health;

//};

//#endif /*CHARACTER_H_*/
#include <string>
using namespace std;
#include <vector>
#include "item.h"
using std::vector;


class Character {
private:
    string description;
    vector < Item > itemsInCharacter;
public:
    void addItems(Item *Item);
    void putItems(Item *Item);
    Item hasItem(string name);
    int getItemIndex(Item *item);

public:
    Character(string description);
    string shortDescription();
    //string longDescription();
    string printInventory();

};

//#endif /*CHARACTER_H_*/
