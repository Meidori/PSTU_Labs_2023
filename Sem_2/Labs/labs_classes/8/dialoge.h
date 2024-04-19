#pragma once
#include <iostream>
#include <string>

#include "vector.h"
#include "event.h"

class Dialoge : public Vector {
public:
    Dialoge() {
        end_state = 0;
    }


    virtual ~Dialoge() {}


    virtual void get_event(Event &event) {
        std::string operation_codes = "m+-szq";
        std::string selector;
        std::string parametr;

        char code;
        std::cout << ">";
        std::cin >> selector;
        code = selector[0];

        if (operation_codes.find(code) >= 0) {
            event.event_type = event_message;
            switch (code) {
            case 'm':
                event.command = command_make_group;
                break;
            
            case '+':
                event.command = command_add;
                break;

            case '-':
                event.command = command_delete;
                break;

            case 's':
                event.command = command_print_elems_info;
                break;

            case 'z':
                event.command = command_print_elems_names;
                break;

            case 'q':
                event.command = command_quit;
                break;
            
            default:
                break;
            }

            if (size > 1) {
                parametr = selector.substr(1, selector.length() - 1);
                int parametr_code = atoi(parametr.c_str());
                event.parameter = parametr_code;
            }
        }
        else {
            event.event_type = event_nothing;
        }
    }


    virtual int execute() {
        Event event;
        do {
            end_state = 0;
            get_event(event);
            handle_event(event);
        }
        while(!valid());
        return end_state;
    }


    int valid() {
        if (end_state == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }


    virtual void clear_event(Event& event) {
        event.event_type = event_nothing;
    }

    
    void end_exec() {
        end_state = 1;
    }


    virtual void handle_event(Event &event) {
        if (event.event_type == event_message) {
            switch (event.command) {
                case command_make_group:
                    size = event.parameter;
                    first = new Object* [size];
                    current_position = 0;
                    clear_event(event);
                    break;

                case command_add:
                    add();
                    clear_event(event);
                    break;

                case command_delete:
                    delete_vector();
                    clear_event(event);
                    break;

                case command_print_elems_info:
                    print();
                    clear_event(event);
                    break;

                case command_print_elems_names:
                    print();
                    clear_event(event);
                    break;

                case command_quit:
                    end_exec();
                    clear_event(event);
                    break;

                default:
                    Vector::handle_event(event);
                    break;
            }
        }
    }

protected:
    int end_state;
};