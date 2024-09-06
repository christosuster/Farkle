#include "Player.h"

// Constructor: Initializes the player with a name and default values
Player::Player(const std::string &playerName) {
    name = playerName;
    score = 0;
    farkleCount = 0;
    turns = 0;
}

// Adds points to the player's score
void Player::addScore(int points) {
    score += points;
}

// Increments the player's turn count
void Player::incrementTurns() {
    turns++;
}

// Resets the player's Farkle count to zero
void Player::resetFarkleCount() {
    farkleCount = 0;
}

// Increments the player's Farkle count
void Player::incrementFarkleCount() {
    farkleCount++;
}

// Returns the player's score
int Player::getScore() const {
    return score;
}

// Returns the number of turns the player has taken
int Player::getTurns() const {
    return turns;
}

// Returns the player's Farkle count
int Player::getFarkleCount() const {
    return farkleCount;
}

// Returns the player's name
const std::string &Player::getName() const {
    return name;
}
