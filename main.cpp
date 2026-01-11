#include "Dungeon.hpp"
#include "Player.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

static std::string trim(std::string s) {
  while (!s.empty() && (s.back() == '\r' || s.back() == '\n' ||
                        s.back() == ' ' || s.back() == '\t'))
    s.pop_back();
  size_t i = 0;
  while (i < s.size() && (s[i] == ' ' || s[i] == '\t'))
    ++i;
  if (i > 0)
    s.erase(0, i);
  return s;
}

static void printMenu(const std::vector<std::string> &options) {
  std::cout << "\nChoose an option:\n";
  for (int i = 0; i < static_cast<int>(options.size()); ++i) {
    std::cout << "  " << (i + 1) << ". " << options[static_cast<size_t>(i)]
              << "\n";
  }
  std::cout << std::flush;
}

static int readChoice(int min, int max) {
  while (true) {
    std::cout << "> " << std::flush;

    std::string line;
    if (!std::getline(std::cin, line))
      return min;
    line = trim(line);

    try {
      size_t idx = 0;
      int v = std::stoi(line, &idx, 10);
      if (idx != line.size())
        throw std::invalid_argument("extra");
      if (v < min || v > max) {
        std::cout << "Invalid choice. Enter a number from " << min << " to "
                  << max << ".\n";
        continue;
      }
      return v;
    } catch (...) {
      std::cout << "Invalid input. Please enter a number.\n";
    }
  }
}

static void pressEnterToContinue() {
  std::cout << "\nPress ENTER to continue..." << std::flush;

  if (std::cin.peek() == '\n') {
    std::cin.get();
    return;
  }

  std::string dummy;
  std::getline(std::cin, dummy);
}

struct DifficultyConfig {
  std::string name;
  int hp;
  int atk;
  int def;
};

static DifficultyConfig chooseDifficulty() {
  std::vector<DifficultyConfig> diffs = {
      {"Easy", 40, 10, 3}, {"Normal", 30, 8, 2}, {"Hard", 24, 7, 1}};

  std::cout << "\nSelect difficulty:\n";
  for (int i = 0; i < static_cast<int>(diffs.size()); ++i) {
    const auto &d = diffs[static_cast<size_t>(i)];
    std::cout << "  " << (i + 1) << ". " << d.name << "  (HP " << d.hp
              << ", ATK " << d.atk << ", DEF " << d.def << ")\n";
  }
  std::cout << std::flush;

  const int c = readChoice(1, static_cast<int>(diffs.size()));
  return diffs[static_cast<size_t>(c - 1)];
}

static void showHelp() {
  std::cout << "\n=== HELP ===\n";
  std::cout << "Goal: Find the EXIT room and escape.\n";
  std::cout << "Rules:\n";
  std::cout << " - Some rooms have loot. You can take it to gain stats.\n";
  std::cout << " - Some rooms have enemies. Combat is turn-based:\n";
  std::cout << "     You attack -> enemy attacks -> repeat.\n";
  std::cout << " - Retreat moves you back to the previous room (if any).\n";
  std::cout << "Tips:\n";
  std::cout << " - Defense reduces incoming damage.\n";
  std::cout << " - More ATK helps you finish fights faster.\n";
  std::cout << std::flush;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout << "====================================\n";
  std::cout << "        TEXT DUNGEON CRAWLER         \n";
  std::cout << "====================================\n";
  std::cout << std::flush;

  while (true) {
    std::vector<std::string> mainMenu = {"Start Game", "Help / How to Play",
                                         "Quit"};

    printMenu(mainMenu);
    const int choice = readChoice(1, 3);

    if (choice == 3) {
      std::cout << "\nGoodbye.\n";
      return 0;
    }

    if (choice == 2) {
      showHelp();
      pressEnterToContinue();
      continue;
    }

    std::cout << "\nEnter your name: " << std::flush;
    std::string name;
    std::getline(std::cin, name);
    name = trim(name);
    if (name.empty())
      name = "Hero";

    const DifficultyConfig d = chooseDifficulty();

    std::cout << "\nStarting game...\n";
    std::cout << "Player: " << name << "\n";
    std::cout << "Difficulty: " << d.name << "\n";
    std::cout << std::flush;

    pressEnterToContinue();

    Player player(name, d.hp, d.atk, d.def);
    Dungeon dungeon(std::move(player));

    const int result = dungeon.runDungeon();

    std::cout << "\n=== Run finished (code " << result << ") ===\n";
    std::cout << "Back to main menu.\n" << std::flush;
    pressEnterToContinue();
  }
}
