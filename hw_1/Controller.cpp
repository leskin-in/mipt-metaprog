#include "Controller.h"


int Controller::command(Command<COMMAND_IDENTIFIER> *cmd) {
    if (cmd->datum != 0) {
        return -1;
    }

    this->response_receiver = static_cast<Command<Strategy*>* >(
            (static_cast<Command<std::string>* >(cmd->next))->next
    )->datum;
    return this->decide(
            (static_cast<Command<std::string>* >(cmd->next))->datum
    );
}

int Controller::decide(std::string word) {
    if (word.length() == 0) {
        return -1;
    }

    int calculated_container = ((int)word[0] - (int)'a') % LETTERS_TOTAL;

    auto result_wrapper = Command<int>(calculated_container);
    auto cmd = Command<>(
            MEDIATE_CONTROLLER,
            &result_wrapper
    );
    return response_receiver->command(&cmd);
}
