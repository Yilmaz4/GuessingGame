/*
MIT License

Copyright © 2017-2022 Yilmaz Alpaslan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <string>
#include <locale>
#include <chrono>
#include <list>
#include <map>
#include <algorithm>
#include <format>
#include <limits>
#include <conio.h>
#include <random>

#include "simpleini/SimpleIni.h"

#ifdef _WIN32
	#define NOMINMAX
	#include <Windows.h>
#else
	#error This program only works on Windows platform!
#endif

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

constexpr auto full_block = L"\u2588";
constexpr auto upper_half_block = L"\u2580";
constexpr auto lower_half_block = L"\u2584";

typedef std::wstring str;

namespace GuessingGame {
	static class Game {
	public:
		Game() {

		}
		void start() {
			options options;

			const int space = 10;
			const int length = space * 2 + this->title.length();

			str middlechars;
			for (int i = 0; i < length; i++) {
				middlechars.append(upper_half_block);
			}
			std::wcout << full_block << middlechars << full_block << std::endl;
			std::wcout << full_block << str(space, L' ') << this->title << str(space, L' ') << full_block << std::endl;
			middlechars = L"";
			for (int i = 0; i < length; i++) {
				middlechars.append(lower_half_block);
			}
			std::wcout << full_block << middlechars << full_block << std::endl;


			for (int i = 0; i < length; i++) {
				middlechars.append(upper_half_block);
			}
			std::wcout << full_block << L" " << str(length - 1, L' ') << full_block << std::endl;
			std::wcout << full_block << options.start << str(length - options.start.length(), L' ') << full_block << std::endl;
			std::wcout << full_block << options.settings << str(length - options.settings.length(), L' ') << full_block << std::endl;
			std::wcout << full_block << options.language << str(length - options.language.length(), L' ') << full_block << std::endl;
			std::wcout << full_block << options.exit << str(length - options.exit.length(), L' ') << full_block << std::endl;
			middlechars = L"";
			for (int i = 0; i < length; i++) {
				middlechars.append(upper_half_block);
			}
			std::wcout << full_block << L" " << str(length - 1, L' ') << full_block << std::endl;
			std::wcout << upper_half_block << middlechars << upper_half_block << std::endl;

			while (true) {
				int choice = 0;
				std::wcout << L"Your choice: ";
				std::wcin >> choice;

				switch (choice) {
				case 1: {
					try {
						while (true) {
							this->clear_question();
							const unsigned int number = this->get_random_number(settings.min, settings.max);
							std::wcout << std::format(L"I've chosen a random number between {} and {}. Try to guess! You have {} chances.", settings.min, settings.max, settings.chances) << std::endl;
							int guess;
							bool success = false;
							for (unsigned int chance = 0; chance < settings.chances; chance++) {
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
									unsigned int dif = (guess > number) ? guess - number : number - guess;
									this->clear_question();
									std::wcout << std::format(L"{}The number I've chosen is {}{} than your guess. You have {} chances left!", (dif < 3) ? L"You're too close! " : L"", (dif < 5) ? L"a bit " : (dif >= 5 && dif < 15) ? L"" : L"way ", (number < guess) ? L"lower" : L"higher", settings.chances - chance - 1) << std::endl;
								}
							}
							if (!success) {
								this->clear_question();
								std::wcout << std::format(L"You've run out of chances. The number was {}. Good luck next time!", std::to_wstring(number)) << std::endl;
							}

							HANDLE hstdin;
							DWORD mode;
							hstdin = GetStdHandle(STD_INPUT_HANDLE);
							GetConsoleMode(hstdin, &mode);
							SetConsoleMode(hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);

							std::wcout << L"Do you want to continue the game [y/n]? ";
							unsigned int ch = 10;
							const int keys[4] = { 78, 89, 110, 121 };
							while (!(std::find(std::begin(keys), std::end(keys), ch) != std::end(keys)) || ch == 10) {
								ch = std::wcin.get();
							}
							SetConsoleMode(hstdin, mode);

							switch (ch) {
							case 89 | 121:
								continue;
							case 78 | 110:
								this->clear_question();
								throw std::exception();
							}
						}
					}
					catch (...) {
						break;
					}
					break;
				case 2: {
					CSimpleIniA ini;
					SI_Error rc;

					const char* chances;
					const char* min;
					const char* max;
					
					try {
						const std::map<std::string, int> values = this->get_ini();
					}
					catch (...) {

					}
					break;
				}
				case 3: {

				}
				case 4:
					throw std::exception();
				}
				}
			}
		}
	protected:
		const str version = L"0.1.0";
		const int raw_version[3] = { 0, 1, 0 };
		const str title = std::format(L"Guessing Game v{}", this->version);
	private:
		struct settings {
			int chances = 7;
			int min = 0;
			int max = 50;
		};
		struct options {
			str start = L"  1) Start the game";
			str settings = L"  2) Settings";
			str language = L"  3) Language";
			str exit = L"  4) Exit";
		};
		settings settings;

		void load_ini(const std::string& filename = "GuessingGame.ini") {
			CSimpleIniA ini;
			SI_Error rc;

			if (!this->file_exists(filename)) {
				ini.SetUnicode();

				rc = ini.LoadFile("GuessingGame.ini");
				this->settings.chances = atoi(ini.GetValue("Settings", "chances", "7"));
				this->settings.min = atoi(ini.GetValue("Settings", "min", "0"));
				this->settings.max = atoi(ini.GetValue("Settings", "max", "50"));
			}
			else throw std::exception();
		}
		std::map<std::string, int> get_ini(const std::string& filename = "GuessingGame.ini") {
			CSimpleIniA ini;
			SI_Error rc;
			
			if (!this->file_exists(filename)) {
				std::map<std::string, int> result = {
					{ "chances", 7 },
					{ "min", 00 },
					{ "max", 50 }
				};

				ini.SetUnicode();
				rc = ini.LoadFile("GuessingGame.ini");

				result["chances"] = atoi(ini.GetValue("Settings", "chances", "7"));
				result["min"] = atoi(ini.GetValue("Settings", "min", "0"));
				result["max"] = atoi(ini.GetValue("Settings", "max", "50"));
				return result;
			}
			else throw std::exception();
		}

		static int get_random_number(const int min, const int max) {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> distr(min, max);

			return distr(gen);
		}
		static void pause() {
			std::wcout << L"Press any key to continue . . . ";

			HANDLE hstdin;
			DWORD mode;
			hstdin = GetStdHandle(STD_INPUT_HANDLE);
			GetConsoleMode(hstdin, &mode);
			SetConsoleMode(hstdin, ENABLE_ECHO_INPUT | ENABLE_PROCESSED_INPUT);

			unsigned int ch = 10;
			while (ch == 10) {
				ch = std::wcin.get();
			}
			SetConsoleMode(hstdin, mode);
		}
		static void clear_question(const int length = 1000) {
			COORD position = { 0, 10 };
			HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(output, position);
			std::wcout << str(length, L' ') << std::endl;
			SetConsoleCursorPosition(output, position);
		}
		static inline bool file_exists(const std::string& path) {
			FILE* file;
			if (errno_t err = fopen_s(&file, path.c_str(), "r")) {
				fclose(file);
				return true;
			}
			else {
				return false;
			}
		}
	};
}

int main(int argc, char* argv[], char* options[])
{
	SetConsoleOutputCP(CP_UTF8);
	setvbuf(stdout, nullptr, _IOFBF, 1000);
	std::wcout.sync_with_stdio(false);
	std::wcout.imbue(std::locale("en_US.utf8"));

	try {
		GuessingGame::Game game;
		game.start();
	}
	catch (...) {
		return 0;
	}
	return 0;
}