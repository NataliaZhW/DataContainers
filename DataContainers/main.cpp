//DataContainers
#include <iostream>
using namespace std;

#define delimiter "\n----------------------------------------------\n\n"
#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext) { count++; cout << "EConstructor:\t" << this << endl; }
	~Element() { count--; cout << "EDestructor:\t" << this << endl; }
	int getData()const { return Data; }
	static int getСount() { return count; } //
	Element* getPNext()const { return pNext; }
	void setData(int Data) { this->Data = Data; }
	void setPNext(Element* pNext) { this->pNext = pNext; }
	friend class ForwardList;
};
int Element::count = 0;

class ForwardList
{
protected:
	Element* Head;
	unsigned int size;
public:
	ForwardList() :Head(nullptr), size(0) { cout << "LConstructor:\t" << this << endl; }
	explicit ForwardList(int sizeL) :ForwardList()
	{
		while (sizeL--)push_front(0);
		// for (int i = 0; i < sizeL; i++) { push_front(0); }
		cout << "Constructor:\t" << this << endl;
	}

	ForwardList(const ForwardList& obg) :ForwardList() //делегируем создание пустого списка
	{
		*this = obg;	//Повторно используем код CopyAssignment
		//for (Element* Temp = obg.Head; Temp; Temp = Temp->pNext) { push_back(Temp->Data); }
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& obg) : ForwardList()
	{
		*this = std::move(obg);	//Функция std::move() принудительно вызывает MoveAssignment для класса.
		//this->Head = obg.Head;
		//this->size = obg.size;
		//obg.Head = nullptr;
		//obg.size = 0;
		cout << "MoveConstructor:\t" << this << endl;
	}

	~ForwardList() { while (Head)pop_front(); cout << "LDestructor:\t" << this << endl; }

	//                       Operators:
	ForwardList& operator =(const ForwardList& obg)
	{
		if (this == &obg)return *this;
		this->~ForwardList();
		for (Element* Temp = obg.Head; Temp; Temp = Temp->pNext) { push_back(Temp->Data); }
		cout << "CopyAssignment:\t" << this << "\n";
		return *this;
	}
	ForwardList& operator=(ForwardList&& obg)   //noexcept??
	{
		if (this == &obg) return *this;
		this->~ForwardList();
		this->Head = obg.Head;
		this->size = obg.size;
		obg.Head = nullptr;
		obg.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	const int& operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//					get  set:
	int getSize()const { return size; }
	Element* getHead()const { return Head; }
	Element* getEnd()
	{
		if (!Head) cout << "Head = nullptr" << endl;
		Element* Temp = Head;
		while (Temp->pNext) { Temp = Temp->pNext; }
		return Temp;
	}

	//					Adding elements:
	void push_front(int Data) { Head = new Element(Data, Head); size++; }//добавляет значение в начало списка
	void push_back(int Data)//добавляет значение в конец списка
	{
		if (Head == nullptr) return push_front(Data);// !!!!!!! в push_front() уже есть size++  
		else
		{
			this->getEnd()->setPNext(new Element(Data));
			size++;
		}
	}
	void pop_front()//удаляет начальный элемент списка
	{
		if (Head == nullptr) { cout << "Error" << endl; return; }
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()//удаляет последний элемент списка
	{
		if (Head == nullptr) { cout << "Error" << endl; return; }
		if (Head->pNext == nullptr)return pop_front();// !!!!!!! в pop_front() уже есть size--  
		else
		{
			Element* Temp = Head;
			while (Temp->pNext->pNext)Temp = Temp->pNext;
			delete Temp->pNext;
			Temp->pNext = nullptr;
			size--;
		}
	}
	void insert(int Index, int Data)//вставляет значение в список по заданному индексу
	{
		if (Index > size) { cout << "Error" << endl; return; }
		if (Index == 0)return push_front(Data);
		else
		{
			Element* Temp = Head;
			for (int i = 0; i < Index - 1; i++) if (Temp->pNext) Temp = Temp->pNext;
			Temp->pNext = new Element(Data, Temp->pNext);
			size++;
		}
	}
	void erase(int Index) //удаляет значение из списка по заданному индексу
	{
		if (Index > size) { cout << "Error" << endl; return; }
		if (Index == size)return pop_back();
		else
		{
			Element* Temp = Head; //Итератор 
			for (int i = 0; i < Index - 2; i++) { Temp = Temp->pNext; }//-2 т.к. перед удаляемым
			Element* erased = Temp->pNext;//указатель удаляемый элемент
			Temp->pNext = Temp->pNext->pNext;
			delete erased;
			size--;
		}
	}
	
	//					Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element::count << endl;
	}
	//friend ForwardList operator+(const ForwardList& First, const ForwardList& Second);

	ForwardList(std::initializer_list<int> d)
	{
		for (int i : d)
		{
			this->push_back(i);
		}
	}
	//ForwardList(int arr[])
	//{
	//	
	//}
};

ForwardList operator+(const ForwardList& First, const ForwardList& Second)
{
	ForwardList TempList = First;
	for (Element* iter = Second.getHead(); iter; iter = iter->getPNext())
		TempList.push_back(iter->getData());
	return TempList;
}
#define BASE_CHECK
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK




int main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	ForwardList list;
	//int n;
	//cout << "Введите воличество элементов списка: "; cin >> n;
	//for (int i = 0; i < n; i++)
	//{
	//	//list.push_front(rand() % 100);
	//	list.push_back(rand() % 100);
	//}
	for (int i = 0; i < 5; i++)
	{
		//list.push_front(rand() % 100);
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
	//int index;
	//int value;
	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.insert(index, value);
	//list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
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
#endif // COUNT_CHECK

#ifdef SIZE_CONSTRUCTOR_CHECK
	ForwardList list(5);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // SIZE_CONSTRUCTOR_CHECK

	ForwardList list4(5);
	list4.print();
	cout << delimiter << endl;

	ForwardList list1 = { 3, 5, 8, 13, 21 };
	list1.print();
	ForwardList list2 = { 34, 55, 89 };
	list2.print();
	ForwardList list3;
	list3 = list1 + list2;	//Конкатенация
	list3.print();
	cout << delimiter << endl;


}