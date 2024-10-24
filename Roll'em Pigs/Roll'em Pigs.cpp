//Zac Schmunk - 10/23/2024
//Roll'em Pigs

#include <iostream>
#include <cmath>

using namespace std;

char getInput(void);
bool isWinningScore(int score);
bool isTurnPointsLost(int die1value, int die2value);
bool isGameScoreLost(int die1value, int die2value);
int rollDie(void);

// Get input from human player
char getInput(void) {
    char input;
    bool validInput = false;

    do {
        cout << "Enter 'R' to roll again or 'E' to end turn: ";
        cin >> input;
        input = tolower(input);

        if (input == 'r' || input == 'e') {
            validInput = true;
        }
        else {
            cout << "Invalid input! Please try again.\n";
        }
    } while (!validInput);

    return input;
}

// Check if score is winning score
bool isWinningScore(int score) {
    return score >= 100;
}

// Check if turn points are lost (at least one 1)
bool isTurnPointsLost(int die1value, int die2value) {
    return (die1value == 1 || die2value == 1);
}

// Check if game score is lost (both dice show 1)
bool isGameScoreLost(int die1value, int die2value) {
    return (die1value == 1 && die2value == 1);
}

// Roll a single die
int rollDie(void) {
    // Generate random number between 1 and 6
    return (rand() % 6) + 1;
}

int main() {
    // Seed random number generator
    srand(time(0));

    int humanScore = 0;
    int computerScore = 0;
    bool gameOver = false;

    cout << "Welcome to the game of Pig!\n";
    cout << "First player to reach 100 points wins.\n\n";

    while (!gameOver) {
        // Human's turn
        cout << "\n** HUMAN'S TURN **\n";
        cout << "Current score - Human: " << humanScore << ", Computer: " << computerScore << "\n";

        int turnPoints = 0;
        bool turnEnded = false;

        while (!turnEnded && !gameOver) {
            int die1 = rollDie();
            int die2 = rollDie();
            cout << "You rolled: " << die1 << " and " << die2 << "\n";

            if (isGameScoreLost(die1, die2)) {
                cout << "Double 1s! All points lost!\n";
                humanScore = 0;
                turnEnded = true;
            }
            else if (isTurnPointsLost(die1, die2)) {
                cout << "Rolled a 1! Turn points lost!\n";
                turnEnded = true;
            }
            else {
                turnPoints += (die1 + die2);
                cout << "Turn points: " << turnPoints << "\n";

                char choice = getInput();
                if (choice == 'e') {
                    humanScore += turnPoints;
                    if (isWinningScore(humanScore)) {
                        cout << "Human wins with " << humanScore << " points!\n";
                        gameOver = true;
                    }
                    turnEnded = true;
                }
            }
        }

        if (!gameOver) {
            // Computer's turn
            cout << "\n** COMPUTER'S TURN **\n";
            cout << "Current score - Human: " << humanScore << ", Computer: " << computerScore << "\n";

            turnPoints = 0;
            turnEnded = false;

            while (!turnEnded && !gameOver) {
                int die1 = rollDie();
                int die2 = rollDie();
                cout << "Computer rolled: " << die1 << " and " << die2 << "\n";

                if (isGameScoreLost(die1, die2)) {
                    cout << "Double 1s! All points lost!\n";
                    computerScore = 0;
                    turnEnded = true;
                }
                else if (isTurnPointsLost(die1, die2)) {
                    cout << "Rolled a 1! Turn points lost!\n";
                    turnEnded = true;
                }
                else {
                    turnPoints += (die1 + die2);
                    cout << "Turn points: " << turnPoints << "\n";

                    // Computer strategy: stop if 20+ points accumulated or can win
                    if (turnPoints >= 20 || (computerScore + turnPoints >= 100)) {
                        computerScore += turnPoints;
                        cout << "Computer ends turn.\n";
                        if (isWinningScore(computerScore)) {
                            cout << "Computer wins with " << computerScore << " points!\n";
                            gameOver = true;
                        }
                        turnEnded = true;
                    }
                    else {
                        cout << "Computer rolls again.\n";
                    }
                }
            }
        }
    }

    return 0;
}