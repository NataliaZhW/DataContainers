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


	Element(const Element& obg) :Data(obg.Data), pNext(obg.pNext) 
     //нужно еще как то разбираться с предыдущим элементом
	{ count++; cout << "CopyConstructor:\t" << this << endl; }
	//Element(Element&& obg)//нужно еще как то разбираться с предыдущим элементом
	//{
	//	*this = std::move(obg);
	//	cout << "MoveConstructor:\t" << this << endl;
	//}
	//Element& operator =(const Element& obg)//нужно еще как то разбираться с предыдущим элементом
	//{
	//	if (this == &obg)return *this;
	//	this->Data = obg.Data;
	//	this->pNext = obg.pNext;
	//	cout << "CopyAssignment:\t" << this << "\n";
	//	return *this;
	//}
	//Element& operator=(Element&& obg)   //нужно еще как то разбираться с предыдущим элементом
	//{
	//	if (this == &obg) return *this;
    //	this->Data = obg.Data;
	//	this->pNext = obg.pNext;
	//	obg.Data = 0;
	//	obg.pNext = nullptr;
	//	cout << "MoveAssignment:\t" << this << endl;
	//	return *this;
	//}

	operator int() const { return this->Data; }
	//operator int() { return this->Data; }
	Element* operator ++() { return pNext; } //не работает
	Element* operator ++(int) { return pNext; }//не работает


	static int getСount() { return count; } //
	Element* getPNext()const { return pNext; }
	void setData(int Data) { this->Data = Data; }
	void setPNext(Element* pNext) { this->pNext = pNext; }
	friend class ForwardList;
};

int Element::count = 0;

ostream& operator<<(ostream& out, Element &temp)
{
	out << temp.getData();
	return out;
}



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
	ForwardList(const std::initializer_list<int>& d) : ForwardList()
	{
		for (int i : d)
		{
			this->push_back(i);
		}
		//for (const int* it = d.begin(); it != d.end(); it++)
		//{
		//	//it - iterator
		//	push_back(*it);
		//}
	}
	ForwardList(int* arr, int sizeA) : ForwardList()
	{
		for (int i = 0; i < sizeA; i++)
		{
			this->push_back(arr[i]);
		}
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
	//Element* operator ++() { return pNext; }
	//Element* operator ++(int) { return pNext; }

	//					get  set:
	int getSize()const { return size; }
	Element* getHead()const { return Head; }
	Element* begin()const { return Head; }
	Element* getEnd()const//последний элемент существующий
	{

		if (!Head) { cout << "Head = nullptr" << endl; return Head; }
		Element* Temp = Head;
		while (Temp->pNext) { Temp = Temp->pNext; }
		return Temp;
	}
	Element* end()const//указатель наа ноль после последнего элемента 
	{
		if (!Head) { cout << "Head = nullptr" << endl; return Head; }
		Element* Temp = Head;
		while (Temp->pNext) { Temp = Temp->pNext; }
		return Temp->pNext;
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


};

ForwardList operator+(const ForwardList& First, const ForwardList& Second)
{
	ForwardList TempList = First;
	for (Element* iter = Second.getHead(); iter; iter = iter->getPNext())
		TempList.push_back(iter->getData());
	return TempList;
}
void Print(int arr[])
{
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK
//#define OPERATOR_PLUS_CHECK
//#define INITIALIZER_LIST_CONSTRUCTOR_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST



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

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list4(5);
	list4.print();
	cout << delimiter;
	cout << delimiter;
	cout << delimiter << endl;

	int j[] = { 0, 5, 0, 13, 0 };
	ForwardList list0(j, sizeof(j) / sizeof(int));
	list0.print();
	cout << delimiter;
	cout << delimiter;
	cout << delimiter << endl;
	ForwardList list1 = { 3, 5, 8, 13, 21 };
	list1.print();
	ForwardList list2 = { 34, 55, 89 };
	list2.print();
	ForwardList list3;
	list3 = list1 + list2;	//Конкатенация
	cout << delimiter << endl;
	cout << delimiter << endl;
	list3.print();
	cout << delimiter << endl;
#endif // OPERATOR_PLUS_CHECK


#ifdef INITIALIZER_LIST_CONSTRUCTOR_CHECK
	ForwardList list1 = { 3, 5, 8, 13, 21 };
	list1.print();
#endif // INITIALIZER_LIST_CONSTRUCTOR_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	//int* arr = new int[5] {3, 5, 8, 13, 21};
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Range-based for:
	for (int i : arr)
	{
		cout << i << tab;
	}
	//Range - это диапазон. Под данным термином в этом контексте понимают контейнер,
	//т.е., контейнеры иногда нзывают 'range'.
	//Следовательно, Range-based for - это цикл for для контейнеров.
	//https://legacy.cplusplus.com/doc/tutorial/control/#:~:text=equal%20to%2050.-,Range%2Dbased%20for%20loop,-The%20for%2Dloop
	cout << endl;

	cout << typeid(arr).name() << endl;
	Print(arr);
	//delete[] arr;  
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list1 = { 3, 5, 8, 13, 21, 55};
	list1.print();
	cout << list1.begin()->getData() << "\n";
	cout << list1.getEnd()->getData() << "\n";
	cout << list1.end() << "\n";
	
	//for (const auto& i : list1) //не работает
	//{
	//	cout << i.getData() << tab;
	//}
	
	//for (auto i = list1.begin(); i != list1.end(); i++)//не работает
	//for (int i : list1)		
	//{
	//	cout << i << tab;
	//}
	//cout << endl;

	Element el(333, 0);
	cout << el << endl << endl;
	
	cout << delimiter;
	cout << list1[1] <<  endl;
	Element* el2=list1.begin();
	
	cout << el2->getData() << endl;
	cout << (++el2)->getData() << endl;
	cout << sizeof(list1) << endl;// всегда одинаковое 16
	
	int a = list1[5];
	cout << a << endl;

#endif // RANGE_BASED_FOR_LIST
}