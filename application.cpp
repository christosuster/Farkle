#include "application.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Die.h"
#include <limits>
#include <thread>
#include <chrono>


Application::Application() {
    humanPlayer = nullptr;
    gameOver = false;
    dice.resize(6); // Initialize 6 dice
}

Application::~Application() {
    delete humanPlayer;
}

void Application::run() {
    std::cout << "==== Welcome to Farkle ====\n";
    runMenu();
}

// Displays the player's name, turn score, and total score on the console.
void Application::showPlayerStats(const Player *player, const int turnScore) {
    std::cout << "\n========================================================\n";
    std::cout << player->getName() << "'s turn | Turn Score: " << turnScore << " | Total Score: " << player->
            getScore() << "\n";
    std::cout << "========================================================\n";
}


// Displays the player's total score at the end of their turn on the console.
void Application::showPlayerTurnEndStats(const Player *player) {
    std::cout << "\n========================================================\n";
    std::cout << player->getName() << "'s Total Score: " << player->
            getScore() << "\n";
    std::cout << "========================================================\n";
}


// Displays the game menu and processes user input until the game ends.
void Application::runMenu() {
    do {
        int choice;
        std::cout << "\n==== Farkle Game Menu ====\n";
        std::cout << "[1] End the game\n";
        std::cout << "[2] Display Game Rules\n";
        std::cout << "[3] Play Farkle\n";
        std::cout << "[4] Display the Reflection Report\n";
        std::cout << "\nEnter your choice: ";

        // Validate user input
        while (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }

        switch (choice) {
            case 1:
                gameOver = true;
                std::cout << "Exiting the game...\n";
                break;
            case 2:
                displayGameRules("gameRules.txt");
                break;
            case 3:
                playFarkle();
                break;
            default:
                std::cout << "\nInvalid option. Please choose again.\n";
                break;
        }
    } while (!gameOver);
}


// Reads and displays game rules from the specified file.
void Application::displayGameRules(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }
    std::cout << "\n==== Game Rules ====\n";
    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}


// Determines if the given dice configuration results in a Farkle (i.e., no scoring combination).
bool Application::isFarkle(const std::vector<Die> &dice) {
    std::vector<int> dice_value_count(7, 0); // Index 0 is unused, 1-6 for die values

    // Count occurrences of each die value, ignoring locked dice
    for (const auto &die: dice) {
        if (!die.isLocked()) {
            dice_value_count[die.getValue()]++;
        }
    }

    // If there are any dice with values 1 or 5, it's not a Farkle
    if (dice_value_count[1] > 0 || dice_value_count[5] > 0) {
        return false;
    }

    // Check for special combinations of dice
    for (int i = 1; i <= 6; ++i) {
        if (dice_value_count[i] == 6) {
            // All dice are the same (3000 points)
            return false;
        }

        if (dice_value_count[i] == 4) {
            // Four of a kind
            return false;
        }

        if (dice_value_count[i] == 3) {
            // Three of a kind
            return false;
        }

        if (dice_value_count[i] == 2) {
            // Check for three pairs or one pair with four of a kind
            int pairs = 0;
            for (int j = 1; j <= 6; ++j) {
                if (dice_value_count[j] == 2) {
                    pairs++;
                }
            }
            if (pairs == 3) {
                return false; // Three pairs is a valid combination
            }
            if (pairs == 1) {
                for (int j = 1; j <= 6; ++j) {
                    if (dice_value_count[j] == 4) {
                        return false; // One pair and four of a kind is valid
                    }
                }
            }
        }
    }

    // No valid scoring combination found, so it is a Farkle
    return true;
}


// Function to simulate computer thinking for a given number of milliseconds
void Application::simulateThinking(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Function to print the current dice values to the console
void Application::printDice(const std::vector<Die> &dice) {
    std::string lines[6];
    std::cout << std::endl;
    int i = 0;
    for (const Die &die: dice) {
        i++;
        switch (die.getValue() && !die.isLocked() ? die.getValue() : 0) {
            case 1:
                lines[0] += "+-------+  ";
                lines[1] += "|       |  ";
                lines[2] += "|   *   |  ";
                lines[3] += "|       |  ";
                lines[4] += "+-------+  ";
                lines[5] += "   [" + std::to_string(i) + "]     ";
                break;
            case 2:
                lines[0] += "+-------+  ";
                lines[1] += "| *     |  ";
                lines[2] += "|       |  ";
                lines[3] += "|     * |  ";
                lines[4] += "+-------+  ";
                lines[5] += "   [" + std::to_string(i) + "]     ";
                break;
            case 3:
                lines[0] += "+-------+  ";
                lines[1] += "| *     |  ";
                lines[2] += "|   *   |  ";
                lines[3] += "|     * |  ";
                lines[4] += "+-------+  ";
                lines[5] += "   [" + std::to_string(i) + "]     ";
                break;
            case 4:
                lines[0] += "+-------+  ";
                lines[1] += "| *   * |  ";
                lines[2] += "|       |  ";
                lines[3] += "| *   * |  ";
                lines[4] += "+-------+  ";
                lines[5] += "   [" + std::to_string(i) + "]     ";
                break;
            case 5:
                lines[0] += "+-------+  ";
                lines[1] += "| *   * |  ";
                lines[2] += "|   *   |  ";
                lines[3] += "| *   * |  ";
                lines[4] += "+-------+  ";
                lines[5] += "   [" + std::to_string(i) + "]     ";
                break;
            case 6:
                lines[0] += "+-------+  ";
                lines[1] += "| *   * |  ";
                lines[2] += "| *   * |  ";
                lines[3] += "| *   * |  ";
                lines[4] += "+-------+  ";
                lines[5] += "   [" + std::to_string(i) + "]     ";
                break;
            default:
                lines[0] += "+-------+  ";
                lines[1] += "|       |  ";
                lines[2] += "|       |  ";
                lines[3] += "|       |  ";
                lines[4] += "+-------+  ";
                lines[5] += "   [X]     ";
        }
    }

    // Print each line of the combined dice
    for (const std::string &line: lines) {
        std::cout << line << std::endl;
    }
}

// Calculates the score based on the positions of the dice and their values.
int Application::getScoreFromDiePosition(const std::vector<int> &positions, const std::vector<Die> &dice) {
    int score = 0;
    std::vector<int> dice_value_count(7, 0); // Count occurrences of each die value

    // Count dice values at the given positions
    for (int position: positions) {
        dice_value_count[dice[position - 1].getValue()]++;
    }

    // Check for a straight (1-6)
    if (dice_value_count[1] == 1 && dice_value_count[2] == 1 && dice_value_count[3] == 1 &&
        dice_value_count[4] == 1 && dice_value_count[5] == 1 && dice_value_count[6] == 1) {
        score += 1500; // Straight is worth 1500 points
        for (int i = 1; i <= 6; ++i) {
            dice_value_count[i]--;
        }
    }

    // Check for special combinations
    for (int i = 1; i <= 6; ++i) {
        if (dice_value_count[i] == 6) {
            score += 3000; // All dice are the same (3000 points)
            dice_value_count[i] -= 6;
            break;
        }

        if (dice_value_count[i] == 5) {
            score += 2000; // Five of the same kind
            dice_value_count[i] -= 5;
            continue;
        }

        if (dice_value_count[i] == 4) {
            int pairs = 0;
            for (int j = 1; j <= 6; ++j) {
                if (dice_value_count[j] == 2) {
                    pairs++;
                }
            }
            if (pairs == 1) {
                score += 1500; // Four of a kind and a pair
                break;
            }
            score += 1000; // Four of the same kind
            dice_value_count[i] -= 4;
            continue;
        }

        if (dice_value_count[i] == 3) {
            int sets = 0;
            for (int j = 1; j <= 6; ++j) {
                if (dice_value_count[j] == 3) {
                    sets++;
                }
            }
            if (sets == 2) {
                score += 2500; // Two sets of three of the same kind
                break;
            }
            score += (i == 1) ? 1000 : i * 100; // Three of the same kind
            dice_value_count[i] -= 3;
            continue;
        }

        if (dice_value_count[i] == 2) {
            int pairs = 0;
            for (int j = 1; j <= 6; ++j) {
                if (dice_value_count[j] == 2) {
                    pairs++;
                }
            }
            if (pairs == 3) {
                score += 1500; // Three pairs
                break;
            }
            if (pairs == 1) {
                for (int j = 1; j <= 6; ++j) {
                    if (dice_value_count[j] == 4) {
                        score += 1500; // One pair and four of a kind
                        break;
                    }
                }
            }
        }
    }

    // Add points for single "1"s and "5"s
    score += dice_value_count[1] * 100; // Single "1" is worth 100 points
    score += dice_value_count[5] * 50; // Single "5" is worth 50 points

    return score;
}


// Prompts the user to select dice to lock and updates turn score based on selection.
std::vector<int> Application::selectDice(std::vector<Die> &dice, int &turnScore, const Player *currentPlayer) {
    std::vector<int> selectedIndices;

    // Continuously prompt the user until valid dice are selected
    while (true) {
        std::vector<int> dice_value_count(7, 0); // Count occurrences of each die value
        std::string input;
        std::vector<int> valid_positions;

        // Prompt user for dice selection
        std::cout <<
                "\nPlease select the die you want using the number under it. Do not use spaces or commas. Press ENTER to finish.\n";
        std::cout << "The dice you want are: ";
        std::cin >> input;
        bool invalidInput = false;

        // Process user input
        for (char c: input) {
            int digit = c - '0';

            // Validate digit and check if die is locked
            if (digit >= 1 && digit <= 6) {
                if (!dice[digit - 1].isLocked()) {
                    dice_value_count[dice[digit - 1].getValue()]++;
                    valid_positions.push_back(digit);
                } else {
                    std::cout << "Die " << digit << " is already locked. Try again.\n";
                    invalidInput = true;
                    break;
                }
            } else {
                std::cout << "Invalid index. Try again.\n";
                invalidInput = true;
                break;
            }
        }

        // Validate selections based on game rules
        for (int valid_position: valid_positions) {
            int diceValue = dice[valid_position - 1].getValue();

            if (diceValue == 2 || diceValue == 3 || diceValue == 4 || diceValue == 6) {
                if (dice_value_count[diceValue] == 1) {
                    bool straight = true;
                    for (int i = 1; i <= 6; i++) {
                        if (dice_value_count[i] != 1) {
                            straight = false;
                            break;
                        }
                    }

                    if (!straight) {
                        std::cout << "\nDie " << valid_position << " is an invalid selection in this scenario\n";
                        invalidInput = true;
                        break;
                    }
                }
                if (dice_value_count[diceValue] == 2) {
                    int pairs = 0;
                    for (int j = 1; j <= 6; ++j) {
                        if (dice_value_count[j] == 2) {
                            pairs++;
                        }
                    }
                    if (pairs == 3) {
                        continue;
                    }
                    bool four_of_a_kind = false;
                    if (pairs == 1) {
                        for (int j = 1; j <= 6; ++j) {
                            if (dice_value_count[j] == 4) {
                                four_of_a_kind = true;
                                break;
                            }
                        }
                    }
                    if (four_of_a_kind) {
                        continue;
                    }

                    std::cout << "\nDie " << valid_position << " is an invalid selection in this scenario\n";
                    invalidInput = true;
                    break;
                }
            }
        }

        if (invalidInput) continue;

        // Lock valid dice and update turn score
        for (int i: valid_positions) {
            dice[i - 1].lock();
        }

        turnScore += getScoreFromDiePosition(valid_positions, dice);

        // Show updated player stats
        showPlayerStats(currentPlayer, turnScore);

        break;
    }

    return selectedIndices;
}


// Main game loop for playing Farkle
void Application::playFarkle() {
    std::string playerName;
    std::cout << "\nEnter player name: ";
    std::cin >> playerName;

    // Initialize players
    humanPlayer = new Player(playerName);
    computer = new Player("Computer");
    bool playing = true;

    Player *currentPlayer = humanPlayer;

    // Game loop
    while (playing && currentPlayer->getFarkleCount() < 3 && currentPlayer->getScore() < 500) {
        int turnScore = 0; // Initialize turn score
        bool farkle = false;

        showPlayerStats(currentPlayer, turnScore);

        // Roll dice
        for (Die &die: dice) {
            die.unlock(); // Unlock all dice
            die.roll(); // Roll each die
        }

        printDice(dice);

        // Check for Farkle
        if (isFarkle(dice)) {
            std::cout << "\n********** Farkle! No points for this round. ********** \n";
            showPlayerTurnEndStats(currentPlayer);
            simulateThinking(500); // Simulate thinking
            currentPlayer->incrementFarkleCount(); // Increment Farkle count
            farkle = true;
        } else {
            currentPlayer->resetFarkleCount(); // Reset Farkle count
        }

        // Player's turn
        while (!farkle) {
            if (currentPlayer == humanPlayer) {
                std::vector<int> selectedIndices = selectDice(dice, turnScore, currentPlayer);

                char choice;
                while (true) {
                    std::cout << "\nDo you want to [q]uit, [r]oll or [s]core: ";
                    std::cin >> choice;
                    if (choice == 'q' || choice == 'r' || choice == 's') break;
                }

                if (choice == 's' || choice == 'S') {
                    currentPlayer->addScore(turnScore); // Add score
                    std::cout << "\n********** End of turn **********\n";
                    showPlayerTurnEndStats(currentPlayer);
                    break;
                }
                if (choice == 'r' || choice == 'R') {
                    // Roll unlocked dice
                    for (Die &die: dice) {
                        if (!die.isLocked()) {
                            die.roll();
                        }
                    }
                    printDice(dice);

                    // Check for Farkle again
                    if (isFarkle(dice)) {
                        std::cout << "\n********** Farkle! No points for this round. ********** \n";
                        simulateThinking(500);
                        std::cout << "\n********** Computer's Turn ********** \n";
                        simulateThinking(500);
                        currentPlayer->incrementFarkleCount();
                        farkle = true;
                    }
                }

                if (choice == 'q' || choice == 'Q') {
                    playing = false; // Exit game
                    break;
                }
            } else {
                // Computer's turn
                std::cout << "\nComputer is thinking...\n";
                simulateThinking(2000); // Simulate thinking
                std::vector<int> selectedIndices;

                // Simple AI: lock dice contributing to score
                for (int i = 0; i < dice.size(); ++i) {
                    if (!dice[i].isLocked()) {
                        if (dice[i].getValue() == 1 || dice[i].getValue() == 5) {
                            selectedIndices.push_back(i + 1);
                            dice[i].lock();
                        }
                    }
                }

                std::cout << "\nComputer locked dice: ";
                simulateThinking(500); // Simulate thinking
                for (auto index: selectedIndices) {
                    std::cout << index << " ";
                }
                std::cout << std::endl;

                turnScore += getScoreFromDiePosition(selectedIndices, dice);
                showPlayerStats(currentPlayer, turnScore);
                simulateThinking(1000);

                // Decide whether to score or roll again
                if (turnScore >= 300) {
                    currentPlayer->addScore(turnScore); // Add score
                    std::cout << "\nComputer decides to score. \n";
                    simulateThinking(500); // Simulate thinking
                    showPlayerTurnEndStats(currentPlayer);
                    break;
                } else {
                    std::cout << "\nComputer decides to roll again.\n";
                    simulateThinking(1000);

                    // Roll remaining dice
                    for (Die &die: dice) {
                        if (!die.isLocked()) {
                            die.roll();
                        }
                    }
                    printDice(dice);

                    // Check for Farkle
                    if (isFarkle(dice)) {
                        simulateThinking(1000);
                        std::cout << "\n********** Farkle! No points for this round. ********** \n";
                        simulateThinking(500);
                        currentPlayer->incrementFarkleCount();
                        farkle = true;
                    }
                    simulateThinking(1000);
                }
            }
        }

        // Check for win or loss
        if (currentPlayer->getScore() >= 500) {
            std::cout << "\nCongratulations! " << currentPlayer->getName() << " wins the game with " << currentPlayer->
                    getScore() << " points!\n";
            playing = false;
        } else if (currentPlayer->getFarkleCount() >= 3) {
            std::cout << "\nSorry, " << currentPlayer->getName() << " lost the game after 3 Farkles.\n";
            playing = false;
        } else {
            // Switch player
            currentPlayer = (currentPlayer == humanPlayer) ? computer : humanPlayer;
        }
    }

    // Display final stats
    std::cout << "\n********** Final Player Stats **********\n";
    std::cout << humanPlayer->getName() << " - Score: " << humanPlayer->getScore() << "\n";
    std::cout << computer->getName() << " - Score: " << computer->getScore() << "\n";

    runMenu(); // Return to main menu
}


int main() {
    Application app; // Create an Application instance
    app.run(); // Run the application
    return 0; // Exit the program
}

