#include <iostream>
#include <list>
#include<vector>
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
	list <Item>* adjacency;
public:
	Graph()
	{
		//default constructor
		vertices = 0;
		adjacency = new list<Item>[vertices];
	}

	//////////////////////////////////////

	Graph(int vertices)
	{
		//overloaded constructor
		this->vertices = vertices;
		adjacency = new list<Item>[vertices];
	}
	/////////////////////////////////////////


	void addEdge(Item v, Item  w)
	{
		// as it is an undirected graph.
		adjacency[w.value].push_back(v);
		adjacency[v.value].push_back(w);
	}
	/////////////////////////////////////////////

	void print()
	{
		for (int v = 0; v < vertices; v++)
		{
			cout << "\n Structure of vertex " << v << "\n head ";
			for (auto x : adjacency[v])
			{
				cout << "-> " << x.value;
			}
			cout << endl;
		}
	}
	/////////////////////////////////////////////

	void getneighbours(int val)
	{
		cout << "\n neighbours  of vertex " << val << " are  \n";
		for (auto x : adjacency[val])
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

	int DFS(int vertices, bool visited[])
	{
		cout << " " << vertices << " ";
		visited[vertices] = true;

		list<int>::iterator i;
		for (i = adjacency[vertices].begin(); i != adjacency[vertices].end(); i++)
		{
			if (visited[*i] == false)
			{
				DFS(*i, visited);
			}
		}
	}

	/////////////////////////////////////////////

	void DFS(int vertices)
	{
		bool* visited = new bool[this->vertices];
		for (int i = 1; i < this->vertices; i++)
		{
			visited[i] = false;
		}
		DFS(vertices, visited);

	}

	//////////////////////////////////////////

	~Graph()
	{
		adjacency->~list();// built in destructor of list 
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
	g.getneighbours(2);
	system("pause");
	return 0;
}