#include "tty.h"

void terminal_writestring(struct limine_terminal_request terminal_request, const char* data) {
    // terminal_write(data, strlen(data));
    struct limine_terminal* terminal = terminal_request.response->terminals[0];
    terminal_request.response->write(terminal, data, strlen(data));
}
