#ifndef PARSER_H_
#define PARSER_H_

#include "Command.h"
#include "CommandWords.h"

class Parser {
private:
	CommandWords *commands;

public:
	Parser();
    Command* getCommand();
    void getInput(string playerInput/*, bool isNewCommand*/);
    string showCommands();
    string buffer = "";
    bool newCommand;
};

#endif /*PARSER_H_*/
