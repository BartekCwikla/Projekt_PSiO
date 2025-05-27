#ifndef SWORD_H
#define SWORD_H

#include "melee.h"

class Sword : public Melee {
public:
    Sword(float damage);
    void upgrade(){};
};


#endif // SWORD_H
