#include "Player.hpp"
#include "Room.hpp"

Player::Player(const std::string &nm, int mHlt, int att, int deff)
    : GameCharacter(nm, mHlt, att, deff) {
  Item starterSword("Dagger", 0, 5, 0);
  addItem(starterSword);
}

void Player::addItem(const Item &itm) {
  inventory.push_back(itm);
  increaseStats(itm.getHealth(), itm.getAttack(), itm.getDefense());
}

void Player::lootRoom(Room *room) {
  if (!room)
    return;

  for (const auto &itm : room->getItems()) {
    addItem(itm);
  }

  room->clearLoot();
}

void Player::changeRoom(Room *newRoom) {
  if (!newRoom)
    return;
  previousRoom = currentRoom;
  currentRoom = newRoom;
}
