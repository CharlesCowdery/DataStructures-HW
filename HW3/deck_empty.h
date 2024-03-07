#pragma once
#include <iostream>
#include <string>

class DeckEmpty: public std::exception {
    private:
        std::string const message = "\n Error: Queue is already empty.";
    public:
        DeckEmpty() {}
        std::string GetMessage() {
            return message;
        }
};
