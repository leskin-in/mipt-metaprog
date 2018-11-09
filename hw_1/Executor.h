#ifndef MIPT_METAPROG_EXECUTOR_H
#define MIPT_METAPROG_EXECUTOR_H

#include "Strategy.h"


template<Strategy* strategy>
class Executor {
public:
    /**
     * Construct an executor
     */
    Executor() = default;

    /**
     * "call" this Executor
     * @param data
     * @return return code of the underlying strategy.
     * @return 0 if successful, <0 if an error happens
     */
    int command(Command<> *data) {
        return strategy->command(data);
    }
};


#endif //MIPT_METAPROG_EXECUTOR_H
