#pragma once
#include "Player.hpp"
#include "Room.hpp"
#include <array>
#include <string>
#include <vector>

class Dungeon {
public:
  explicit Dungeon(Player p);
  int runDungeon();

private:
  static constexpr int NUM_ROOMS = 4;

  Player player;
  std::array<Room, NUM_ROOMS> rooms;

  std::array<Room, NUM_ROOMS> buildRooms();

  void enterRoom(Room &room);
  void handleEmptyRoom(Room &room);
  void handleRoomWithChest(Room &room);
  void handleRoomWithEnemies(Room &room);
  void handleMovement(Room &room);

  bool fight(GameCharacter &enemy, Room &room);

  void printActions(const std::vector<std::string> &actions) const;
  int readChoice(int min, int max) const;
};
