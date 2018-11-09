#include "Mediator.h"


int Mediator::command(Command<COMMAND_IDENTIFIER> *cmd) {
    if (storages_registered != LETTERS_TOTAL || !controller_registered || !output_processor_registered) {
        return -1;
    }
    switch(cmd->datum) {
        case MEDIATE_STORAGE:
            return this->process_storage_datum(static_cast<Command<std::vector<std::string> >* >(cmd->next));
        case MEDIATE_IO:
            return this->process_IO(static_cast<Command<std::string> * >(cmd->next));
        case MEDIATE_CONTROLLER:
            return this->process_controller_command(static_cast<Command<int> * >(cmd->next));
        case MEDIATE_IO_OP:
            return this->process_IO_op(static_cast<Command<std::string> * >(cmd->next));
        default:
            return -1;
    }
}

int Mediator::process_IO(Command<std::string> *cmd) {
    last_word = cmd->datum;

    Command<Strategy*> command_2(this);
    Command<std::string> command_1(cmd->datum, &command_2);
    Command<> command_wrapper(0, &command_1);

    return controller->command(&command_wrapper);
}

int Mediator::process_storage_datum(Command<std::vector<std::string> > *cmd) {
    if(cmd->datum.size() == 0) {
        return 0;
    }
    Command<std::vector<std::string> > command(cmd->datum);
    Command<> command_wrapper(1, &command);

    return output_processor->command(&command_wrapper);
}

int Mediator::process_controller_command(Command<int> *cmd) {
    Command<std::string> command(last_word);
    Command<> command_wrapper(1, &command);

    return storages[cmd->datum]->command(&command_wrapper);
}

int Mediator::process_IO_op(Command<std::string> *cmd) {
    std::string user_command = cmd->datum;

    if (user_command == "show") {
        Command<Strategy*> command(this);
        Command<> command_wrapper(0, &command);

        for (auto storage = storages.begin(); storage != storages.end(); storage++) {
            (*storage)->command(&command_wrapper);
        }

        return 0;
    }
    else {
        return -1;
    }
}

void Mediator::register_storage(Strategy *storage) {
    if (storages_registered == LETTERS_TOTAL) {
        return;
    }
    this->storages[storages_registered] = storage;
    storages_registered += 1;
}

void Mediator::register_controller(Strategy *controller) {
    this->controller = controller;
    controller_registered = true;
}

void Mediator::register_output_processor(Strategy *output_processor) {
    this->output_processor = output_processor;
    output_processor_registered = true;
}
