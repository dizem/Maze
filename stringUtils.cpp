#include "stringUtils.h"

#include <cstdio>

// There are hundreds of libraries out there for doing this kind of stuff, but if you don't want to include them for just a couple of functions, here's an
// example of one way of implementing trim/split operations.

std::string StringUtils::trim(const std::string &str)
{
	if (str.length() == 0)
		return str;

	int startPos = 0;
	while (isspace(str[startPos]) && startPos < (int) str.length())
		startPos++;
	int endPos = str.length() - 1;
	while (isspace(str[endPos]) && endPos >= 0)
		endPos--;

	return str.substr(startPos, endPos - startPos + 1);
}

std::vector<std::string> StringUtils::split(const std::string &contents, const std::string &tags)
{
	int start = 0;
	std::vector<std::string> tokens;

	for (int i = 0; i < (int) contents.size(); i++)
	{
		if (tags.find(contents[i]) == std::string::npos)
			continue;
		if (i == start) start = i + 1;
		else
		{
			tokens.push_back(std::string(&contents[start], i - start));
			start = i + 1;
		}
	}

	if (start < (int) contents.size())
		tokens.push_back(std::string(&contents[start], contents.size() - start));

	return tokens;
}
