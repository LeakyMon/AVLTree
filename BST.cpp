#include "BST.h"
//Constructor
AVLTree::AVLTree(): root(nullptr) {}

					//----INSERT, SEARCH, DELETE----//

//From main calls helper funciton

void AVLTree::insert(string name, int ID)
{
	//if validate is true... ID 8 digits, name isAlpha
	if (validate(name, ID)) {
		root = insertNode(root, name, ID);
	}
	//Doesnt pass validation
	else {
		cout << "unsuccessful" << endl;
	}
}

//Helper function for insert

AVLTree::TreeNode* AVLTree::insertNode(TreeNode* node, string name, int ID)
{
	if (node == nullptr) //If tree is empty
	{
		cout << "successful" << endl;
		return new TreeNode(name, ID);
	}
	else if (ID == node->ID) {
		//Node already exists
		cout << "unsuccessful" << endl;
		return node;
	}
	else if (ID < node->ID) { //Recurse through left or right

		node->left = insertNode(node->left, name, ID);

	}
	else {
		node->right = insertNode(node->right, name, ID);
	}
	
	int bal = BF(node, 0); //Find balance factor
	
	if (bal < -1 || bal > 1) { // Find which rotation
		return rotations(node, bal, ID);
	}
	else { //No rotation needed because its in between -1 to 1
		return node;
	}
	return node;
}



void AVLTree::searchID(int ID)
{
	TreeNode* curr = root;
	string temp = findID(curr, ID); //Calls findID to find it
	cout << temp << endl; 
}

void AVLTree::searchName(string name)
{
	queue<TreeNode*> q;
	TreeNode* curr = root;
	int temp = findName(curr, name); //finds the name and returns the ID corresponded to that name
	if (temp == 0) { //Temp not found so doesnt exist. 0 was returned from findName
		cout << "unsuccessful" << endl;
	}
}

//Helper functions
string AVLTree::findID(TreeNode* node, int ID)
{
	string nameFound;
	if (node == nullptr) { //Empty Tree
		nameFound = "unsuccessful";
	}
	else if (ID == node->ID) {
		nameFound = node->name;
	}
	else if (ID < node->ID) {
		return findID(node->left, ID);
	}
	else if (ID > node->ID) {
		return findID(node->right, ID);
	}
	else {
		nameFound = "unsuccessful";
	}
	return nameFound;
}

int AVLTree::findName(TreeNode* node, string name)
{
	int tempID = 0;
	if (node == nullptr) {}
	else if (name == node->name) {
		tempID = node->ID;
		cout << tempID << endl;
		//lines.push_back(to_string(tempID));
	}
	else {
		tempID = (findName(node->left, name) + findName(node->right, name));
	}
	return tempID;
}


void AVLTree::remove(int key, int n)
{
	TreeNode* temp = root;
	TreeNode* curr;
	//Two options first to remove given the ID only and second to remove given Name
	if (n == 0) {
		removeNode(temp, key);
	}
	else {
		int cnt = 0;
		curr = removeInorder(temp, n, cnt); //Curr finds the node, removeNode will remove it
		removeNode(temp, curr->ID);
	}
}

AVLTree::TreeNode* AVLTree::removeNode(TreeNode* node, int key)
{
	//TreeNode* min;
	bool root1 = false;
	if (node == nullptr) {
		//cout << "unsuccessful" << endl;
		return node;
	}
	if (key > node->ID) {
		//min = node->right;
		node->right = removeNode(node->right, key);
		return node;
	}
	else if (key < node->ID) {
		//min = node->left;
		node->left = removeNode(node->left, key);
		return node;
	}
	else if (key == node->ID) {
		//CASES FOR REMOVAL 
		
		TreeNode* temp = nullptr;

		//LEAF NODE
		if (node->left == nullptr && node->right == nullptr) {
			
			node = nullptr;
			cout << "successful" << endl;
			lines.push_back("Successful");
			return node;
		
		}
		//ONE CHILD
		else if (node->left == nullptr || node->right == nullptr) {
			cout << "successful" << endl;

			if (node->left == nullptr) {
				TreeNode* curr = node->right;
				free(node);
				
				if (root1 == true) {
					this->root = curr;
				}
				return curr;
			}
			else {
				TreeNode* curr = node->left;
				//node == curr;
				free(node);
				if (root1 == true) {
					this->root = curr;
				}
				return curr;	
			}
		}
		//TWO CHILDREN
		else if (node->left != nullptr && node->right != nullptr) {
			cout << "successful" << endl;
			lines.push_back("Successful");
			TreeNode* curr = node;
			TreeNode* min = node->right;
			while (min && min->left != nullptr) {
				curr = min;
				min = min->left;
			}
			if (curr != node)
				curr->left = min->right;
			else
				curr->right = min->right;

			//Set all min prop to node properties
			node->height = min->height;
			node->ID = min->ID;
			node->name = min->name;

			node->right = removeNode(node->right, min->ID);	
		}
	}
	else {
		cout << "unsuccessful" << endl;
	}
	return node;

}

AVLTree::TreeNode* AVLTree::traverse(TreeNode* node, int key)
{
		if (node == nullptr) {
			return node;
		}
		//LEFT ROOT RIGHT
		if (node->ID == key) {
			return node;
		}
		else if (node->ID > key) { //Left
			node->left = traverse(node->left, key);
		}
		else { //Right
			node->right = traverse(node->right, key);
		}
}

AVLTree::TreeNode* AVLTree::removeInorder(TreeNode* node, int n, int& count)
{
	//LEFT ROOT RIGHT
	if (node == nullptr) {
		return nullptr;
	}
	TreeNode* l = removeInorder(node->left, n, count);
	if (l != nullptr) {
		return l;
	}
	count++;
	if (count == n + 1) {
		return node;
	}
	return removeInorder(node->right, n, count);
	
}

						//-----ROTATIONS-----//


AVLTree::TreeNode* AVLTree::rotations(TreeNode* node, int bal, int ID)
{
	//LEFT
	if (bal < -1) { //Balance factor < -1 unbalanced either rotate Right Left or Left
		if (ID < node->right->ID) {
			return RL(node);
		}
		else {
			return rotateLeft(node, bal);
		}
		
	}
	//RIGHT
	else if (bal > 1) { //Balance factor greater than 1 either rotate right or Left Right
		if (ID < node->left->ID) {
			return rotateRight(node, bal);
		}
		else {	
			return LR(node); //Left right Rotations
		}
	}
	return node;
}

AVLTree::TreeNode* AVLTree::rotateLeft(TreeNode* node, int bal)
{
	TreeNode *p; //Grandchild, parent, child
	
	p = node->right;
	node->right = p->left;
	p->left = node;
	return p;
	
}

AVLTree::TreeNode* AVLTree::rotateRight(TreeNode* node, int bal)
{
	TreeNode* p; //Grandchild, parent, child

	p = node->left;
	node->left = p->right;
	p->right = node;
	return p;

}

AVLTree::TreeNode* AVLTree::LR(TreeNode* node)
{
	TreeNode* p;
	node->left = rotateLeft(node->left, 0);
	p = rotateRight(node, 0);
	return p;
}

AVLTree::TreeNode* AVLTree::RL(TreeNode* node)
{
		TreeNode* gc, * p, * c;
		node->right = rotateRight(node->right, 0);
		p = rotateLeft(node, 0);
		return p;
}


						//-----ACCESSORS-----//


int AVLTree::BF(TreeNode* node, int bal)
{
	if (node == nullptr) {
		return 0;
	}
	int l, r;
	l = getHeight(node->left); //Finds left height
	r = getHeight(node->right); //Finds right height
	return (l - r);
}

int AVLTree::getHeight(TreeNode* node)
{
	if (node == nullptr) {
		return -1;
	}
	int l = getHeight(node->left);
	int r = getHeight(node->right);
	
	return max(l, r) + 1;
}


						//-----TRAVERSALS-----//


string AVLTree::printTraversals(TreeNode* node, int option)
{
	if (option == 1) {//inorder
		
		if (node == nullptr) {
			return "";
		}
		//LEFT ROOT RIGHT
		string leftTree = printTraversals(node->left, option);
		string rightTree = printTraversals(node->right, option);
		return leftTree  + node->name + ", " + rightTree;
		
	}
	else if (option == 2) { //preorder
		if (node == nullptr) {
			return "";
		}
		//ROOT LEFT RIGHT
		string leftTree = printTraversals(node->left, option);
		string rightTree = printTraversals(node->right, option);
		return node->name + ", " + leftTree + rightTree;
	}
	else if (option == 3) {
		if (node == nullptr) {
			return "";
		}
		//LEFT RIGHT ROOT
		string leftTree = printTraversals(node->left, option);
		string rightTree = printTraversals(node->right, option);
		return leftTree + rightTree  + node->name + ", ";
	}
	else {}
}

bool AVLTree::levelCnt(TreeNode* node, int level)
{
	bool res = false;
	if (node == nullptr) { //Empty tree
		res = false;
		return res;
	}
	if (level == 1) //There is at least 1 level
	{
		res = true;
		return res;
	}

	bool left = levelCnt(node->left, level - 1);
	bool right = levelCnt(node->right, level - 1);
	res = (left || right); //if left and right are true res = true
	return res;
}

string AVLTree::inOrder()
{
	TreeNode* temp = root;
	return printTraversals(temp, 1);
}

string AVLTree::preOrder()
{
	TreeNode* temp = root;
	return printTraversals(temp, 2);
}

string AVLTree::postOrder()
{
	TreeNode* temp = root;
	return printTraversals(temp, 3);
}

string AVLTree::numLvls()
{
	TreeNode* temp = root;
	int level = 1;

	//While there are still nodes left to check 
	while (levelCnt(temp, level) != false) {
		level++;
	}

	return to_string(level - 1);
}



						//-----PARAMETERS-----//


bool AVLTree::validate(string name, int ID)
{
	string s = to_string(ID);
	//Checks to make sure ID is 8 long
	if (s.size() != 8) {
		return false;
	}
	//Checks is is in alphabet
	for (int i = 0; i < name.size(); i++) {
		if (name.at(i) == ' ' || isalpha(name.at(i))) {

		}
		else {
			return false;
		}	
	}
	return true;
}



						//-----DISPLAY-----//


void AVLTree::Display(int level)
{
	
	disp(level, root);
}

void AVLTree::disp(int lvl, TreeNode* ptr)
{
	int i;
	if (ptr != nullptr)
	{
		//Referenced from online to help me visualize how a tree would look 
		disp(lvl + 1, ptr->right);
		cout << endl;
		if (ptr == root)
			cout << "Root -> ";
		for (i = 0; i < lvl && ptr != root; i++)
			cout << "        ";
		cout << ptr->ID << " " << ptr->name << " " << ptr->height << endl;
		disp(lvl + 1, ptr->left);
	}

}
//ORIGINALLY THOGUHT WE NEEDED TO WRITE TO TEXT FILE
void AVLTree::Write(const string& filename, const vector<string>& output, int x)
{
	outFile.insert(0, to_string(x));
	//cout << outFile;
	std::ofstream outFile(filename);

	// Check if the file was successfully opened
	if (!outFile.is_open()) {
		std::cerr << "Failed to open output file" << std::endl;
		return;
	}

	// Write the output to the file
	for (int i = 0; i < lines.size(); i++) {
		outFile << lines.at(i) << endl;
	}

}



