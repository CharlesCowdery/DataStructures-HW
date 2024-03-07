#pragma once
#include <iostream>
#include <string>
using std::string;

class StackFull : public std::exception {
    private:
        string const message = "\nError: Stack is full. Cannot add to stack.";
    public:
        // Constructor
        StackFull() {}
        // Getter
        string what() {
            return message;
        }
};