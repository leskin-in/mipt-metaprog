#ifndef MIPT_METAPROG_STORAGE_H
#define MIPT_METAPROG_STORAGE_H

#include "Strategy.h"
#include "Executor.h"

#include <set>
#include <string>
#include <vector>


class Storage : public Strategy {
public:
    Storage() : response_receiver(nullptr) {}

    /**
     * @param cmd:
     *  0: Get data from storage. Next is
     *      Strategy* - return result placeholder that supports Mediator interface
     *  1: Put data to storage. Next is std::string - word to put
     *  -1: Remove data from storage. Next is std::string - word to remove
     */
    int command(Command<> *cmd) override;

private:
    Strategy* response_receiver;

    std::set<std::string> words;

    /**
     * Get at most n entities from the storage
     * @note The caller must take care of the memory by that pointer;
     * @note Memory is guaranteed to be allocated using new() call
     *
     * A pointer to std::vector<std::string> will be send as a command to the response_receiver
     */
    int get(unsigned int n);

    /**
     * Put a word to storage
     * @return 1 if word was actually inserted, 0 otherwise
     */
    int put(std::string word);

    /**
     * Remove a word from storage
     * @return 1 if word was actually removed, 0 otherwise
     */
    int remove(std::string word);
};


#endif //MIPT_METAPROG_STORAGE_H
