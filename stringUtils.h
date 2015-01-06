#pragma once

#include <string>
#include <vector>

namespace StringUtils
{
	///
	/// Returns a string with leading and trailing whitespace removed. Here for simplicity.
	///
	std::string trim(const std::string &str);

	///
	/// Returns a vector of strings, tokenised using the characters given in tags. Here for simplicity.
	///
	std::vector<std::string> split(const std::string &contents, const std::string &tags);
}
