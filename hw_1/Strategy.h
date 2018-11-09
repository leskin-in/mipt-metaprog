#ifndef MIPT_METAPROG_STRATEGY_H
#define MIPT_METAPROG_STRATEGY_H

#include "Command.h"


/**
 * Interface Strategy. A set of algorithms to execute
 */
class Strategy {
public:
    Strategy() = default;

    virtual ~Strategy() = default;

    /**
     * Execute command. See description in subclasses
     * @return <0 if command fails, 0 if command succeeds, >0 - see description in subclasses
     */
    virtual int command(Command<>* cmd) = 0;
};


#endif //MIPT_METAPROG_STRATEGY_H
