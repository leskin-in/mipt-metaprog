#include <iostream>

#include "IOProcessor.h"
#include "Mediator.h"
#include "Proxy.h"
#include "Storage.h"
#include "Controller.h"
#include "Command.h"

#include "hardcoded_settings.h"

#include <array>

using namespace std;


int main() {
    // Construct objects
    IOProcessor io(&cin, &cout);
    Controller controller;
    Storage storages[LETTERS_TOTAL];
    Mediator mediator;

    // Fill mediator
    mediator.register_output_processor(&io);
    mediator.register_controller(&controller);
    for (int i = 0; i < LETTERS_TOTAL; i++) {
        mediator.register_storage(&storages[i]);
    }

    // Construct proxy
    Proxy<PROXY_ECHO> proxy_drop(&mediator);

    // proxy_drop subscribes for updates from io
    Command<Strategy*> cmd_holder(&proxy_drop);
    Command<> cmd_wrapper(-1, &cmd_holder);
    io.command(&cmd_wrapper);

    io.start_streaming();

    return 0;
}
