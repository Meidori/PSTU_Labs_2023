#pragma once
#include <iostream>
#include <string>


class Error {
public:
    virtual void what() {};
};


class Index_Error : public Error {
public:
    Index_Error() {
        error_message = "Index_Error";
    }
    

    virtual void what() {
        std::cout << error_message << std::endl;
    }

protected:
    std::string error_message;
};


class Size_Error : public Error {
public:
    Size_Error() {
        error_message = "Size_Error";
    }
    

    virtual void what() {
        std::cout << error_message << std::endl;
    }

protected:
    std::string error_message;
};


class Step_Error : public Error {
public:
    Step_Error() {
        error_message = "Step_Error";
    }
    

    virtual void what() {
        std::cout << error_message << std::endl;
    }

protected:
    std::string error_message;
};