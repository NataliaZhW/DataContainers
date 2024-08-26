//DataContainers
#include <iostream>
using namespace std;

#define delimiter "\n----------------------------------------------\n\n"
#define tab "\t"

template<typename T>class Element
{
	T Data;
	Element* pNext;
	static int count;
public:
	Element(T Data) :Data(Data), pNext(nullptr) { count++; cout << "EConstructor:\t" << this << endl; }
	Element(T Data, Element<T>* pNext) :Data(Data), pNext(pNext) { count++; cout << "EConstructor:\t" << this << endl; }
	~Element() { count--; cout << "EDestructor:\t" << this << endl; }
	T getData()const { return Data; }

	//operator T() const { return this->Data; }
	static T getСount() { return count; } //
	//void setData(T Data) { this->Data = Data; }
	template<typename T>friend class Iterator;
	template<typename T>friend class ForwardList;
};

template<typename T> int Element<T>::count = 0;

template<typename T>ostream& operator<<(ostream& out, Element<T>& temp)
{
	out << temp.getData();
	return out;
}

template<typename T>class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp) :Temp(Temp) { cout << "IConstructor:\t" << this << endl; }
	~Iterator() { cout << "IDestructor:\t" << this << endl; }
	Iterator& operator++() { Temp = Temp->pNext; return *this; }
	Iterator operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator<T>& other)const { return this->Temp == other.Temp; }
	bool operator!=(const Iterator<T>& other)const { return this->Temp != other.Temp; }
	T operator*()const { return Temp->Data; }
	T& operator*() { return Temp->Data; }

	//template<typename T>friend class ForwardList;
};


template<typename T> class ForwardList
{
protected:
	Element<T>* Head;
	unsigned int size;
public:
	ForwardList() :Head(nullptr), size(0) { cout << "LConstructor:\t" << this << endl; }
	explicit ForwardList(int sizeL) :ForwardList()
	{
		while (sizeL--)push_front(0);
		cout << "Constructor:\t" << this << endl;
	}
	ForwardList(const ForwardList<T>& obg) :ForwardList() //делегируем создание пустого списка
	{
		*this = obg;	//Повторно используем код CopyAssignment
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList<T>&& obg) : ForwardList()
	{
		*this = std::move(obg);	//Функция std::move() принудительно вызывает MoveAssignment для класса.	
		cout << "MoveConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<T>& d) : ForwardList()
	{
		for (T i : d) { this->push_back(i); }
	}
	~ForwardList() { while (Head)pop_front(); cout << "LDestructor:\t" << this << endl; }

	//                       Operators:
	ForwardList<T>& operator =(const ForwardList<T>& obg)
	{
		if (this == &obg)return *this;
		this->~ForwardList();
		for (Element<T>* Temp = obg.Head; Temp; Temp = Temp->pNext) { push_back(Temp->Data); }
		cout << "CopyAssignment:\t" << this << "\n";
		return *this;
	}
	ForwardList<T>& operator=(ForwardList<T>&& obg)   //noexcept??
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
	T& operator[](int index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	const T& operator[](int index)const
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//					get  set:
	Iterator<T> begin() { return Head; }
	Iterator<T> end() { return nullptr; }
	int getSize()const { return size; }
	Element<T>* getHead()const { return Head; }
	Element<T>* getEnd()const//последний элемент существующий
	{

		if (!Head) { cout << "Head = nullptr" << endl; return Head; }
		Element<T>* Temp = Head;
		while (Temp->pNext) { Temp = Temp->pNext; }
		return Temp;
	}

	//					Adding elements:
	void push_front(T Data) { Head = new Element<T>(Data, Head); size++; }//добавляет значение в начало списка
	void push_back(T Data)//добавляет значение в конец списка
	{
		if (Head == nullptr) return push_front(Data);// !!!!!!! в push_front() уже есть size++  
		else
		{
			Element<T>* Temp = Head;
			while (Temp->pNext)	Temp = Temp->pNext;
			Temp->pNext = new Element<T>(Data);
			size++;
		}
	}
	void pop_front()//удаляет начальный элемент списка
	{
		if (Head == nullptr) { cout << "Error" << endl; return; }
		Element<T>* Temp = Head;
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
			Element<T>* Temp = Head;
			while (Temp->pNext->pNext)Temp = Temp->pNext;
			delete Temp->pNext;
			Temp->pNext = nullptr;
			size--;
		}
	}
	void insert(int Index, T Data)//вставляет значение в список по заданному индексу
	{
		if (Index > size) { cout << "Error" << endl; return; }
		if (Index == 0)return push_front(Data);
		else
		{
			Element<T>* Temp = Head;
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
			Element<T>* Temp = Head; //Итератор 
			for (int i = 0; i < Index - 2; i++) { Temp = Temp->pNext; }//-2 т.к. перед удаляемым
			Element<T>* erased = Temp->pNext;//указатель удаляемый элемент
			Temp->pNext = Temp->pNext->pNext;
			delete erased;
			size--;
		}
	}

	//					Methods:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << *Temp << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element<T>::count << endl;
	}
	//friend ForwardList operator+(const ForwardList& First, const ForwardList& Second);


};

template<typename T>ForwardList<T> operator+(const ForwardList<T>& First, const ForwardList<T>& Second)
{
	ForwardList<T> TempList = First;
	for (Element<T>* iter = Second.getHead(); iter; iter = iter->getPNext())
		TempList.push_back(iter->getData());
	return TempList;
}
//template<typename T>void Print(T arr[])
//{
//	cout << typeid(arr).name() << endl;
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
//	{
//		cout << arr[i] << tab;
//	}
//	cout << endl;
//}

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
	ForwardList<int> list1 = { 3, 5, 8, 13, 21, 55 };

	list1.print();
	/*cout << list1.getEnd()->getData() << "\n";

	for (int i : list1)
	{
		cout << i << tab;
	}
	cout << endl;

	Element<int> el(333, 0);
	cout << el.getData() << endl << endl;
*/
	cout << delimiter;
	//cout << list1[1] << endl;
	//Element<int>* el2 = list1.getHead();

	//cout << el2->getData() << endl;
	//cout << sizeof(list1) << endl;// всегда одинаковое 16

	//int a1 = list1[5];
	//cout << a1 << endl;
	//
	ForwardList<double> d_list = { 2.7, 3.14, 5.5, 8.3 };
	d_list.print();
	cout << d_list.getEnd()->getData() << "\n";

	for (double i : d_list)
	{
		cout << i << tab;
	}
	cout << endl;

	Element<double> el8(333.2);
	cout << el8 << endl << endl;

	cout << delimiter;
	cout << d_list[1] << endl;
	Element<double>* el9 = d_list.getHead();

	cout << el9->getData() << " !!!!!!" << endl;
	cout << sizeof(d_list) << endl;// всегда одинаковое 16

	double a = d_list[1];
	cout << a << endl;

	ForwardList<std::string> s_list = { "Хорошо", "живет", "на", "свете", "Винни", "Пух" };
	cout << s_list[1] << endl;

#endif // RANGE_BASED_FOR_LIST
}