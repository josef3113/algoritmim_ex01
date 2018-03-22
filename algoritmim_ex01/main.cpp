#include "Node.h"

void MaxFromStructsList(list<Node> &StructList);
void ListOfStructsInput();

Node MaxFromStructsArray(Node* StructArray, int low, int high, int size);
void ArrayOfStructsInput();


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

void ArrayOfStructsInput()
{
	int size, max1 = 0, max2 = 0;

	cout << "Enter size: "; cin >> size;
	Node *Arr = new Node[size];
	for (int i = 0; i < size; i++)
	{
		Arr[i].data = rand() % 100 + 1;
	}

	for (int i = 0; i < size; i++)
	{
		cout << Arr[i].data << endl;
	}

	Node max_node = MaxFromStructsArray(Arr, 0, size - 1, size);

	max1 = max_node.data;

	while (!max_node.MyStack.empty())
	{
		if (max2 <= max_node.MyStack.top())
			max2 = max_node.MyStack.top();
		max_node.MyStack.pop();
	}
	cout << "Max1 is: " << max1 << endl << "Max2 is: " << max2 << endl;
	main();
}

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