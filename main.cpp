#include <iostream>
#include "interface.h"
#include"Stack.h"
#include "ArraySequence.h"
#include "tests.h"

using namespace std;

int main()
{
	Start();
	while (true)
	{
		int choice;
		ShowMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			try
			{


				int arr[7] = { 1, 2, 3, 4, 5, 6, 7 };
				ArraySequence<int>* ob1 = new ArraySequence<int>(4);
				ob1->Set(0, 1);
				ob1->Set(2, 2);
				ob1->Set(3, 3);
				ob1->InsertAt(2, 10);
				for (int i = 0; i < ob1->GetLength(); i++)
				{
					int value;
					if (ob1->TryGetValue(i, value))
						cout << value;
				}

			}
			catch (exception error)
			{

			};
			break;
		case 2:
			Test();
			break;
		case 3:
			End();
			exit(0);
		default:
			cout << endl << "Incorrect input. Please, repeat.\n";
			break;
		};
	};
};