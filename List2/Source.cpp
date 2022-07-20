#include<iostream>
using namespace std;
using std::cin;
using std::cout;


#define tab "\t"
#define delimiter "\n--------------------------------------------------\n"

class List;
class Element
{
	int Data;
	Element* pPrev;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) : Data(Data), pNext(pNext), pPrev(pPrev)
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
	friend class List;
	friend List operator+(const List& left, const List& right);
};

int Element::count = 0;

//class Iterator
//{
//	Element* Temp;
//public:
//	Iterator(Element* Temp = nullptr) : Temp(Temp)
//	{
//		cout << "ItConstructor:\t" << this << endl;
//	}
//	~Iterator()
//	{
//		cout << "ItDestructor:\t" << this << endl;
//	}
//
//	Iterator& operator++()
//	{
//		Temp = Temp->pNext;
//		return *this;
//	}
//
//	Iterator operator++(int)
//	{
//		Iterator old = *this;
//		Temp = Temp->pNext;
//		return old;
//	}
//
//	bool operator==(const Iterator& other)const
//	{
//		return this->Temp == other.Temp;
//	}
//	bool operator!=(const Iterator& other)const
//	{
//		return this->Temp != other.Temp;
//	}
//
//	const int& operator*()const
//	{
//		return Temp->Data;
//	}
//	int& operator*()
//	{
//		return Temp->Data;
//	}
//};

class List
{
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	/*Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}*/

	List()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(initializer_list<int> il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	List(const List& other) :List()
	{
		*this = other; //CopyAssignment
		cout << "CopyConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head != 0)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	List(List&& other) :List()
	{
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "MoveConstructor:\t" << this << endl;
	}

	//					Operator
	List& operator=(const List& other)
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
	List& operator=(List&& other)
	{
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	//					Adding Elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Element* New = new Element(Data);
			Head = New;
			Tail = New;
			size++;
		}
		Element* New = new Element(Data, Head);
		//New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Element* New = new Element(Data, nullptr, Head);
		New->pPrev = Tail;
		Tail->pNext = New;/*new Element(Data);*/
		Tail = New;
		size++;
	}

	//				Removing elements:
	void pop_front()
	{
		//1) ���������� ����� ���������� ��������;
		Element* erased = Head->pPrev;
		//2) ��������� ������� �� ������:
		Head = Head->pNext;
		//3) ������� ������� �� ������
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
	/*void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		if (index > size)
		{
			cout << "Error: Ount of range" << endl;
			return;
		}
		Element* Temp = Tail;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pPrev;
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}*/
	/*void erase(int index)
	{
		Element* Temp = Tail;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pPrev;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Temp->pNext;
		size--;
	}*/
	//			Methods:
	void print()const
	{

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ��������� ������: " << Element::count << endl;


	}
	friend List operator+(const List& left, const List& right);

};

List operator+(const List& left, const List& right)
{
	List cat = left;
	for (Element* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	cout << "Operator+" << endl;
	return cat;
}

#define BASE_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_ARRAY

void main()
{
	setlocale(LC_ALL, "");
	int n;
#ifdef BASE_CHECK
	cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
		//	list.push_back(rand() % 100);
	}
	list = list;
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();

	/*int index, data;
	cout << "������� ������: "; cin >> index;
	cout << "������� ��������: "; cin >> data;
	list.insert(data, index);
	list.print();
*/
/*cout << "������� ������: "; cin >> index;
list.erase(index);
list.print();*/

//ForwardList list2 = list; //CopyConstructor
	cout << delimiter << endl;
	List list2;
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
	//(���� for �� ������ ���������, ���� for ��� �����������
	for (int i : arr)
		cout << i << tab;
	cout << endl;
	//�������� 'i' ��������������� ��������� �������� ������� �������� �������.  
#endif // RANGE_BASED_ARRAY

	/*List list = { 3,5,8,13,21 };
	list.print();*/

	/*for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;*/

	/*for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;*/


	/*for (Element* Temp = begin(); Element* != end(); Temp = Temp->pNext)
	{
	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}*/
}

