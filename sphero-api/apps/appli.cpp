#include <iostream>
#include <string>

#include "CommandHandler.h"

using namespace std;

int main(void)
{

	cout << "\033]0;Sphero-cmd\007";
	cout.flush();

	init();

	string command("");
	showHelp();
	do
	{
		cout << "Sphero > ";
		getline(cin, command);
	}
	while(handleCommand(command));


	return 0;
}
