#include "ErrorCheck.h"
#include <iostream>
#include <limits>

int getNumericInput(int min, int max, const std::string& prompt) {
    int input;
    std::cout << prompt;  // Display the prompt before capturing input
    while (true) {
        if (std::cin >> input) {
            if (input >= min && input <= max) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
                return input;
            } else {
                std::cout << "Error: Input is out of range. Please enter a number between " << min << " and " << max << ":\n";
            }
        } else {
            std::cout << "Error: Invalid input. Please enter a number.\n";
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore incorrect input
            std::cout << prompt;  // Re-display the prompt after an error
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (!input.empty()) {
            return input; // Returns input if it is not empty
        } else {
            std::cout << "Error: Input cannot be empty. Please try again.\n";
        }
    }
}
