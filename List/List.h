#pragma once

#include <iostream>
//#include<string>

using namespace std;

#define delimiter "\n----------------------------------------------\n\n"
#define tab "\t"

/// ///////////////////////////////////////////////////////////////////// ///
/// /////////		Class declaration                    		///////// ///

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;	

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {};
		~ConstBaseIterator() {};

		//				Comparison operators:
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;

		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {};
		~ConstIterator() {};

		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {};
		~ConstReverseIterator() {};

		//				Increment/Decrement:
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {};
		~Iterator() {};
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp) {};
		~ReverseIterator() {};
		T& operator*();
	};

	ConstIterator begin()const;
	Iterator begin();

	ConstIterator end()const;
	Iterator end();

	ConstReverseIterator rbegin()const;
	ReverseIterator rbegin();

	ConstReverseIterator rend()const;
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//						Operators:
	List<T>& operator=(const List<T>& other);

	//						Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//					Removing elements:
	void pop_front();
	void pop_back();
	void erase(int num);

	//					Methods:
	void print()const;
	void reverse_print()const;
};
/// /////////            Class declaration end                   ///////// ///
/// ////////////////////////////////////////////////////////////////////// ///