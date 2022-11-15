#ifndef __TTY_H
#define __TTY_H

#include <stddef.h>
#include <stdint.h>
#include <limine.h>

void terminal_writestring(struct limine_terminal_request terminal_request, const char* data);

extern volatile struct limine_terminal_request terminal_request; 

#endif