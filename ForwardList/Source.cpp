﻿#include<iostream>
using namespace std;
using std::cin;
using std::cout;


#define tab "\t"
#define delimiter "\n--------------------------------------------------\n"

class ForwardList;
class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class Iterator;
	friend class ForwardList;
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);
};

int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}
	int& operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;//Голова списка
	unsigned int size;
public:
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	ForwardList()
	{
		Head = nullptr; //Когда голова списка указывает на 0 - список пуст
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(initializer_list<int> il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp -> pNext;
		}*/
		*this = other; //CopyAssignment
		cout << "CopyConstructor:\t" << this << endl;

		/*Head == nullptr;
		size = 0;*/
	}
	~ForwardList()
	{
		while (Head != 0)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}

	//					Operator
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;
		while (Head)pop_front();
		Element* Temp = other.Head;
		while (Temp)
		{
			push_back(Temp->Data);
			Temp = Temp->pNext;
		}
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	//					Adding Elements:
	void push_front(int Data) //Добавление элемента в начало списка
	{
		//1) Создаем новый элемент;
		//Element* New = new Element(Data);
		////2) Присоедяем новый элемент к началу списка
		//New->pNext = Head;
		//3) Говорим, что новый элемент является головой списка
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Дойти до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//3) Присоединяем новый элемент к списку:
		Temp->pNext = new Element(Data);
		size++;
	}

	//				Removing elements:
	void pop_front()
	{
		//1) Запоминаем адрес удаляемого элемента;
		Element* erased = Head;
		//2) Исключаем элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из памяти
		delete erased;
		size--;
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Data, int index)
	{
		//index -= 1;
		if (index == 0)return push_front(Data);
		if (index = size)return push_back(Data);
		if (index > size)
		{
			cout << "Error: Ount of range" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Temp->pNext;
		size--;
	}
	//			Methods:
	void print()const
	{

		//Element* Temp = Head; //Temp - это итератор
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //переход на следующий элемент
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;


	}
	friend ForwardList operator+(const ForwardList& left, const ForwardList& right);

};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat = left;
	//Element* Temp = right.Head;
	//while (Temp)
	//{
	//	cat.push_back(Temp->Data);
	//	Temp = Temp -> pNext;
	//}
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	cout << "Operator+" << endl;
	return cat;
}

//#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_ARRAY

void main()
{
	setlocale(LC_ALL, "");
	int n;
#ifdef BASE_CHECK
	cout << "Введите размер списка: "; cin >> n;
	int arr[5];
	ForwardList list; //Создали односвязный список list
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list = list;
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();

	int index, data;
	cout << "Введите индекс: "; cin >> index;
	cout << "Введите значение: "; cin >> data;
	list.insert(data, index);
	list.print();

	/*cout << "Введите индекс: "; cin >> index;
	list.erase(index);
	list.print();*/

	//ForwardList list2 = list; //CopyConstructor
	cout << delimiter << endl;
	ForwardList list2;
	cout << delimiter << endl;
	list2 = list;
	list2.print();
#endif // BASE_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

	cout << delimiter << endl;
	//ForwardList list3 = list1 + list2;
	ForwardList list3;
	list3 = list1 + list2;
	cout << delimiter << endl;
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
		cout << arr[i] << tab;
	cout << endl;

	//rahge-based for 
	//(цикл for на основе диапазона, цикл for для контейнеров
	for (int i : arr)
		cout << i << tab;
	cout << endl;
	//Итератор 'i' последовательно принимает значение каждого элемента массива.  
#endif // RANGE_BASED_ARRAY

	ForwardList list = { 3,5,8,13,21 };
	list.print();

	for (int i: list)
	{
		cout << i << tab;
	}
	cout << endl;
	
	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;


	/*for (Element* Temp = begin(); Element* != end(); Temp = Temp->pNext)
	{
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}*/
}

