#pragma once

class TwoDHashTable {
public:
    TwoDHashTable();
    ~TwoDHashTable();
    int Insert(int value);
    int Find(int value);
    int Remove(int value);
    void Print();

private:
    int table[100][5]; // table[slots][slot depth]
    int Hash(int value);
};