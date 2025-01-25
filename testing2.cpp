#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string.h>
using namespace std;

// Replace number of seats with number of passengers as per the problem statement
// Show success message when ticket is booked successfully
// Remove that change in color for invalid input because it's inconsitent

void separator();
void display_schedules(int, char trains[], int stops[], string schedules[4][10][3]);
void book_tickets(string schedules[4][10][3], char trains[], int available_seats[], string passengers_data[40][7], int passengers);
void view_ticket(string passengers_data[40][7]);

int main()
{
    int n = 4; // Number of trains
    char trains[n] = {'A', 'B', 'C', 'D'};
    string departure[n] = {"05:00", "10:00", "16:00", "21:00"};
    int available_seats[n] = {40, 40, 40, 40};
    int stops[] = {7, 7, 9, 9}; // Number of places the trains are going to stop at as shown in the following array. Each entry corresponds to trains[i]

    // The passengers array holds all the data about a passenger such as name, boarding station, destination station, number of seats booked, train name, departure time, and price
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
        Sleep(500);
        cout << "=> Press 2 to book tickets" << endl;
        Sleep(500);
        cout << "=> Press 3 to view your ticket" << endl;
        Sleep(500);
        cout << "=> Press 0 to exit" << endl
             << endl;
        Sleep(500);
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
            Sleep(2000);
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
            book_tickets(schedules, trains, available_seats, passengers_data, passengers);
        }
        else if (choice == 3)
        {
            view_ticket(passengers_data);
        }

        else
        {
            system("cls");
            system("Color 0C");
            cout << "Invalid Input! Try Again!";
            Sleep(2000);
            system("cls");
            system("Color 07");
            continue;
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
    Sleep(500);
    cout << setw(20) << left << "Station" << setw(20) << left << "Departure Time" << endl
         << endl;
    for (int i = 0; i < stops[tindex]; i++)
    {
        cout << setw(20) << left << schedules[tindex][i][0] << setw(20) << left << schedules[tindex][i][1] << endl;
        Sleep(500);
    }

    separator();
}

void book_tickets(string schedules[4][10][3], char trains[], int available_seats[], string passengers_data[40][7], int passengers)
{
    string boarding_station, destination_station, booked_train, name;
    int boarding_index = -1, destination_index = -1, seats = 0, train_index, ticket_price;

    cout << "Enter boarding station: ";
    cin >> boarding_station;
    cout << "Enter destination station: ";
    cin >> destination_station;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (boarding_station == schedules[i][j][0])
            {
                boarding_index = j;
            }
            if (destination_station == schedules[i][j][0])
            {
                destination_index = j;
            }
        }
        if (boarding_index != -1 && destination_index != -1 && boarding_index < destination_index)
        {
            booked_train = string(1, trains[i]);
            train_index = i;
            break;
        }
    }
    if (boarding_index != -1 && destination_index != -1 && boarding_index < destination_index)
    {
        while (true)
        {
            cout << "Enter number of seats: ";
            cin >> seats;
            if (seats > 0)
            {
                break;
            }
            else
            {
                cout << "Invalid input!" << endl;
            }
        }

        // Check availability of seats
        if (seats <= available_seats[train_index])
        {
            cout << "Enter your name: ";
            cin >> name;
            cout << endl;
            available_seats[train_index] -= seats;
            ticket_price = seats * (stoi(schedules[train_index][destination_index][2]) - stoi(schedules[train_index][boarding_index][2]));

            // Entering data to passengers array
            passengers_data[passengers][0] = name;
            passengers_data[passengers][1] = boarding_station;
            passengers_data[passengers][2] = destination_station;
            passengers_data[passengers][3] = booked_train;
            passengers_data[passengers][4] = schedules[train_index][0][1];
            passengers_data[passengers][5] = to_string(seats);
            passengers_data[passengers][6] = to_string(ticket_price);
            passengers++;
            cout << "Ticket booked successfully!" << endl;
        }
        else
        {
            cout << "Sorry, only " << available_seats[train_index] << " seats are available." << endl
                 << endl;
        }
    }
    else
    {
        cout << "Sorry, no trains found for the entered route" << endl
             << endl;
    }
}

void view_ticket(string passengers_data[40][7])
{
    string name = "";
    cout << "Enter passenger name: ";
    cin >> name;

    int passenger_index = -1;
    for (int i = 0; i < 40; i++)
    {
        if (name == passengers_data[i][0])
        {
            passenger_index = i;
            break;
        }
    }

    if (passenger_index == -1)
    {
        cout << name << " was not found in the list of passengers" << endl;
    }

    separator();
    Sleep(500);
    cout << setw(25) << left << "Name" << setw(10) << "|" << setw(25) << left << passengers_data[passenger_index][0] << endl;
    Sleep(500);
    cout << setw(25) << left << "Boarding Station" << setw(10) << "|" << setw(25) << left << passengers_data[passenger_index][1] << endl;
    Sleep(500);
    cout << setw(25) << left << "Destination Station" << setw(10) << "|" << setw(25) << left << passengers_data[passenger_index][2] << endl;
    Sleep(500);
    cout << setw(25) << left << "Train Name" << setw(10) << "|" << setw(25) << left << passengers_data[passenger_index][3] << endl;
    Sleep(500);
    cout << setw(25) << left << "Departure Time" << setw(10) << "|" << setw(25) << left << passengers_data[passenger_index][4] << endl;
    Sleep(500);
    cout << setw(25) << left << "Ticket Price" << setw(10) << "|" << setw(25) << left << passengers_data[passenger_index][5] << endl;
    Sleep(500);
    cout << setw(25) << left << "Number of Seats" << setw(10) << "|" << setw(25) << left << passengers_data[passenger_index][6] << endl;
    separator();

    // The passengers array holds all the data about a passenger such as name, boarding station, destination station, number of seats booked, train name, departure time, and price
}