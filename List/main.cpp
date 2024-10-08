﻿
#include <iostream>
using namespace std;

#define delimiter "\n----------------------------------------------\n\n"
#define tab "\t"


class List
{
	class Element
	{
		int Data;		//значение элемента
		Element* pNext;	//указатель на следующий элемент
		Element* pPrev;	//указатель на предыдущий элемент
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev) {}
		~Element() {}
		friend class List;
	}*Head, * Tail;	//объекты класса можно объявлять непосредственно после его описания.
	//Element* Head;
	//Element* Tail;
	size_t size;	//size_t - это typedef на 'unsigned int'.
	//Директива 'typedef' создает псевдоним для существующего типа данных.
	//typedef имеет следующий синтаксис:
	//				typedef существующий_тип_данных псевдоним
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}

		//				Comparison operators:
		bool operator==(const ConstBaseIterator& other)const { return this->Temp == other.Temp; };
		bool operator!=(const ConstBaseIterator& other)const { return this->Temp != other.Temp; };

		const int& operator*()const { return Temp->Data; };
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
		
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++()
		{
			//Prefix increment
			Temp = Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			//Suffix increment
			ConstIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		//				Comparison operators:
		//bool operator==(const Iterator& other)const { return this->Temp == other.Temp; }
		//bool operator!=(const Iterator& other)const { return this->Temp != other.Temp; }

		//const int& operator*()const { return Temp->Data; }
		//int& operator*() { return Temp->Data; }
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		//				Increment/Decrement:
		ConstReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		//				Comparison operators:
		bool operator==(const ConstReverseIterator& other)const { return this->Temp == other.Temp; }
		bool operator!=(const ConstReverseIterator& other)const { return this->Temp != other.Temp; }

		//		Dereference operators (Операторы разыменования):
		//const int& operator*()const { return Temp->Data; }
		//int& operator*() { return Temp->Data; }

	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		int& operator*() { return Temp->Data; };
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		int& operator*() { return Temp->Data; };
	};

	ConstIterator begin()const { return Head; };
	Iterator begin() { return Head; };

	ConstIterator end()const { return nullptr; };
	Iterator end() { return nullptr; };

	ConstReverseIterator rbegin()const { return Tail; };
	ReverseIterator rbegin() { return Tail; };

	ConstReverseIterator rend()const { return nullptr; };
	ReverseIterator rend() { return nullptr; };




	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:" << this << endl;
	}
	~List() { while (Tail)pop_back(); cout << "LDestructor:\t" << this << endl; }

	//						Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}

	//						Adding elements:
	void push_front(int Data)//добавляет значение в начало списка
	{
		if (Head == nullptr && Tail == nullptr) { Head = Tail = new Element(Data); }
		else
		{
			//1) Создаем новый элемент:
			//2) Привязываем новый элемент к началу списка:
			//4) Смещаем Голову на новый элемент:
			//3) Привязываем теперь второй элемент списка к новому, теперь первому, элементу:
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;
	}
	void push_back(int Data)//добавляет значение в конец списка
	{
		if (Head == nullptr && Tail == nullptr) { Head = Tail = new Element(Data); }
		else
		{
			//1) Создаем новый элемент:
			//2) Привязываем новый элемент к концу списка:
			//4) Смещаем хвост на новый элемент:
			//3) Привязываем теперь второй с конца элемент списка к новому, теперь первому с конца, элементу:
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size)return;
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}

		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}

	//					Removing elements:
	void pop_front()//удаляет начальный элемент списка
	{
		if (Head == nullptr) { cout << "Error" << endl; return; }
		if (size == 1)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			//1) Смещаем Голову на следующий элемент:
			Head = Head->pNext;

			//2) Удаляем элемент 'Head->pPrev' из памяти:
			delete Head->pPrev;

			//3) Зануляем указатель 'Head->pPrev':
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()//удаляет последний элемент списка
	{
		if (Head == nullptr) { cout << "Error" << endl; return; }
		if (size == 1)
		{
			delete Tail;
			Head = Tail = nullptr;
		}
		//if (Head == Tail)return pop_front();
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
	void erase(int num)
	{
		if (num >= size - 1)return pop_back();
		if (num == 0)return pop_front();
		Element* Temp = Head;
		if (num <= size / 2)
			for (int i = 0; i < num; i++)
				Temp = Temp->pNext;
		else
		{
			Temp = Tail;
			for (int i = num; i < size - 1; i++)
				Temp = Temp->pPrev;
		}
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete Temp;
		size--;
	}

	//					Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке: " << size << endl;
	}
};
List operator+(const List& left, const List& right)
{
	List buffer = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}

//#define BASE_CHECK
//#define ITERATORS_CHECK
#define OPERATOR_PLUS_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();
	cout << delimiter;

	list.push_back(33);
	list.push_front(33);
	list.print();
	cout << delimiter;

	list.pop_back();
	list.pop_front();
	list.print();
	int index;
	int value;

	//cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	//cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.erase(index);
	//list.insert(value, index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)cout << i << tab; cout << endl;

	//List::Iterator it;
	//const int jt = *it;

	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK


#ifdef OPERATOR_PLUS_CHECK
	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	for (int i : list1) cout << i << tab; cout << endl;
	for (int i : list2) cout << i << tab; cout << endl;
	for (int i : list3) cout << i << tab; cout << endl;

	for (List::Iterator it = list3.begin(); it != list3.end(); ++it)
	{
		*it *= 100;
	}
	for (int i : list3) cout << i << tab; cout << endl;
#endif // OPERATOR_PLUS_CHECK






}