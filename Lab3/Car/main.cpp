#include "stdafx.h"
#include "CarRemote.h"
#include "Car.h"

using namespace std;

int main()
{
	CCar car;
	CRemoteControl remoteControl(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
}