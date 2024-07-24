//DataContainers
#include <iostream>
using namespace std;

#define delimiter "\n----------------------------------------------\n\n"
#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) { cout << "EConstructor:\t" << this << endl; }
	~Element() { cout << "EDestructor:\t" << this << endl; }
	friend class ForwardList;
};
class ForwardList
{
protected:
	Element* Head;
	unsigned int size;
public:
	ForwardList() :Head(nullptr), size(0) { cout << "LConstructor:\t" << this << endl; }
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	void push_front(int Data) { Head = new Element(Data, Head); }
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element(Data);
	}
	void pop_front()
	{
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void insert(int Index, int Data)//вставляет значение в список по заданному индексу
	{
		if (Index == 0)return push_front(Data);
		Element* Temp = Head;
		int size = 0;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
			size++;
		}
		if (Index > size)
		{
			cout << "Error" << endl;
			return;
		}
		Temp = Head;
		for (int i = 0; i < Index - 1; i++)if (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
	}
	void erase(int Index) //удаляет значение из списка по заданному индексу
	{
		Element* Temp = Head; //Итератор 
		int size = 0;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
			size++;
		}
		if (Index == size)return pop_back();
		if (Index > size)
		{
			cout << "Error" << endl;
			return;
		}
		Temp = Head; //Возврат к голове
		 
		for (int i = 0; i < Index - 2; i++)//(перед удаляемым)
		{
			Temp = Temp->pNext; 
		}
		Element* erased = Temp->pNext;//указатель удаляемый элемент
		Temp->pNext = Temp->pNext->pNext; 
		//////Запуталась 
		delete erased;
	}
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
};
	int main()
	{
		setlocale(LC_ALL, "");
		ForwardList list;
		for (int i = 0; i < 5; i++)
		{		
			list.push_back(rand() % 100);
		}
		list.print();
		list.push_back(3);
		list.push_front(3);
		list.print();
		list.pop_back();
		list.print();
		list.insert(1,1);
		list.print();
		list.erase(2);
		list.print();

	}