#include <iostream>
#include <random>
#include <string>
#include <limits>
#include <cctype>

struct Difficulty {
    std::string name;
    int minVal;
    int maxVal;
    int maxAttempts;
};

int askIntInRange(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        int x;
        if (std::cin >> x) {
            if (x >= lo && x <= hi) return x;
            std::cout << "Please enter a number between " << lo << " and " << hi << ".\n";
        } else {
            std::cout << "That's not a number. Try again.\n";
        }
        std::cin.clear(); // clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard line
    }
}

bool askYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string s;
        if (!(std::cin >> s)) return false;
        if (!s.empty()) {
            char c = std::tolower(static_cast<unsigned char>(s[0]));
            if (c == 'y') return true;
            if (c == 'n') return false;
        }
        std::cout << "Please enter Y or N.\n";
    }
}

Difficulty selectDifficulty() {
    std::cout << "\nChoose difficulty:\n"
              << "  1) Easy    (1–50,    10 attempts)\n"
              << "  2) Medium  (1–100,    8 attempts)\n"
              << "  3) Hard    (1–1000,  10 attempts)\n"
              << "  4) Custom  (you choose range & attempts)\n";
    int choice = askIntInRange("Enter 1–4: ", 1, 4);

    switch (choice) {
        case 1: return {"Easy",   1,   50, 10};
        case 2: return {"Medium", 1,  100,  8};
        case 3: return {"Hard",   1, 1000, 10};
        default: {
            int lo = askIntInRange("Custom - enter minimum (>= -1e6): ", -1000000, 1000000);
            int hi = askIntInRange("Custom - enter maximum (<=  1e6): ",  -1000000, 1000000);
            while (hi < lo) {
                std::cout << "Max must be >= Min. Try again.\n";
                hi = askIntInRange("Custom - enter maximum: ", -1000000, 1000000);
            }
            int maxA = askIntInRange("Custom - attempts (1–100): ", 1, 100);
            return {"Custom", lo, hi, maxA};
        }
    }
}

int main() {
    std::cout << "===== Number Guessing Game =====\n";

    // Random engine seeded once
    std::random_device rd;
    std::mt19937 rng(rd());

    do {
        Difficulty d = selectDifficulty();
        std::uniform_int_distribution<int> dist(d.minVal, d.maxVal);
        int secret = dist(rng);

        std::cout << "\nDifficulty: " << d.name
                  << " | Range: " << d.minVal << "–" << d.maxVal
                  << " | Attempts: " << d.maxAttempts << "\n";
        std::cout << "I have picked a number. Can you guess it?\n\n";

        bool won = false;
        for (int attempt = 1; attempt <= d.maxAttempts; ++attempt) {
            std::cout << "[Attempt " << attempt << " of " << d.maxAttempts << "] ";
            int guess = askIntInRange("Enter your guess: ", d.minVal, d.maxVal);

            if (guess == secret) {
                std::cout << "🎉 Correct! You guessed it in " << attempt << " attempt"
                          << (attempt == 1 ? "" : "s") << ".\n";
                won = true;
                break;
            } else if (guess < secret) {
                std::cout << "Too low";
            } else {
                std::cout << "Too high";
            }

            // Optional “warmer/colder” hint for medium/large ranges
            int span = d.maxVal - d.minVal;
            if (span >= 50) {
                int diff = std::abs(secret - guess);
                if      (diff <= span / 50)  std::cout << " (blazing hot)";
                else if (diff <= span / 20)  std::cout << " (hot)";
                else if (diff <= span / 10)  std::cout << " (warm)";
                else if (diff <= span / 5)   std::cout << " (cool)";
                else                         std::cout << " (cold)";
            }
            std::cout << ". ";
            std::cout << "Remaining: " << (d.maxAttempts - attempt) << "\n";
        }

        if (!won) {
            std::cout << "Out of attempts! The number was: " << secret << ". Better luck next time!\n";
        }

    } while (askYesNo("\nPlay again? (Y/N): "));

    std::cout << "Thanks for playing. Goodbye!\n";
    return 0;
}
