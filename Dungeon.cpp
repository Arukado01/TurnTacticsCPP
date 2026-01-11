#include "Dungeon.hpp"
#include "GameCharacter.hpp"
#include "Item.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

Dungeon::Dungeon(Player p) : player(std::move(p)), rooms(buildRooms()) {}

std::array<Room, Dungeon::NUM_ROOMS> Dungeon::buildRooms() {
  std::array<Room, NUM_ROOMS> r = {
      Room(0, false, {Item("Small Potion", 5, 0, 0)}, {}),
      Room(1, false, {Item("Iron Shield", 0, 0, 2)}, {}),
      Room(2, false, {}, {}), Room(3, true, {}, {})};

  r[2].addEnemy(std::make_unique<GameCharacter>("Goblin", 18, 6, 1));
  r[1].addEnemy(std::make_unique<GameCharacter>("Rat", 10, 4, 0));

  r[0].setExit(Room::Dir::East, 1);
  r[0].setExit(Room::Dir::South, 2);

  r[1].setExit(Room::Dir::West, 0);
  r[1].setExit(Room::Dir::South, 3);

  r[2].setExit(Room::Dir::North, 0);
  r[2].setExit(Room::Dir::East, 3);

  r[3].setExit(Room::Dir::North, 1);
  r[3].setExit(Room::Dir::West, 2);

  return r;
}

void Dungeon::printActions(const std::vector<std::string> &actions) const {
  std::cout << "\nChoose an action:\n";
  for (int i = 0; i < static_cast<int>(actions.size()); ++i) {
    std::cout << "  " << (i + 1) << ". " << actions[static_cast<size_t>(i)]
              << "\n";
  }
  std::cout << std::flush;
}

int Dungeon::readChoice(int min, int max) const {
  while (true) {
    std::cout << "> " << std::flush;

    std::string line;
    if (!std::getline(std::cin, line)) {
      return min;
    }

    while (!line.empty() && (line.back() == '\r' || line.back() == '\n' ||
                             line.back() == ' ' || line.back() == '\t')) {
      line.pop_back();
    }

    try {
      size_t idx = 0;
      int value = std::stoi(line, &idx, 10);
      if (idx != line.size())
        throw std::invalid_argument("extra");
      if (value < min || value > max) {
        std::cout << "Invalid choice. Enter a number from " << min << " to "
                  << max << ".\n";
        continue;
      }
      return value;
    } catch (...) {
      std::cout << "Invalid input. Please enter a number.\n";
    }
  }
}

int Dungeon::runDungeon() {
  std::cout << "=== TEXT RPG ===\n";
  std::cout << "Player: " << player.getName()
            << " | HP: " << player.getCurrentHealth() << "/"
            << player.getMaxHealth() << " | ATK: " << player.getAttack()
            << " | DEF: " << player.getDefense() << "\n";
  std::cout << std::flush; 

  player.moveToRoom(0);

  while (true) {
    if (player.isDead()) {
      std::cout << "\nGame Over.\n" << std::flush;
      return 0;
    }

    Room &room = rooms[static_cast<size_t>(player.getCurrentRoomId())];
    enterRoom(room);

    if (room.getIsExit() && !room.hasEnemies() && !player.isDead()) {
      std::cout << "\nYou found the exit and escaped. You win!\n" << std::flush;
      return 0;
    }
  }
}

void Dungeon::enterRoom(Room &room) {
  std::cout << "\n--- Room " << room.getId()
            << (room.getIsExit() ? " (EXIT)" : "") << " ---\n";
  std::cout << std::flush; 

  if (room.hasEnemies()) {
    handleRoomWithEnemies(room);
    return;
  }

  if (room.hasLoot()) {
    handleRoomWithChest(room);
    return;
  }

  handleEmptyRoom(room);
}

void Dungeon::handleEmptyRoom(Room &room) {
  std::cout << "This room is empty.\n" << std::flush;
  handleMovement(room);
}

void Dungeon::handleRoomWithChest(Room &room) {
  std::cout << "You found loot!\n";

  const auto &items = room.getItems();
  for (const auto &itm : items) {
    std::cout << " - " << itm.getName() << " (HP+" << itm.getHealth()
              << ", ATK+" << itm.getAttack() << ", DEF+" << itm.getDefense()
              << ")\n";
  }
  std::cout << std::flush; 

  std::vector<std::string> actions = {"Take all loot", "Ignore and move"};
  printActions(actions);

  const int choice = readChoice(1, 2);
  if (choice == 1) {
    auto looted = room.takeAllItems();
    for (const auto &itm : looted) {
      player.grantReward(itm.getHealth(), itm.getAttack(), itm.getDefense());
      std::cout << "You looted: " << itm.getName() << "\n";
    }

    std::cout << "Updated stats: HP " << player.getCurrentHealth() << "/"
              << player.getMaxHealth() << " | ATK " << player.getAttack()
              << " | DEF " << player.getDefense() << "\n";
    std::cout << std::flush; 
  }

  handleMovement(room);
}

bool Dungeon::fight(GameCharacter &enemy, Room &room) {
  while (!enemy.isDead() && !player.isDead()) {
    std::cout << "\nEnemy: " << enemy.getName()
              << " | HP: " << enemy.getCurrentHealth() << "/"
              << enemy.getMaxHealth() << " | ATK: " << enemy.getAttack()
              << " | DEF: " << enemy.getDefense() << "\n";

    std::cout << "You: " << player.getName()
              << " | HP: " << player.getCurrentHealth() << "/"
              << player.getMaxHealth() << " | ATK: " << player.getAttack()
              << " | DEF: " << player.getDefense() << "\n";
    std::cout << std::flush; 

    std::vector<std::string> actions = {"Attack", "Retreat"};
    printActions(actions);
    const int choice = readChoice(1, 2);

    if (choice == 2) {
      const int prev = player.getPreviousRoomId();
      if (prev >= 0) {
        std::cout << "You retreat!\n" << std::flush;
        player.moveToRoom(prev);
      } else {
        std::cout << "No previous room to retreat to.\n" << std::flush;
      }
      return false;
    }

    const int dealt = enemy.takeDamage(player.getAttack());
    std::cout << "You dealt " << dealt << " damage to " << enemy.getName()
              << "!\n";
    if (enemy.isDead())
      break;

    const int taken = player.takeDamage(enemy.getAttack());
    std::cout << enemy.getName() << " dealt " << taken << " damage to you!\n";
    std::cout << std::flush; 
  }

  if (player.isDead()) {
    std::cout << "\nYou were defeated by " << enemy.getName() << ".\n"
              << std::flush;
    return true;
  }

  std::cout << "\nYou defeated " << enemy.getName() << "!\n";
  player.grantReward(5, 2, 1);
  std::cout << "Reward: +5 MaxHP, +2 ATK, +1 DEF\n";
  std::cout << "Updated stats: HP " << player.getCurrentHealth() << "/"
            << player.getMaxHealth() << " | ATK " << player.getAttack()
            << " | DEF " << player.getDefense() << "\n";
  std::cout << std::flush;

  room.clearEnemies();
  return true;
}

void Dungeon::handleRoomWithEnemies(Room &room) {
  auto &enemies = room.getEnemies();
  if (enemies.empty()) {
    handleEmptyRoom(room);
    return;
  }

  GameCharacter &enemy = *enemies.front();
  std::cout << "You see an enemy: " << enemy.getName() << "!\n" << std::flush;

  std::vector<std::string> actions = {"Fight", "Back to previous room"};
  printActions(actions);
  const int choice = readChoice(1, 2);

  if (choice == 2) {
    const int prev = player.getPreviousRoomId();
    if (prev >= 0)
      player.moveToRoom(prev);
    else
      std::cout << "No previous room.\n";
    std::cout << std::flush;
    return;
  }

  fight(enemy, room);
}

void Dungeon::handleMovement(Room &room) {
  std::vector<std::string> actions;
  std::vector<int> targets;

  auto addMove = [&](const char *label, Room::Dir d) {
    const int t = room.getExit(d);
    if (t >= 0) {
      actions.emplace_back(label);
      targets.push_back(t);
    }
  };

  addMove("Go North", Room::Dir::North);
  addMove("Go East", Room::Dir::East);
  addMove("Go South", Room::Dir::South);
  addMove("Go West", Room::Dir::West);

  if (actions.empty()) {
    std::cout << "No exits. (This should not happen)\n" << std::flush;
    return;
  }

  printActions(actions);
  const int choice = readChoice(1, static_cast<int>(actions.size()));
  const int targetRoomId = targets[static_cast<size_t>(choice - 1)];
  player.moveToRoom(targetRoomId);
}
