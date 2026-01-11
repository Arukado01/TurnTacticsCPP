#pragma once
#include "GameCharacter.hpp"
#include "Item.hpp"
#include <vector>

class Player : public GameCharacter {
private:
  int currentRoomId = 0;
  int previousRoomId = -1;
  std::vector<Item> inventory;

  void addItem(const Item &itm);
  void applyItemStats(const Item &itm);

public:
  Player(const std::string &nm, int mHlt, int att, int deff);

  int getCurrentRoomId() const;
  int getPreviousRoomId() const;

  void moveToRoom(int newRoomId);

  const std::vector<Item> &getInventory() const;

  void grantReward(int deltaMaxHp, int deltaAtk, int deltaDef);
};
