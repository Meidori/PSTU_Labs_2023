#pragma once
#include <iostream>

#include "event.h"


class Object {
public:
    Object() {};
    virtual void print() = 0;
    virtual void input() = 0;
    virtual ~Object() {};
    virtual void handle_event(const Event& event) = 0;
};