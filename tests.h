#pragma once
#include"Stack.h"
#include<iostream>

using namespace std;
template <class T>
T Stack<T>:: rfun(T value1, T value2)
{
	return value1 * 2 + value2;
}

template <class T>
T Stack<T>::mfun(T value)
{
	return value * 3;
}

template <class T>
bool Stack<T>::wfun(T value)
{
	if (value != 2)
		return true;
	return false;
}
void MapTest()
{
	cout << "***************************************" << endl;
	cout << "Function 'Map' testing (type: int)\n" << endl;
	int arr[4] = { 1, 2, 3, 4 };
	Sequence<int>* seq = new ArraySequence<int>(arr, 4);
	Stack<int>* ob1 = new Stack<int>(arr, 4);
	Stack<int>* ob2 = new Stack<int>(*ob1);
	Stack<int>* ob3 = new Stack<int>();
	Stack<int>* ob4 = new Stack<int>(seq);

	cout << "Starting meanings of objects:\n" << endl;
	cout << "Object 1 ";
	ob1->Print();
	cout << "Object 2 (copy of Object 2) ";
	ob2->Print();
	cout << "Object 3 (Empty Stack)" << endl;
	cout << "Object 4 (Stack of length 3 with undefined meanings)\n" << endl;

	cout << "----------------------------------------" << endl;
	cout << "Using function 'Map'\n" << endl;

	Stack<int>* mob1 = ob1->Map(mfun);
	cout << "Object 1 (modified) ";
	mob1->Print();

	Stack<int>* mob2 = ob2->Map(mfun);
	cout << "Object 2 (copy of Object 2)(modified) ";
	mob2->Print();

	try
	{
		Stack<int>* mob3 = ob3->Map(mfun);
		cout << "Object 3 (Empty Stack)(modified) " << endl;
		mob3->Print();

	}
	catch (out_of_range error)
	{
		cout << "Object 3 is empty. Impossible operation." << endl;
	};

	try
	{
		Stack<int>* mob4 = ob4->Map(mfun);
		cout << "Object 4 (Stack of length 3 with undefined meanings)(modified) " << endl;
		mob4->Print();
	}
	catch (invalid_argument error)
	{
		cout << "Object 4 of length 3 with undefined meanings. Impossible operation.\n" << endl;
	};

	cout << "----------------------------------------" << endl;
	cout << "Expected output:\n" << endl;
	cout << "Object 1: aaa bbb ccc ddd" << endl;
	cout << "Object 2 (copy of Object 2): aaa bbb ccc ddd" << endl;
	cout << "Object 3 (Empty Stack): IndexError" << endl;
	cout << "Object 4 (Stack of length 3 with undefined meanings): ValueError\n" << endl;

	cout << "***************************************" << endl;

}

void WhereTest()
{
	cout << "***************************************" << endl;
	cout << "Function 'Where' testing (type: int)\n" << endl;

	int arr[4] = { 1, 2, 3, 4 };
	Sequence<int>* seq = new ArraySequence<int>(arr, 4);
	Stack<int>* ob1 = new Stack<int>(arr, 4);
	Stack<int>* ob2 = new Stack<int>(*ob1);
	Stack<int>* ob3 = new Stack<int>();
	Stack<int>* ob4 = new Stack<int>(seq);

	cout << "Starting meanings of objects:\n" << endl;
	cout << "Object 1 ";
	ob1->Print();
	cout << "Object 2 (copy of Object 2) ";
	ob2->Print();
	cout << "Object 3 (Empty Stack)" << endl;
	cout << "Object 4 (Stack of length 3 with undefined meanings)\n" << endl;

	cout << "----------------------------------------" << endl;
	cout << "Using function 'Where'\n" << endl;

	Stack<int>* mob1 = ob1->Where(wfun);
	cout << "Object 1 (modified) ";
	mob1->Print();

	Stack<int>* mob2 = ob2->Where(wfun);
	cout << "Object 2 (copy of Object 2)(modified) ";
	mob2->Print();

	try
	{
		Stack<int>* mob3 = ob3->Where(wfun);
		cout << "Object 3 (Empty Stack)(modified) " << endl;
		mob3->Print();

	}
	catch (out_of_range error)
	{
		cout << "Object 3 is empty. Impossible operation." << endl;
	};

	try
	{
		Stack<int>* mob4 = ob4->Where(wfun);
		cout << "Object 4 (Stack of length 3 with undefined meanings)(modified) " << endl;
		mob4->Print();
	}
	catch (invalid_argument error)
	{
		cout << "Object 4 of length 3 with undefined meanings. Impossible operation.\n" << endl;
	};

	cout << "----------------------------------------" << endl;
	cout << "Expected output:\n" << endl;
	cout << "Object 1: a b d" << endl;
	cout << "Object 2 (copy of Object 2): a b d" << endl;
	cout << "Object 3 (Empty Stack): IndexError" << endl;
	cout << "Object 4 (Stack of length 3 with undefined meanings): ValueError\n" << endl;

	cout << "***************************************" << endl;
}

void ReduceTest()
{
	cout << "***************************************" << endl;
	cout << "Function 'Reduce' testing (type: int)\n" << endl;

	int arr[4] = { 1, 2, 3, 4 };
	Sequence<int>* seq = new ArraySequence<int>(arr, 4);
	Stack<int>* ob1 = new Stack<int>(arr, 4);
	Stack<int>* ob2 = new Stack<int>(*ob1);
	Stack<int>* ob3 = new Stack<int>();
	Stack<int>* ob4 = new Stack<int>(seq);

	cout << "Starting meanings of objects:\n" << endl;
	cout << "Object 1 ";
	ob1->Print();
	cout << "Object 2 (copy of Object 2) ";
	ob2->Print();
	cout << "Object 3 (Empty Stack)" << endl;
	cout << "Object 4 (Stack of length 3 with undefined meanings)\n" << endl;

	cout << "----------------------------------------" << endl;
	cout << "Using function 'Reduce'\n" << endl;

	int result1 = ob1->Reduce(rfun,3);
	cout << "Object 1-result ";
	cout << result1;
	cout << endl;

	int result2 = ob2->Reduce(rfun,3);
	cout << "Object 2 (copy of Object 2)-result ";
	cout << result2;
	cout << endl;

	try
	{
		int result3 = ob3->Reduce(rfun,3);
		cout << "Object 3 (Empty Stack)-result " << endl;
		cout << result3;

	}
	catch (out_of_range error)
	{
		cout << "Object 3 is empty. Impossible operation." << endl;
	};

	try
	{
		int result4 = ob4->Reduce(rfun,3);
		cout << "Object 4 (Stack of length 3 with undefined meanings)-result " << endl;
		cout << result4;
	}
	catch (invalid_argument error)
	{
		cout << "Object 4 of length 3 with undefined meanings. Impossible operation." << endl;
	};
	cout << endl;

	cout << "----------------------------------------" << endl;
	cout << "Expected output:\n" << endl;
	cout << "Object 1-result: aabbccdd" << endl;
	cout << "Object 2 (copy of Object 2)-result: aabbccdd" << endl;
	cout << "Object 3 (Empty Stack)-result: IndexError" << endl;
	cout << "Object 4 (Stack of length 3 with undefined meanings)-result: ValueError\n" << endl;
	cout << endl;

	cout << "***************************************" << endl;
}

void Test()
{
	cout << endl << "Testing..." << endl;
	MapTest();
	WhereTest();
	ReduceTest();
}