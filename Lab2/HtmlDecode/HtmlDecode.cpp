#include "stdafx.h"
#include "HtmlDecode.h"

using namespace std;

string HtmlDecode(string const& html)
{
	static map<string, char> htmlEntities = {
		{ "&quot;", '"' },
		{ "&apos;", '\'' },
		{ "&lt;", '<' },
		{ "&gt;", '>' },
		{ "&amp;", '&' }
	};
	string resultStr;
	resultStr.reserve(html.length());

	size_t lastSearchPos = 0;
	size_t searchPos = 0;

	while (searchPos != html.length())
	{
		auto it = find_if(htmlEntities.begin(), htmlEntities.end(), [&](auto & entity) {
			return html.compare(searchPos, entity.first.length(), entity.first) == 0;
		});
		if (it != htmlEntities.end())
		{
			resultStr.append(html, lastSearchPos, searchPos - lastSearchPos);
			resultStr += it->second;
			searchPos += it->first.length();
			lastSearchPos = searchPos;
		}
		else
		{
			++searchPos;
		}
	}
	resultStr.append(html, lastSearchPos);

	return resultStr;
}