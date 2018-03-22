#include "Node.h"

void MaxFromStructsList(list<Node> &StructList);
void ListOfStructsInput();

Node MaxFromStructsArray(Node* StructArray, int low, int high, int size);
void ArrayOfStructsInput();
Node RecursivTwoMax(Node* i_arr, int i_size);







void main()
{
	srand(time(NULL));
	int choice;

	cout << "Choose type: " << endl;
	cout << "1) - Recursive (array of structs)." << endl;
	cout << "2) - Iterative (list of structs)." << endl;
	cout << "3) - Exit!" << endl;
	cout << "You're choice: "; cin >> choice;

	switch (choice)
	{
	case 1: ArrayOfStructsInput(); break;
	case 2: ListOfStructsInput(); break;
	default: cout << "Bye bye!" << endl; break;
	}

}

void MaxFromStructsList(list<Node> &StructList)
{
	int max1 = 0, max2 = 0;

	list<Node>::iterator start = StructList.begin();
	list<Node>::iterator end = StructList.end();

	for (; start != end; start++)
	{
		cout << "[" << start->data << "] ";
	}
	cout << endl;

	while (StructList.size() > 1)
	{
		start = StructList.begin();
		list<Node>::iterator next = StructList.begin();
		++next;
		int size = StructList.size();

		for (int j = 0; j<size / 2; start++, j++)
		{
			if (start->data > next->data)
			{
				start->MyStack.push(next->data);
				StructList.erase(next);
				next = start;
				next++;
				if (j < size / 2 - 1)
					next++;
			}
			else
			{
				next->MyStack.push(start->data);
				StructList.erase(start);
				start = next;
				next++;
				if (j < size / 2 - 1)
					next++;
			}
		}
	}

	start = StructList.begin();

	while (!start->MyStack.empty())
	{
		if (max2 <= start->MyStack.top())
			max2 = start->MyStack.top();
		start->MyStack.pop();
	}
	max1 = start->data;

	cout << "Max1 is: " << max1 << endl << "Max2 is: " << max2 << endl;
	main();
}

void ListOfStructsInput()
{
	int choice, size, num;
	Node temp_node;
	list<Node> StructList;
	cout << "Choose input type: " << endl;
	cout << "1) - Random" << endl;
	cout << "2) - Manual" << endl;

	cin >> choice;

	switch (choice)
	{
	case 1:
	{

		cout << "Enter size: "; cin >> size;
		for (int i = 1; i <= size; i++)
		{
			temp_node.data = rand() % 100 + 1;
			StructList.push_front(temp_node);
		}
		MaxFromStructsList(StructList);
		break;

	}
	case 2:
	{
		cout << "Enter size: "; cin >> size;
		for (int i = 1; i <= size; i++)
		{
			cin >> num;
			temp_node.data = num;
			StructList.push_front(temp_node);
		}
		MaxFromStructsList(StructList);
		break;
	}
	default: cout << "Invalid choice!" << endl;
		ListOfStructsInput();
		break;
	}

}



/////////////////////////////////////////////////////////////////////////////////////

Node* CreatAndFillArryRandom(int& i_size)
{
	cout << "Enter size of Arry: ";
	cin >> i_size;
	Node *ArrOfNodes = new Node[i_size];
	for (int i = 0; i < i_size; i++)
	{
		ArrOfNodes[i].data = rand() % 100 + 1;
	}
    
	return ArrOfNodes;
}

void PrintArryOfNodes(Node* i_ArrToPrint, int i_size)
{
	for (int i = 0; i < i_size; i++)
	{
		cout << i_ArrToPrint[i].data << endl;
	}
}

Node RecursivTwoMax(Node* i_arr, int i_size)
{
	int sizeRight;
	if (i_size < 2)
	{
		return i_arr[0];
	}

	else
	{
		if (i_size % 2 != 0)       // check size odd 
		{
			sizeRight = (i_size / 2) + 1;
		}
		else
		{
			sizeRight = i_size / 2;
		}

		Node teamLeft = RecursivTwoMax((i_arr + i_size / 2), sizeRight);
		Node teamRight = RecursivTwoMax(i_arr, i_size / 2);

		if (teamLeft.data > teamRight.data)
		{
			teamLeft.MyStack.push(teamRight.data);
			return teamLeft;
		}
		else
		{
			teamRight.MyStack.push(teamLeft.data);
			return teamRight;

		}


	}

}

void PrintTwoMax(Node i_ToPrint)
{
	int max1 = i_ToPrint.data;
	int max2 = i_ToPrint.MyStack.top();
	i_ToPrint.MyStack.pop();

	while (!i_ToPrint.MyStack.empty())
	{
		if (max2 <= i_ToPrint.MyStack.top())
		{
			max2 = i_ToPrint.MyStack.top();
		}

		i_ToPrint.MyStack.pop();
	}
	cout << "Max1 is: " << max1 << endl << "Max2 is: " << max2 << endl;

}

void ArrayOfStructsInput()   //arry of struct!!!
{
	int size;
	Node *Arr = CreatAndFillArryRandom(size);
	PrintArryOfNodes(Arr, size);
	Node max_node = RecursivTwoMax(Arr, size);
	PrintTwoMax(max_node);

	main();
}

///////////////////////////////////////////////////////////////////////////////





Node MaxFromStructsArray(Node *StructArray, int low, int high, int size)
{
	int mid = low + high / 2;

	if (size == 1)
		return StructArray[low];

	else if (size == 2)
	{
		if (StructArray[low].data > StructArray[high].data)
		{
			StructArray[low].MyStack.push(StructArray[high].data);
			return StructArray[low];
		}
		else
		{
			StructArray[high].MyStack.push(StructArray[low].data);
			return StructArray[high];
		}
	}
	else
	{
		int odd_or_even = size % 2;
		Node left_max = MaxFromStructsArray(StructArray, low, mid, size / 2 + odd_or_even);
		Node right_max = MaxFromStructsArray(StructArray, mid, high, size / 2);

		if (left_max.data > right_max.data)
		{
			left_max.MyStack.push(right_max.data);
			return left_max;
		}
		else
		{
			right_max.MyStack.push(left_max.data);
			return right_max;
		}
	}
}