#include "item.h"

Item::Item (string inDescription, int inWeightGrams, float inValue, bool isFood, bool isWeapon) {
    description = inDescription;
    setWeight(inWeightGrams);
    value = inValue;
//    this->isFood = isFood;
//    this->isWeapon = isWeapon;
//    isAFood(*this->isFood);
//    isAWeapon(*isWeapon);
}

Item::Item(string inDescription) {
    description = inDescription;
}

void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
       cout << "weight invalid, must be 0<weight<9999" ;
    else
       weightGrams = inWeightGrams;
}

bool Item::isAFood(bool *foodCheck){
    return foodCheck;

}
bool Item::isAWeapon(bool *weaponCheck){
    return weaponCheck;
}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
       cout << "value invalid, must be 0<value<9999" ;
    else
       value = inValue;
}

void Item::setWeaponCheck(int isWeapon)
{
    if(isWeapon > 0 || isWeapon < 0)
        cout << "Item not a weapon" ;
    else
        cout << "Item is a weapon" ;
}

string Item::getShortDescription()
{
    return description;
}

string Item::getLongDescription()
{
    return " item(s), " + description + ".\n";
}

