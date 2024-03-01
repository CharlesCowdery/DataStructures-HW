#pragma once
#include <iostream>
using std::string;

class StackFull {
    private:
        string const message = "\nError: Stack is full. Cannot add to stack.";
    public:
        // Constructor
        StackFull() {}
        // Getter
        string GetMessage() {
            return message;
        }
};