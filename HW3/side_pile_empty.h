#pragma once
#include <iostream>
using std::string;
using std::cout;

class StackEmpty: public std::exception {
    private:
        string const message = "\n Error: Stack is empty. Cannot remove from stack.";
    public:
        StackEmpty() {}
        string GetMessage() {
            return message;
        }
};