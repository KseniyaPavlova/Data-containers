#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n--------------------------------------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{

			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	unsigned int size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Adding Elements:
	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail=New;
	}
	else
	{
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
	}*/
		if (Head == nullptr &&Tail == nullptr)
			Head = Tail = new Element(Data);
		else
			Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		/*	Element* New = new Element(Data);
				if (Head == nullptr && Tail == nullptr)
				{
					Head = Tail = New;
				}
				else
				{
					New->pPrev = Tail;
					Tail->pNext = New;
					}*/
		if (Head == nullptr && Tail == nullptr)
			Head = Tail = new Element(Data);
		else
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Data, int index)
	{
		if (index > size) return;
		if (index == 0) return push_front(Data);
		if (index == size) return push_back(Data);

		Element* Temp;
		if (index < size / 2)
		{
			Temp=Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size-index-1; i++)Temp = Temp->pPrev;
		}
		Temp->pPrev=Temp->pPrev->pNext = new Element(Data, Temp,Temp->pPrev);
		/*New->pNext = Temp;
		New->pPrev = Temp->pPrev;*/
		//Temp->pPrev->pNext = New;
		//Temp->pPrev = New;
		size++;
	}

	//						Removing Elements:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr) return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			Head = Head->pNext;
			delete Head->pPrev;
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		if (Head == Tail) return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index >= size)return;
		if (index == 0)return pop_front();
		/*if(index==)*/
		// 1) ������� �� ���������� ��������:
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++) Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++) Temp = Temp->pPrev;
		}
		//2) ��������� ������� �� ������:
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		//3) ������� ������� �� ������:
		delete Temp;
		size--;

	}



	//			Methods:
	void print()const
	{
		cout << "Head: " << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� " << size << endl;
	}
	void reverse_print()const
	{
		cout << "Tail: " << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	list.insert(value, index);
	list.print();
	list.reverse_print();

	cout << "������� ������ ���������� ��������: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
}