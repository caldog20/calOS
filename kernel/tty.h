#ifndef __TTY_H
#define __TTY_H

#include <limine.h>
#include <stddef.h>
#include <stdint.h>

void terminal_writestring(struct limine_terminal_request terminal_request, const char* data);

extern volatile struct limine_terminal_request terminal_request;

#endif