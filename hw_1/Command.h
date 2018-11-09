#ifndef MIPT_METAPROG_COMMAND_H
#define MIPT_METAPROG_COMMAND_H

/**
 * A first field of every Command
 */
typedef int COMMAND_IDENTIFIER;


template<class Datum=COMMAND_IDENTIFIER>
struct Command {
    /// Datum of this command
    Datum datum;

    /// Pointer to next Command object
    void* next;

    explicit Command(Datum datum) : datum(datum), next(nullptr) {}

    Command(Datum datum, void* next) : datum(datum), next(next) {}
};


/// Command types (used as COMMAND_IDENTIFIER)
typedef enum Command_types {
    MEDIATE_STORAGE = 0,
    MEDIATE_IO,
    MEDIATE_IO_OP,
    MEDIATE_CONTROLLER
} Command_type;


#endif //MIPT_METAPROG_COMMAND_H
