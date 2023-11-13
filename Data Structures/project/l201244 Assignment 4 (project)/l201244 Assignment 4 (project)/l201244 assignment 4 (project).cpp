#include <iostream>
#include <list>
#include <vector>
#include <fstream>
using namespace std;

//////////////////////////////////////////// QUESTION NO 1////////////////////////////////////////////////.

class Information
{
private:
	int User_Id;
	char Operation_Type;

public:

	Information()
	{
		//dafault 
		User_Id = -1;
		Operation_Type = 'N';
	}

	Information(int Id, char Operation)
	{
		//overloaded
		User_Id = Id;
		Operation_Type = Operation;
	}

	// << operator overloader.
	friend ostream& operator<<(ostream& os, const Information& Info)
	{
	// so that we can use it with cout.
		os << "User Id : " << Info.User_Id << endl;
		if (Info.Operation_Type == 'R')
		{
			os << "Operation Type : Reading \n";
		}
		else if (Info.Operation_Type == 'W')
		{
			os << "Operation Type : Writing \n";
		}

		return os;
	}

	void Print_User_Id()
	{
		cout << "User Id : " << User_Id << "\n";
	}

	void Print_Operation()
	{
		if (Operation_Type == 'R')
		{
			cout << "Operation Type : Reading \n";
		}
		else if (Operation_Type == 'W')
		{
			cout << "Operation Type : Writing \n";
		}
	}

	template <class T>
	friend class Heap_Item;

	template <class T>
	friend class Priority_Queue;

	template <class T>
	friend class Hash_Item;

	template <class T>
	friend class Hash_Table;

};

template <class T>
class Heap_Item		//one element of heap.
{
private:
	T Key;
	Information Info;
public:

	//default.
	Heap_Item()
	{
		Info = Information();
		Key = -1;		//0-100 tk hoskti.
	}

	//parameterized.
	Heap_Item(T Key, Information Info)
	{
		this->Key = Key;
		this->Info = Info;
	}

	// overloaded cons, incase he enters info differnetly.
	Heap_Item(int Id, T Key, char Operation) :Info(Id, Operation)
	{
		this->Key = Key;
	}

	//	overloaded swap because when we extract, we swap the root with the last item.
	void Swap(Heap_Item<T>& x, Heap_Item<T>& y)
	{
		//simple swapping.
		Heap_Item<T> temp(x.Key, x.Info);
		x.Key = y.Key;
		x.Info = y.Info;

		y.Key = temp.Key;
		y.Info = temp.Info;
	}

	//console output operator overloading .
	// so when we cout any heapitem , it will print it without error.
	friend ostream& operator<<(ostream& os, const Heap_Item& Item)
	{
		os << Item.Info;
		os << "Priority : " << Item.Key << "\n";
		return os;
	}

	// first prints user id, then priority, then operation
	// we need that because because we had to check the queue 
	// also it cannot  print it in the order we want.
	void Print_Heap_Item()
	{
		Info.Print_User_Id();
		cout << "Priority : " << Key << "\n";
		Info.Print_Operation();
	}


	//destructor.
	~Heap_Item()
	{
	}

	template <class T>
	friend class Priority_Queue;

	template <class T>
	friend class Hash_Item;

	template <class T>
	friend class Hash_Table;

};

template <class T>
class Priority_Queue
{
private:
	vector<Heap_Item<T>> Heap_Array;		//vectors array. of heap items
	int Capacity;		// in case the user gives the max capacity before the start.(size of piroity queue).
	int Current_Size;		// for record of the number of elements we have entered in the vector array.
	Heap_Item<T> Minimum;		// because it is the maxheap, we have max num in o(1). we also know that minheap will
	// be at the leaf node, but as we dont know where will be our leaf, this var will help us to find min item in o1.

	//returns Parent 
	int Parent(int i)
	{
		return (i - 1) / 2;		//gives us index.
	}
	//return Left child
	int Left(int i)
	{
		return (2 * i + 1);
	}
	//Return Right child.
	int Right(int i)
	{
		return (2 * i + 2);
	}

public:

	// constructor.		hamesha default values ayen.
	Priority_Queue() :Minimum()	// it will call the cons of heap item. (not that neccessay but for personal satisfaction)
	{
		Current_Size = 0;
		Capacity = 0;
		Heap_Array.resize(Capacity);		// builtit func which will resize the vector 

	}

	//overloaded constructor			// id        key,   optype.
	Priority_Queue(int capacity) :Minimum(INT_MAX, INT_MAX, NULL)	//int_max stores the max value which can entered be in int.
	{
		Current_Size = 0;
		Capacity = capacity;
		Heap_Array.resize(Capacity);
	}

	// if mins priority is more than given temp.
	// used in insert..
	void Set_Minimum(Heap_Item<T> Temp)
	{
		if (this->Minimum.Key > Temp.Key)
		{
			Minimum.Key = Temp.Key;
			Minimum.Info.User_Id = Temp.Info.User_Id;
			Minimum.Info.Operation_Type = Temp.Info.Operation_Type;
		}
	}

	/// after insetring, we are checking it whther it is minimum. after that we check its property of PQ.
	void Insert_Heap_Item(int Id, T Key, char Operation)
	{
		Heap_Item<T> Temp(Id, Key, Operation);	//const

		Set_Minimum(Temp);

		// First insert the new key at the end
		Current_Size++;			// for record.
		int i = Current_Size - 1;		// from the back because we have to check parents.
		Heap_Array.push_back(Temp);			// stored the heapitem at the end.

		// Fix the min heap property if it is violated
		// started from the end cuz we have to check the parent bar bar.
		while (i != 0 && Heap_Array[Parent(i)].Key < Heap_Array[i].Key) { // if parents key is smaller than the child's key.
			swap(Heap_Array[i], Heap_Array[Parent(i)]);		// calling the swap func()S
			i = Parent(i);// after swapping parents with child. now we have to check again (parent with grandparent basically).
		}
	}

	// Method to remove minimum element (or root) from min heap
	Heap_Item<T> Extract_Max()
	{
		if (Current_Size <= 0)		// if queue is empty.
		{
			cout << "Size of Queue is already zero\n";
		}

		Heap_Item<T> Temp = Heap_Array[0];		//stroing max element at temp

		if (Current_Size == 1) {	//incase only 1 element
			Current_Size--;
			Heap_Array.clear();			//clear it. complt
			return Temp;
		}

		// incase vector is kinda filled
		// Store the minimum value, and remove it from heap
		Heap_Array[0] = Heap_Array[Current_Size - 1];		//swapping it with leaf node. 
		Heap_Array.erase(Heap_Array.begin() + Current_Size - 1);	//delete the last node (heap array cirrent size -1)
		Current_Size--;		// because it is removed.

		Max_Heapify(0);			// for property of PQ.

		return Temp;
	}


	// A recursive method to heapify a subtree with the root at given index
	// in this ,heaps properties and satisfied. assumes that the subtrees are already heapified
	void Max_Heapify(int i)
	{
		int l = Left(i);
		int r = Right(i);
		int largest = i;		//given node.
		//							child>parent.
		if (l < Current_Size && Heap_Array[l].Key > Heap_Array[i].Key)
		{
			largest = l;		//left is largest.
		}
		//								right>parent	
		if (r < Current_Size && Heap_Array[r].Key > Heap_Array[largest].Key)
		{
			largest = r;		//right is largest
		}

		if (largest != i)			// if largest is changed.
		{
			swap(Heap_Array[i], Heap_Array[largest]);		// swap it
			Max_Heapify(largest);// recursive call.
		}
	}

	// finds the max item present in our PQ AND returns it.
	Heap_Item<T> Find_Max()
	{
		if (Current_Size != 0)
		{
			Heap_Item<T> temp = Heap_Array[0];
			return temp;
		}
		else
		{
			cout << "Heap is Empty\n";
			return Heap_Item<T>();		//incase its empty, call the default cons .
		}
	}

	// returns the minimum val in o1
	Heap_Item<T> Find_Min()
	{
		if (Current_Size != 0)
		{
			Heap_Item<T> temp = Minimum;		// that is why we had minimum nameed memeber variable in private.
			return temp;
		}
		else
		{
			cout << "Heap is Empty\n";
			return Heap_Item<T>();
		}

	}

	// incase we want the max  priority id. (cuz we were heapifying on the basis of key).
	int Find_Max_Id()
	{
		T Max_Id = -1;
		if (Is_Empty() == true)
		{
			Max_Id = -1;
		}
		else
		{
			Max_Id = Heap_Array[0].Info.User_Id; // max element's priority.
		}
		return Max_Id;

	}

	// incase we want the id with minimum priority.
	int Find_Min_Id()
	{
		T Min_Id = -1;
		if (Is_Empty() == true)
		{
			Min_Id = -1;
		}
		else
		{
			Min_Id = Minimum.Info.User_Id; // the node with minimum priority.
		}
		return Min_Id;
	}


	// incase we want the operation we want of the node with lowest priority.
	char Find_Min_Operation()
	{
		char Min_Operation;
		if (Is_Empty() == true)
		{
			Min_Operation = 'N';		// N means null.
		}
		else
		{
			Min_Operation = Minimum.Info.Operation_Type;		// the op type of the node with lowest priority.
		}
		return Min_Operation;
	}


	char Find_Max_Operation()
	{
		char Max_Operation;
		if (Is_Empty() == true)
		{
			Max_Operation = 'N';	// null
		}
		else
		{
			Max_Operation = Heap_Array[0].Info.Operation_Type; // the op type of the node with highest priority.
		}
		return Max_Operation;
	}

	// simply prints the whole queue user,optype,key.
	void Print_Queue()
	{
		for (int i = 0; i < Heap_Array.size(); i++)
		{
			//prints literally every node.
			cout << Heap_Array[i] << endl;
		}
	}

	// takes an array and make it priority quueu by sorting.
	void Build_Queue(Heap_Item<T> Array[], int size)		//cuz we dont know the size (also either vector or an array).
	{
		for (int i = 0; i < size; i++)
		{
			this->Insert_Heap_Item(Array[i].Info.User_Id, Array[i].Key, Array[i].Info.Operation_Type);	//har node or insert krdo.
		}
	}

	//Return Current Size of Queue 
	int Size()
	{
		return Current_Size;
	}

	//Returns True If Queue is Empty otherwise false
	bool Is_Empty()
	{
		if (Current_Size == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//Destructor
	~Priority_Queue()
	{
	}

	template <class T>
	friend class Hash_Item;

	template <class T>
	friend class Hash_Table;

};


/////////////////////////////////////////////////QUESTION NO 2/////////////////////////////////////////////////...

template <class T>
class Hash_Item
{
private:
	// har hash table k index pr aik LL hai or uske aik node pr (following mem variables hain.)
	vector<int> User_Reading_Array;		// har node pr aik user array hgi (jo jo read krega uski id rkhwadenge.).user id jaigi
	int User_Writing;	// simple variable at everynode (when we are writing, reading array must be 0)
	// if we are only reading, then writting variable must be -1.
	int File_Id;		// file id 
	Priority_Queue<T> Queue;	// a queue (storing the id and priority of each user alongwith operation.)
	// when the user with highest priority enters and reading array is full
	// jb b reading array me aik b id ho(size not 0), to agr koi write wala user arha hai to usko waiting queue me rkhwana h
	// agr koi user arha hai for reading, or uski priority max item se bari hai, to usko reading array me bhejdo.

public:
	// constructor.
	Hash_Item()
	{
		File_Id = -1;
		User_Writing = -1;
	}

	// overloaded cons
	Hash_Item(int File)
	{
		File_Id = File;
		User_Writing = -1;
	}

	template <class T>
	friend class Hash_Table;
};

template <class T>
class Hash_Table
{
private:
	vector <list<Hash_Item<T>>> Hash_Array;		// as i said above. (array (hash table)).
	int Table_Size;			// kitne vectors ki array ho.
public:

	// default const
	Hash_Table()
	{
		Table_Size = 11;		// must be prime.
		Hash_Array.resize(Table_Size);	// resire krdo.
	}

	// hash function.
	int Magic_Function(const int Id)	//takey id change na ho.
	{
		int magic = Id % Table_Size;		// takes mod of table size with the given id aand returns it.
		return magic;
	}

	// this code will help us find if the file exists or not.
	// incase any file id is repititve. we should not insert it again, it will tell us if
	bool Find_File_Id(int file)
	{
		bool flag = false;
		list<Hash_Item<T>> ::template iterator i = Hash_Array[Magic_Function(file)].begin();
		for (; i != Hash_Array[Magic_Function(file)].end(); i++)	
		{
			if (i->File_Id == file)
			{
				flag = true;;
			}
		}
		return flag;
	}

	// this code will insert a file in our hash table.
	void Insert_File_Id(int file)
	{
		if (Find_File_Id(file) == false)	// if it doesnt exits previously.
		{
			Hash_Item<T> Temp(file);
			Hash_Array[Magic_Function(file)].push_back(Temp);	// magic func will return the index
			// hash array k us index pr jake usko push back krdo

		}
	}

	// inserts the data in the hash table
	void Insert_Data(int FileId, int UserId, T key, char Operation)
	{
		if (this->Find_File_Id(FileId) == true)	// if it exists.
		{
			list<Hash_Item<T>> ::template iterator i = Hash_Array[Magic_Function(FileId)].begin();// from the start.
			for (; i != Hash_Array[Magic_Function(FileId)].end(); i++) // jb tk us node pr ni phnchty.
			{
				if (i->File_Id == FileId)	// if u have found the file id.
				{
					if (Operation == 'R')		// if the user wants to read.
					{
						if (i->User_Writing == -1 && i->Queue.Size() == 0)	// everythins is empty(user is the first user.)
						{
							i->User_Reading_Array.push_back(UserId);	// acess dedo reading ki.
						}
						else if (i->User_Writing != -1)		// agr koi write krra ha
						{
							i->Queue.Insert_Heap_Item(UserId, key, Operation);			// to usko waiting qeueu me put krdo.
						}
						else if (i->User_Writing == -1 && i->Queue.Size() != 0)
						{
							Heap_Item<T> Temp = i->Queue.Find_Max();		//agr log hain lekin no one is writing.
							if (Temp.Key > key)
							{
								i->Queue.Insert_Heap_Item(UserId, key, Operation);	// check its priority with the max item
								// if coming's priority is less, put it in waiting queue.
							}
							else if (Temp.Key < key)
							{
								// if cmings priority is highest.
								i->User_Reading_Array.push_back(UserId);
								// grant it read acess. while other remains in PQ.
							}
						}
					}
					// incase he wants to write.
					else if (Operation == 'W')
					{

						if (i->User_Writing == -1 && i->User_Reading_Array.size() == 0)	// is hes the first user.
						{
							i->User_Writing = UserId;			// grant it writing access.

						}
						else
							// incase someone is already writing  or even reading it
						{
							i->Queue.Insert_Heap_Item(UserId, key, Operation); // waiting queue me daldo.
						}
					}
				}
			}
		}
		// if the file dont exists.
		else if (this->Find_File_Id(FileId) == false)
		{
			cout << "File Doesnot Exist\n";
		}
	}

	// this code will help us to print every node at every index of the hash table.
	void Print_Hash_Table()
	{
		for (int j = 0; j < Table_Size; j++)	// we will traverse at every index of the hash table.
		{
			list<Hash_Item<T>> ::template iterator i = Hash_Array[j].begin();	// phly node pr jai LL k
			for (i = Hash_Array[j].begin(); i != Hash_Array[j].end(); i++)
			{
				// id of the user.
				cout << "File Id : " << i->File_Id << endl;
				if (i->User_Writing != -1)
					// if  he wants to write. or he himself is writing.
				{
					cout << "Acess Granted to User : " << i->User_Writing << " , Write\n";

				}
				else if (i->User_Writing == -1)		// if no one is writting.
				{
					// traverse in the reading array.
					for (int k = 0; k < i->User_Reading_Array.size(); k++)
					{
						// bcz more than 1 person can read the file.
						cout << "Acess Granted to User " << i->User_Reading_Array[k] << " ,Read\n";
					}
				}

				cout << "Next ";	// who is next after the one who is with highest priority in our PQ.
				if (i->Queue.Size() == 0)
				{
					cout << "None\n";
				}
				else
				{
					// the one who has the max priority.
					// print it
					cout << "User " << i->Queue.Find_Max_Id() << " ,";
					// if we wants to read
					if (i->Queue.Find_Max_Operation() == 'R')
					{
						// he wants to read
						cout << "Read \n";
					}
					// if he wants to write.
					else if (i->Queue.Find_Max_Operation() == 'W')
					{
						cout << "Write \n";
					}
				}

				// now we also have to tell that how many users are waiting.
				cout << "Waiting ";
				if (i->Queue.Size() == 0)
					// if there is no one
				{
					cout << "None\n\n\n";
				}
				else
					// the number of people weaiting will be equal to the size of the waiting queue.
				{
					cout << i->Queue.Size() << " Users \n\n\n";
				}

			}
		}

	}

	// this code will help us to release a user from the file id. if he no longer need to acceess.
	// using file and user id
	void Release_File(int FileId, int UserID)
	{
		// if the file exists
		if (this->Find_File_Id(FileId) == true)
		{
			list<Hash_Item<T>> ::template iterator i = Hash_Array[Magic_Function(FileId)].begin();	// going every node of the LL.
			for (; i != Hash_Array[Magic_Function(FileId)].end(); i++) 
			{
				// if file id is found.
				if (i->File_Id == FileId)
				{
					//this var will find the index of id in the reading array.
					int Id_Match_Index; // will be used to tell at which index user is in reading array.

					// it tells us if id exisits in reading array (true = reading ).
					bool Id_Found = false;
					for (int k = 0; k < i->User_Reading_Array.size(); k++)	// reading array traversal.
					{
						//if u have found the given id.
						if (i->User_Reading_Array[k] == UserID)
						{
							Id_Match_Index = k;// assign it to the id mathc index
							Id_Found = true;
						}
					}

					// if we have found it in the reading array.
					if (Id_Found == true)
					{
						//clear krdo usko.
						i->User_Reading_Array.erase(i->User_Reading_Array.begin() + Id_Match_Index);	
						// remove krne k bad resize krne ki b zrurt, so after deleting, resize the reading array.
						i->User_Reading_Array.shrink_to_fit(); // builtin func to shrink the array. in vector.

						// hoskta hai after removing the person, reading array becomes empty, lekin hamari
						// waiting list me koi ho.

						// if reading array in empty,				// waiting list not zero
						if ((i->User_Reading_Array.size() == 0) && (i->Queue.Size() != 0)
							&& (i->Queue.Find_Max_Operation() == 'W'))	// highest priority wants to write.
						{
							// writing ko assign krdo
							i->User_Writing = i->Queue.Find_Max_Id();
							// usko b queue se nikal do.
							i->Queue.Extract_Max();
						}
						// if the  waiting queue is not zero,     if the highest priority wants to read
						else if ((i->Queue.Size() != 0) && (i->Queue.Find_Max_Operation() == 'R'))
						{
							// while waiting queue is not 0			the highest priority wants to read.
							while (i->Queue.Size() != 0 && i->Queue.Find_Max_Operation() == 'R')
							{
								// assign for pushinig back
								int Id = i->Queue.Find_Max_Id();	// assignt the higshest priority.
								i->User_Reading_Array.push_back(Id);	// from waiting queue to reading array
								i->Queue.Extract_Max();	// extract it from waiting queue.
							}
						}

					}
					// else the id is not found in reading array.
					// it will be writing object. then.
					else if (Id_Found == false)
					{
						// if its in writing .
						if (i->User_Writing == UserID)
						{
							// phly writing ko -1 kiya .
							i->User_Writing = -1;
							bool flag = false;
							// same like above that all other wants to write.
							while (i->Queue.Size() != 0 && i->Queue.Find_Max_Operation() == 'R')
							{
								flag = true;
								int Id = i->Queue.Find_Max_Id();
								i->User_Reading_Array.push_back(Id);// to array.
								i->Queue.Extract_Max();
							}
							// the one with highest priority wants to write.
							if (i->Queue.Size() != 0 && i->Queue.Find_Max_Operation() == 'W'&& flag == false)
							{
								i->User_Writing = i->Queue.Find_Max_Id();
								i->Queue.Extract_Max();
							}
						}

						// if the user id is found nowehere.
						else if (i->User_Writing != UserID)
						{
							cout << "User Id not Found !!!\n";
						}

					}
				}
			}
		}
		else
			// IF THE FILE ID IS NOT FOUND
		{
			cout << "File ID not Found!!!\n";
		}
	}

	// this file will help us to delete the whole file from the hash table if no one is currently acessing it.
	void Delete_File()
	{
		for (int j = 0; j < Table_Size; j++)	// hash table traversing
		{
		jmp:	// coal style xD
			list<Hash_Item<T>> ::template iterator i = Hash_Array[j].begin();
			for (i = Hash_Array[j].begin(); i != Hash_Array[j].end(); i++)
			{
			// if no one is reading or writting.
				if (i->User_Reading_Array.size() == 0 && i->User_Writing == -1)
				{
					// erase it 
					Hash_Array[j].erase(i);
					// if we dont go to the start, i will have garbage val, and we have no node anymore, it will through an 
					// error if we i++.
					// again assign it at begining because we want to traverse from the start again.
					i = Hash_Array[j].begin();
					// if there is no node left. 
					if (i == Hash_Array[j].end())
					{
						goto jmp;
					}
				}
			}
		}
	}

	// this code will help us to read the file ids only from the text..
	void Read_File_ID(string Name)
	{
		ifstream Rdr(Name);	
		int FileId;

		while (!Rdr.eof())
		{
			Rdr >> FileId;	// cin in rdr
			Rdr.ignore(200, '\n');	// ignore all other characters in line until u reach end of line.200 characters ignore maro.

			// as given in document.
			if (FileId < 5000 || FileId>99999)
			{
				cout << "Invalid File ID!!!\n";
				break;
			}
			// insert it in the hash table.
			this->Insert_File_Id(FileId);

		}
	}

	// this will read the whole file .
	void FileReading(string Name)
	{
		ifstream Rdr(Name);
		int FileId;
		int UserId;
		int Priority;
		char Oper;
		char comma;

		while (!Rdr.eof())
		{
			Rdr >> FileId;
			Rdr >> comma;
			Rdr >> UserId;
			Rdr >> comma;
			Rdr >> Priority;
			Rdr >> comma;
			Rdr >> Oper;
			Rdr.ignore(50, '\n');

			// as given in requirements.
			if (FileId < 5000 || FileId>99999)
			{
				cout << "Invalid File ID!!!\n";
				break;
			}

			// conditions
			if (UserId < 0 || UserId>10000)
			{
				cout << "Invalid User Id!!!\n";
				break;
			}

			if (Priority < 0 || Priority>100)
			{
				cout << "Invalid Priority!!!\n";
				break;
			}

			if (Oper != 'R' && Oper != 'W')
			{
				cout << "Invalid Operation!!!\n";
				break;
			}

			this->Insert_Data(FileId, UserId, Priority, Oper);

		}
	}

	//Destructor
	~Hash_Table()
	{}

};






int main()
{




	Hash_Table<int>  Hash;
	string name = "Text.txt";
	int option = 0;
	do
	{
		system("cls");
		cout << "What operation do you want to perform? " <<
			" Select Option number. Enter 0 to exit." << endl;
		cout << "0. Exit " << endl;
		cout << "1. Print Hash Table with File information" << endl;
		cout << "2. Load data" << endl;
		cout << "3. Insert a File" << endl;
		cout << "4. Delete a File" << endl;
		cout << "5. Request Access" << endl;
		cout << "6. Release File" << endl;
		cout << endl;
		cin >> option;


		switch (option)
		{
		case 0:
			break;
		case 1:
			Hash.Print_Hash_Table();
			break;
		case 2:
			Hash.Read_File_ID(name);	//only name of the file ids.
			break;
		case 3:
			Hash.FileReading(name);	// it will read the whole id.
			//Hash.Insert_Data();
			break;
		case 4:
			Hash.Delete_File();
			break;
		case 5:
			cout << "Enter File Id :\n";
			int file;
			cin >> file;

			cout << "Enter User Id :\n";
			int user;
			cin >> user;

			cout << "Enter Priority :\n";
			int prior;
			cin >> prior;

			cout << "Enter Operation :\n";
			char oper;
			cin >> oper;

			Hash.Insert_Data(file, user, prior, oper);
			break;
		case 6:
			cout << "Enter File Id you want to release :\n";
			int file1;
			cin >> file1;
			cout << "Enter User Id you want to release :\n";
			int user1;
			cin >> user1;
			Hash.Release_File(file1, user1);
			break;
		}
		system("pause");
	} while (option != 0);

	return 0;
}