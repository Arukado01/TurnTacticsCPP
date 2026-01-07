#include "Room.hpp"
#include <utility>

Room::Room(int position, bool exit, std::vector<Item> items,
           std::vector<std::unique_ptr<GameCharacter>> enemies)
    : pos(position), isExit(exit), items(std::move(items)),
      enemies(std::move(enemies)) {}

void Room::clearLoot() { items.clear(); }
void Room::clearEnemies() { enemies.clear(); }

int Room::getPosition() const { return pos; }
bool Room::getIsExit() const { return isExit; }

void Room::addItem(const Item &itm) { items.push_back(itm); }

void Room::addEnemy(std::unique_ptr<GameCharacter> enm) {
  if (!enm)
    return;
  enemies.push_back(std::move(enm));
}

const std::vector<Item> &Room::getItems() const { return items; }

const std::vector<std::unique_ptr<GameCharacter>> &Room::getEnemies() const {
  return enemies;
}
