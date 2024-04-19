#pragma once


const int event_nothing = 0;
const int event_message = 100;
const int command_add = 1;
const int command_delete = 2;
const int command_print_elems_info = 3;
const int command_print_elems_names = 4;
const int command_make_group = 6;
const int command_quit = 101;


class Event {
public:
    int event_type;
    union {
        int command;
        struct {
            int message;
            int parameter;
        };
    };
};