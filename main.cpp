#include <iostream>
#include <string>
#include <cstdio>
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

#define NOMINMAX
#include <Windows.h>

using namespace std;

namespace user_interface {
	class menus;
}

class user_interface::menus {
	public:
		menus(bool enableUTF8 = true) {
			if (enableUTF8) {
				SetConsoleOutputCP(CP_UTF8);
				setvbuf(stdout, nullptr, _IOFBF, 1000);
				std::wcout.sync_with_stdio(false);
				std::wcout.imbue(std::locale("en_US.utf8"));
			}
		}
		void printMainMenu() {
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
		}
		void printOptions(bool ask = true) {
			const int space = 10;
			const int length = space * 2 + this->title.length();

			
			options options;

			std::wstring middlechars;
			for (int i = 0; i < length; i++) {
				middlechars.append(L"\u2580");
			}
			std::wcout << this->full_block << L" " << std::wstring(length - 1, L' ') << this->full_block << std::endl;
			std::wcout << this->full_block << options.printHelloWorld << std::wstring(length - options.printHelloWorld.length(), L' ') << this->full_block << std::endl;
			std::wcout << this->full_block << options.askForInput << std::wstring(length - options.askForInput.length(), L' ') << this->full_block << std::endl;
			std::wcout << this->full_block << options.calculator << std::wstring(length - options.calculator.length(), L' ') << this->full_block << std::endl;
			std::wcout << this->full_block << options.exit << std::wstring(length - options.exit.length(), L' ') << this->full_block << std::endl;
			middlechars = L"";
			for (int i = 0; i < length; i++) {
				middlechars.append(L"\u2580");
			}
			std::wcout << this->full_block << L" " << std::wstring(length - 1, L' ') << this->full_block << std::endl;
			std::wcout << L'\u2580' << middlechars << L'\u2580' << std::endl;
			if (ask) {
				while (true) {
					std::wstring raw_wish;
					int wish;
					for (int i = 0; true; i++) {
						std::wstring question = i == 0 ? L"Your wish: " : L"Please enter a valid input! Your wish: ";
						std::wcout << question;
						std::wcin >> raw_wish;

						std::wstringstream convertor;
						convertor << raw_wish;
						convertor >> wish;
						if (convertor.fail()) {
							this->clear_question();
							continue;
						}

						list<int> main_inputs = { 1, 2, 3, 4 };
						if (std::find(main_inputs.begin(), main_inputs.end(), wish) != main_inputs.end()) {
							break;
						}
						else {
							this->clear_question();
							continue;
						}
					}
					this->clear_question();
					std::wstring input;
					char oper = ' ';
					float number1, number2;
					switch (wish) {
						case 1: {
							std::wcout << L"Hello World!" << std::endl;
							break;
						}
						case 2: {
							std::wcout << L"Enter something: ";
							std::wcin >> input;
							clear_question();
							std::wcout << L"You've entered: " << input << std::endl;
							break;
						}
						case 3: {
							for (int i = 0; true; i++) {
								std::wstring question = i == 0 ? L"Enter operator: " : L"The operator can be either +, -, * or /. Enter operator: ";
								std::wcout << question;
								std::cin >> oper;
								this->clear_question();

								list<char> oper_inputs = { '+', '-', '*', '/' };
								if (std::find(oper_inputs.begin(), oper_inputs.end(), oper) != oper_inputs.end()) {
									break;
								}
								else {
									this->clear_question();
									continue;
								}
							}

							std::wcout << L"Enter two operands: ";
							std::cin >> number1 >> number2;
							this->clear_question();

							switch (oper) {
							case '+':
								std::wcout << this->remove_trailing_zeros(std::to_wstring(number1)) << std::format(L" {} ", oper) << this->remove_trailing_zeros(std::to_wstring(number2)) << " = " << number1 + number2 << std::endl;
								break;
							case '-':
								std::wcout << this->remove_trailing_zeros(std::to_wstring(number1)) << std::format(L" {} ", oper) << this->remove_trailing_zeros(std::to_wstring(number2)) << " = " << number1 - number2 << std::endl;
								break;
							case '*':
								std::wcout << this->remove_trailing_zeros(std::to_wstring(number1)) << std::format(L" {} ", oper) << this->remove_trailing_zeros(std::to_wstring(number2)) << " = " << number1 * number2 << std::endl;
								break;
							case '/':
								std::wcout << this->remove_trailing_zeros(std::to_wstring(number1)) << std::format(L" {} ", oper) << this->remove_trailing_zeros(std::to_wstring(number2)) << " = " << number1 / number2 << std::endl;
								break;
							}
							break;
						}
						case 4: {
							throw std::exception();
						}
					}
					this->pause();
					this->clear_question();
				}
			}
		}
	protected:
		const std::wstring version = L"0.1.0";
		const std::wstring title = std::format(L"Hello World v{} on C++", this->version);

		const std::wstring full_block = L"\u2588";
		const std::wstring upper_half_block = L"\u2580";
		const std::wstring lower_half_block = L"\u2584";
	private:
		struct options {
			std::wstring printHelloWorld = L"  1) Print \"Hello World!\"";
			std::wstring askForInput = L"  2) Ask for input";
			std::wstring calculator = L"  3) Calculator";
			std::wstring exit = L"  4) Exit";
		};
		void pause() {
			system("pause");
		}
		void clear_question(int length = 1000) {
			COORD position = { 0, 10 };
			HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleCursorPosition(output, position);
			std::wcout << std::wstring(length, L' ') << std::endl;
			SetConsoleCursorPosition(output, position);
		}
		bool ends_with(std::wstring const& fullString, std::wstring const& ending) {
			if (fullString.length() >= ending.length()) {
				return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
			}
			else return false;
		}
		std::wstring remove_trailing_zeros(std::wstring str)
		{
			for (string::size_type s = str.length() - 1; s > 0; --s) {
				if (str[s] == '0') {
					str.erase(s, 1);
				}
				else break;
			}
			if (this->ends_with(str, L".")) str.erase(str.end() - 1);
			return str;
		}
};

int main(int argc, char* argv[]) {
	user_interface::menus menus;
	try {
		menus.printMainMenu();
		menus.printOptions(true);
	}
	catch (...) {
		return 0;
	}
	return 0;
}