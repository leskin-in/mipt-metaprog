#ifndef MIPT_METAPROG_IOPROCESSOR_H
#define MIPT_METAPROG_IOPROCESSOR_H

#include "Strategy.h"
#include "Command.h"

#include <string>
#include <vector>
#include <istream>
#include <algorithm>
#include <string>


class IOProcessor : public Strategy {
public:
    /**
     * Construct a new IOProcessor
     * @param stream_i pointer to input stream
     * @param stream_o pointer to output stream
     * Streaming does not start automatically. Call start_streaming()
     */
    IOProcessor(std::basic_istream<char>* stream_i, std::basic_ostream<char>* stream_o) :
    stream_i(stream_i), stream_o(stream_o) {};

    /**
     * @param cmd:
     *  0: Output a message. Next is std::string
     *  1: Output a list of words. Next is std::vector<std::string>
     *  -1: Bind an observer. Next is Strategy*
     */
    int command(Command<> *cmd) override;

    /**
     * Start an endless cycle of listening and writing to the streams from constructor.
     *
     * @note At the moment, this is a blocking call. It will lock until the EOF or '!!' is reached
     */
    void start_streaming();

private:
    std::basic_istream<char>* stream_i;
    std::basic_ostream<char>* stream_o;

    std::vector<Strategy*> subscribers;

    /**
     * Output one message and go to new line
     */
    void out(std::string message);

    /**
     * Output a few words and go to new line
     */
    void out(std::vector<std::string> words);

    /**
     * Add a new subscriber for the input stream
     */
    void add_subscriber(Strategy *subscriber);

    void print_help();
};


#endif //MIPT_METAPROG_IOPROCESSOR_H
