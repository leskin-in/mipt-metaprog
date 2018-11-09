#include "Storage.h"


int Storage::command(Command<> *cmd) {
    switch (cmd->datum) {
        case 0:
            this->response_receiver = (static_cast<Command<Strategy*>* >(cmd->next))->datum;
            return this->get((unsigned int)words.size());
        case 1:
            this->put(
                    (static_cast<Command<std::string>* >(cmd->next))->datum
            );
            return 0;
        case -1:
            this->remove(
                    (static_cast<Command<std::string>* >(cmd->next))->datum
            );
            return 0;
        default:
            return -1;
    }
}

int Storage::get(unsigned int n) {
    auto result = n == 0 ? std::vector<std::string>() : std::vector<std::string>(n);
    int i = 0;
    for (auto it = this->words.begin(); it != words.end() && i < n; it++, i++) {
        result[i] = *it;
    }
    result.shrink_to_fit();

    auto result_wrapper = Command<std::vector<std::string> >(result);
    auto cmd = Command<>(
            MEDIATE_STORAGE,
            &result_wrapper
    );
    return response_receiver->command(&cmd);
}

int Storage::put(std::string word) {
    return this->words.insert(word).second ? 1 : 0;
}

int Storage::remove(std::string word) {
    return this->words.erase(word) ? 1 : 0;
}
