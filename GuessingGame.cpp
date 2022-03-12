#include <iostream>
#include <string>
#include <locale>
#include <iterator>
#include <limits>
#include <ios>
#include <conio.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <sstream>
#include <list>
#include <format>
#include <random>

#define NOMINMAX
#include <Windows.h>

class Game {
public:
    Game() {
		this->start_game();
    }
    void start_game() {
		range range;
		settings settings;
		options options;

		const int space = 10;
		const int length = space * 2 + this->title.length();

		std::wstring middlechars;
		for (int i = 0; i < length; i++) {
			middlechars.append(L"\u2580");
		}
		std::wcout << this->full_block << middlechars << this->full_block << std::endl;
		std::wcout << this->full_block << std::wstring(space, L' ') << this->title << std::wstring(space, L' ') << this->full_block << std::endl;
		middlechars = L"";
		for (int i = 0; i < length; i++) {
			middlechars.append(L"\u2584");
		}
		std::wcout << this->full_block << middlechars << this->full_block << std::endl;


		for (int i = 0; i < length; i++) {
			middlechars.append(L"\u2580");
		}
		std::wcout << this->full_block << L" " << std::wstring(length - 1, L' ') << this->full_block << std::endl;
		std::wcout << this->full_block << options.start << std::wstring(length - options.start.length(), L' ') << this->full_block << std::endl;
		std::wcout << this->full_block << options.settings << std::wstring(length - options.settings.length(), L' ') << this->full_block << std::endl;
		std::wcout << this->full_block << options.language << std::wstring(length - options.language.length(), L' ') << this->full_block << std::endl;
		std::wcout << this->full_block << options.exit << std::wstring(length - options.exit.length(), L' ') << this->full_block << std::endl;
		middlechars = L"";
		for (int i = 0; i < length; i++) {
			middlechars.append(L"\u2580");
		}
		std::wcout << this->full_block << L" " << std::wstring(length - 1, L' ') << this->full_block << std::endl;
		std::wcout << L'\u2580' << middlechars << L'\u2580' << std::endl;

		int choice;
		while (true) {
			std::wcout << L"Your choice: ";
			std::wcin >> choice;
			
			switch (choice) {
			case 1: {
				this->clear_question();
				int number = this->get_random_number(range.min, range.max);
				std::wcout << std::format(L"I've chosen a random number between {} and {}. Try to guess! You have {} chances.", range.min, range.max, settings.chances) << std::endl;
				int guess;
				bool success = false;
				for (int chance = 0; chance < settings.chances; chance++) {
					std::wcout << L"Your guess: ";
					std::wcin >> guess;
					if (guess == number) {
						this->clear_question();
						if (chance <= 2) std::wcout << L"Wow, how did you guess it that fast??" << std::endl;
						else if (chance > 2 && chance < 5) std::wcout << L"You got it!" << std::endl;
						else std::wcout << L"You finally got it! Congrats!" << std::endl;
						success = true;
						break;
					}
					else {
						int dif = (guess > number) ? guess - number : number - guess;
						this->clear_question();
						std::wcout << std::format(L"The number I've chosen is {}{} than your guess. You have {} chances left!", (dif < 5) ? L"a bit " : (dif >= 5 && dif < 15) ? L"" : L"way ", (number < guess) ? L"lower" : L"higher", settings.chances - chance - 1) << std::endl;
					}
				}
				if (!success) {
					std::wcout << L"You've run out of chances. Good luck next time!" << std::endl;
				}
				break;
			}
			case 2: {

			}
			case 3: {

			}
			case 4:
				throw std::exception();
			}
		}

    }
protected:
	const std::wstring version = L"0.1.0";
	const std::wstring title = std::format(L"Guessing Game v{}", this->version);

	const std::wstring full_block = L"\u2588";
	const std::wstring upper_half_block = L"\u2580";
	const std::wstring lower_half_block = L"\u2584";
private:
	struct range {
		int min = 0;
		int max = 50;
	};
	struct settings {
		int chances = 7;
		int difficulty = 2;
	};
	struct options {
		std::wstring start =    L"  1) Start the game";
		std::wstring settings = L"  2) Settings";
		std::wstring language = L"  3) Language";
		std::wstring exit =     L"  4) Exit";
	};

    int get_random_number(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(min, max);

        return distr(gen);
    }
	void clear_question(int length = 1000) {
		COORD position = { 0, 10 };
		HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(output, position);
		std::wcout << std::wstring(length, L' ') << std::endl;
		SetConsoleCursorPosition(output, position);
	}
};

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
    std::wcout.sync_with_stdio(false);
    std::wcout.imbue(std::locale("en_US.utf8"));

	try {
		Game game;
	}
	catch (...) {
		return 0;
	}
	return 0;
}
