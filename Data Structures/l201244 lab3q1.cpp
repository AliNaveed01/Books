#include <iostream>
using namespace std;

template<class T>
class node {
private:
    node<T>* next;
    node<T>* prev;
    T data;
    //////////////////////////////
public:

    node()
    {
        //default constructor
        next = nullptr;
        prev = nullptr;
        data = 0;
    }
    ////////////////////////////////////////
    node(T data, node<T>* next, node<T>* prev)
    {
        //overloaded constructor
        this->data = data;
        this->prev = prev;
        this->next = next;
    }
    template <class T>
    friend class list;
};
/////////////////////////////////////////////////////


template <class T>
class list {
private:

    node<T>* head;
    node<T>* tail;
    int len;
    ////////////////////////////////////////////

public:
    list()
    {
        // default constructor
        head = new node<T>; //making head and tail a proper node will help us lessening checks
        tail = new node<T>; // making tail a proper node in the list  
        head->next = tail; // dummy head
        tail->prev = head;
        head->prev = nullptr;
        tail->next = nullptr;// dummy tail
        len = 0;   
    }
    list(node<T>* head, node<T>* tail)
    {
        //overloaded constructor
        this->head = head;
        this->tail = tail;
    }
    void InsertatStart(T element)
    {
        
        node<T>* temp = new node<T>*(data, head->next, tail); // giving head as head->next(th) element
        head->next = temp;
        temp->next->prev = temp;
        //len = len + 1;
        len++;
    }
    void InsertatEnd(T element)
    {
        tail->prev = new node<T>(data, tail, tail->prev);
        tail->prev->prev->next = tail->prev;
        len++;
        // temp->prev->next = temp;
        //temp->next->prev = temp;
        //len++;
    }
    void deleteNode(node<T>* ptr)
    {

        node<T>* temp = head;
        while (temp != nullptr)
        {
            if (temp == ptr)
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                delete temp;
                len--;
                break;
            }
            temp = temp->next;
        }
    }
    void addNoteafter(node<T>* ptr, T  x)
    {
        node<T>* temp1 = head;
        for (int i = 0; i < len; i++)
        {
            if (temp1 == ptr)
            {
                temp1->next = new node<T>(x, temp1->next, temp1);
            }
            temp1 = temp1->next;
        }
        len++;
    }

    bool search(T v)
    {
        node<T>* temp = head->next;
        for (int i = 0; i < len; i++)
        {
            if (temp->data == v)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;

    }
    void print()
    {
        node<T>* temp = head->next;
        for (int i = 0; i < len; i++)
        {
            cout << temp->data<<" ";
            temp = temp->next;
        }
        cout << endl;
    }
    void insertAtMiddle(T const element)
    {

    }
    void reverse()
    {

    }
    ~list()
    {
        //destructor.
        node<T>* temp;
        while (head != nullptr)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
        temp = nullptr;
    }

};


int main()
{
    list<char> test;
    test.InsertatStart('x');
    test.InsertatEnd('y');
    test.print();
    cout << test.search('x') << endl;

    system("pause");
    return 0;
}