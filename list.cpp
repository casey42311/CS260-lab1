#include "memoryleakdetect.h"		// this must be the first #include in each of your .cpp files
#include <iostream>
#include "list.h"

using namespace std;

List::List() :
	headByName(nullptr),
	headByRating(nullptr)
{
	
}

List::~List()
{
	Node *node(headByRating);
	Node *nextNode;

	while (node != nullptr)
	{
		nextNode = node->nextByRating;
		delete node;
		node = nextNode;
	}
}

List::Node::Node(const Winery& winery) :
	nextByName(nullptr),
	nextByRating(nullptr),
	item(winery.getName(), winery.getLocation(), winery.getAcres(), winery.getRating())
{
	
}

void List::displayByName(ostream& out) const
{
	Node *display(headByName);

	display->item.displayColumnHeadings(out);

	//While not at the end of the list
	while (display != nullptr)
	{
		out << &display->item << endl;
		display = display->nextByName;
	}
}

void List::displayByRating(ostream& out) const
{
	Node *display(headByRating);
	
	display->item.displayColumnHeadings(out);

	//While not at the end of the list
	while (display != nullptr)
	{
		out << &display->item << endl;
		display = display->nextByRating;
	}
}

void List::insert(const Winery& winery)
{
	Node *newNode(new Node(winery));
	Node *byRating(headByRating);
	Node *byName(headByName);
	Node *trail(nullptr);
	int flag(0);

	//If list is empty
	if (headByRating == nullptr)
	{
		headByRating = headByName = newNode;
		return;
	}
	
	//Insert in the correct spot by rating
	if (newNode->item.getRating() > headByRating->item.getRating())
	{
		newNode->nextByRating = byRating;
		headByRating = newNode;
	}
	else if (newNode->item.getRating() < headByRating->item.getRating())
	{
		while (byRating != nullptr)
		{
			if (newNode->item.getRating() > byRating->item.getRating())
			{
				newNode->nextByRating = byRating;
				trail->nextByRating = newNode;
				flag = 1;
				break;
			}
			trail = byRating;
			byRating = byRating->nextByRating;
		}
		if (flag == 0)
		{
			trail->nextByRating = newNode;
		}
	}

	//Reset to insert by Name
	flag = 0;
	trail = headByName;

	//Insert in the correct spot by name
	if (strcmp(newNode->item.getName(), headByName->item.getName()) < 0)
	{
		newNode->nextByName = byName;
		headByName = newNode;
	}
	else if (strcmp(newNode->item.getName(), headByName->item.getName()) > 0)
	{
		while (byName != nullptr)
		{
			if (strcmp(newNode->item.getName(), byName->item.getName()) < 0)
			{
				newNode->nextByName = byName;
				trail->nextByName = newNode;
				flag = 1;
				break;
			}
			trail = byName;
			byName = byName->nextByName;
		}
		if (flag == 0)
		{
			trail->nextByName = newNode;
		}
	}
}

Winery * const List::find(const char * const name) const
{
	Node *find(headByName);

	//Compares the value of name until it finds the correct node
	while (find != nullptr)
	{
		//If the correct node was found, return a const pointer to the winery it holds
		if (strcmp(find->item.getName(), name) == 0)
			return &find->item;

		find = find->nextByName;
	}
	return 0;
}

bool List::remove(const char * const name)
{
	Node *remove(headByName);
	Node *trail(headByName);
	int rating(0);

	while (remove != nullptr)
	{
		if (strcmp(remove->item.getName(), name) == 0)
		{
			if (remove == headByName)
			{
				rating = remove->item.getRating();
				headByName = headByName->nextByName;
				break;
			}
			else
			{
				rating = remove->item.getRating();
				trail->nextByName = remove->nextByName;
				break;
			}
		}
		trail = remove;
		remove = remove->nextByName;
	}

	trail = headByRating;
	remove = headByRating;

	while (remove != nullptr)
	{
		if (remove->item.getRating() == rating)
		{
			if (remove == headByRating)
			{
				headByRating = headByRating->nextByRating;
				delete remove;
				return true;
			}
			else
			{
				trail->nextByRating = remove->nextByRating;
				delete remove;
				return true;
			}
		}
		trail = remove;
		remove = remove->nextByRating;
	}

	return false;
}