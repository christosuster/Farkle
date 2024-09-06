#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
    std::string name; // Player's name
    int score; // Player's score
    int turns; // Number of turns the player has taken
    int farkleCount; // Number of Farkles the player has had

public:
    Player(const std::string &playerName); // Constructor

    void addScore(int points); // Adds points to the player's score
    void incrementTurns(); // Increments the turn count
    void resetFarkleCount(); // Resets the Farkle count to zero
    void incrementFarkleCount(); // Increments the Farkle count

    int getScore() const; // Returns the player's score
    int getTurns() const; // Returns the number of turns
    int getFarkleCount() const; // Returns the Farkle count
    const std::string &getName() const; // Returns the player's name
};

#endif // PLAYER_H
