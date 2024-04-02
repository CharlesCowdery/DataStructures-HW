#pragma once
class Hash2d {
public:
	int nums[100][5];
	Hash2d();
	~Hash2d();
	int hash(int val);
	int insert(int val);
	int remove(int val);
	int find(int val);
	void print();
};