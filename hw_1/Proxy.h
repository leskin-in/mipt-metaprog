#ifndef MIPT_METAPROG_PROXY_H
#define MIPT_METAPROG_PROXY_H

#include "Strategy.h"
#include "Strategy.h"

#include <iostream>


typedef enum Proxy_types {
    /**
     * Drop all calls and report success
     */
    PROXY_DROP,
    /**
     * @warning applicable only for connections where 1st datum is std::string
     *
     * For every call:
     *  do 'cout << <1st datum>';
     *  pass call to Mediator
     */
    PROXY_ECHO
} Proxy_type;


/**
 * A universal proxy
 *
 * @remark We could use a function as a template parameter or a constructor parameter.
 * This would expand the applicability of this proxy, but the implementation would be more difficult
 */
template<Proxy_type type>
class Proxy : public Strategy {
public:
    /**
     * Construct a proxy. The calls will be passed to the given mediator
     */
    explicit Proxy(Strategy* mediator) : mediator(mediator) {};

    /**
     * Replaces Mediator interface, but only for MEDIATE_IO calls. Thus:
     * @param cmd:
     *  MEDIATE_IO: Notification from IOProcessor. Next is std::string - input data
     *  <other>: return -1
     */
    int command(Command<> *cmd) override {
        switch (type) {
            case PROXY_DROP:
                return 0;
            case PROXY_ECHO:
                std::cout << (static_cast<Command<std::string>* >(cmd->next))->datum << std::endl;
                return this->mediator->command(cmd);
            default:
                return -1;
        }
    }

private:
    Strategy* mediator;
};


#endif //MIPT_METAPROG_PROXY_H
