#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

int main()
{
	string str;
	StreamToString(cin, str);
	cout << HtmlDecode(str) << endl;
	return 0;
}