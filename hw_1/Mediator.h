#ifndef MIPT_METAPROG_MEDIATOR_H
#define MIPT_METAPROG_MEDIATOR_H

#include "Command.h"
#include "Strategy.h"
#include "hardcoded_settings.h"

#include <array>
#include <string>
#include <vector>


/**
 * A mediator. Controls interaction between all other components
 */
class Mediator : public Strategy {
public:

    /**
     * @param cmd:
     *  MEDIATE_STORAGE: Data from Storage. Next is std::vector<std::string>* - words from storage
     *  MEDIATE_IO: Notification from IOProcessor. Next is std::string - input data
     *  MEDIATE_IO_OP: Notification from IOProcessor. Next is std::string - command for mediator to execute
     *  MEDIATE_CONTROLLER: Command from Controller. Next is int - controller command (container ID)
     */
    int command(Command<> *cmd) override;

    /**
     * Register a new Storage
     * @note all LETTERS_TOTAL storages must be registered; otherwise any operations are not permitted
     * @note if all storages are ALREADY registered, no new storages are accepted
     */
    void register_storage(Strategy* storage);

    /**
     * Register a new Controller
     */
    void register_controller(Strategy* controller);

    /**
     * Register a new IOProcessor (only output processor is actually necessary)
     */
    void register_output_processor(Strategy* output_processor);

private:
    Strategy* controller;
    Strategy* output_processor;

    std::array<Strategy*, LETTERS_TOTAL> storages;

    int storages_registered = 0;
    bool controller_registered = false;
    bool output_processor_registered = false;

    std::string last_word;

    /**
     * Process notification from IOProcessor
     */
    int process_IO(Command<std::string> *cmd);

    /**
     * Process Storage response
     */
    int process_storage_datum(Command<std::vector<std::string>> *cmd);

    /**
     * Process controller command
     */
    int process_controller_command(Command<int> *cmd);

    /**
     * Process operation notification from IOProcessor
     */
    int process_IO_op(Command<std::string> *cmd);
};


#endif //MIPT_METAPROG_MEDIATOR_H
