#pragma once
#include "GameCharacter.hpp"
#include "Item.hpp"
#include <vector>

class Room;

class Player : public GameCharacter {
private:
  Room *currentRoom = nullptr;
  Room *previousRoom = nullptr;
  std::vector<Item> inventory;

  void addItem(const Item &itm);

  void increaseStats(int hlt, int att, int deff) {
    maxHealthIncrease(hlt);
    increaseHealth(hlt);
    increaseAttack(att);
    increaseDefense(deff);
  }

public:
  Player(const std::string &nm, int mHlt, int att, int deff);
  ~Player() = default;

  void lootRoom(Room *room);
  void changeRoom(Room *newRoom);

  Room *getCurrentRoom() const { return currentRoom; }
  Room *getPreviousRoom() const { return previousRoom; }
  const std::vector<Item> &getInventory() const { return inventory; }
};
