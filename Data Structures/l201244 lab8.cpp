#include<iostream>
using namespace std;

template <typename k, typename v>
class TNode
{
	k key;
	v value;
	TNode<k, v>* left;
	TNode<k, v>* right;
	int Height =0;
	

	TNode(k const ky, v const val) // overloaded constructor
	{
		key = ky;
		value = val;
		left = nullptr;
		right = nullptr;

	}
	TNode(k const ky) // overloaded constructor
	{
		value = 0;
		key = ky;
		left = nullptr;
		right = nullptr;

	}

	TNode(v const val) // overloaded constructor
	{
		key = 0;
		value = val;
		left = nullptr;
		right = nullptr;
	}



	template<class k, class v>
	friend class BST;
};



template<class k, class v>
class BST
{
	TNode<k, v>* root;

public:

	BST() :root{ nullptr } {}


	int height()
	{
		return height(root);
	}

	int height(TNode<k, v>* node)
	{
		if (node == nullptr)
		{
			return -1;
		}
		else
		{
			int d = height(node->left);
			int t = height(node->right);


			if (d > t)
			{
				return(d + 1);

			}
			else
			{
				return (t + 1);
			}
		}
	}

	void insertRec(k const  key, v const value)
	{
		insertRec(root, key, value);
	}
	void insertRec(TNode<k, v>*& ptr, k const  key, v const value)
	{
		if (ptr == nullptr)
			ptr = new TNode<k, v>(key, value);
		else if (ptr->key == key)
			ptr->value = value;
		else if (ptr->key < key)
			insertRec(ptr->right, key, value);
		else
			insertRec(ptr->left, key, value);
	}

	void insert(k const  key, v const value)
	{
		if (root == nullptr) 
		{
			root = new TNode<k, v>(key, value);
			return;
		}
		TNode<k, v>* temp = root;
		TNode<k, v>* parent = nullptr;
		bool flag = true;
		while (temp != nullptr)
		{
			parent = temp;
			if (temp->key == key) {
				temp->value = value;
				flag = false;
			}
			else if (temp->key < key)
				temp = temp->right;
			else
				temp = temp->left;
		}
		if (flag)
		{
			if (parent->key < key)
				parent->right = new TNode<k, v>(key, value);
			else
				parent->left = new TNode<k, v>(key, value);
		}
	}

	v* search(k key)
	{
		return search(root, key);
	}
	v* search(TNode<k, v>* ptr, k key)
	{
		if (ptr == nullptr)
			return nullptr;
		else if (ptr->key == key)
			return &ptr->value;
		else if (ptr->key < key)
			return search(ptr->right, key);
		else
			return search(ptr->left, key);
	}

	void inorderPrintKeysRec() const
	{
		inorderPrintKeysRec(this->root);
		cout << endl;
	}

	void inorderPrintKeysRec(TNode<k, v>* curr) const
	{
		if (curr != nullptr)
		{
			inorderPrintKeysRec(curr->left);
			cout << curr->key << " ";
			inorderPrintKeysRec(curr->right);
		}
	}

	int length()
	{
		return length(root);
	}
	int length(TNode<k, v>* temp)
	{
		if (temp == nullptr)
			return 0;
		else
		{
			return (length(temp->left) + length(temp->right) + 1);
		}
	}


	void deleteNode(k const key)
	{
		// this is a wrapper function for delete node function
		this->deleteNode(key, this->root);
	}
	void deleteNode(k const temp_key, TNode<k,v>*& ptr)
	{
		if (ptr != nullptr)
		{
			if (ptr->key < temp_key)
				deleteNode(temp_key, ptr->right);
			else if (ptr->key > temp_key)
				deleteNode(temp_key, ptr->left);
			else
				deleteNode(ptr);
		}
	}
	void deleteNode(TNode<k,v>*& ptr)
	{
		
		if (ptr != nullptr)
		{
			TNode<k,v>* temp = ptr;
			TNode<k,v>* previous = ptr;
			if (ptr->left == nullptr) 
				ptr = ptr->right;
			else if (ptr->right == nullptr) 
				ptr = ptr->left;
			

			else
			{
				temp = ptr->left;
				while (temp->right != nullptr) 
				{
					previous = temp;
					temp = temp->right;
				}
				ptr->key = temp->key;
				ptr->value = temp->value;

				if (previous != ptr)
					previous->right = temp->left; 
				else
					previous->left = temp->left;
			}
			delete temp;
		}
	}


};

template<class T>
class AVL: public BST
{

public:
	AVL()
	{
		BST();
	}
	//////////////////////

	void balance(TNode<T>*& t) {
		if (t == nullptr) {
			return;
		}

		if (height(t->right) - height(t->left) < -1) {// -2 or less
			if (height(t->left->left) >= height(t->left->right)) {
				right_rotate(t);
			}
			else {
				left_right_rotate(t);
			}
		}
		else if (height(t->right) - height(t->left) > 1) {
			if (height(t->right->right) >= height(t->right->left)) {
				rotate_left(t);
			}
			else {
				right_left_rotate(t);
			}
		}

		t->height = max(height(t->left), height(t->right)) + 1;
	}

	///////////////////////////////////////////////////////////////////////////////
				//FROM LECTURE NOTES...
	/////////////////////////////////////////////////////////////////////////
	/*void rightRotate(TNode<k, v>*& x)
	{

		TNode<k, v>* orphan = x->leftChild->rightChild;

		TNode<k, v>* y = x->leftChild;

		y->rightChild = x;

		x->leftChild = orphan;

		x->height = Height(x);

		y->height = Height(y);

		x = y;

	}

	void leftRotate(TNode<k, v>*& x)
	{
		TNode<k, v>* orphan = x->rightChild->leftChild;

		TNode<k, v>* y = x->rightChild;

		y->leftChild = x;

		x->rightChild = orphan;

		x->height = Height(x);

		y->height = Height(y);

		x = y;
	}

	void doubleLeftRightRotation(TNode<k, v>*& X)
	{
		leftRotate(X->leftChild);
		rightRotate(X);
	}

	void doubleRightLeftRotation(TNode<k, v>*& X)
	{
		rightRotate(X->rightChild);
		leftRotate(X);
	}*/

	void balance(TNode<T>*& x)
	{
		if (x == nullptr)
			return;

		if (Height(x->leftChild) - Height(x->rightChild) > 1)

			if (Height(x->leftChild->leftChild) >= Height(x->leftChild->rightChild))
				rightRotate(x);

			else
				doubleLeftRightRotation(x);

		else if (Height(x->rightChild) - Height(x->leftChild) > 1)
			if (Height(x->rightChild->rightChild) >= Height(x->rightChild->leftChild))
				leftRotate(x);
			else
				doubleRightLeftRotation(x);

		x->height = max(Height(x->leftChild), Height(x->rightChild)) + 1;
	}
	///////////////////////////

	//void rightRotate(AVLNode*& x) {

	//	// 1. detach Y(left child’s) right subtree

	//	AVLNode* orphan = x->left->right;

	//	// 2. consider Y(left child) to be the new parent

	//	AVLNode* y = x->left;

	//	// 3. attach old parent onto right of new parent

	//	y1->right = x;

	//	// 4. attach new parent's old right subtree as

	//	// left subtree of old parent

	//	x->left = orphan;

	//	x->height = height(x); // update nodes'

	//	y->height = height(y); // height values

	//	x = Y;

	//}






};

int main()
{
	AVL<int> tree;


	for (int i = 1; i <= 100; i++)
		tree.insert(i,i);

	for (int i = -1; i >= -100; i--)
		tree.insert(i,i);

	for (int i = 150; i > 100; i--)
		tree.insert(i,i);

	for (int i = -150; i < -100; i++)
		tree.insert(i,i);

	for (int i = 150; i > 100; i--)
		tree.delete(i,i);



	tree.inorderPrintKeys();
	cout << endl << endl;
	cout << "Tree Height: " << tree.height() << endl;

	Node* val = tree.search(-100);

	if (val != nullptr)
	{
		cout << "Key= -100 found" << endl;
	}

	val = tree.search(-151);
	if (val == nullptr)
	{
		cout << "Key= -151 not found" << endl;
	}

	system("pause");
	return 0;
}
