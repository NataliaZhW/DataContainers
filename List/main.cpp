
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
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() { cout << "EDestructor:\t" << this << endl; }
		friend class List;
	}*Head, * Tail;	//объекты класса можно объявлять непосредственно после его описания.
	//Element* Head;
	//Element* Tail;
	size_t size;	//size_t - это typedef на 'unsigned int'.
	//Директива 'typedef' создает псевдоним для существующего типа данных.
	//typedef имеет следующий синтаксис:
	//				typedef существующий_тип_данных псевдоним
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List() { cout << "LDestructor:\t" << this << endl; }

	//						Adding elements:
	void push_front(int Data)//добавляет значение в начало списка
	{
		if (Head == nullptr && Tail == nullptr) { Head = Tail = new Element(Data); }
		else
		{
			//1) Создаем новый элемент:
			//2) Привязываем новый элемент к началу списка:
			//4) Смещаем Голову на новый элемент:
			Head = new Element(Data, Head, nullptr);
			//3) Привязываем теперь второй элемент списка к новому, теперь первому, элементу:
			Head->pNext->pPrev = Head;
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
			Tail = new Element(Data, nullptr, Tail);
			//3) Привязываем теперь второй с конца элемент списка к новому, теперь первому с конца, элементу:
			Tail->pPrev->pNext = Tail;
		}
		size++;
	}

	void pop_front()//удаляет начальный элемент списка
	{
		if (Head == nullptr) { cout << "Error" << endl; return; }
		if (size == 1)
		{
			Tail = 0;
		}
		Element* Temp = Head;
		Head = Head->pNext;
		Head->pPrev = nullptr;
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


	? ? ? pop_back(? ? ? );		//удаляет последний элемент списка	DONE

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

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();
}