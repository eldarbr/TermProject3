#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

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
	out << endl;
	return out;
}




struct CarOwnersList {
	CarOwner* firstOwner = NULL;


	bool InsertToList(CarOwner* owner) {
		bool collision = false;
		if (firstOwner) { collision = true; }
		owner->setNextOwner(firstOwner);
		firstOwner = owner;
		return collision;
	}

	void DeleteList() {
		while (firstOwner) {
			CarOwner* tmp = firstOwner->getNextOwner();
			delete firstOwner;
			firstOwner = tmp;
		}
	}

	char DeleteFromList(string name) {
		///
		///	0 - didn't delete
		/// 1 - did delete, nothing else
		/// 2 - did delete, list contains something else
		/// 

		CarOwner* tmp = firstOwner;
		// empty list
		if (!tmp) {
			return 0;
		}
		// element for deleting is first
		else if (tmp->getName() == name) {
			tmp = firstOwner->getNextOwner();
			delete firstOwner;
			firstOwner = tmp;
			if (tmp) { return 2; }
			return 1;
		}
		// list contains only one element
		else if (!tmp->getNextOwner()) {
			return 0;
		}
		else {
			while (tmp->getNextOwner()) {
				if (tmp->getNextOwner()->getName() == name) {
					CarOwner* buff = tmp->getNextOwner()->getNextOwner();
					delete tmp->getNextOwner();
					tmp->setNextOwner(buff);
					if (buff) { return 2; }
					return 1;
				}
				else {
					tmp = tmp->getNextOwner();
				}
			}
		}
		return 0;
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
	Ticket(int id, tm timestamp, string carLicencePlate, bool isPaid = false)
	{
		this->id = id;
		this->timestamp = timestamp;
		this->carLicencePlate = carLicencePlate;
		this->isPaid = isPaid;
	}

	// getter for id
	int getId() { return id; }
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
	void setId(int id) { this->id = id; }
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
	if (!ticket) { return out; }
	out << "Ticket ID:\t" << ticket->getId()
		<< "\nLicence pl:\t" << ticket->getLicencePlate()
		<< "\nTimestamp:\t" << ticket->getTimestampStr()
		<< "\nIs paid:\t" << (ticket->getIsPaid() ? "yes" : "no");
	out << endl;
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


TicketsTreeElement* RotateTreeLeft(TicketsTreeElement* tree)
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
	if (rand() % (p->size + 1) == 0 && p->ticket.getId() >= 0)
		return TreeInsertToRoot(p, t);
	if (p->ticket.getId() > t.getId())
		p->leftChild = TreeRandomisedInsert(p->leftChild, t);
	else
		p->rightChild = TreeRandomisedInsert(p->rightChild, t);
	FixTreeSize(p);
	return p;
}


TicketsTreeElement* TreeJoinNodes(TicketsTreeElement* p, TicketsTreeElement* q)
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

void EmptyTree(TicketsTreeElement* p) {
	if (p->leftChild) {
		EmptyTree(p->leftChild);
		delete p->leftChild;
		p->leftChild = NULL;
	}
	if (p->rightChild) {
		EmptyTree(p->rightChild);
		delete p->rightChild;
		p->rightChild = NULL;
	}
}

TicketsTreeElement* TreeRemoveNode(TicketsTreeElement* p, int id)
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



struct Trunk
{
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

void ShowTrunks(Trunk* p)
{
	if (p == nullptr) {
		return;
	}
	ShowTrunks(p->prev);
	cout << p->str;
}




void PrintTree(TicketsTreeElement* root, Trunk* prev = NULL, bool isLeft = false)
{
	if (root == NULL) {
		return;
	}
	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);
	PrintTree(root->rightChild, trunk, true);
	if (!prev) {
		trunk->str = "---";
	}
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else {
		trunk->str = "`---";
		prev->str = prev_str;
	}
	ShowTrunks(trunk);
	if (root->ticket.getId() < 0) {
		cout << " root" << endl;
	}
	else {
		cout << " " << root->ticket.getId() << endl;
	}
	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	PrintTree(root->leftChild, trunk, false);
}






struct HashTableAnalytics {
	unsigned int capacity = 0;
	unsigned int population = 0;
	unsigned int filling = 0;
	unsigned int collisions = 0;
	double fillingRate = 0;			// will be out of date until GetAnalytics() is called
	double collisionsRate = 0;		// will be out of date until GetAnalytics() is called
};


class OwnersHashTable {
	unsigned int capacity = 100;
	CarOwnersList* arr = NULL;



	HashTableAnalytics analytics = HashTableAnalytics();

	const double fillingRateUpperLimit = 0.8;
	const double collisionsRateUpperlimit = 0.4;
	const double fillingRateLowerLimit = 0.1;


public:


	OwnersHashTable() {
		SetupArray();
	}

	OwnersHashTable(int capacity) {
		if (capacity % 13 == 0) { capacity++; }
		int last_capacity = this->capacity;
		this->capacity = capacity;
		try {
			SetupArray();
		}
		catch (...) {
			this->capacity = last_capacity;
		}
	}

	void SetupArray() {
		if (arr) { throw "there is already an array"; }
		arr = new CarOwnersList[capacity];
	}

	void DeleteArray(bool deleteLists = false) {
		if (deleteLists) {
			for (int i = 0; i < capacity; i++) {
				arr[i].DeleteList();
			}
		}
		delete arr;
		arr = NULL;
		analytics = HashTableAnalytics();
	}


	void InsertToTable(CarOwner* owner) {
		if (owner->getName() == "") throw "wrong name - can't hash";
		analytics.population++;
		int index = Hash(*owner);
		if (arr[index].InsertToList(owner)) {
			analytics.collisions++;
		}
		else {
			analytics.filling += 1;
		}
	}

	void DeleteFromTable(string name) {
		int index = Hash(name);
		char result = arr[index].DeleteFromList(name);
		if (result == 1) {
			analytics.population--;
			analytics.filling--;
		}
		else if (result == 2) {
			analytics.collisions--;
			analytics.population--;
		}
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
			hash += p * ascii;
		}
		return hash % capacity;
	}

	unsigned int getCapacity() { return capacity; }


	HashTableAnalytics GetAnalytics() {
		analytics.capacity = this->capacity;
		analytics.fillingRate = (float)analytics.filling / analytics.capacity;
		analytics.collisionsRate = (float)analytics.collisions / analytics.population;
		return analytics;
	}

	void Rehash(int newCapacity = 0) {
		if (newCapacity < 0) throw "wrong capacity";
		if (!newCapacity) newCapacity = GetAnalytics().population * 2;
		OwnersHashTable ht = OwnersHashTable(newCapacity);
		if (arr) {
			for (int i = 0; i < capacity; i++) {
				CarOwner* owner = arr[i].firstOwner;
				while (owner) {
					ht.InsertToTable(owner);
					owner = owner->getNextOwner();
				}
			}
			DeleteArray();
		}
		this->arr = ht.getArray();
		this->capacity = ht.getCapacity();
	}


	bool RehashPending() {
		HashTableAnalytics an = GetAnalytics();
		if (an.fillingRate > fillingRateUpperLimit ||
			an.collisionsRate > collisionsRateUpperlimit ||
			an.fillingRate < fillingRateLowerLimit) {
			return true;
		}
		return false;
	}

	CarOwnersList* getArray() { return arr; }

};



class ConsoleInterface {
public:
	static void OutputTicketsList(TicketsList list) {
		TicketsListElement* element = list.firstElement;
		while (element) {
			cout << element->ticketId << " ";
			element = element->nextElement;
		}
		cout << endl;
	}

	static void OutputCarOwnersList(CarOwnersList list) {
		CarOwner* element = list.firstOwner;
		while (element) {
			cout << endl;
			cout << element;
			element = element->getNextOwner();
		}
		cout << endl;
	}

	static void OutputHashTable(OwnersHashTable table) {
		int capacity = table.getCapacity();
		for (int i = 0; i < capacity; i++) {
			cout << "\n-------------------------------------------------\n\nHash=" << i << endl;
			OutputCarOwnersList(table.GetOwnersByIndex(i));
			cout << "\n";
		}
	}

	static void OutputCarOwner(CarOwner owner) {
		cout << &owner;
	}

	static void OutputTicketFromTree(TicketsTreeElement* tree, int ticketId) {
		Ticket t = FindTicket(tree, ticketId)->ticket;
		cout << "id:\t" << t.getId()
			<< "\nplate:\t" << t.getLicencePlate()
			<< "\ntime:\t" << t.getTimestampStr()
			<< "\npaid?\t" << (t.getIsPaid() ? "yes" : "no")
			<< endl;
		cout << endl;
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
		srand(time(0));
		setlocale(LC_ALL, "rus");
		ifstream fn;
		int fileLength;

		TicketsTreeElement* ticketsTree = new TicketsTreeElement(-1);
		OwnersHashTable hashTable = OwnersHashTable();
		bool initialised = false;


		int scenario;

		do {
			if (initialised) {		// список задан
				system("cls");
				cout
					<< "\nЧто вы хотите сделать?\n"
					<< "1. Вывести хэш-таблицу на экран\n"
					<< "2. Вывести аналитику таблицы на экран\n"
					<< "3. Вывести дерево штрафов на экран\n"
					<< "4. Найти в владельца хэш-таблице\n"
					<< "5. Добавить владельца в хэш-таблицу\n"
					<< "6. Удалить владельца из хэш-таблицы\n"
					<< "7. Очистить хэш-таблицу\n"
					<< "8. Найти штраф\n"
					<< "9. Добавить штраф\n"
					<< "10. Удалить штраф\n"
					<< "11.Очистить штрафы\n"
					<< "12.Выйти\n"
					<< "> ";
				scenario = InputUsersChoice(Menu);
				switch (scenario) {
				case 1: {
					ConsoleInterface::OutputHashTable(hashTable);
					system("pause");
					break;
				}
				case 2: {
					ConsoleInterface::OutputHashTableAnalytics(hashTable.GetAnalytics());
					system("pause");
					break;
				}
				case 3: {
					PrintTree(ticketsTree);
					system("pause");
					break;
				}
				case 4: {
					bool found = false;
					string name;
					cout << "Введите имя для поиска > ";
					cin >> name;
					CarOwner* co = hashTable.GetOwnersByIndex(hashTable.Hash(name)).firstOwner;
					while (co) {
						if (co->getName() == name) {
							found = true;
							cout << "Найдена запись!" << endl << co;
							break;
						}
						co = co->getNextOwner();
					}
					if (!found) { cout << "Запись с таким именем не найдена.\n"; }
					system("pause");
					break;
				}
				case 5: {
					cout << "Введите строку информации о водителе в соответствии со стандартом:" << endl;
					cout << "name; birthday.day; birthday.month; birthday.year; phoneN; licenceId; licenceExp.day;"
						<< "licenceExp.month; licenceExp.year; licencePlate; techPassport; gibddId; tickets" << endl;
					CarOwner* co = new CarOwner();
					cin >> co;
					hashTable.InsertToTable(co);
					cout << "Добавлена запись:\n" << co << endl;
					system("pause");
					break;
				}
				case 6: {
					string name;
					cout << "Введите имя для удаления из таблицы > ";
					cin >> name;
					hashTable.DeleteFromTable(name);
					cout << "Вхождение было удалено\n";
					system("pause");
					break;
				}
				case 7: {
					hashTable.DeleteArray(true);
					cout << "Таблица владельцев была очищена\n";
					system("pause");
					break;
				}
				case 8: {
					int id;
					cout << "Введите ИД штрафа для поиска > ";
					cin >> id;
					TicketsTreeElement* t = FindTicket(ticketsTree, id);
					if (!t) {
						cout << "Элемент не найден\n";
					}
					else {
						cout << "Элемент найден:\n"
							<< &(t->ticket);
					}
					system("pause");
					break;
				}
				case 9: {
					cout << "Введите строку информации о штрафе в соответствии со стандартом:" << endl;
					cout << "id; timestamp.minute; timestamp.hour; timestamp.day; timestamp.month;"
						<< " timestamp.year; licencePlate; isPaid" << endl;
					Ticket* t = new Ticket();
					cin >> t;
					TreeRandomisedInsert(ticketsTree, *t);
					delete t;
					system("pause");
					break;
				}
				case 10: {
					int id;
					cout << "Введите ИД штрафа для удаления > ";
					cin >> id;
					TicketsTreeElement* f = FindTicket(ticketsTree, id);
					if (!f) {
						cout << "Штраф не найден" << endl;
					}
					else {
						cout << "Удаляется штраф:\n" << &(f->ticket) << endl;
						TreeRemoveNode(ticketsTree, id);
						cout << "Удаление завершено\n";
					}
					system("pause");
					break;
				}
				case 11: {
					EmptyTree(ticketsTree);
					system("pause");
					break;
				}
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
					initialised = true;
					break;
				case 2:
					cout << "Введите имя файла с владельцами > ";
					string filename;
					cin >> filename;
					fn.open(filename);

					if (!fn.is_open()) {
						cout << "Файл не найден\n";
						break;
					}
					if (fn.eof()) {
						cout << "Файл пустой\n";
						break;
					}
					fn >> fileLength;
					if (fileLength == 0) {
						cout << "В файле нет данных\n";
						break;
					}
					cout << "Количество данных для прочтения: " << fileLength << endl;


					hashTable.DeleteArray(true);
					hashTable.Rehash(fileLength * 2);

					for (int i = 0; i < fileLength; i++) {
						CarOwner* co = new CarOwner();
						fn >> co;
						hashTable.InsertToTable(co);
					}
					fn.close();
					cout << "Данные о владельцах прочитаны. Информация о хэш-таблице:\n";
					ConsoleInterface::OutputHashTableAnalytics(hashTable.GetAnalytics());



					cout << "\n\nВведите имя файла со штрафами > ";

					cin >> filename;
					fn.open(filename);

					if (!fn.is_open()) {
						cout << "Файл не найден\n";
						break;
					}
					if (fn.eof()) {
						cout << "Файл пустой\n";
						break;
					}
					fn >> fileLength;
					if (fileLength == 0) {
						cout << "В файле нет данных\n";
						break;
					}
					cout << "Количество данных для прочтения: " << fileLength << endl;

					for (int i = 0; i < fileLength; i++) {
						Ticket* t = new Ticket();
						fn >> t;
						ticketsTree = TreeRandomisedInsert(ticketsTree, *t);
						delete t;
					}
					fn.close();
					cout << "Данные о штрафах прочитаны\n";
					initialised = true;
					system("pause");
					break;
				}
			}
		} while (scenario != 12 && initialised
			|| scenario != 3 && !initialised);
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
			while (variant < 1 || variant>12) {
				cout << "Wrong input. Try again > ";
				cin >> variant;
			}
		}
		return variant;
	}
};


int main()
{
	ConsoleInterfaceMenu::InitialMenu();
}
