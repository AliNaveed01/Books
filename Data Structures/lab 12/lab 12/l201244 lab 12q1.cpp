#include <iostream>
#include <list>
using namespace std;
class Item
{
public:
	int value;
	
	////////////////////////////
	Item()
	{
		value = 0;
	}
	///////////////////////////////

	Item(int value)
	{
		this->value = value;
	}
	//////////////////////////////
};

///////////////////////////////////////////

class Graph
{
private:
	int vertices;
	list <Item>* ptr;
public:
	Graph()
	{
		//default constructor
		vertices = 0;
		ptr = new list<Item>[vertices];
	}

	//////////////////////////////////////

	Graph(int vertices)
	{
		//overloaded constructor
		this->vertices = vertices;
		ptr = new list<Item>[vertices];
	}
	/////////////////////////////////////////


	void addEdge(Item v, Item  w)
	{
		ptr[w.value].push_back(v);
		ptr[v.value].push_back(w);
	}
	/////////////////////////////////////////////

	void print()
	{
		for (int v = 0; v < vertices; v++)
		{
			cout << "\n Structure of vertex "<< v << "\n head ";
			for (auto x : ptr[v])
			{
				cout << "-> " << x.value;
			}
			cout << endl;
		}
	}
	/////////////////////////////////////////////

	void getneighbours(int val)
	{
		cout <<"\n neighbours  of vertex " << val << " are  \n";
		for (auto x : ptr[val])
		{
			cout << x.value << " ";
		}
		cout << endl;
	}
	////////////////////////////////////////

	void inOutdegree()
	{
		int* arr = new int[vertices];
		//int* arr1 = new int[vertices];
	}
	///////////////////////////////////////


	~Graph()
	{
		ptr->~list();// built in destructor of list 
	}
	///////////////////////////////////////

};
int main()
{
	Graph g(10);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 4);
	g.addEdge(2, 9);
	g.addEdge(3, 4);
	g.addEdge(5, 6); 
	g.addEdge(5, 7);
	g.addEdge(6, 8);
	g.addEdge(7, 8);
	g.addEdge(7, 9);

	g.print();
	g.getneighbours(0);
	system("pause");
	return 0;
}
