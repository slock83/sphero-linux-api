#include <iostream>
#include <string>

#include "CommandHandler.h"

using namespace std;

int main(void)
{
	
	cout << "\033]0;Sphero-cmd\007";
	cout.flush();

	string command("");
	do
	{
		getline(cin, command);
	}
	while(handleCommand(command));
	
	
	return 0;
}
