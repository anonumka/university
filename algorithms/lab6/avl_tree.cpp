#include "avl_tree.hpp"

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <chrono>

using namespace std;
using namespace chrono;

avl_tree::avl_tree() : root(nullptr)
{
}

avl_tree::~avl_tree()
{
	if (root != nullptr)
		removeTree(root);
}

void avl_tree::add(const int key)
{
	root = add(root, key);
}

void avl_tree::remove(const int key)
{
	root = remove(root, key);
}

int getCount(const Node const* node, const int low, const int high)
{
	if (node == nullptr)
		return 0;

	if (node->key >= low && node->key <= high)
	{
		// Вывод числа которое находится в промежутке
		cout << node->key << " | ";

		return 1 + getCount(node->left, low, high) + getCount(node->right, low, high);
	}


	if (node->key < low)
		return getCount(node->right, low, high);

	return getCount(node->left, low, high);
}

void avl_tree::iterate(Node* node, const int a, const int b)
{
	if (node == nullptr)
		return;

	if (a < node->key)
		iterate(node->left, a, b);

	if (a <= node->key && b >= node->key)
	{
		remove(node->key);
		return;
	}

	if (b > node->key)
		iterate(node->right, a, b);
}

void avl_tree::process()
{ 
	auto t1 = high_resolution_clock::now();
	Node* minNode = getMin(root->left);
	auto t2 = high_resolution_clock::now();
	float res = duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
	Node* maxNode = getMax(root->right);

	int max = maxNode->key;
	int min = minNode->key;

	cout << "Минимальное значение: " << min << endl 
		 <<	"Максимальное значение: " << max << endl
		<< "Время поиска: " << res << endl;

	remove(min); remove(max);
	max /= 2; min /= 2;
	add(max); add(min);
	rebalance(root);
}

void getLine(const Node* root, const int depth, vector<int>& vals)
{
	if (depth <= 0 && root != nullptr)
	{
		vals.push_back(root->key);
		return;
	}

	if (root->left != nullptr)
		getLine(root->left, depth - 1, vals);
	else if (depth - 1 <= 0)
		vals.push_back(1 << 31);

	if (root->right != nullptr)
		getLine(root->right, depth - 1, vals);
	else if (depth - 1 <= 0)
		vals.push_back(1 << 31);
}

void printRow(const Node* p, const int height, const int depth)
{
	vector<int> vec;
	getLine(p, depth, vec);

	cout << setw((height - depth) * 2);

	bool toggle = true;

	if (vec.size() > 1)
	{
		for (int v : vec)
		{
			if (v != 1 << 31)
			{
				if (toggle)
					cout << "/" << "   ";
				else
					cout << "\\" << "   ";
			}

			toggle = !toggle;
		}

		cout << endl;
		cout << setw((height - depth) * 2);
	}

	for (int v : vec)
	{
		if (v != 1 << 31)
			cout << v << "   ";
	}

	cout << endl;
}

void avl_tree::output() const
{
	cout << "Элементы дерева: " << endl;
	const int height = getHeight(root) * 2;

	for (int i = 0; i < height; i++)
		printRow(root, height, i);
}

Node* avl_tree::getMin(Node* node)
{
	if (node == nullptr)
		return nullptr;

	while (node->left != nullptr)
		node = node->left;

	return node;
}

Node* avl_tree::getMax(Node* node)
{
	if (node == nullptr)
		return nullptr;

	while (node->right != nullptr)
		node = node->right;

	return node;
}

Node* avl_tree::removeMax(Node* node)
{
	if (node->right == nullptr)
		return node->left;

	node->right = removeMax(node->right);

	return rebalance(node);
}

Node* avl_tree::removeMin(Node* node)
{
	if (node->left == nullptr)
		return node->right;

	node->left = removeMin(node->left);

	return rebalance(node);
}

Node* avl_tree::add(Node* node, const int key)
{
	if (node == nullptr)
		return new Node(key);

	if (key > node->key)
	{
		node->right = add(node->right, key);
		node = rebalance(node);
	}
	else if (key < node->key)
	{
		node->left = add(node->left, key);
		node = rebalance(node);
	}

	return node;
}

Node* avl_tree::remove(Node* node, const int key)
{
	if (node == nullptr)
		return nullptr;

	if (key < node->key)
	{
		node->left = remove(node->left, key);
	}
	else if (key > node->key)
	{
		node->right = remove(node->right, key);
	}
	else
	{
		Node* leftNode = node->left;
		Node* rightNode = node->right;

		delete node;

		if (rightNode == nullptr)
			return leftNode;

		Node* min = getMin(rightNode);

		min->right = removeMin(rightNode);
		min->left = leftNode;

		return rebalance(min);
	}

	return rebalance(node);
}

Node* avl_tree::leftLeft(Node* parent)
{
	Node* temp = parent->left;

	parent->left = temp->right;
	temp->right = parent;

	return temp;
}

Node* avl_tree::rightRight(Node* parent)
{
	Node* newNode = parent->right;

	parent->right = newNode->left;
	newNode->left = parent;

	return newNode;

}

Node* avl_tree::bigRight(Node* parent)
{
	Node* newNode = parent->left;
	parent->left = rightRight(newNode);

	return leftLeft(parent);
}

Node* avl_tree::bigLeft(Node* parent)
{
	Node* newNode = parent->right;

	parent->right = leftLeft(newNode);
	return rightRight(parent);
}

void avl_tree::removeTree(Node* node)
{
	if (node != nullptr)
	{
		removeTree(node->left);
		removeTree(node->right);

		delete node;
	}
}

int avl_tree::getHeight(Node* node)
{
	if (node == nullptr)
		return 0;

	const int leftHeight = getHeight(node->left);
	const int rightHeight = getHeight(node->right);

	const int maxHeight = max(leftHeight, rightHeight);

	return maxHeight + 1;
}

int avl_tree::getBalanceFactor(Node* node)
{
	if (node == nullptr)
		return 0;

	const int leftHeight = getHeight(node->left);
	const int rightHeight = getHeight(node->right);

	return leftHeight - rightHeight;
}

Node* avl_tree::rebalance(Node* node)
{
	const int factor = getBalanceFactor(node);

	if (factor > 1)
	{
		if (getBalanceFactor(node->left) > 0)
			node = leftLeft(node);
		else
			node = bigRight(node);
	}
	else if (factor < -1)
	{
		if (getBalanceFactor(node->right) > 0)
			node = bigLeft(node);
		else
			node = rightRight(node);
	}

	return node;
}
