
#include "Monster.h"

Monster::Monster(string description) : Character(description) {
    isDead = true;
}

string Monster::getNoise() {
    return "Roar!";
}
