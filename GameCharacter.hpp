#pragma once
#include <string>

class GameCharacter {
protected:
  std::string name;
  int maxHealth;
  int currentHealth;
  int attack;
  int defense;

  void increaseHealth(int delta);
  void maxHealthIncrease(int delta);
  void increaseAttack(int delta);
  void increaseDefense(int delta);

public:
  GameCharacter(const std::string &nm, int mHlt, int att, int deff);
  virtual ~GameCharacter() = default;

  const std::string &getName() const;
  int getMaxHealth() const;
  int getCurrentHealth() const;
  int getAttack() const;
  int getDefense() const;

  int takeDamage(int amount);
  bool isDead() const;
};
