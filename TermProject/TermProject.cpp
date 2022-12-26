#include <iostream>

using namespace std;


string GetTimeAsString(string formatString, tm theTime)
{
	formatString += '\a'; //force at least one character in the result
	string buffer;
	buffer.resize(formatString.size());
	int len = strftime(&buffer[0], buffer.size(), formatString.c_str(), &theTime);
	while (len == 0) {
		buffer.resize(buffer.size() * 2);
		len = strftime(&buffer[0], buffer.size(), formatString.c_str(), &theTime);
	}
	buffer.resize(len - 1); //remove that trailing '\a'
	return buffer;
}


struct TicketsListElement
{
	int ticketId;
	TicketsListElement* nextElement = NULL;

};


struct TicketsList {
	TicketsListElement* firstElement = NULL;


	// default constructor
	TicketsList() {};

	TicketsList(int data[], int n) {
		GenerateTicketsList(data, n);
	}

	void DeleteList() {
		while (firstElement) {
			TicketsListElement* tmp = firstElement->nextElement;
			delete firstElement;
			firstElement = tmp;
			cout << (tmp == NULL ? 1 : 0) << endl;
		}
		firstElement = NULL;
	}

	void GenerateTicketsList(int data[], int n) {
		if (!data || !n) { return; }
		if (n < 1) {
			firstElement = NULL;
			return;
		}
		TicketsListElement* element = new TicketsListElement{ data[0] };
		for (int i = 1; i < n; i++) {
			element = new TicketsListElement{ data[i], element };
		}
		firstElement = element;
	}
};


class CarOwner
{

	string name;
	tm birthday;
	string phoneNumber = "";
	unsigned int drivingLicence = 0;
	tm drivingLicenceExpiry;
	string carLicencePlate = "";
	string techPassportId = "";
	int gibddId = 0;
	TicketsList ticketsList = TicketsList(NULL, NULL);
	CarOwner* nextOwner = NULL;


	const string standardStringFormat = "%d.%m.%y";



	// default constructor
	CarOwner() { };


public:

	// simple constructor for tests
	CarOwner(string name) {
		this->name = name;
	}

	// class constructor
	CarOwner(string name, tm birthday, string phoneNumber, unsigned int drivingLicence,
		tm drivingLicenceExpiry, string carLicencePlate, string techPassportId,
		int gibddId, int* tickets = NULL, int ticketsAmount = NULL)
	{
		this->name = name;
		this->birthday = birthday;
		this->phoneNumber = phoneNumber;
		this->drivingLicence = drivingLicence;
		this->drivingLicenceExpiry = drivingLicenceExpiry;
		this->carLicencePlate = carLicencePlate;
		this->techPassportId = techPassportId;
		this->gibddId = gibddId;
		this->ticketsList = TicketsList(tickets, ticketsAmount);
	}


	//// GETTERS

	// getter for name
	string getName() { return name; };
	// getter for birthday
	tm getBirthday() { return birthday; };

	// getter for birthday as string
	string getBirthdayStr() { return GetTimeAsString(standardStringFormat, birthday); }


	// getter for phoneNumber
	string getPhoneNumber() { return phoneNumber; };
	// getter for drivingLicence
	unsigned int getDrivingLicence() { return drivingLicence; };
	// getter for drivingLicenceExpiry
	tm getDrivingLicenceExpiry() { return drivingLicenceExpiry; };
	string getDrivingLicenceExpiryStr() { return GetTimeAsString(standardStringFormat, drivingLicenceExpiry); }
	// getter for carLicencePlate
	string getCarLicencePlate() { return carLicencePlate; };
	// getter for techPassportId
	string getTechPassportId() { return techPassportId; };
	// getter for gibddId
	int getGibddId() { return gibddId; };
	// getter for ticketsList
	TicketsList getTicketsList() { return ticketsList; };
	// getter for ticketsList
	CarOwner* getNextOwner() { return nextOwner; };


	//// SETTERS

	// setter for nextOwner
	void setNextOwner(CarOwner* owner) { nextOwner = owner; }


	unsigned int GetLength() {
		if (nextOwner) { return nextOwner->GetLength() + 1; }
		else return 1;
	}


};


struct CarOwnersList {
	CarOwner* firstOwner = NULL;


	void InsertToList(CarOwner* owner) {
		owner->setNextOwner(firstOwner);
		firstOwner = owner;
	}

	void DeleteList() {
		while (firstOwner) {
			CarOwner* tmp = firstOwner->getNextOwner();
			delete firstOwner;
			firstOwner = tmp;
		}
	}

	void DeleteFromList(string name) {
		CarOwner* tmp = firstOwner;
		// empty list
		if (!tmp) {
			return;
		}
		// element for deleting is first
		else if (tmp->getName() == name) {
			tmp = firstOwner->getNextOwner();
			delete firstOwner;
			firstOwner = tmp;
			return;
		}
		// list contains only one element
		else if (!tmp->getNextOwner()) {
			return;
		}
		else {
			while (tmp->getNextOwner()) {
				if (tmp->getNextOwner()->getName() == name) {
					CarOwner* buff = tmp->getNextOwner()->getNextOwner();
					delete tmp->getNextOwner();
					tmp->setNextOwner(buff);
					return;
				}
				else {
					tmp = tmp->getNextOwner();
				}
			}
		}
	}

	unsigned int GetLength() {
		if (firstOwner) return firstOwner->GetLength();
		else return 0;
	}
};


class Ticket
{

	unsigned int id;
	tm timestamp;
	string carLicencePlate;
	bool isPaid;

public:
	// default constructor
	Ticket() {};

	// class constructor
	Ticket(unsigned int id, tm timestamp, string carLicencePlate, bool isPaid = false)
	{
		this->id = id;
		this->timestamp = timestamp;
		this->carLicencePlate = carLicencePlate;
		this->isPaid = isPaid;
	}

	// getter for id
	unsigned int getId() { return id; }
	// getter for timestamp
	tm getTimestamp() { return timestamp; }
	string getTimestampStr() {
		return GetTimeAsString("%H:%M %d.%m.%y", timestamp);
	}
	// getter for licencePlate
	string getLicencePlate() { return carLicencePlate; }
	// getter for isPaid
	bool getIsPaid() { return isPaid; }

};


struct TicketsTreeElement // структура для представления узлов дерева
{
	Ticket ticket;
	int size;
	TicketsTreeElement* rightChild ;
	TicketsTreeElement* leftChild;
	
	TicketsTreeElement(Ticket ticket) {
		this->ticket = ticket;
		rightChild = 0;
		leftChild = 0;
		size = 1;
	}
};

int GetTreeSize(TicketsTreeElement* p) 
{
	if (!p) return 0;
	return p->size;
}

void FixTreeSize(TicketsTreeElement* p)
{
	p->size = GetTreeSize(p->leftChild) + GetTreeSize(p->rightChild) + 1;
}


TicketsTreeElement* FindTicket(TicketsTreeElement* tree, int id)
{
	if (!tree) return 0;
	if (id == tree->ticket.getId())
		return tree;
	if (id < tree->ticket.getId())
		return FindTicket(tree->leftChild, id);
	else
		return FindTicket(tree->rightChild, id);
}

TicketsTreeElement* RotateTreeRight(TicketsTreeElement* tree) 
{
	TicketsTreeElement* q = tree->leftChild;
	if (!q) return tree;
	tree->leftChild = q->rightChild;
	q->rightChild = tree;
	q->size = tree->size;
	FixTreeSize(tree);
	return q;
}


TicketsTreeElement* RotateTreeLeft(TicketsTreeElement* tree) // левый поворот вокруг узла q
{
	TicketsTreeElement* p = tree->rightChild;
	if (!p) return tree;
	tree->rightChild = p->leftChild;
	p->leftChild = tree;
	p->size = tree->size;
	FixTreeSize(tree);
	return p;
}


TicketsTreeElement* TreeInsertToRoot(TicketsTreeElement* tree, Ticket t)
{
	if (!tree) return new TicketsTreeElement(t);
	if (t.getId() < tree->ticket.getId())
	{
		tree->leftChild = TreeInsertToRoot(tree->leftChild, t);
		return RotateTreeRight(tree);
	}
	else
	{
		tree->rightChild = TreeInsertToRoot(tree->rightChild, t);
		return RotateTreeLeft(tree);
	}
}


TicketsTreeElement* TreeRandomisedInsert(TicketsTreeElement* p, Ticket t)
{
	if (!p) return new TicketsTreeElement(t);
	if (rand() % (p->size + 1) == 0)
		return TreeInsertToRoot(p, t);
	if (p->ticket.getId() > t.getId())
		p->leftChild = TreeRandomisedInsert(p->leftChild, t);
	else
		p->rightChild = TreeRandomisedInsert(p->rightChild, t);
	FixTreeSize(p);
	return p;
}


TicketsTreeElement* TreeJoinNodes(TicketsTreeElement* p, TicketsTreeElement* q) // объединение двух деревьев
{
	if (!p) return q;
	if (!q) return p;
	if (rand() % (p->size + q->size) < p->size)
	{
		p->rightChild = TreeJoinNodes(p->rightChild, q);
		FixTreeSize(p);
		return p;
	}
	else
	{
		q->leftChild = TreeJoinNodes(p, q->leftChild);
		FixTreeSize(q);
		return q;
	}
}



TicketsTreeElement* TreeRemoveNode(TicketsTreeElement* p, int id) // удаление из дерева p первого найденного узла с ключом k 
{
	if (!p) return p;
	if (p->ticket.getId() == id)
	{
		TicketsTreeElement* q = TreeJoinNodes(p->leftChild, p->rightChild);
		delete p;
		return q;
	}
	else if (id < p->ticket.getId())
		p->leftChild = TreeRemoveNode(p->leftChild, id);
	else
		p->rightChild = TreeRemoveNode(p->rightChild, id);
	return p;
}


struct HashTableAnalytics {
	unsigned int capacity = 0;
	unsigned int population = 0;
	unsigned int filling = 0;
	unsigned int collisions = 0;
	double fillingRate = 0;
	double collisionsRate = 0;
};


class OwnersHashTable {
	unsigned int capacity = 100;
	CarOwnersList* arr = NULL;

	const double fillingRateLimit = 0.8;
	const double collisionsRatelimit = 0.4;


public:


	OwnersHashTable() {
		SetupArray();
	}

	OwnersHashTable(int capacity) {
		this->capacity = capacity;
		SetupArray();
	}


	void SetupArray() {
		arr = new CarOwnersList[capacity];
	}

	void DeleteArray() {
		for (int i = 0; i < capacity; i++) {
			arr[i].DeleteList();
		}
		delete arr;
	}


	void InsertToTable(CarOwner* owner) {
		int index = Hash(*owner);
		arr[index].InsertToList(owner);
	}

	void DeleteFromTable(string name) {
		int index = Hash(name);
		arr[index].DeleteFromList(name);
	}

	CarOwnersList GetOwnersByIndex(int index) {
		if (index < 0 || index >= capacity) { throw "wrong index"; }
		return arr[index];
	}


	int Hash(string name) {
		return Hash(name, capacity);
	}

	int Hash(CarOwner owner) {
		return Hash(owner.getName());
	}

	static int Hash(string name, int capacity) {
		// (ascii - 64) * 13^(pos%7+1)
		size_t size = name.length();
		unsigned int hash = 0;
		for (int i = 0; i < size; i++) {
			int p = i % 7 + 1;
			p = pow(13, p);
			int ascii = int(name[i]) - 64;
			hash = p * ascii;
		}
		return hash % capacity;
	}

	unsigned int getCapacity() { return capacity; }


	HashTableAnalytics GetAnalytics() {
		HashTableAnalytics analytics{ capacity };
		for (int i = 0; i < capacity; i++) {
			unsigned int length = arr[i].GetLength();
			analytics.population += length;
			if (length > 0) {
				analytics.filling++;
				analytics.collisions += length - 1;
			}
		}
		analytics.fillingRate = (float)analytics.filling / analytics.capacity;
		analytics.collisionsRate = (float)analytics.collisions / analytics.capacity;
		return analytics;
	}

	OwnersHashTable Rehash() {
		OwnersHashTable ht = OwnersHashTable(GetAnalytics().population * 2);
		for (int i = 0; i < capacity; i++) {
			CarOwner* owner = arr[i].firstOwner;
			while (owner) {
				ht.InsertToTable(owner);
				owner = owner->getNextOwner();
			}
		}
		return ht;
	}

	bool RehashPending() {
		HashTableAnalytics an = GetAnalytics();
		if (an.fillingRate > fillingRateLimit ||
			an.collisionsRate > collisionsRatelimit) {
			return true;
		}
		return false;
	}


};


class ConsoleInterface {
public:
	static void OutputTicketsList(TicketsList list) {
		TicketsListElement* element = list.firstElement;
		while (element) {
			cout << element->ticketId << " ";
			element = element->nextElement;
		}
	}

	static void OutputCarOwnersList(CarOwnersList list) {
		CarOwner* element = list.firstOwner;
		cout << "\nLIST OF OWNERS\n";
		while (element) {
			OutputCarOwner(*element);
			cout << endl;
			element = element->getNextOwner();
		}
	}

	static void OutputHashTable(OwnersHashTable table) {
		int capacity = table.getCapacity();
		for (int i = 0; i < capacity; i++) {
			cout << i << " in table\n";
			OutputCarOwnersList(table.GetOwnersByIndex(i));
			cout << "\n";
		}
	}

	static void OutputCarOwner(CarOwner owner) {
		cout << "Name:\t\t" << owner.getName() << endl;
		cout << "Bithday:\t" << owner.getBirthdayStr() << endl;
		cout << "Phone number:\t" << owner.getPhoneNumber() << endl;
		cout << "Dr. licence:\t" << owner.getDrivingLicence() << endl;
		cout << "Dr. l. expiry:\t" << owner.getDrivingLicenceExpiryStr() << endl;
		cout << "GIBDD id:\t" << owner.getGibddId() << endl;
		cout << "Licence plate:\t" << owner.getCarLicencePlate() << endl;
		cout << "Tech passport:\t" << owner.getTechPassportId() << endl;
	}

	static void OutputHashTableAnalytics(HashTableAnalytics analytics) {
		cout << "Capacity:\t" << analytics.capacity
			<< "\nPopulation:\t" << analytics.population
			<< "\nFilling:\t" << analytics.filling
			<< "\nFilling rate:\t" << analytics.fillingRate
			<< "\nCollisions:\t" << analytics.collisions
			<< "\nCollisions rate:" << analytics.collisionsRate
			<< endl;
	}

};


int main()
{
	/*
	int data[5] = { 1,2,3,4,5 };
	int n = 5;
	TicketsList list = TicketsList(data, n);
	ConsoleInterface::OutputTicketsList(list);
	list.DeleteList();


	OwnersHashTable ht = OwnersHashTable(10);
	string s1 = "Eldar";
	string s2 = "Nail";
	string s3 = "Andrey";
	string s4 = "Anton";
	string s5 = "Nikita";
	string s6 = "Alina";
	string s7 = "Eldar";

	CarOwner* c1 = new CarOwner(s1);
	CarOwner* c2 = new CarOwner(s2);
	CarOwner* c3 = new CarOwner(s3);
	CarOwner* c4 = new CarOwner(s4);
	CarOwner* c5 = new CarOwner(s5);
	CarOwner* c6 = new CarOwner(s6);
	CarOwner* c7 = new CarOwner(s7);




	ht.InsertToTable(c1);
	ht.InsertToTable(c2);
	ht.InsertToTable(c3);
	ht.InsertToTable(c4);
	ht.InsertToTable(c5);
	ht.InsertToTable(c6);
	ht.InsertToTable(c7);

	ConsoleInterface::OutputHashTable(ht);

	cout << "\n\ndeleting " << s2 << endl;

	ht.DeleteFromTable(s2);

	ConsoleInterface::OutputHashTable(ht);

	ht.DeleteArray();
	*/

	/* HASH TABLE DEMO */
	CarOwner* c1 = new CarOwner("Eldar", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c2 = new CarOwner("Nail", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c3 = new CarOwner("Alina", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c4 = new CarOwner("Anton", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c5 = new CarOwner("Pasha", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c6 = new CarOwner("Andrey", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);

	OwnersHashTable ht = OwnersHashTable(10);
	ht.InsertToTable(c1);
	ht.InsertToTable(c2);
	ht.InsertToTable(c3);
	ht.InsertToTable(c4);
	ht.InsertToTable(c5);
	ht.InsertToTable(c6);
	ConsoleInterface::OutputHashTable(ht);

	HashTableAnalytics an = ht.GetAnalytics();
	ConsoleInterface::OutputHashTableAnalytics(an);
	ht.DeleteFromTable("Alina");
	ConsoleInterface::OutputHashTable(ht);
	an = ht.GetAnalytics();
	ConsoleInterface::OutputHashTableAnalytics(an);

	//*/

	/* CAR OWNERS LIST DEMO
	*
	*
	*
	CarOwner* c1 = new CarOwner("Eldar", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c2 = new CarOwner("Nail", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c3 = new CarOwner("Alina", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c4 = new CarOwner("Anton", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c5 = new CarOwner("Pasha", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c6 = new CarOwner("Andrey", tm{ 0,0,0,1,0,20 },
		"+79257093995", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222);

	CarOwnersList cl;
	cl.InsertToList(c1);
	cl.InsertToList(c2);
	cl.InsertToList(c3);
	cl.InsertToList(c4);
	cl.InsertToList(c5);
	cl.InsertToList(c6);

	cout << cl.GetLength() << endl;

	ConsoleInterface::OutputCarOwnersList(cl);
	*/
}
