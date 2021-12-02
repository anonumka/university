#include <iostream>
#include <stack>
#include <vector>
#include <iomanip>
#include "avl_tree.hpp"
#include "chrono"

using namespace std;
using namespace chrono;

struct def_tree
{
	int value;

	def_tree* left;
	def_tree* right;
};

def_tree* getMin(def_tree* node)
{
	if (node == nullptr)
		return nullptr;

	while (node->left != nullptr)
		node = node->left;

	return node;
}

def_tree* getMax(def_tree* node)
{
	if (node == nullptr)
		return nullptr;

	while (node->right != nullptr)
		node = node->right;

	return node;
}

def_tree* removeMin(def_tree* node)
{
	if (node->left == nullptr)
		return node->right;

	node->left = removeMin(node->left);
	return node->left;
}

def_tree* del_node(def_tree* node, const int key)
{
	if (node == NULL) return node;
	if (key == node->value) 
	{
		def_tree* newNode;
		if (node->right == NULL)
			newNode = node->left;
		else 
		{
			def_tree* ptr = node->right;
			if (ptr->left == NULL) 
			{
				ptr->left = node->left;
				newNode = ptr;
			}
			else 
			{

				def_tree* pmin = ptr->left;
				while (pmin->left != NULL) 
				{
					ptr = pmin;
					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = node->left;
				pmin->right = node->right;
				newNode = pmin;
			}
		}
		delete node;
		return newNode;
	}
	else if (key < node->value)
		node->left = del_node(node->left, key);
	else
		node->right = del_node(node->right, key);
	return node;
}

def_tree* ins_node(def_tree* n, int key)
{
	if (n == NULL) {
		n = new def_tree();
		if (n != NULL) {
			n->value = key;
			n->left = n->right = NULL;
		}
		return n;
	}

	if (key < n->value)
		n->left = ins_node(n->left, key);
	else
		n->right = ins_node(n->right, key);
	return n;
}

// Wrapper over print2DUtil()
void print(def_tree* n, int lvl)
{
	if (n)
	{
		print(n->left, lvl + 1);
		for (int i = 0; i < lvl; i++) 
			cout << ".";
		cout << n->value << endl;
		print(n->right, lvl + 1);
	}
}

void process(def_tree* tree)
{
	cout << "Бинарное дерево: \n";
	print(tree, 0);

	auto t1 = high_resolution_clock::now();
	def_tree* minNode = getMin(tree);
	auto t2 = high_resolution_clock::now();
	def_tree* maxNode = getMax(tree);
	float res = duration_cast<microseconds>(t2 - t1).count() / 1000.0f;
	int min = minNode->value;
	int max = maxNode->value;

	cout << "Минимальное значение: " << min << endl
		<< "Максимальное значение: " << max << endl
		<< "Время поиска: " << res << endl;

	del_node(tree, min); del_node(tree, max);
	min /= 2; max /= 2;
	ins_node(tree, min); ins_node(tree, max);

	cout << "Измененное бинарное дерево: \n";
	print(tree, 0);

}

int main()
{
	setlocale(LC_ALL, "Russian");
	/*def_tree* tree = NULL;
	for (int i = 0; i < 16; i++)
		tree = ins_node(tree, rand() % 128);
	process(tree);*/

	avl_tree tree;
	for (int i = 0; i < 3; i++)
		tree.add(rand() % 128);
	tree.output();
	tree.process();
	tree.output();
	return 0;
}