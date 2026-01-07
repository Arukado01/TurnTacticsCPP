#include "Item.hpp"
#include <algorithm>

Item::Item(const std::string &nm, int hlt, int att, int deff)
    : name(nm), health(std::max(0, hlt)), attack(std::max(0, att)),
      defense(std::max(0, deff)) {}

const std::string &Item::getName() const { return name; }
int Item::getHealth() const { return health; }
int Item::getAttack() const { return attack; }
int Item::getDefense() const { return defense; }
