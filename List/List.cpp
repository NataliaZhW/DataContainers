#include"List.h"

//--------------------------------------------------------------------------//

/// ///////////////////////////////////////////////////////////////////// ///
/// /////////		Class definition                    		///////// ///


////////////////////////////////////////////////////////////////////////////

template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev) {}
template<typename T>List<T>::Element::~Element() {}

//				Comparison operators:
template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T>const T& List<T>::ConstBaseIterator::operator*()const { return Temp->Data; }


//							Const iterator:
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

//						Const reverse iterator:
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator  List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator  List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}


//							  Iterator:
template<typename T>T& List<T>::Iterator::operator*() { return ConstBaseIterator::Temp->Data; }

//						   ReverseIterator:
template<typename T>T& List<T>::ReverseIterator::operator*() { return ConstBaseIterator::Temp->Data; }

////////////			  Iterators methods:					////////////
////////////////////////////////////////////////////////////////////////////

/// -------------------------------------------------------------------- ///

////////////////////////////////////////////////////////////////////////////
////////////				List methods:						////////////
template<typename T>typename List<T>::ConstIterator List<T>::begin()const { return Head; }
template<typename T>typename List<T>::Iterator List<T>::begin() { return Head; }

template<typename T>typename List<T>::ConstIterator List<T>::end()const { return nullptr; }
template<typename T>typename List<T>::Iterator List<T>::end() { return nullptr; }

template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const { return Tail; }
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin() { return Tail; }

template<typename T>typename List<T>::ConstReverseIterator List<T>::rend()const { return nullptr; }
template<typename T>typename List<T>::ReverseIterator List<T>::rend() { return nullptr; }

template<typename T>List<T>::List() { Head = Tail = nullptr;	size = 0; }

template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		//push_front(*it);
		push_back(*it);
	}
}
template<typename T>List<T>::List(const List<T>& other) :List() { *this = other; }
template<typename T>List<T>::~List() { while (Tail)pop_back(); }

//						Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	return *this;
}


//						Adding elements:
template<typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr) { Head = Tail = new Element(Data); }
	else { Head = Head->pPrev = new Element(Data, Head); }
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr) { Head = Tail = new Element(Data); }
	else { Tail = Tail->pNext = new Element(Data, nullptr, Tail); }
	size++;
}
template<typename T>void List<T>::insert(T Data, int Index)
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
template<typename T>void List<T>::pop_front()
{
	if (Head == nullptr) { cout << "Error" << endl; return; }
	if (size == 1) { delete Head;		Head = Tail = nullptr; }
	else
	{
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == nullptr) { cout << "Error" << endl; return; }
	if (size == 1)
	{
		delete Tail;
		Head = Tail = nullptr;
	}
	else
	{
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
	}
	size--;
}
template<typename T>void List<T>::erase(int num)
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
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов в списке: " << size << endl;
}
template<typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов в списке: " << size << endl;
}
////////////				List methods:						////////////
////////////////////////////////////////////////////////////////////////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List buffer = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);		
	}
	return buffer;
}
/// /////////              Class definition end               	///////// ///
/// ///////////////////////////////////////////////////////////////////// ///