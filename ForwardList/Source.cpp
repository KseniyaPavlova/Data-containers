﻿#include<iostream>
using namespace std;

#define tab "\t"


class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};


class ForwardList
{
	Element* Head; //Голова списка
public:
	ForwardList()
	{
		Head = nullptr; //Когда голова списка указывает на 0 - список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head != 0)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Adding Elements:
	void push_front(int Data) //Добавление элемента в начало списка
	{
		//1) Создаем новый элемент;
		Element* New = new Element(Data);
		//2) Присоедяем новый элемент к началу списка
		New->pNext = Head;
		//3) Говорим, что новый элемент является головой списка
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) Дойти до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		//3) Присоединяем новый элемент к списку:
		Temp->pNext = New;
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
	}
	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void insert(int Data, int index)
	{
		//index -= 1;
		Element* New = new Element(Data);
		Element* Temp = Head;
			for (int i = 0;i < index-1; i++)Temp = Temp->pNext;
			New->pNext = Temp->pNext;
			Temp->pNext = New;
			//Temp = Temp->pNext;
	}
	void erase (int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Temp->pNext =Temp->pNext->pNext;
	/*	delete Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;*/
	}
		//			Methods:
		void print()const
		{

			Element* Temp = Head; //Temp - это итератор
			while (Temp)
			{
				cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
				Temp = Temp->pNext; //переход на следующий элемент
			}
		}

	};

	void main()
	{
		setlocale(LC_ALL, "");
		int n;
		cout << "Введите размер списка: "; cin >> n;
		int arr[5];
		ForwardList list; //Создали односвязный список list
		for (int i = 0; i < n; i++)
		{
			//list.push_front(rand() % 100);
			list.push_back(rand() % 100);
		}
		list.print();
		/*list.pop_front();
		list.pop_back();
		list.print();*/

		int index, data;
		/*cout << "Введите индекс: "; cin >> index;
		cout << "Введите значение: "; cin >> data;
		list.insert(data,index);
		list.print();*/

		cout << "Введите индекс: "; cin >> index;
		list.erase(index);
		list.print();
	}

