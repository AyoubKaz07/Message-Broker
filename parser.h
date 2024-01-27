#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <optional>
#include "handlers.h"
#include <sstream>

class CommandParser {
public:
    static std::unique_ptr<AbsractHandler> parse(Command* command) {
        if (command->input.compare(0, 4, "PING") == 0) {
            return std::make_unique<PingCommandHandler>(COMMAND_TYPE::PING);
        } else if (command->input.compare(0, 3, "SUB") == 0) {
            std::string topic = ParseToken(command->input);
            return std::make_unique<SubCommandHandler>(topic, COMMAND_TYPE::SUB);
        } else if (command->input.compare(0, 3, "PUB") == 0) {
            std::string topic = ParseToken(command->input);
            return std::make_unique<PubCommandHandler>(topic, COMMAND_TYPE::PUB);
        } else if (command->input.compare(0, 5, "UNSUB") == 0) {
            std::string topic = ParseToken(command->input);
            return std::make_unique<UnsubCommandHandler>(topic, COMMAND_TYPE::UNSUB);
        } else {
            return nullptr;
        }

    };

    static std::string ParseToken(std::string input) {
        std::istringstream iss(input);
        std::string topic, subCommand;

        iss >> subCommand >> topic;
        return topic;
    }
};