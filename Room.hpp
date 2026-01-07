#pragma once
#include "GameCharacter.hpp"
#include "Item.hpp"
#include <memory>
#include <vector>

class Room {
private:
  int pos;
  bool isExit;
  std::vector<Item> items;
  std::vector<std::unique_ptr<GameCharacter>> enemies;

public:
  Room(int position, bool exit, std::vector<Item> items,
       std::vector<std::unique_ptr<GameCharacter>> enemies);
  ~Room() = default;

  void clearLoot();
  void clearEnemies();

  int getPosition() const;
  bool getIsExit() const;

  void addItem(const Item &itm);
  void addEnemy(std::unique_ptr<GameCharacter> enm);

  const std::vector<Item> &getItems() const;
  const std::vector<std::unique_ptr<GameCharacter>> &getEnemies() const;
};
