#include "IOProcessor.h"


int IOProcessor::command(Command<COMMAND_IDENTIFIER> *cmd) {
    switch(cmd->datum) {
        case 0:
            out((static_cast<Command<std::string>* >(cmd->next))->datum);
            return 0;
        case 1:
            out((static_cast<Command<std::vector<std::string> >* >(cmd->next))->datum);
            return 0;
        case -1:
            add_subscriber((static_cast<Command<Strategy*>* >(cmd->next))->datum);
            return 0;
        default:
            return -1;
    }
}

void IOProcessor::start_streaming() {
    std::string current;
    int command_execution_result = 0;

    Command<std::string> command(current);
    Command<> command_wrapper(MEDIATE_IO, &command);

    this->out("Type \"!help\" to get help");

    while (true) {
        (*stream_i) >> current;

        if (current.length() > 0 && current[0] == '!') {
            // Process command
            command_wrapper.datum = MEDIATE_IO_OP;

            current = current.substr(1);
            std::transform(current.begin(), current.end(), current.begin(), ::tolower);

            if (current == "exit") {
                break;
            }
            else if (
                (current == "show")
            ) {
                // Pass, these are acceptable commands; they are processed by Mediator
            }
            else {
                print_help();
                continue;
            }
        }
        else if (current.length() > 1 && current[0] == '\\' && current[1] == '!') {
            command_wrapper.datum = MEDIATE_IO;
            current = current.substr(1);
        }
        else {
            command_wrapper.datum = MEDIATE_IO;
        }

        command.datum = current;
        for (auto subscriber = subscribers.begin(); subscriber != subscribers.end(); subscriber++) {
            command_execution_result = (*subscriber)->command(&command_wrapper);
            if (command_execution_result != 0) {
                (*stream_o) << "One of subscribers return non-zero exit code (" << command_execution_result << ")" << std::endl;
            }
        }
    }
}

void IOProcessor::out(std::string message) {
    (*stream_o) << message << std::endl;
}

void IOProcessor::out(std::vector<std::string> words) {
    std::string divisor;
    for (auto it = words.begin(); it != words.end(); it++) {
        (*stream_o) << divisor;
        divisor = ", ";
        (*stream_o) << "'" << *it << "'";
    }
    (*stream_o) << std::endl;
}

void IOProcessor::add_subscriber(Strategy *subscriber) {
    subscribers.push_back(subscriber);
}

void IOProcessor::print_help() {
    (*stream_o) << "Available commands:" << std::endl;
    (*stream_o) << "exit" << std::endl;
    (*stream_o) << "show - show all stored words" << std::endl;
}
