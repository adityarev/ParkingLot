#include <iostream>
#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <queue>
using namespace std;

class Vehicle
{
	string reg_id;
	int no_parking;
	string colour;

public :
	Vehicle() {}
	
	Vehicle(string reg_id, int no_parking, string colour) {
		this->reg_id = reg_id;
		this->no_parking = no_parking;
		this->colour = colour;
	}
	
	string getRegID() { return this->reg_id; }
	int getNoParking() { return this->no_parking; }
	string getColour() { return this->colour; }
};

class Parking
{
	int N;
	string *pos;
	priority_queue<int, vector<int>, greater<int> > numPQ;
	map<string, Vehicle> onParking;
	map<string, bool> isExist;

public :
	Parking() {}
	
	Parking(int N) {
		this->N = N;
		
		pos = new string[N+2];
		for (int i=1; i<=N; i++)
			pos[i] = "-",
			numPQ.push(i);
		
		onParking.clear();
		isExist.clear();
		
		printf("Created a parking lot with %d slots\n", N);
	}
	
	void add_car(string reg_id, string colour) {
		if (!numPQ.empty()) {
			int curr = numPQ.top();
			numPQ.pop();
			
			isExist[reg_id] = true;
			pos[curr] = reg_id;
			Vehicle new_car(reg_id, curr, colour);
			onParking[reg_id] = new_car;
			
			printf ("Allocated slot number: %d\n", curr);
		}
		else puts("Sorry, parking lot is full");
	}
	
	void remove_car(int no_parking) {
		if (pos[no_parking] == "-") {
			puts("Parking slot already empty");
			return;
		}
		
		isExist[pos[no_parking]] = false;
		numPQ.push(no_parking);
		onParking.erase(pos[no_parking]);
		pos[no_parking] = "-";
		printf ("Slot number %d is free\n", no_parking);
	}
	
	void viewStatus() {
		printf ("Slot No.\tRegistration No\tColour\n");
		for (int i=1; i<=N; i++) {
			if (pos[i] != "-") {
				Vehicle curr = onParking[pos[i]];
				cout << curr.getNoParking() << "\t";
				cout << curr.getRegID() << "\t";
				cout << curr.getColour() << endl;
			}
		}
	}
	
	void get_regID_by_colour(string colour) {
		bool exist = false;
		
		for (int i=1; i<=N; i++) {
			if (pos[i] != "-") {
				Vehicle curr = onParking[pos[i]];
				if (curr.getColour() == colour) {
					if (!exist) exist = true;
					else cout << ", ";
					cout << curr.getRegID();
				}
			}
		}
		if (!exist) cout << "Not Found";
		cout << endl;
	}
	
	void get_regID_by_noParking(int no_parking) {
		if (pos[no_parking] == "-") puts("Not Found");
		else cout << pos[no_parking] << endl;
	}
	
	void get_noParking_by_colour(string colour) {
		bool exist = false;
		
		for (int i=1; i<=N; i++) {
			if (pos[i] != "-") {
				Vehicle curr = onParking[pos[i]];
				if (curr.getColour() == colour) {
					if (!exist) exist = true;
					else cout << ", ";
					cout << curr.getNoParking();
				}
			}
		}
		if (!exist) cout << "Not Found";
		cout << endl;
	}
	
	void get_noParking_by_regID(string reg_id) {
		if (isExist[reg_id]) {
			Vehicle curr = onParking[reg_id];
			cout << curr.getNoParking() << endl;
		}
		else puts("Not Found");
	}
	
	void get_colour_by_regID (string reg_id) {
		Vehicle curr = onParking[reg_id];
		if (isExist[reg_id]) cout << curr.getColour() << endl;
		else puts("Not Found");
	}
	
	void get_colour_by_no_parking(int no_parking) {
		if (pos[no_parking] != "-") {
			Vehicle curr = onParking[pos[no_parking]];
			cout << curr.getColour() << endl;
		}
		else puts("Not Found");
	}
};

int main(int argc, char **argv)
{
	Parking *parkingLot;
	int N;
	string command;
	
	for (int i=0; i<argc; i++) {
		printf ("%d -> %s\n", i+1, argv[i]);
	}
	
	// Waiting for create command
	while (cin >> command) {
		if (command == "create_parking_lot") {
			cin >> N;
			parkingLot = new Parking(N);
			break;
		}
		else puts("No parking lot available, please create it first!");
	}
	
	int no_parking;
	string reg_id, colour;
	while (cin >> command) {
		if (command == "park") {
			cin >> reg_id >> colour;
			parkingLot->add_car(reg_id, colour);
		}
		else if (command == "leave") {
			cin >> no_parking;
			parkingLot->remove_car(no_parking);
		}
		else if (command == "status") {
			parkingLot->viewStatus();
		}
		else if (command == "registration_numbers_for_cars_with_colour") {
			cin >> colour;
			parkingLot->get_regID_by_colour(colour);
		}
		else if (command == "registration_number_for_slot_number") {
			cin >> no_parking;
			parkingLot->get_regID_by_noParking(no_parking);
		}
		else if (command == "slot_numbers_for_cars_with_colour") {
			cin >> colour;
			parkingLot->get_noParking_by_colour(colour);
		}
		else if (command == "slot_number_for_registration_number") {
			cin >> reg_id;
			parkingLot->get_noParking_by_regID(reg_id);
		}
		else if (command == "colour_for_registration_number") {
			cin >> reg_id;
			parkingLot->get_colour_by_regID(reg_id);
		}
		else if (command == "colour_for_slot_number") {
			cin >> no_parking;
			parkingLot->get_colour_by_no_parking(no_parking);
		}
		else puts("Invalid command!");
	}
	
	return 0;
}
