#pragma once
#include "GameCharacter.hpp"
#include "Item.hpp"
#include <array>
#include <memory>
#include <vector>

class Room {
public:
  enum class Dir : int { North = 0, East = 1, South = 2, West = 3 };

private:
  int id;
  bool isExit;
  std::vector<Item> items;
  std::vector<std::unique_ptr<GameCharacter>> enemies;

  std::array<int, 4> exits;

  static constexpr std::size_t dirIndex(Dir d) {
    return static_cast<std::size_t>(static_cast<int>(d));
  }

public:
  Room(int roomId, bool exit, std::vector<Item> loot = {},
       std::vector<std::unique_ptr<GameCharacter>> foes = {});

  int getId() const;
  bool getIsExit() const;

  void setExit(Dir d, int targetRoomId);
  int getExit(Dir d) const;

  bool hasLoot() const;
  bool hasEnemies() const;

  void clearLoot();
  void clearEnemies();

  void addItem(const Item &itm);
  void addEnemy(std::unique_ptr<GameCharacter> enm);

  const std::vector<Item> &getItems() const;
  std::vector<Item> takeAllItems();
  std::vector<std::unique_ptr<GameCharacter>> &getEnemies();
};
