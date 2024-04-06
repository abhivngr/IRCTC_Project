#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int ticket;
int count = 0;

const int nm = 20;
string trainNumber[nm] = {};
string sourceStation[nm] = {};
string destinationStation[nm] = {};
string departureTime[nm] = {};
string arrivalTime[nm] = {};
string totalDistance[nm] = {};

void AddRecord()
{
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
    cout << "totalDistance :";
    getline(cin, td);

    for (int i = 0; i < nm; i++)
    {
        if (trainNumber[i].empty())
        {
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

void DisplayRecords()
{
    cout << "Train Records:\n";
    cout << "----------------------------------------\n";
    cout << "Train No\tSource\t\tDestination\tDeparture\tArrival\tTotalDistance\n";
    cout << "----------------------------------------\n";

    for (int i = 0; i < nm; i++)
    {
        if (!trainNumber[i].empty())
        {
            cout << trainNumber[i] << "\t\t" << sourceStation[i] << "\t\t" << destinationStation[i] << "\t\t" << departureTime[i] << "\t\t" << arrivalTime[i] << "\t\t" << totalDistance[i] << endl;
        }
    }
}

void WriteToFile(const string filename)
{
    ofstream file(filename, ios::app);
    if (file.is_open())
    {
        for (int i = 0; i < nm; i++)
        {
            if (!trainNumber[i].empty())
            {
                file << trainNumber[i] << "\t\t" << sourceStation[i] << "\t\t" << destinationStation[i] << "\t\t" << departureTime[i] << "\t\t" << arrivalTime[i] << "\t\t" << totalDistance[i] << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file.\n";
    }
}

void ReadFromFile(const string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string tno, source, destination, depTime, arrTime, td;
        int count = 0;
        while (count < nm && file >> tno >> source >> destination >> depTime >> arrTime >> td)
        {
            trainNumber[count] = tno;
            sourceStation[count] = source;
            destinationStation[count] = destination;
            departureTime[count] = depTime;
            arrivalTime[count] = arrTime;
            totalDistance[count] = td;
            count++;
        }
        file.close();
        DisplayRecords(); // Display records after reading all of them.
    }
    else
    {
        cout << "Unable to open file.\n";
    }
}

void SearchTrainRecord(const string filename, const string searchTerm1, const string searchTerm2)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string tno, source, destination, depTime, arrTime, td;
        int count = 0;

        while (file >> tno >> source >> destination >> depTime >> arrTime >> td)
        {
            if (source == searchTerm1 && destination == searchTerm2)
            {
                count++;
                cout << "Train Record:\n";
                cout << "----------------------------------------\n";
                cout << "Train No\tSource\t\tDestination\tDeparture\tArrival\tTotalDistance\n";
                cout << "----------------------------------------\n";
                cout << tno << "\t\t" << source << "\t\t" << destination << "\t\t" << depTime << "\t\t" << arrTime << "\t\t" << td << endl;
            }
        }

        if (count == 0)
        {
            cout << "Train record source and destination station " << searchTerm1 << " to " << searchTerm2 << " not found." << endl;
        }

        file.close();
    }
    else
    {
        cout << "Unable to open file.\n";
    }
}
// Calculate charges for economy travel
void economy(const string filename, const string searchTerm1, const string searchTerm2)
{
    ifstream file(filename);
    string economydistance;
    if (file.is_open())
    {
        string tno, source, destination, depTime, arrTime, td;
        while (file >> tno >> source >> destination >> depTime >> arrTime >> td)
        {
            if (source == searchTerm1 && destination == searchTerm2)
            {
                economydistance = td;
            }
        }
    }
    int economycharge = 5;                // Base charge for the service
    int distance = stoi(economydistance); // Convert string to integer
    int economytotalcost = ticket * economycharge * distance;
    cout << "Total charge for Economy Travel is : " << economytotalcost << endl;
}
// Calculate charges for ac travel
void ac(const string filename, const string searchTerm1, const string searchTerm2)
{
    ifstream file(filename);
    string acdistance;
    if (file.is_open())
    {
        string tno, source, destination, depTime, arrTime, td;
        while (file >> tno >> source >> destination >> depTime >> arrTime >> td)
        {
            if (source == searchTerm1 && destination == searchTerm2)
            {
                acdistance = td;
            }
        }
    }
    int accharge = 15;               // Base charge for the service
    int distance = stoi(acdistance); // Convert string to integer
    int actotalcost = ticket * accharge * distance;
    cout << "Total charge for AC Travel is : " << actotalcost << endl;
}
string pnr(const string filename)
{
    ifstream file(filename);
    int rev_trno = 0;
    // srand(time(NULL));// Seed the random number generator with current time
    // if (file.is_open())
    // {
    //     string tno, source, destination, depTime, arrTime, td;
    //     int trno;

    //     while (file >> tno >> source >> destination >> depTime >> arrTime >> td)
    //     {
    //         trno = stoi(tno);
    //     }

    //     while (trno > 0)
    //     {
    //         rev_trno = rev_trno * 10 + trno % 10;
    //         trno = trno / 10;
    //     }
        //}

        unsigned long long pnr_number = 0;
        for (int i = 0; i < 10; ++i) {
            pnr_number = pnr_number * 10 + (rand() % 10);   // rand function is used to generate random number.
        }
        file.close();
        stringstream ss;
        ss << pnr_number;
        return ss.str();
}
void book(const string filename, const string filename1)
{
    string searchTerm1, searchTerm2,tno, source, destination, depTime, arrTime, td, trainno;
    int age;
    string name;
    char gender;
    cout << "Enter the source and final station to search: ";
    // cin.ignore(); // Clear the input buffer before reading string with getline
    getline(cin, searchTerm1);
    getline(cin, searchTerm2);

    SearchTrainRecord("train_records.txt", searchTerm1, searchTerm2);
    cout << "\nEnter number of ticket\n";
    cin >> ticket;
    // Available tickets for each coach type
    int avail_economy = 36, avail_ac = 36; // Assuming half of the total tickets are economy and AC
    int coach;
    cout << "Enter coach category:- \n 1 for Economy\n 2 for AC \n";
    cin >> coach;
    ifstream traindetails(filename);
    if (traindetails.is_open())
    {
        int count = 0;
        while (traindetails >> tno >> source >> destination >> depTime >> arrTime >> td)
        {
            if(source==searchTerm1 && destination==searchTerm2)
            {
                trainno=tno;
            }
        }
        traindetails.close();
    }
    ofstream bookedTickets(filename1, ios::app); // Open file to write booked tickets
    if (!bookedTickets.is_open()) {
        cout << "Unable to open file for booked tickets.\n";
        return;
    }
    // Check availability and book tickets according to the selected coach
    switch (coach)
    {
    case 1: // Economy
        avail_economy = avail_economy - count;
        cout << "Available ticket is " << avail_economy << "ticket \n";
        if (count < avail_economy)
        {
            cout << "Economy coach selected. Booking tickets...\n";
            for (int i = 0; i < ticket; i++)
            {
                cout << "Enter passenger name:\n";
                cin >> name;
                cout << "Enter passenger age:\n";
                cin >> age;
                cout << "Enter passenger gender :\n";
                cin >> gender;
                count++;
                // Write booked ticket details to file along with PNR number, train number, fare cost by economy, source and destination stations
                bookedTickets << "Name: " << name << "\t Age: " << age << "\tGender: " << gender << "\tPNR: " << pnr("train_records.txt");
                //pnr("train_records.txt"); // Generate PNR number and display
                bookedTickets << "\nTrain Number: " << trainno; // Assuming only one train record is displayed
                economy("train_records.txt", searchTerm1, searchTerm2);
                bookedTickets << "\tSource: " << searchTerm1 << "\tDestination: " << searchTerm2 << endl;
            }
        }
        else
        {
            cout << "Economy coach is fully booked. Please select another coach.\n";
        }
        break;
    case 2: // AC
        avail_ac = avail_ac - count;
        cout << "Available ticket is " << avail_ac << "ticket \n";
        if (count < avail_ac)
        {
            cout << "AC coach selected. Booking tickets...\n";
            for (int i = 0; i < ticket; i++)
            {
                cout << "Enter passenger name:\n";
                cin >> name;
                cout << "Enter passenger age:\n";
                cin >> age;
                cout << "Enter passenger gender :\n";
                cin >> gender;
                count++;
                // Write booked ticket details to file along with PNR number, train number, fare cost by AC, source and destination stations
                bookedTickets << "Name: " << name << "\tAge: " << age << "\tGender: " << gender << "\tPNR: " << pnr("train_records.txt");
                cout << pnr("train_records.txt"); // Generate PNR number and display
                bookedTickets << "\nTrain Number: " << trainno; // since only one train need to be displayed.
                ac("train_records.txt", searchTerm1, searchTerm2);
                bookedTickets << "\tSource: " << searchTerm1 << "\tDestination: " << searchTerm2 << endl;
            }
        }
        else
        {
            cout << "AC coach is fully booked. Please select another coach.\n";
        }
        break;
    default:
        cout << "Invalid coach selection.\n";
    }

    bookedTickets.close(); // Close the file after writing
}
void DisplayTicketByPNR(const string filename, const string pnr)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        int count = 0;
        while (getline(file, line))
        {
            // Check if the line contains the PNR number
            if (line.find(pnr) != string::npos)
            {
                cout << "Ticket Details:\n";
                cout << line << endl; // Display the entire line containing the PNR number
                count++;
                break;
            }
        }
        if (count==0)
        {
            cout << "Ticket with PNR number " << pnr << " not found.\n";
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file.\n";
    }
}

void menu()
{
    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "\t1. Add Train Record\n";
        cout << "\t2. Display Train Records\n";
        cout << "\t3. Book Tickets\n";
        cout << "\t4. Exit\n";
        cout << "\tEnter your choice: ";
        cin >> choice;
        string adminid;
        int adminpass;
        string searchTerm1, searchTerm2;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "                            ----------=>Admin portal<=----------                            ";
            cout << "\n                                  Admin Id : ";
            getline(cin, adminid);
            cout << "\n                                  Admin Password : ";
            cin >> adminpass;
            if (adminid == "admin" && adminpass == 1234)
            {
                cout << "\n                           1.Add train record.";
                cout << "\n                           2. Search the train from source to destination station.\n";
                cout << "                             Enter the choice : ";
                int ch;
                cin >> ch;
                switch (ch)
                {
                case 1:
                    cout << "                              Add train record.\n";
                    AddRecord();
                    WriteToFile("train_records.txt");
                    break;
                case 2:
                    cout << "                        Enter the source and final station to search: \n";
                    cin.ignore(); // Clear the input buffer before reading string with getline
                    getline(cin, searchTerm1);
                    getline(cin, searchTerm2);
                    SearchTrainRecord("train_records.txt", searchTerm1, searchTerm2);
                    break;
                default:
                    break;
                }
            }
            break;
        case 2:
            ReadFromFile("train_records.txt");
            break;
            break;
        case 3:
            book("train_records.txt","booked_tickets.txt");
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 4.\n";
        }
    } while (choice != 4);
}

int main()
{
    menu();
    return 0;
}
