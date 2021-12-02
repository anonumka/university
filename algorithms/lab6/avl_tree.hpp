#pragma once

struct Node
{
	int key;
	int height;

	Node* left;
	Node* right;

	explicit Node(const int k)
	{
		key = k;
		height = 1;

		left = right = nullptr;
	}
};


class avl_tree
{
public:
	avl_tree();
	~avl_tree();

	void add(int);
	void remove(int);

	void process();

	void output() const;
private:
	void iterate(Node*, int, int);

	static Node* getMin(Node*);
	static Node* getMax(Node*);

	static Node* removeMax(Node*);
	static Node* removeMin(Node*);

	static void removeTree(Node*);

	static int getHeight(Node*);
	static int getBalanceFactor(Node*);

	static Node* rebalance(Node*);

	static Node* add(Node*, int);
	static Node* remove(Node*, int);

	static Node* leftLeft(Node*);
	static Node* rightRight(Node*);

	static Node* bigRight(Node*);
	static Node* bigLeft(Node*);

	Node* root;

};

