#ifndef ACTIONRESULT_H
#define ACTIONRESULT_H


#include <memory>
#include <vector>

struct Meteor;
struct Enemy;

struct ActionResult {
    std::vector<std::unique_ptr<Meteor>> newMeteors;

    std::vector<Enemy*> enemiesToDamage;
};

#endif // ACTIONRESULT_H
