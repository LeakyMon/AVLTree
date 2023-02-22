#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <cctype>
#include <iomanip>
#include <queue>
#include <stack>
#include <fstream>


using namespace std;

class AVLTree { //constructor(s), functions to build/maintain/search/traverse the AVL tree, and destructor

private:
	class TreeNode { //store student info, left and right children, maybe the height + constructor
	public:
		
		string name;
		int ID;
		TreeNode* left;
		TreeNode* right;
		int height;
		
		TreeNode() : ID(1), left(nullptr), right(nullptr), height(0){}
		TreeNode(string name, int ID) : name(name), ID(ID), left(nullptr), right(nullptr), height(1) {}
		TreeNode(string name, int ID, int height) : name(name), ID(ID), left(nullptr), right(nullptr), height(height) {}
		TreeNode(string name, int ID, TreeNode*left, TreeNode* right, int height) : name(name), ID(ID), left(left), right(right), height(height) {}

	};
	TreeNode* root;
	//HELPER FUNCTIONS TO BE CALLED FROM AVL FUNCTIONS FROM MAIN
	TreeNode* insertNode(TreeNode* node, string name, int ID);
	TreeNode* rotations(TreeNode* node, int bal, int ID);
	TreeNode* rotateLeft(TreeNode* node, int bal);
	TreeNode* rotateRight(TreeNode* node, int bal);
	TreeNode* LR(TreeNode* node);
	TreeNode* RL(TreeNode* node);
	TreeNode* removeNode(TreeNode* node, int key);
	TreeNode* traverse(TreeNode* node, int key);
	TreeNode* removeInorder(TreeNode* node, int key, int &count);

	string findID(TreeNode* node, int ID); // print name;
	int findName(TreeNode* node, string name);

	//DISPLAY USED TO HELP ME VISUALIZE
	void disp(int lvl, TreeNode* ptr);

	string printTraversals(TreeNode* node, int option);

	bool levelCnt(TreeNode* node, int total);

public:
	string outFile = "output.txt";

	AVLTree();
	
	void Display(int lvl); //PERSONAL USE TO HELP VISUALIZE
	void insert(string name, int ID);
	void remove(int key, int n);

	void searchID(int ID);
	void searchName(string name);

	string inOrder();
	string preOrder();
	string postOrder();
	string numLvls();

	bool validate(string name, int ID);

	int BF(TreeNode* node, int bal);
	int getHeight(TreeNode* node);

	void Write(const string& filename, const vector<string>& output, int x);
	vector<string> lines;

};
