#ifndef DIE_H
#define DIE_H

class Die {
    int value; // Stores the current value of the die
    bool locked; // Indicates if the die is locked

public:
    Die(); // Constructor
    void roll(); // Rolls the die to a new random value
    void lock(); // Locks the die
    void unlock(); // Unlocks the die
    int getValue() const; // Returns the current value of the die
    bool isLocked() const; // Returns whether the die is locked
    void reset(); // Resets the die to its initial state
};

#endif
