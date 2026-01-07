#pragma once
#include <string>

class Item {
private:
  std::string name;
  int health;
  int attack;
  int defense;

public:
  Item(const std::string &nm, int hlt, int att, int deff);
  virtual ~Item() = default;

  const std::string &getName() const;
  int getHealth() const;
  int getAttack() const;
  int getDefense() const;
};
