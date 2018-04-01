#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
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
protected :
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

class IParking : public Parking {
public :
	IParking() { }
	IParking(int N) : Parking(N) { }
	
	void run() {
		string command;
		string reg_id;
		int no_parking;
		string colour;
		
		while (cin >> command) {
			if (command == "park") {
				cin >> reg_id >> colour;
				add_car(reg_id, colour);
			}
			else if (command == "leave") {
				cin >> no_parking;
				remove_car(no_parking);
			}
			else if (command == "status") {
				viewStatus();
			}
			else if (command == "registration_numbers_for_cars_with_colour") {
				cin >> colour;
				get_regID_by_colour(colour);
			}
			else if (command == "registration_number_for_slot_number") {
				cin >> no_parking;
				get_regID_by_noParking(no_parking);
			}
			else if (command == "slot_numbers_for_cars_with_colour") {
				cin >> colour;
				get_noParking_by_colour(colour);
			}
			else if (command == "slot_number_for_registration_number") {
				cin >> reg_id;
				get_noParking_by_regID(reg_id);
			}
			else if (command == "colour_for_registration_number") {
				cin >> reg_id;
				get_colour_by_regID(reg_id);
			}
			else if (command == "colour_for_slot_number") {
				cin >> no_parking;
				get_colour_by_no_parking(no_parking);
			}
			else puts("Invalid command!");
		}
	}
};

class IParkingFile : public Parking {
public :
	IParkingFile() { }
	IParkingFile(int N) : Parking(N) { }
	
	void run(FILE *inp_file) {
		char input[101];
		char command[51];
		char reg_id[21];
		int no_parking;
		char colour[21];
		FILE *in = inp_file;
		
		while (fgets(input, sizeof(input), in)) {
			sscanf(input, "%s", command);
			
			if (strcmp(command,"park") == 0) {
				sscanf(input, "%s %s %s", command, reg_id, colour);
				add_car(toString(reg_id, strlen(reg_id)), toString(colour, strlen(colour)));
			}
			else if (strcmp(command,"leave") == 0) {
				sscanf(input, "%s %d", command, &no_parking);
				remove_car(no_parking);
			}
			else if (strcmp(command,"status") == 0) {
				viewStatus();
			}
			else if (strcmp(command,"registration_numbers_for_cars_with_colour") == 0) {
				sscanf(input, "%s %s", command, colour);
				get_regID_by_colour(toString(colour, strlen(colour)));
			}
			else if (strcmp(command,"registration_number_for_slot_number") == 0) {
				sscanf(input, "%s %d", command, &no_parking);
				get_regID_by_noParking(no_parking);
			}
			else if (strcmp(command,"slot_numbers_for_cars_with_colour") == 0) {
				sscanf(input, "%s %s", command, colour);
				get_noParking_by_colour(toString(colour, strlen(colour)));
			}
			else if (strcmp(command,"slot_number_for_registration_number") == 0) {
				sscanf(input, "%s %s", command, reg_id);
				get_noParking_by_regID(toString(reg_id, strlen(reg_id)));
			}
			else if (strcmp(command,"colour_for_registration_number") == 0) {
				sscanf(input, "%s %s", command, reg_id);
				get_colour_by_regID(toString(reg_id, strlen(reg_id)));
			}
			else if (strcmp(command,"colour_for_slot_number") == 0) {
				sscanf(input, "%s %d", command, &no_parking);
				get_colour_by_no_parking(no_parking);
			}
			else puts("Invalid command!");
		}
	}
	
	string toString(char s[], int n) {
		string str = "";
		for (int i=0; i<n; i++)
			str += s[i];
		return str;
	}
};

int main(int argc, char **argv)
{
	if (argc<2) {
		IParking *parkingLot;
		
		// Waiting for create command
		string command;
		while (cin >> command) {
			if (command == "create_parking_lot") {
				int N;
				cin >> N;
				parkingLot = new IParking(N);
				break;
			}
			else puts("No parking lot available, please create it first!");
		}
		
		parkingLot->run();
	}
	else  {
		FILE *in;
		in = fopen(argv[1], "r");
		IParkingFile *parkingLot;
		
		char input[101];
		while (fgets(input, sizeof(input), in)) {
			char command[51];
			sscanf(input, "%s", command);
			if (strcmp(command,"create_parking_lot") == 0) {
				int N;
				sscanf(input, "%s %d", command, &N);
				parkingLot = new IParkingFile(N);
				break;
			}
			else puts("No parking lot available, please create it first!");
		}
		
		parkingLot->run(in);
		fclose(in);
	}
	
	return 0;
}
