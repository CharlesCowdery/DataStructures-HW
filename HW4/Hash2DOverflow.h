#pragma once
#include <iostream>
using std::string;

class HashOverflow: public std::exception {
    private:
        string const message = "\n Error: Cannot insert, hash table is full.";
    public:
        HashOverflow() {}
        string GetMessage() {
            return message;
        }
};
