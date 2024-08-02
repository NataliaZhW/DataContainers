
#include <iostream>
using namespace std;

#define delimiter "\n----------------------------------------------\n\n"
#define tab "\t"


class List
{
	class Element
	{
		int Data;		//�������� ��������
		Element* pNext;	//��������� �� ��������� �������
		Element* pPrev;	//��������� �� ���������� �������
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element() { cout << "EDestructor:\t" << this << endl; }
		friend class List;
	}*Head, * Tail;	//������� ������ ����� ��������� ��������������� ����� ��� ��������.
	//Element* Head;
	//Element* Tail;
	size_t size;	//size_t - ��� typedef �� 'unsigned int'.
	//��������� 'typedef' ������� ��������� ��� ������������� ���� ������.
	//typedef ����� ��������� ���������:
	//				typedef ������������_���_������ ���������
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List() { cout << "LDestructor:\t" << this << endl; }

	//						Adding elements:
	void push_front(int Data)//��������� �������� � ������ ������
	{
		if (Head == nullptr && Tail == nullptr) { Head = Tail = new Element(Data); }
		else
		{
			//1) ������� ����� �������:
			//2) ����������� ����� ������� � ������ ������:
			//4) ������� ������ �� ����� �������:
			Head = new Element(Data, Head, nullptr);
			//3) ����������� ������ ������ ������� ������ � ������, ������ �������, ��������:
			Head->pNext->pPrev = Head;
		}
		size++;
	}
	void push_back(int Data)//��������� �������� � ����� ������
	{
		if (Head == nullptr && Tail == nullptr) { Head = Tail = new Element(Data); }
		else
		{
			//1) ������� ����� �������:
			//2) ����������� ����� ������� � ����� ������:
			//4) ������� ����� �� ����� �������:
			Tail = new Element(Data, nullptr, Tail);
			//3) ����������� ������ ������ � ����� ������� ������ � ������, ������ ������� � �����, ��������:
			Tail->pPrev->pNext = Tail;
		}
		size++;
	}

	void pop_front()//������� ��������� ������� ������
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
	void pop_back()//������� ��������� ������� ������
	{
		if (Head == nullptr) { cout << "Error" << endl; return; }
		if (Head->pNext == nullptr)return pop_front();// !!!!!!! � pop_front() ��� ���� size--  
		else
		{
			Element* Temp = Head;
			while (Temp->pNext->pNext)Temp = Temp->pNext;
			delete Temp->pNext;
			Temp->pNext = nullptr;
			size--;
		}
	}


	? ? ? pop_back(? ? ? );		//������� ��������� ������� ������	DONE

	//					Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� � ������: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� � ������: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();
}