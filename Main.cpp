#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string.h>
using namespace std;

void separator();
void display_schedules(int, char trains[], int stops[], string schedules[4][10][3]);
void book_tickets(string schedules[4][10][3], char trains[], int available_berths[], string passengers_data[40][7], int passengers);
void view_ticket(string passengers[40][7]);

int main()
{
    int n = 4; // Number of trains
    char trains[n] = {'A', 'B', 'C', 'D'};
    string departure[n] = {"05:00", "10:00", "16:00", "21:00"};
    int available_berths[n] = {40, 40, 40, 40};
    int stops[] = {7, 7, 9, 9}; // Number of places the trains are going to stop at as shown in the following array. Each entry corresponds to trains[i]

    // The passengers array holds all the data about a passenger such as name, boarding station, destination station, number of berths booked, train name, departure time, and price
    int passengers = 0;
    string passengers_data[40][7];

    // The following array is a bit complex so read this to understand what's going on:
    // The first dimension which is of length 4 corresponds to an entry in the trains array (A, B, C, D)
    // The second dimension which is of length 10 is to hold info regarding all the stations that the train is going to stop at.
    // The third dimension which is of length 3 is to store three different kinds of data about a particular train. The first entry is the name of the station, the second is for the departure time from that station and the third is the price it takes to get from the source destination to the station. Note that the price is 0 for all the first entries because that is where the train first departs from

    string schedules[4][10][3] = {
        // Train A: Rawalpindi to Karachi
        {
            {"Rawalpindi", "05:00", "0"},
            {"Lahore", "08:30", "1000"},
            {"Khanewal", "12:30", "2000"},
            {"Bahawalpur", "15:00", "3000"},
            {"Rohri", "19:30", "4000"},
            {"Hyderabad", "23:00", "5000"},
            {"Karachi", "(Destination)", "6000"}},

        // Train B: Karachi to Rawalpindi
        {
            {"Karachi", "10:00", "0"},
            {"Hyderabad", "11:30", "1000"},
            {"Rohri", "15:00", "2000"},
            {"Bahawalpur", "19:30", "3000"},
            {"Khanewal", "22:00", "4000"},
            {"Lahore", "02:00", "5000"},
            {"Rawalpindi", "(Destination)", "6000"}},

        // Train C: Lahore to Karachi
        {
            {"Lahore", "16:00", "0"},
            {"Sahiwal", "18:00", "1000"},
            {"Khanewal", "20:30", "1500"},
            {"Bahawalpur", "22:30", "2000"},
            {"Rahim Yar Khan", "01:00", "2500"},
            {"Rohri", "04:30", "3000"},
            {"Nawabshah", "07:00", "3500"},
            {"Hyderabad", "09:00", "4000"},
            {"Karachi", "(Destination)", "4500"}},

        // Train D: Karachi to Lahore
        {
            {"Karachi", "21:00", "0"},
            {"Hyderabad", "22:30", "1000"},
            {"Nawabshah", "01:00", "1500"},
            {"Rohri", "04:30", "2000"},
            {"Rahim Yar Khan", "07:00", "2500"},
            {"Bahawalpur", "10:00", "3000"},
            {"Khanewal", "13:00", "3500"},
            {"Sahiwal", "15:30", "4000"},
            {"Lahore", "(Destination)", "4500"}}};

    int choice;
    while (true)
    {
        cout << "=> Press 1 to view train schedules" << endl;
        cout << "=> Press 2 to book tickets" << endl;
        cout << "=> Press 3 to view your ticket" << endl;
        cout << "=> Press 0 to exit" << endl
             << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            system("cls");
            system("Color 0C");
            cout << "Invalid Input! Try Again!";
            Sleep(1000);
            system("cls");
            system("Color 07");
            continue;
        }

        if (choice == 0)
        {
            break;
        }
        else if (choice == 1)
        {
            display_schedules(n, trains, stops, schedules);
        }
        else if (choice == 2)
        {
            book_tickets(schedules, trains, available_berths, passengers_data, passengers);
        }
        char show_menu;
        cout << "Return to menu? (y/n): ";
        cin >> show_menu;
        show_menu = tolower(show_menu);
        if (show_menu == 'y')
        {
            system("cls");
        }
        else
        {
            break;
        }
    }

    return 0;
}
void separator()
{
    cout << endl
         << "--------------------------------------------------------------------" << endl
         << endl;
}
void display_schedules(int n, char trains[], int stops[], string schedules[4][10][3])
{
    char tname;
    cout << "Enter name of the train (A, B, C, D): ";
    cin >> tname;

    tname = toupper(tname);
    int tindex;

    for (int i = 0; i < n; i++)
    {
        if (trains[i] == tname)
        {
            tindex = i;
            break;
        }
    }
    separator();
    cout << setw(20) << left << "Station" << setw(20) << left << "Departure Time" << endl;
    for (int i = 0; i < stops[tindex]; i++)
    {
        cout << setw(20) << left << schedules[tindex][i][0] << setw(20) << left << schedules[tindex][i][1] << endl;
        Sleep(500);
    }

    separator();
}

void book_tickets(string schedules[4][10][3], char trains[], int available_berths[], string passengers_data[40][7], int passengers)
{
    string boarding_station, destination_station, departure_time;
    int berths, price;

    cout << "Enter boarding station: ";
    cin >> boarding_station;
    cout << "Enter destination station: ";
    cin >> destination_station;

    while (true)
    {
        cout << "Enter number of berths: ";
        cin >> berths;
        if (berths <= 0)
        {
            cout << "Enter valid number of berths!" << endl;
        }
        else
        {
            break;
        }
    }

    // Here I'm going to search through the schedules of each of the trains and find the one that has the boarding and destination stations in its route. Note that for the train to be selected it is imperative that the boarding station has an index less than that of the destination station.

    int boarding_index, destination_index; // Indices of the respective stations along the train's route
    char booked_train;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (boarding_station == schedules[i][j][0])
            {
                boarding_index = j;
            }
            else if (destination_station == schedules[i][j][0])
            {
                destination_index = j;
            }
        }
        if (destination_index - boarding_index > 0)
        {
            if (available_berths[i] > 0)
            {
                if (berths <= available_berths[i])
                {
                    booked_train = trains[i];
                    departure_time = schedules[i][boarding_index][1];
                    price = berths * stoi(schedules[i][destination_index][2]) - stoi(schedules[i][boarding_index][2]);
                    available_berths[i] -= berths;
                    break;
                }
                else
                {
                    char book_or_not;
                    cout << "Sorry, there are only " << available_berths[i] << " available. Do you wish to book them?" << endl;
                    cout << "Enter your choice (y/n): ";
                    cin >> book_or_not;
                    book_or_not = tolower(book_or_not);
                    if (book_or_not == 'y')
                    {
                        book_tickets(schedules, trains, available_berths, passengers_data, passengers);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "Sorry, no berths available for the entered boarding and destination stations" << endl;
            }
        }
        else
        {
            cout << "Sorry, no trains are available for the entered boarding and destination stations" << endl;
        }
    }

    // If tickets were successfully booked, update the passenger's data in the passenger array
    if (booked_train)
    {
        string name;
        cout << "Enter your name: ";
        cin.ignore(1000, '\n');
        getline(cin, name);

        // Index of a particular passenger in the passenger data array:
        int i = passengers;
        // The passengers array holds all the data about a passenger such as name, boarding station, destination station, number of berths booked, train name, departure time, and price

        // Passenger's Name:
        passengers_data[i][0] = name;
        // Boarding Station:
        passengers_data[i][1] = boarding_station;
        // Destination Station:
        passengers_data[i][2] = destination_station;
        // Boarding Station:
        passengers_data[i][3] = berths;
        // Boarding Station:
        passengers_data[i][4] = booked_train;
        // Boarding Station:
        passengers_data[i][5] = departure_time;
        // Boarding Station:
        passengers_data[i][6] = price;
    }
}

void view_ticket(string passengers[40][7]) {}