#include "stdafx.h"
#include "HtmlDecode.h"
#include "GetlineIterator.h"

using namespace std;

int main()
{
	transform(CGetlineIterator(cin), CGetlineIterator(), ostream_iterator<string>(cout, "\n\n"), [](string const& str)
	{
		return HtmlDecode(str);
	});
	return 0;
}