#include <iostream>
using namespace std;

template <typename k, typename v>
class TNode
{
private:
	k key;
	v value;
	TNode<k, v>* leftChild;
	TNode<k, v>* rightChild;

public:
	template<typename k, typename v>
	friend class BST;

	TNode()
	{
		// default constructor
		key = 0;
		value = 0;
		leftChild = nullptr;
		rightChild = nullptr;
	}
	//////////////////////////////////////
	TNode(k const key, v const value)
	{
		// overloaded constructor

		this->key = key;
		this->value = value;
		leftChild = nullptr;
		rightChild = nullptr;
	}
	//////////////////////////////////////

	~TNode()
	{
		//destructor
	}
	//////////////////////////////////////
};


template <typename k, typename v>
class BST
{
private:
	TNode <k, v>* root;


public:

	BST()
	{
		root = nullptr;
		//default constructor
	}
	//////////////////////////////////////

	
	void insertRec(k const  key, v const value)
	{
		InsertRec(key, value, root);
	}
	//////////////////////////////////////

	void InsertRec(k const  key, v const value, TNode<k, v>*& node)	//helper (wrapper)
	{
		if (node == nullptr)
		{
			node = new TNode<k, v>(key, value);
		}
		else if (node->value > value)
		{
			InsertRec(key, value, node->leftChild);
		}
		else if (node->value < value)
		{
			InsertRec(key, value, node->rightChild);
		}
	}
	//////////////////////////////////////

	
	void insert(k key, v val)
	{
		TNode <k, v>* temp = root;
		insertion( key, val, temp);
	}

	//////////////////////////////////////

	void insertion(k key, v val, TNode<k, v>*& temp)	//wrapper
	{
		TNode<k, v>* temp2 = root;
		if (root == nullptr)
		{
			root = new TNode<k, v>(key, val);
		}
			
		else
		{

			while (temp != nullptr)
			{
				if (temp->key < key)
				{
					temp2 = temp;
					temp = temp->rightChild;
				}
				else if (temp->key > key)
				{
					temp2 = temp;
					temp = temp->leftChild;
				}
				else if (temp->key == key)
				{
					temp->value = val;
				}
			}
			temp2->leftChild = new TNode<k, v>(key, val);
		}
	}
	//////////////////////////////////////

	v search(k key)
	{
		return search(key, root);
	}
	//////////////////////////////////////

	v search(k keyy, TNode<k, v>*& curr)		//wrapper
	{
		if (curr == nullptr)
		{
			return -1;
		}
		else if (curr->key == keyy)
		{
			return curr->key;
		}
		else if (curr->key < keyy)
		{
			return search(keyy, curr->rightChild);
		}
		else
		{
			return search(keyy, curr->leftChild);
		}
	}
	//////////////////////////////////////


	void inorderPrintKeysRec()
	{
		InOrder(root);
	}
	//////////////////////////////////////


	void InOrder(TNode<k, v>* t)
	{
		if (t)
		{
			InOrder(t->leftChild);
			cout << t->value<<endl;
			InOrder(t->rightChild);

		}
	}


	////////////////////////////////////////////////////////////////
	int length()
	{
		int count = 0;
		length(root, count);
		return count;

	}

	void length(TNode<k, v>*& ptr, int& count)
	{

		if (ptr != nullptr)
		{
			length(ptr->left, count);
			count = count + 1;
			length(ptr->right, count);
		}
	}
	//////////////////////////////////////


	/*void printAllAncestors(k const  key) const
	{

	}*/
};



int main()
{
	BST<int, int> tree; //the key and value both are of type int

	tree.insert(500, 500);
	tree.insertRec(1000, 1000);
	//tree.insert(1, 1);
	tree.insert(600, 600);
	tree.insertRec(700, 700);
	tree.insert(10, 10);
	tree.insert(30, 30);
	tree.insertRec(9000, 9000);
	tree.insert(50000, 50000);
	tree.insertRec(20, 20);


	//cout << "Printing keys using iterative inorder traversal: ";
	//tree.inorderPrintKeys();

	cout << endl << endl << "Printing keys using recursive inorder traversal: ";
	tree.inorderPrintKeysRec();

	cout << endl << "Printing the keys of ancestor nodes of 20" << endl;
	//tree.printAllAncestors(20);*/

	system("pause");
	return 0;
}
