#include "Die.h"  // Include the header file for the Die class
#include <cstdlib>
#include <ctime>

// Constructor: Initializes the die
Die::Die() {
    value = 0;
    locked = false;
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator
}

// Rolls the die to a new value if it is not locked
void Die::roll() {
    if (!locked) {
        value = (rand() % 6) + 1; // Random number between 1 and 6
    }
}

// Locks the die to prevent it from being rolled
void Die::lock() {
    locked = true;
}

// Unlocks the die to allow it to be rolled
void Die::unlock() {
    locked = false;
}

// Returns the current value of the die
int Die::getValue() const {
    return value;
}

// Returns whether the die is locked
bool Die::isLocked() const {
    return locked;
}

// Resets the die to its initial state
void Die::reset() {
    value = 0;
    locked = false;
}
