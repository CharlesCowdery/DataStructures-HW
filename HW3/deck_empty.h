#pragma once
#include <iostream>

class deckEmpty: public std::exception {
    private:
        std::string const message = "\n Error: Queue is empty. Cannot remove from queue.";
    public:
        deckEmpty() {}
        std::string GetMessage() {
            return message;
        }
};