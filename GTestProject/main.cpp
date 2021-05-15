#include "pch.h"
#include "manualTests.h"

int main(int argc, char **argv)
{
	std::cout << "select:\n1: Automated tests\n2: Manual tests\n";
	std::string selectionIN;
	std::cin >> selectionIN;
	int selection = 0;
	try {
		selection = stoi(selectionIN);
	}
	catch (std::invalid_argument& e) {
		std::cout << "please enter a number\nexiting...\n";
		exit(1);
	};
	if (selection == 1) {
		testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();
		system("pause");
	}
	if (selection == 2) {
		runAll();
		system("pause");
		return 0;
	}
	else {
		std::cout<<"no valid input entered\nexiting...\n";
	}
}