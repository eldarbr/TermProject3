#include <iostream>
#include <string>
#include <sstream>

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

	void AddTicket(int id) {
		TicketsListElement* newTicket = new TicketsListElement{ id, firstElement };
		firstElement = newTicket;
	}
};


class CarOwner
{

	string name = "";
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






public:

	// default constructor
	CarOwner() { };


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
	// setter for birthday
	void setBirthday(tm bday) { birthday = bday; }
	// setter for drivingLicence
	void setDrivingLicence(int id) { drivingLicence = id; }
	// setter for drivingLicenceExpiry
	void setDrivingLicenceExpiry(tm timestamp) { drivingLicenceExpiry = timestamp; }
	// setter for gibddId
	void setGibddId(int id) { gibddId = id; }
	// setter for name
	void setName(string name) { this->name = name; }
	// setter for phoneNumber
	void setPhoneNumber(string phoneNumber) { this->phoneNumber = phoneNumber; }
	// setter for carLicencePlate
	void setCarLicencePlate(string carLicencePlate) { this->carLicencePlate = carLicencePlate; }
	// setter for techPassport
	void setTechPassportId(string techPassportId) { this->techPassportId = techPassportId; }


	void addTicket(int ticketId) { this->ticketsList.AddTicket(ticketId); }



	unsigned int GetLength() {
		if (nextOwner) { return nextOwner->GetLength() + 1; }
		else return 1;
	}




};

istream& operator>>(istream& is, CarOwner* owner)
{

	string name, phoneNumber, bdD, bdM, bdY, licId,
		licED, licEM, licEY, gbddId, tckts, carLicencePlate,
		techPassportId;
	if (getline(is, name, ';') &&
		getline(is, bdD, ';') &&
		getline(is, bdM, ';') &&
		getline(is, bdY, ';') &&
		getline(is, phoneNumber, ';') &&
		getline(is, licId, ';') &&
		getline(is, licED, ';') &&
		getline(is, licEM, ';') &&
		getline(is, licEY, ';') &&
		getline(is, carLicencePlate, ';') &&
		getline(is, techPassportId, ';') &&
		getline(is, gbddId, ';') &&
		getline(is, tckts)) {


		owner->setName(name);
		owner->setPhoneNumber(phoneNumber);
		owner->setCarLicencePlate(carLicencePlate);
		owner->setTechPassportId(techPassportId);
		owner->setGibddId(stoi(gbddId));

		owner->setBirthday(tm{ 0,0,0,stoi(bdD),stoi(bdM) - 1,stoi(bdY) - 1900 });
		owner->setDrivingLicence(stoi(licId));
		owner->setDrivingLicenceExpiry(tm{ 0,0,0,stoi(licED),stoi(licEM),stoi(licEY) });


		int f;
		stringstream ss(tckts);
		while ((ss >> f))
			owner->addTicket(f);



	}
	return is;
}

ostream& operator<<(ostream& out, CarOwner* owner) {
	out << "Name:\t\t" << owner->getName() << endl;
	out << "Bithday:\t" << owner->getBirthdayStr() << endl;
	out << "Phone number:\t" << owner->getPhoneNumber() << endl;
	out << "Dr. licence:\t" << owner->getDrivingLicence() << endl;
	out << "Dr. l. expiry:\t" << owner->getDrivingLicenceExpiryStr() << endl;
	out << "GIBDD id:\t" << owner->getGibddId() << endl;
	out << "Licence plate:\t" << owner->getCarLicencePlate() << endl;
	out << "Tech passport:\t" << owner->getTechPassportId() << endl;
	TicketsList tl = owner->getTicketsList();
	if (tl.firstElement) {
		out << "Tickets id:\t";
		TicketsListElement* leel = tl.firstElement;
		while (leel) {
			out << leel->ticketId << " ";
			leel = leel->nextElement;
		}
	}
	return out;
}




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

	int id;
	tm timestamp;
	string carLicencePlate;
	bool isPaid;

public:
	// default constructor
	Ticket() {};

	Ticket(int id) {
		this->id = id;
	}

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

	// setter for name
	void setId(unsigned int id) { this->id = id; }
	// setter for timestamp
	void setTimestamp(tm timestamp) { this->timestamp = timestamp; }
	// setter for carLicencePlate
	void setCarLicencePlate(string carLicencePlate) { this->carLicencePlate = carLicencePlate; }
	// setter for isPaid
	void setIsPaid(bool isPaid) { this->isPaid = isPaid; }

};



istream& operator>>(istream& is, Ticket* ticket) {
	string id, carLPlate, isPaid, tmMn, tmH, tmD, tmM, tmY;

	if (getline(is, id, ';') &&
		getline(is, tmMn, ';') &&
		getline(is, tmH, ';') &&
		getline(is, tmD, ';') &&
		getline(is, tmM, ';') &&
		getline(is, tmY, ';') &&
		getline(is, carLPlate, ';') &&
		getline(is, isPaid)) {

		ticket->setId(stoi(id));
		ticket->setCarLicencePlate(carLPlate);
		ticket->setIsPaid((isPaid) == "1" ? true : false);
		ticket->setTimestamp(tm{ 0,stoi(tmMn),stoi(tmH),stoi(tmD),stoi(tmM) - 1,stoi(tmY) - 1900 });

	}
	return is;
}


ostream& operator<<(ostream& out, Ticket* ticket) {
	out << "Ticket ID:\t" << ticket->getId()
		<< "\nLicence pl:\t" << ticket->getLicencePlate()
		<< "\nTimestamp:\t" << ticket->getTimestampStr()
		<< "\nIs paid:\t" << (ticket->getIsPaid() ? "yes" : "no");
	return out;
}





struct TicketsTreeElement // структура для представления узлов дерева
{
	Ticket ticket;
	int size;
	TicketsTreeElement* rightChild;
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
		if (owner->getName() == "") throw "wrong name - can't hash";
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
		analytics.collisionsRate = (float)analytics.collisions / analytics.population;
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
		cout << &owner;
	}

	static void OutputTicketsListElements(TicketsListElement* tle) {
		while (tle) {

		}
	}

	static void OutputTicketFromTree(TicketsTreeElement* tree, int ticketId) {
		Ticket t = FindTicket(tree, ticketId)->ticket;
		cout << "id:\t" << t.getId()
			<< "\nplate:\t" << t.getLicencePlate()
			<< "\ntime:\t" << t.getTimestampStr()
			<< "\npaid?\t" << (t.getIsPaid() ? "yes" : "no")
			<< endl;
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


class ConsoleInterfaceMenu {
	enum UserScenarios { Initial, Menu };
public:
	static void InitialMenu() {
		setlocale(LC_ALL, "rus");

		int scenario;

		OwnersHashTable hashTable = OwnersHashTable();
		TicketsTreeElement* ticketsTree = new TicketsTreeElement(Ticket(-1));

		do {
			if (hashTable.GetAnalytics().population != 0) {		// список задан
				system("cls");
				cout
					<< "\nЧто вы хотите сделать?\n"
					<< "1. Вывести всю хэш-таблицу на экран\n"
					<< "2. Найти в владельца хэш-таблице\n"
					<< "3. Добавить владельца в хэш-таблицу\n"
					<< "4. Удалить владельца из хэш-таблицы\n"
					<< "5. Очистить хэш-таблицу\n"
					<< "6. Найти штраф\n"
					<< "7. Добавить штраф\n"
					<< "8. Удалить штраф\n"
					<< "9. Очистить штрафы\n"
					<< "10.Выйти\n"
					<< "> ";
				scenario = InputUsersChoice(Menu);
				switch (scenario) {
				case 1:
					
					system("pause");
					break;
				case 2:
					
					system("pause");
					break;
				case 3:
					
					break;
				case 4:
					system("pause");
					break;
				case 5:
					system("pause");
					break;
				case 6:
					system("pause");
					break;
				case 7:
					system("pause");
					break;
				case 8:
					system("pause");
					break;
				case 9:
					system("pause");
					break;
				}
			}
			else {					// список не задан
				system("cls");
				cout << "\tЧто вы хотите сделать?\n"
					<< "1. Создать пустые структуры\n"
					<< "2. Прочитать данные из файлов\n"
					<< "3. Выход\n"
					<< "> ";
				scenario = InputUsersChoice(Initial);
				switch (scenario)
				{
				case 1:
					system("pause");
					break;

				case 2:
					system("pause");
					break;
				case 3:
					system("pause");
					break;
				}
			}
		} while (scenario != 10 && hashTable.GetAnalytics().population
			|| scenario != 2 && hashTable.GetAnalytics().population);
	}

	static int InputUsersChoice(UserScenarios scenario) {
		int variant;
		cin >> variant;
		if (scenario == Initial) {
			while (variant < 1 || variant > 3) {
				cout << "Wrong input. Try again > ";
				cin >> variant;
			}
		}
		else if (scenario == Menu) {
			while (variant < 1 || variant>10) {
				cout << "Wrong input. Try again > ";
				cin >> variant;
			}
		}
		return variant;
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

	/* HASH TABLE DEMO
	CarOwner* c1 = new CarOwner("Eldar", tm{ 0,0,0,1,0,21 },
		"+79257093991", 123, tm{ 0,0,0,1,1,123 }, "o944xe124",
		"YPP122", 1222, new int[2]{ 1,2 }, 2);
	CarOwner* c2 = new CarOwner("Nail", tm{ 0,0,0,1,0,22 },
		"+79257093992", 123, tm{ 0,0,0,2,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c3 = new CarOwner("Alina", tm{ 0,0,0,1,0,23 },
		"+79257093993", 123, tm{ 0,0,0,3,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c4 = new CarOwner("Anton", tm{ 0,0,0,1,0,24 },
		"+79257093994", 123, tm{ 0,0,0,4,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c5 = new CarOwner("Pasha", tm{ 0,0,0,1,0,25 },
		"+79257093995", 123, tm{ 0,0,0,5,1,123 }, "o944xe124",
		"YPP122", 1222);
	CarOwner* c6 = new CarOwner("Andrey", tm{ 0,0,0,1,0,26 },
		"+79257093996", 123, tm{ 0,0,0,6,1,123 }, "o944xe124",
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

	Ticket t1 = Ticket(0, tm{ 0,13,14,14,1,45 }, "0944xe124");
	TicketsTreeElement* tree = new TicketsTreeElement(t1);

	Ticket t2 = Ticket(1, tm{ 0,3,4,1,4,47 }, "0944xe124");
	tree = TreeRandomisedInsert(tree, t2);


	cout << endl << endl;

	ConsoleInterface::OutputTicketFromTree(tree, 1);
	cout << endl;
	ConsoleInterface::OutputTicketFromTree(tree, 0);


	*/

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

	CarOwner* c1 = new CarOwner();
	cin >> c1;

	cout << c1;
	cout << endl;
	Ticket* t1 = new Ticket();
	cin >> t1;
	cout << endl;
	cout << t1;
}
