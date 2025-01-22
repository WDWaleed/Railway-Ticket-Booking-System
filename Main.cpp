#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

void separator();
void displaySchedules(int, char trains[], int stops[], string schedules[4][10][3]);

int main()
{
    int n = 4; // Number of trains
    char trains[n] = {'A', 'B', 'C', 'D'};
    string departure[n] = {"05:00", "10:00", "16:00", "21:00"};
    int avalaibleBerths[n] = {40, 40, 40, 40};
    int stops[] = {7, 7, 9, 9}; // Number of places the trains are going to stop at as shown in the following array. Each entry corresponds to trains[i]

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
        if (choice == 1)
        {
            displaySchedules(n, trains, stops, schedules);
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
void displaySchedules(int n, char trains[], int stops[], string schedules[4][10][3])
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