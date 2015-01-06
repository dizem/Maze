#pragma once

#include <string>
#include <vector>
#include <functional>

// In assignment 2 this can be improved so that these forward declarations will not be needed.
class Maze;

///
/// An individual command line option (ie, -g, --sv).
///
class Option
{
	friend class OptionSet;
private:
	std::string tag;																///< Type of argument entered from the command line.
	std::string report;																///< Message that is printed when running the option.
	std::string error;																///< Message that is printed if the function associated with the option fails.
	std::function <bool (Maze *maze, Option *option)> f;		///< Function that is executed when running the option.
	std::vector<std::string> values;												///< Values that have been entered after the arg, when parsed.
	std::string descr;																///< Description of what the argument does.
	int nExpected;																	///< No. of args expected to be entered after the tag on the command line.

private:
	///
	/// Returns a string with `x` tags replaced with strings from the values vector.
	///
	std::string parseMsg(const std::string &msg) const;

public:
	///
	/// Default constructor that creates an empty command line option.
	///
	Option() : nExpected(0) {}

	///
	/// Constructs a command line option of type 'tag', example usage:
	///
	/// { "-g", "Generating maze with seed: `0`, width: `1`, height: `2`\n", "Failed to build maze", "Generate maze: seed width height", 3 }
	///
	/// Where tags inside `` are used to print the value at the matching location in the values vector, when printing reports and errors.
	///
	/// @param tag type of argument.
	/// @param report message that is printed when running the option.
	/// @param error message that is printed if the function f returns false.
	/// @param f function that is executed when running the option.
	/// @param descr description of what the argument does.
	/// @param nExpected number of args expected to be entered after tag on the command line.
	///
	Option(const std::string &tag, const std::string &report, const std::string &error, std::function<bool (Maze *maze, Option *option)> f,
		const std::string &descr = "", int nExpected = 1) : tag(tag), report(report), error(error), f(f), descr(descr), nExpected(nExpected) {}

	///
	/// Executes function f, passing to it maze, builder and this.
	/// @return the value returned by f.
	///
	bool run(Maze *maze);

	///
	/// Prints string stored in report to cout, after running parseMsg on it.
	///
	void printReport() const;

	///
	/// Prints the string stored in error to cout, after running parseMsg on it.
	///
	void printError() const;

	///
	/// Returns value from the values vector at pos.
	/// @param pos the location of the desired element in the values vector.
	/// @return that data stored at location pos in the values vector.
	///
	const std::string &getValue(size_t pos) const;
};

///
/// Simplifies processing of command line args.
///
class OptionSet
{
private:
	std::vector<Option> options;			///< Set of available options. This should use a different data structure for simplicity in assignment 2.
	std::vector<Option> commands;			///< Set of commands that have been parsed.

public:
	///
	/// Default constructor that creates an empty OptionSet.
	///
	OptionSet() {}

	///
	/// Constructs an OptionSet with a given set of options, example usage for assignment 1:
	///
	///	{ "--lb", "Loading maze: `0`\n", "Failed to load maze: `0`\n", &loadBinary, "Load Binary file: filename.maze" },
	///	{ "--sb", "Saving binary maze: `0`\n", "Failed to save binary maze: `0`\n", &saveBinary, "Save Binary file: filename.maze" },
	///	{ "--sv", "Saving svg maze: `0`\n", "Failed to save svg maze: `0`\n", &saveSVG, "Save SVG file: filename.svg" },
	///	{ "-g", "Generating maze with seed: `0`, width: `1`, height: `2`\n", "Failed to build maze", &generate, "Generate maze: seed width height", 3 },
	///
	OptionSet(const std::vector<Option> &options) : options(options) {}

	///
	/// Returns true if an option with the specified tag exists, otherwise false.
	/// @param tag option type matched against tag in the Option struct.
	/// @return true if the option exists, otherwise false.
	///
	bool hasOption(const std::string &tag);

	///
	/// Returns an option from the options set that matches the specified tag. Returns an empty option if the tag does not exist.
	/// @param tag option type matched against tag in the Option struct.
	/// @return option matching the tag if one exists, otherwise an empty option.
	///
	Option &getOption(const std::string &tag);

	///
	/// Constructs the commands list using the options set, based on the given command line args.
	/// @param argc number of arguments.
	/// @param argv array of strings containing the arguments.
	/// @return false if any args were encountered that don't match options, otherwise true.
	///
	bool parse(int argc, char **argv);

	///
	/// Calls run on all options stored in the commands vector, passing maze and builder to each run call.
	///
	void run(Maze *maze);

	///
	/// Prints tags and their descriptions for all options in the options set.
	///
	void printUsage();
};
