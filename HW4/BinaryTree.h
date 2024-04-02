class nodeTree {
	int data;
	nodeTree* left;
	nodeTree* right;


};

class BinaryTree {
public:
	nodeTree* head;
	int insert(int val);
	int remove(int val);
	int find(int val);
	void print();
	BinaryTree();
	~BinaryTree();
};