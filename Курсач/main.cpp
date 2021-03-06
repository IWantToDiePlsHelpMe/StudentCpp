#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
class Train_ {
public:
	string City;
	string Time;

	Train_() {
		City = "";
		Time = "";
	}

	Train_(string City, string Time) : City(City), Time(Time) {}

	friend ostream& operator<<(ostream& out, Train_& X) {
		out << X.City << " " << X.Time;
		return out;
	}
	friend istream& operator>>(istream& in, Train_& X) {
		in >> X.City >> X.Time;
		return in;
	}
	friend bool operator==(Train_& A, Train_& B) {
		return(A.City == B.City);
	}
};

template<typename Tkey, typename Ttrain>
class Map {
private:
	struct conformity {
		Tkey key;
		Ttrain train;;
	};

	conformity* con_array;
	int size;
	int insize;
public:
	Map() : size(10), insize(0) {
		con_array = new conformity[size];
	}

	~Map() {
		delete[] con_array;
	}

	void add(Tkey key, Ttrain train) {
		bool check = true;
		/* for (int i = 0; i < insize; i++) {
			if (con_array[i].key == key) check = false;
		} */
		if (check == true) {
			if (insize == size) {
				conformity* old = con_array;
				con_array = new conformity[size + 2];
				memcpy(con_array, old, sizeof(conformity) + 2);
				size += 2;
				delete old;
			}
			conformity ct;
			ct.key = key;
			ct.train = train;
			con_array[insize++] = ct;
		}
	}

	friend ostream& operator<<(ostream& out, Map& X) {
		for (int i = 0; i < X.insze; i++) out << X.con_array[i].key << " " << X.con_array[i].train << endl;
		return out;
	}

	friend istream& operator<<(istream& in, Map& X) {
		Tkey key; Ttrain train;
		in >> key;
		in >> train;
		X.add(key, train);
		return in;
	}

	void searchC(Ttrain check){
		for (int i = 0; i < insize; i++) {
			if (con_array[i].train == check) cout << con_array[i].key << " " << con_array[i].train<<endl;
		}
	}

	void searchK(Tkey key) {
		for (int i = 0; i < insize; i++) {
			if (con_array[i].key == key) cout << con_array[i].key << " " << con_array[i].train << endl;
		}
	}

	void print() {
		for (int i = 0; i < insize; i++) {
			cout << con_array[i].key << " " << con_array[i].train << endl;
		}
	}
	void samesign(Ttrain train) {
		for (int i = 0; i < insize; i++)if (con_array[i].train == train) cout << con_array[i].train;
	}

	void savelist() {
		ofstream out;
		out.open("board.txt");
		for (int i = 0; i < insize; i++) {
			if (i == insize - 1) {
				out << con_array[i].key << endl << con_array[i].train << endl;
			}
			else out << con_array[i].key << endl << con_array[i].train << endl;
		}
	}

	void getlist() {
		bool end = 1;
		ifstream lst; lst.open("board.txt");
		if (!lst) { cout << ">ERROR, NO FILE" << endl; }
		else {
			Tkey key;
			Ttrain train;
			while (!lst.eof()) {
				lst >> key;
				lst >> train;
				add(key, train);
			}
		}
		lst.close();
	}


};

int main() {
	Map<int, Train_> Board;
	Board.getlist();
	//// MENU ////
	int Key;
	string City, Time;
	int next = true;
	do {
		cout << "/////MENU///// \n 1) Add train \n 2) Find train by number \n 3) Find train by City \n 4) Show all trains \n 5) Exit " << endl;
		int var;
		cin >> var;
		switch (var) {
		case 1: {
			cout << "Add train \n Input Num, City, Time (hours : minutes): ";
			cin >> Key;
			cin >> City;
			cin >> Time;
			cout << endl;
			Board.add(Key, Train_(City, Time));
			cout << "! \n \n";
			break;
			}
		case 2: {
			cout << "Find train by number \n Enter Num: ";
			cin >> Key;
			cout << endl;
			Board.searchK(Key);
			cout << "! \n \n";
			break;
			}
		case 3: {
			cout << "Find train by City \n Enter City: ";
			cin >> City;
			cout << endl;
			Board.searchC(Train_(City, " "));
			cout << "! \n \n";
			break;
			}
		case 4: {
			cout << "Board \n \n";
			Board.print();
			cout << "! \n \n";
			break;
			}
		case 5: {
			cout << "Exit! Bye!";
			next = false;
			cout << "! \n \n";
			break;
			}
		}
	}while (next);
	Board.savelist();
}
