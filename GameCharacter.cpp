#include "GameCharacter.hpp"
#include <algorithm>

GameCharacter::GameCharacter(const std::string &nm, int mHlt, int att, int deff)
    : name(nm), maxHealth(std::max(1, mHlt)), currentHealth(std::max(1, mHlt)),
      attack(std::max(0, att)), defense(std::max(0, deff)) {}

const std::string &GameCharacter::getName() const { return name; }
int GameCharacter::getMaxHealth() const { return maxHealth; }
int GameCharacter::getCurrentHealth() const { return currentHealth; }
int GameCharacter::getAttack() const { return attack; }
int GameCharacter::getDefense() const { return defense; }

void GameCharacter::increaseHealth(int delta) {
  currentHealth = std::clamp(currentHealth + delta, 0, maxHealth);
}

void GameCharacter::increaseMaxHealth(int delta) {
  maxHealth = std::max(1, maxHealth + delta);
  currentHealth = std::clamp(currentHealth, 0, maxHealth);
}

void GameCharacter::increaseAttack(int delta) {
  attack = std::max(0, attack + delta);
}

void GameCharacter::increaseDefense(int delta) {
  defense = std::max(0, defense + delta);
}

int GameCharacter::takeDamage(int rawAmount) {
  rawAmount = std::max(0, rawAmount);
  const int dmg = std::max(0, rawAmount - defense);
  currentHealth = std::max(0, currentHealth - dmg);
  return dmg;
}

bool GameCharacter::isDead() const { return currentHealth <= 0; }
