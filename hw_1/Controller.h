#ifndef MIPT_METAPROG_CONTROLLER_H
#define MIPT_METAPROG_CONTROLLER_H

#include "Strategy.h"
#include "Command.h"
#include "hardcoded_settings.h"

#include <string>


class Controller : public Strategy {
public:
    /**
     * @param cmd:
     *  0: Expose next word. Next is
     *      std::string
     *      Strategy* - return placeholder that supports Mediator interface
     */
    int command(Command<> *cmd) override;

private:
    Strategy* response_receiver;

    /**
     * Decide which Storage to use for this word and send command to response_receiver
     * The command 1st field is int - container number
     */
    int decide(std::string word);
};


#endif //MIPT_METAPROG_CONTROLLER_H
