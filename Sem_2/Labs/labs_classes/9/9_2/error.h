#pragma once
#include <iostream>
#include <string>


class Error {
    std::string error_message;

public:
    Error(std::string error_message = "Error") {
        this -> error_message = error_message;
    }


    void what() {
        std::cout << error_message;
    }
};