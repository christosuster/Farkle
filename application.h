#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include "Player.h"
#include "Die.h"

class Application {
    Player *humanPlayer;
    Player *computer{};
    std::vector<Die> dice;
    bool gameOver;

public:
    Application();

    ~Application();

    void run();

    static void showPlayerStats(const Player *player, int turnScore); // Display player stats

    static void showPlayerTurnEndStats(const Player *player); // Display player stats at the end of a turn

    void runMenu(); // Display the main menu

    static void displayGameRules(const std::string &filename); // Display the game rules

    static bool isFarkle(const std::vector<Die> &dice); // Check if the dice roll is a Farkle

    static void simulateThinking(int milliseconds); // Simulate computer thinking time

    static void printDice(const std::vector<Die> &dice); // Display the current dice values

    static std::vector<int> selectDice(std::vector<Die> &dice, int &turnScore, const Player *currentPlayer); // Select dice to score

    static int getScoreFromDiePosition(const std::vector<int> &positions, const std::vector<Die> &dice); // Calculate score from selected dice

    void playFarkle(); // Play a game of Farkle
};

#endif // APPLICATION_H
