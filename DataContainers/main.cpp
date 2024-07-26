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
	int getData()const { return Data; }
	Element* getPNext()const { return pNext; }
	void setData(int Data) { this->Data = Data; }
	void setPNext(Element* pNext) { this->pNext = pNext; }
	friend class ForwardList;
};
class ForwardList
{
protected:
	Element* Head;
	unsigned int size;
public:
	ForwardList() :Head(nullptr), size(0) { cout << "LConstructor:\t" << this << endl; }
	~ForwardList() { while (Head)pop_front(); cout << "LDestructor:\t" << this << endl; }

	ForwardList(const ForwardList& obg) :ForwardList() //делегируем создание пустого списка
	{
		for (Element* Temp = obg.Head; Temp; Temp = Temp->pNext) { push_back(Temp->Data); }
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& obg) : ForwardList()
	{
		this->Head = obg.Head;
		this->size = obg.size;
		obg.Head = nullptr;
		obg.size = 0;
		cout << "MoveConstructor:\t" << this << endl;
	}	

	ForwardList(int size) :Head(nullptr), size(0)
	{
		for (int i = 0; i < size; i++) { push_front(0); }
		cout << "Constructor:\t" << this << endl;
	}

	ForwardList& operator =(const ForwardList& obg)
	{
		if (this == &obg)return *this;
		while (Head)pop_front();

		for (Element* Temp = obg.Head; Temp; Temp = Temp->pNext) { push_back(Temp->Data); }
		cout << "CopyAssignment:\t" << this << "\n";
		return *this;
	}
	ForwardList& operator=(ForwardList&& obg)
	{
		if (this == &obg) return *this;
		while (Head)pop_front();

		this->Head = obg.Head;
		this->size = obg.size;
		obg.Head = nullptr;
		obg.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	Element* getHead()const { return Head; }
	Element* getEnd()
	{
		if (!Head) cout << "Head = nullptr" << endl;
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		return Temp;
	}
	int getSize()const { return size; }


	void push_front(int Data) { Head = new Element(Data, Head); size++; }//добавляет значение в начало списка
	void push_back(int Data)//добавляет значение в конец списка
	{
		if (Head == nullptr) return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext) { Temp = Temp->pNext; }
		Temp->pNext = new Element(Data);
		size++;
	}
	void pop_front()//удаляет начальный элемент списка
	{
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()//удаляет последний элемент списка
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Index, int Data)//вставляет значение в список по заданному индексу
	{
		if (Index == 0)return push_front(Data);
		Element* Temp = Head;
		if (Index > size) { cout << "Error" << endl; return; }
		for (int i = 0; i < Index - 1; i++)if (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(int Index) //удаляет значение из списка по заданному индексу
	{
		Element* Temp = Head; //Итератор 
		if (Index == size)return pop_back();
		if (Index > size) { cout << "Error" << endl; return; }		
		for (int i = 0; i < Index - 2; i++) { Temp = Temp->pNext; }//-2 т.к. перед удаляемым
		Element* erased = Temp->pNext;//указатель удаляемый элемент
		Temp->pNext = Temp->pNext->pNext;
		delete erased;
		size--;
	}
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
	}
	//friend ForwardList operator+(const ForwardList& First, const ForwardList& Second);

	/*ForwardList(int* arr) :ForwardList()
	{
		int size = sizeof(arr) / sizeof(int);
		for (int i = 0; i < size; i++) { push_back(arr[i]); }
		cout << "CopyConstructor:\t" << this << endl;
	};*/
};

ForwardList operator+(const ForwardList& First, const ForwardList& Second)
{
	Element* iter = Second.getHead();
	ForwardList TempList = First;
	for (; iter; iter = iter->getPNext())
		TempList.push_back(iter->getData());
	return TempList;
}



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
	list.insert(1, 1);
	list.print();
	list.erase(2);
	list.print();
	cout << list.getHead()->getData() << endl;
	cout << list.getEnd()->getData() << endl;
	cout << list.getSize() << endl;

	ForwardList list4(5);
	list4.print();

	//ForwardList list1 = { 3, 5, 8, 13, 21 };
	//list1.print();
	//ForwardList list2 = { 34, 55, 89 };
	ForwardList list3 = list + list4;	//Конкатенация
	list3.print();


}