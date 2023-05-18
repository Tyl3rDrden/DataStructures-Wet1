#ifndef _WET1_EXCEPTIONS_H
#define _WET1_EXCEPTIONS_H


#include <stdexcept>
#include <string>
#include <exception>
#include <cassert>


class DeleteNonexistentElement : public std::invalid_argument {
public:
    explicit DeleteNonexistentElement(const std::string& message = "Cannot delete nonexistent element.")
        : std::invalid_argument(message) {}

    /*const char* what() const noexcept override {
        //Return some error Thing .. I forgot how to override!
        return ;
    }*/
};
class IdAlreadyExists : public std::invalid_argument {
public:
    explicit IdAlreadyExists(const std::string& message = "Id Already Exists")
        : std::invalid_argument(message) {}

    /*const char* what() const noexcept override {
        //return "InvalidInputException: " + std::string(std::invalid_argument::what());
        return;
    }*/
    
};
class ElementNotFound : public std::invalid_argument {
public:
    explicit ElementNotFound(const std::string& message = "ElementNotFound")
        : std::invalid_argument(message) {}

    /*const char* what() const noexcept override {
        //return "InvalidInputException: " + std::string(std::invalid_argument::what());
        return;
    }*/
    
};



#endif

//Here I'll define possible exceptions