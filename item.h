#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
private:
	string description;
	string longDescription;
	int weightGrams;
	float value;
    bool isWeapon;
    bool isFood;

public:
    Item (string description, int inWeight, float inValue, bool weaponCheck, bool foodCheck);
    Item (string description);
	string getShortDescription();
    string getLongDescription();
	int getWeight();
	void setWeight(int weightGrams);
	float getValue();
	void setValue(float value);
	int getWeaponCheck();
	void setWeaponCheck(int weaponCheck);
    bool isAFood(bool *isFood);
    bool isAWeapon(bool *isWeapon);
};

#endif /*ITEM_H_*/
