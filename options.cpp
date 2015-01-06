#include "options.h"

#include <iostream>

// There is some potential for error here, make sure you check for it in assignment 2.
std::string Option::parseMsg(const std::string &msg) const {
  std::string parsedMsg = msg;

  auto start = parsedMsg.find('`');
  while (start != std::string::npos) {
    parsedMsg.erase(start, 1);
    auto end = parsedMsg.find('`');
    if (end == std::string::npos)
      break;

    auto val = values[std::stoi(parsedMsg.substr(start, end - start))];
    parsedMsg.erase(end, 1);
    parsedMsg.replace(start, end - start, val);

    start = parsedMsg.find('`');
  }

  return parsedMsg;
}


bool Option::run(Maze *maze) {
  return f(maze, this);
}

void Option::printReport() const {
  std::cout << parseMsg(report);
}

void Option::printError() const {
  std::cout << parseMsg(error);
}

const std::string &Option::getValue(size_t pos) const {
  return values[pos];
}


bool OptionSet::hasOption(const std::string &tag) {
  for (auto &o : options)
    if (o.tag == tag)
      return true;
  return false;
}

Option &OptionSet::getOption(const std::string &tag) {
  static Option tmp;
  for (auto &o : options)
    if (o.tag == tag)
      return o;
  return tmp;
}

bool OptionSet::parse(int argc, char **argv) {
  if (argc < 2)
    return false;

  for (int i = 1; i < argc;) {
    auto tag = argv[i];
    if (!hasOption(tag))
      return false;

    commands.push_back(getOption(tag));
    auto &option = commands[commands.size() - 1];

    if (i + option.nExpected >= argc)
      return false;

    for (int j = 0; j < option.nExpected; j++)
      option.values.push_back(argv[i + 1 + j]);

    i += option.nExpected + 1;
  }

  return true;
}

void OptionSet::run(Maze *maze) {
  for (auto &command : commands) {
    command.printReport();
    if (!command.run(maze)) {
      command.printError();
      break;
    }
  }
}

void OptionSet::printUsage() {
  std::cout << "Invalid args, usage:\n";
  for (auto &option : options)
    std::cout << option.tag << ", " << option.descr << "\n";
}
