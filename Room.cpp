#include "Room.hpp"
#include <utility>

Room::Room(int roomId, bool exit, std::vector<Item> loot,
           std::vector<std::unique_ptr<GameCharacter>> foes)
    : id(roomId), isExit(exit), items(std::move(loot)),
      enemies(std::move(foes)), exits{-1, -1, -1, -1} {}

int Room::getId() const { return id; }
bool Room::getIsExit() const { return isExit; }

void Room::setExit(Room::Dir d, int targetRoomId) {
  exits[dirIndex(d)] = targetRoomId;
}

int Room::getExit(Room::Dir d) const { return exits[dirIndex(d)]; }

bool Room::hasLoot() const { return !items.empty(); }
bool Room::hasEnemies() const { return !enemies.empty(); }

void Room::clearLoot() { items.clear(); }
void Room::clearEnemies() { enemies.clear(); }

void Room::addItem(const Item &itm) { items.push_back(itm); }

void Room::addEnemy(std::unique_ptr<GameCharacter> enm) {
  if (!enm)
    return;
  enemies.push_back(std::move(enm));
}

const std::vector<Item> &Room::getItems() const { return items; }

std::vector<Item> Room::takeAllItems() {
  std::vector<Item> out;
  out.swap(items);
  return out;
}

std::vector<std::unique_ptr<GameCharacter>> &Room::getEnemies() {
  return enemies;
}
