#include<iostream>
#include<string>

using namespace std;

class PatientRecord
{
	friend class HospitalData;
private:
	int id;
	string name;
	string date;
	string disease;
	bool status;	// true for admitted and false for discharged
public:
	PatientRecord(int _id = 0, string _name = "", string _date = "", string _disease = "", bool _status = false)
	{
		id = _id;
		name = _name;
		date = _date;
		disease = _disease;
		status = _status;
	}
};

class TNode
{
	friend class HospitalData;
private:
	PatientRecord Patient;
	TNode* left;
	TNode* right;
public:
	TNode(PatientRecord _Patient, TNode* _leftChild = 0, TNode* _rightChild = 0)
	{
		Patient = _Patient;
		left = _leftChild;
		right = _rightChild;
	}
	~TNode()
	{
		left = 0;
		right = 0;
	}
};

class HospitalData
{
private:
	TNode* Root;
	int size; //SIZE OF TREE



	// helper function for insertion.

	void Insert(PatientRecord P1, TNode*& ptr)
	{
		if (ptr == 0)
		{
			ptr = new TNode(P1);
			size++;
		}
		else
		{
			if (P1.id < ptr->Patient.id)
			{
				Insert(P1, ptr->left);
				rightRotate(ptr);
			}
			else
			{
				Insert(P1, ptr->right);
				leftRotate(ptr);
			}
		}
	}


	// helper for deletion 
	void deleteR(int d, TNode*& node)
	{
		if (node)
		{
			if (d > node->Patient.id)
				deleteR(d, node->right);
			else if (d < node->Patient.id)
				deleteR(d, node->left);
			else
				deleteNode(node);
		}
	}

	// helper for printing admitted patients.

	void PrintAdmitted(TNode* ptr)
	{
		if (ptr == 0)
			return;
		else
		{
			PrintAdmitted(ptr->left);
			if (ptr->Patient.status == true)
				cout << ptr->Patient.id << " -> " << ptr->Patient.name << " " << ptr->Patient.disease << " " << ptr->Patient.date << endl;
			PrintAdmitted(ptr->right);
		}
	}

	void printTree(TNode* root)
	{
		if (root == nullptr)
			return;
		// Process right child first
		printTree(root->right);

		cout << endl;

		cout << root->Patient.id << "\n";

		// Process left child
		printTree(root->left);
	}


public:

	// constructor.
	HospitalData(TNode* _Root = 0, int _size = 0)
	{
		Root = _Root;
		size = _size;
	}

	void Delete(TNode* Node)
	{
		if (Node)
		{
			Delete(Node->left);
			Delete(Node->right);
			delete Node;
		}
	}

	// code for left rotation.
	void leftRotate(TNode*& x)
	{
		TNode* Orphan = x->right->left;

		TNode* y = x->right;

		y->left = x;

		x->right = Orphan;

		x = y;
	}

	// code for right rotation.
	void rightRotate(TNode*& x)
	{
		TNode* Orphan = x->left->right;

		TNode* y = x->left;

		y->right = x;

		x->left = Orphan;

		x = y;
	}

	void Insert(PatientRecord P1)
	{
		if (Root == 0)
		{
			Root = new TNode(P1);
			size++;
		}
		else
			if (P1.id < Root->Patient.id)
			{
				Insert(P1, Root->left);
				rightRotate(Root);
			}
			else
			{
				Insert(P1, Root->right);
				leftRotate(Root);
			}
	}

	void deleteR(int d)
	{
		deleteR(d, Root);
	}

	// gives us the right most element.
	int getPredecessor(TNode* n)
	{
		while (n->right != NULL)
			n = n->right;

		return n->Patient.id;
	}


	void deleteNode(TNode*& node)
	{

		TNode* temp = node;
		if (node->left == nullptr)
		{
			node = node->right;
			delete temp;
		}
		else if (node->right == nullptr)
		{
			node = node->left;
			delete temp;
		}
		else
		{
			int d = getPredecessor(node->left);
			node->Patient.id = d;
			deleteR(d, node->left);
		}
	}


	void remove(int d)
	{
		TNode* parent = Root;

		TNode* child = Root;
		size--;
		while (child && child->Patient.id != d)
		{

			parent = child;

			if (parent->Patient.id > d)
				child = child->left;

			else if (parent->Patient.id < d)
				child = child->right;

		}

		if (child)  //if data is found
		{
			if (child == Root)
				deleteNode(Root);

			else if (parent->left == child)
				deleteNode(parent->left);

			else
				deleteNode(parent->right);

		}
	}

	void Print(int P_id)
	{
		Print(P_id, Root);
	}

	void Print(int P_id, TNode* ptr)
	{
		if (P_id == ptr->Patient.id)
		{
			cout << "\n---------------------------\n";
			cout << "Id = " << ptr->Patient.id << endl;
			cout << "Name = " << ptr->Patient.name << endl;
			cout << "Disease = " << ptr->Patient.disease << endl;
			cout << "Date = " << ptr->Patient.date << endl;
			if (ptr->Patient.status == true)
				cout << "Admitted";
			else
				cout << "Discharged";

			cout << "\n\n--------------------------\n";
			return;
		}

		if (P_id < ptr->Patient.id)
			Print(P_id, ptr->left);
		else
			Print(P_id, ptr->right);
	}

	void PrintAdmitted()
	{
		cout << "\nAdmitted Patients Details Are\n";
		PrintAdmitted(Root);
	}

	void move(int& _level, int level, TNode*& ptr, int pid)
	{

		if (_level == level && pid == ptr->Patient.id)
		{
			return;
		}
		else
		{
			if (pid < ptr->Patient.id)
			{
				move(_level, level + 1, ptr->left, pid);
				rightRotate(ptr);
			}
			else
			{
				move(_level, level + 1, ptr->right, pid);
				leftRotate(ptr);
			}
		}

	}

	void Search(int pid, int level)
	{
		int _level = 0;	// for keeping the record of levels u have traversed.
		TNode* ptr = Root;
		bool found = false;

		while (_level <= size)
		{
			if (pid == ptr->Patient.id)
			{
				found = true;
				break;
			}
			if (pid < ptr->Patient.id)
			{
				ptr = ptr->left;
				_level++;
			}
			else
			{
				ptr = ptr->right;
				_level++;
			}
		}

		if (found == true)
		{
			if (_level > level)
			{
				move(_level, level, Root, pid);
			}
			// if level is larger then it will not be moved as written in a3.
		}
	}


	// this will help us find median of the tree.
	void FindMedian(int _medianNo, int _count, TNode* ptr, TNode*& _Median)
	{
		if (ptr == 0)
			return;

		FindMedian(_medianNo, _count + 1, ptr->left, _Median);
		if (_medianNo == _count && ptr != 0)
		{
			_Median = ptr;
			return;
		}
		FindMedian(_medianNo, _count + 1, ptr->right, _Median);

	}

	void Split(HospitalData& _data2)
	{
		int medianNo = size / 2;
		TNode* Median = 0;
		int count = 0;
		FindMedian(medianNo, count, Root, Median);
		Search(Median->Patient.id, 0);
		// ill have middlemost data at the root

		TNode* temp = Root;
		_data2.Root = Root->left;// _data2 has left subtree
		Root = Root->right; // Now Root has the right subtree
		delete temp;
	}

	void printTree()
	{
		printTree(Root);
	}


	//destructor.
	~HospitalData()
	{
		if (Root)
		{
			Delete(Root);
		}
	}

};

int main()
{
	cout << "---------------------------------------------------\n\n" << endl;
	HospitalData data, data2;
	PatientRecord P1(1, "Naveed", "2020", "flu", true);
	PatientRecord P2(7, "Hanan", "2020", "cough", false);
	PatientRecord P3(3, "Shawaiz", "2021", "weakness", true);
	PatientRecord P4(4, "Hassan", "2020", "cough", true);
	PatientRecord P5(2, "Hussain", "2021", "dirrhea", true);
	PatientRecord P6(9, "Harib", "2021", "sore throat", true);



	data.Insert(P1);
	data.Insert(P2);
	data.Insert(P3);
	data.Insert(P4);
	data.Insert(P5);
	data.Insert(P6);

	data.Print(7);
	data.Print(1);
	cout << "---------------------------------------------------\n\n" << endl;

	data.PrintAdmitted();
	cout << "---------------------------------------------------\n\n" << endl;
	data.deleteR(7);
	data.deleteR(2);

	data.PrintAdmitted();

	cout << "---------------------------------------------------\n\n" << endl;
	int choice;
	cout << "press 1 if you want to split the tree.: ";
	cin >> choice;
	if (choice == 1)
	{
		cout << "\nOriginal Tree \n";
		data.printTree();

		data.Split(data2); //data has the right subtree of median
						   //data2 has the left subtree of median


		cout << "\nRight SubTree \n";
		data.printTree();

		cout << "\nLeft SubTree \n";
		data2.printTree();
	}
	else {
		return 0;
	}

	system("pause");
	return 0;
}