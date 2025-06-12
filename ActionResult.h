#ifndef ACTIONRESULT_H
#define ACTIONRESULT_H


#include <memory>
#include <vector>
#include "meteor.h"
#include "projectile.h"

struct Enemy;

struct ActionResult {
    std::vector<std::unique_ptr<Meteor>> newMeteors;
    std::unique_ptr<Projectile> fireball_projectile;
    std::vector<Enemy*> enemiesToDamage;
};

#endif // ACTIONRESULT_H
