#include "Player.hpp"
#include <algorithm>

Player::Player(const std::string &nm, int mHlt, int att, int deff)
    : GameCharacter(nm, mHlt, att, deff) {
  addItem(Item("Dagger", 0, 5, 0));
}

int Player::getCurrentRoomId() const { return currentRoomId; }
int Player::getPreviousRoomId() const { return previousRoomId; }

void Player::moveToRoom(int newRoomId) {
  if (newRoomId == currentRoomId)
    return;
  previousRoomId = currentRoomId;
  currentRoomId = newRoomId;
}

const std::vector<Item> &Player::getInventory() const { return inventory; }

void Player::applyItemStats(const Item &itm) {
  if (itm.getHealth() > 0) {
    increaseMaxHealth(itm.getHealth());
    increaseHealth(itm.getHealth());
  }
  if (itm.getAttack() > 0)
    increaseAttack(itm.getAttack());
  if (itm.getDefense() > 0)
    increaseDefense(itm.getDefense());
}

void Player::addItem(const Item &itm) {
  applyItemStats(itm);
  inventory.push_back(itm);
}

void Player::grantReward(int deltaMaxHp, int deltaAtk, int deltaDef) {
  if (deltaMaxHp != 0) {
    increaseMaxHealth(deltaMaxHp);
    if (deltaMaxHp > 0)
      increaseHealth(deltaMaxHp);
  }
  if (deltaAtk != 0)
    increaseAttack(deltaAtk);
  if (deltaDef != 0)
    increaseDefense(deltaDef);
}
