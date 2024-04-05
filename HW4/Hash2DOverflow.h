#pragma once
#include <iostream>
using std::string;

class Hash2d: public std::exception {
    private:
        string const message = "\n Error: Cannot insert, hash table is full.";
    public:
        int insert() {}
        string GetMessage() {
            return message;
        }
};