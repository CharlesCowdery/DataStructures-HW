#pragma once

class Hash1d {
public:
	int nums[500];
	bool flag[500];
	Hash1d();
	~Hash1d();
	int hash(int val);
	int insert(int val);
	int remove(int val);
	int find(int val);
	void print();
};
