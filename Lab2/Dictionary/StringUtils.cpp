#include "stdafx.h"
#include "StringUtils.h"

std::string StrToLowerCase(std::string const& str)
{
	std::locale rusLocale("Russian");

	std::string loweredStr(str);
	std::transform(loweredStr.begin(), loweredStr.end(), loweredStr.begin(),
		std::bind1st(std::mem_fun(&std::ctype<char>::tolower), &std::use_facet<std::ctype<char>>(rusLocale))
	);

	return loweredStr;
}
