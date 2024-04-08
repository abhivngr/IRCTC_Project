#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime> // For time
#include <sstream> // For stringstream

using namespace std;

const int nm = 20;
string trainNumber[nm] = {};
string sourceStation[nm] = {};
string destinationStation[nm] = {};
string departureTime[nm] = {};
string arrivalTime[nm] = {};
string totalDistance[nm] = {};
int ticketCount = 0; // Updated variable name for clarity

void AddRecord() {
    string tno, source, destination, depTime, arrTime, td;
    cout << "Train no: ";
    getline(cin, tno);
    cout << "Source station: ";
    getline(cin, source);
    cout << "Destination station: ";
    getline(cin, destination);
    cout << "Departure time: ";
    getline(cin, depTime);
    cout << "Arrival time: ";
    getline(cin, arrTime);
    cout << "Total Distance: ";
    getline(cin, td);

    for (int i = 0; i < nm; i++) {
        if (trainNumber[i].empty()) {
            trainNumber[i] = tno;
            sourceStation[i] = source;
            destinationStation[i] = destination;
            departureTime[i] = depTime;
            arrivalTime[i] = arrTime;
            totalDistance[i] = td;
            break;
        }
    }
}

void DisplayRecords() {
    cout << "Train Records:\n";
    cout << "----------------------------------------\n";
    cout << "Train No\tSource\t\tDestination\tDeparture\tArrival\tTotalDistance\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < nm; i++) {
        if (!trainNumber[i].empty()) {
            cout << trainNumber[i] << "\t\t" << sourceStation[i] << "\t\t"
                 << destinationStation[i] << "\t\t" << departureTime[i] << "\t\t"
                 << arrivalTime[i] << "\t\t" << totalDistance[i] << endl;
        }
    }
}

void WriteToFile(const string& filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        for (int i = 0; i < nm; i++) {
            if (!trainNumber[i].empty()) {
                file << trainNumber[i] << "\t" << sourceStation[i] << "\t"
                     << destinationStation[i] << "\t" << departureTime[i] << "\t"
                     << arrivalTime[i] << "\t" << totalDistance[i] << "\n";
            }
        }
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

void ReadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string tno, source, destination, depTime, arrTime, td;
        int count = 0;
        while (count < nm && getline(file, tno, '\t') && getline(file, source, '\t') && 
               getline(file, destination, '\t') && getline(file, depTime, '\t') && 
               getline(file, arrTime, '\t') && getline(file, td)) {
            trainNumber[count] = tno;
            sourceStation[count] = source;
            destinationStation[count] = destination;
            departureTime[count] = depTime;
            arrivalTime[count] = arrTime;
            totalDistance[count] = td;
            count++;
        }
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

// Update the rest of your functions (SearchTrainRecord, economy, ac, pnr, book, DisplayTicketByPNR) similarly, ensuring to use proper file handling and logic.
void SearchTrainRecord(const string& filename, const string& searchTerm1, const string& searchTerm2) {
    ifstream file(filename);
    bool found = false;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string tno, source, destination, depTime, arrTime, td;
            getline(ss, tno, '\t');
            getline(ss, source, '\t');
            getline(ss, destination, '\t');
            getline(ss, depTime, '\t');
            getline(ss, arrTime, '\t');
            getline(ss, td);
            if (source == searchTerm1 && destination == searchTerm2) {
                found = true;
                cout << "Train Record Found:\n";
                cout << "Train No: " << tno << ", Source: " << source << ", Destination: " << destination
                     << ", Departure Time: " << depTime << ", Arrival Time: " << arrTime << ", Total Distance: " << td << endl;
            }
        }
        if (!found) {
            cout << "No train record found for " << searchTerm1 << " to " << searchTerm2 << ".\n";
        }
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}

string pnr() {
    unsigned long long pnr_number = 0;
    for (int i = 0; i < 10; ++i) {
        pnr_number = pnr_number * 10 + (rand() % 10);
    }
    stringstream ss;
    ss << pnr_number;
    return ss.str();
}

void economy(const string& filename, const string& searchTerm1, const string& searchTerm2, int ticketCount) {
    cout << "Total charge for Economy Travel is: " << ticketCount * 5 << " (flat rate per ticket, not distance-based in this example)" << endl;
}

void ac(const string& filename, const string& searchTerm1, const string& searchTerm2, int ticketCount) {
    cout << "Total charge for AC Travel is: " << ticketCount * 15 << " (flat rate per ticket, not distance-based in this example)" << endl;
}

void book(const string& trainFilename, const string& ticketFilename) {
    string searchTerm1, searchTerm2;
    cout << "Enter the source station: ";
    getline(cin, searchTerm1);
    cout << "Enter the destination station: ";
    getline(cin, searchTerm2);

    SearchTrainRecord(trainFilename, searchTerm1, searchTerm2);

    cout << "\nEnter number of tickets: ";
    int ticket;
    cin >> ticket;
    cin.ignore();

    cout << "Enter coach category (1 for Economy, 2 for AC): ";
    int coach;
    cin >> coach;
    cin.ignore();

    string passengerName, pnrNumber = pnr();
    int passengerAge;
    char passengerGender;
    for (int i = 0; i < ticket; i++) {
        cout << "Enter passenger name: ";
        getline(cin, passengerName);
        cout << "Enter passenger age: ";
        cin >> passengerAge;
        cin.ignore();
        cout << "Enter passenger gender (M/F): ";
        cin >> passengerGender;
        cin.ignore();

        ofstream bookedTickets(ticketFilename, ios::app);
        if (!bookedTickets.is_open()) {
            cout << "Unable to open file for booked tickets.\n";
            return;
        }
        bookedTickets << "PNR: " << pnrNumber << "\tName: " << passengerName << "\tAge: " << passengerAge << "\tGender: " << passengerGender << "\n";
        bookedTickets.close();
    }

    if (coach == 1) {
        economy(trainFilename, searchTerm1, searchTerm2, ticket);
    } else if (coach == 2) {
        ac(trainFilename, searchTerm1, searchTerm2, ticket);
    } else {
        cout << "Invalid coach selection.\n";
    }
}

void DisplayTicketByPNR(const string& filename, const string& pnr) {
    ifstream file(filename);
    bool found = false;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find(pnr) != string::npos) {
                found = true;
                cout << "Ticket Details: " << line << endl;
                break;
            }
        }
        if (!found) {
            cout << "Ticket with PNR number " << pnr << " not found.\n";
        }
        file.close();
    } else {
        cout << "Unable to open file.\n";
    }
}


#include <cstdlib> // Required for srand and rand
#include <ctime> // Required for time

// The rest of the includes and function prototypes remain unchanged

void menu() {
    int choice;
    string filename = "train_records.txt";
    string ticketFilename = "booked_tickets.txt";
    
    do {
        cout << "\nMenu:\n"
             << "\t1. Add Train Record\n"
             << "\t2. Display Train Records\n"
             << "\t3. Book Tickets\n"
             << "\t4. Display Tickets by PNR\n"
             << "\t5. Exit\n"
             << "\tEnter your choice: ";
        cin >> choice;
        cin.ignore(); // To handle the newline character after cin >>

        switch (choice) {
            case 1:
                AddRecord();
                WriteToFile(filename);
                break;
            case 2:
                ReadFromFile(filename);
                break;
            case 3:
                book(filename, ticketFilename);
                break;
            case 4: {
                string pnr;
                cout << "Enter PNR to display ticket: ";
                getline(cin, pnr);
                DisplayTicketByPNR(ticketFilename, pnr);
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    } while (choice != 5);
}



int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Properly seed random number generation
    menu();
    return 0;
}
