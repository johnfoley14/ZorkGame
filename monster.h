
#ifndef MONSTER_H_
#define MONSTER_H_

#include "Character.h"
#include <string>

using namespace std;

class Monster : public Character {
private:
    bool isDead;

public:
    Monster(string description);

    string getNoise();
};

#endif /* MONSTER_H_ */
