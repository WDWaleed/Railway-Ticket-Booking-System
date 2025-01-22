#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

void separator();
void displaySchedules(int, char trains[], string departure[], int stops[], string schedules[4][10][2]);

int main()
{
    int n = 4; // Number of trains
    char trains[n] = {'A', 'B', 'C', 'D'};
    string departure[n] = {"05:00", "10:00", "16:00", "21:00"};
    int avalaibleBerths[n] = {40, 40, 40, 40};
    int stops[] = {7, 7, 9, 9}; // Number of places the trains are going to stop at as shown in the following array. Each entry corresponds to trains[i]

    string schedules[4][10][2] = {
        // Train A: Rawalpindi to Karachi
        {
            {"Rawalpindi", "05:00"},
            {"Lahore", "08:30"},
            {"Khanewal", "12:30"},
            {"Bahawalpur", "15:00"},
            {"Rohri", "19:30"},
            {"Hyderabad", "23:00"},
            {"Karachi", "(Destination)"}},

        // Train B: Karachi to Rawalpindi
        {
            {"Karachi", "10:00"},
            {"Hyderabad", "11:30"},
            {"Rohri", "15:00"},
            {"Bahawalpur", "19:30"},
            {"Khanewal", "22:00"},
            {"Lahore", "02:00"},
            {"Rawalpindi", "(Destination)"}},

        // Train C: Lahore to Karachi
        {
            {"Lahore", "16:00"},
            {"Sahiwal", "18:00"},
            {"Khanewal", "20:30"},
            {"Bahawalpur", "22:30"},
            {"Rahim Yar Khan", "01:00"},
            {"Rohri", "04:30"},
            {"Nawabshah", "07:00"},
            {"Hyderabad", "09:00"},
            {"Karachi", "(Destination)"}},

        // Train D: Karachi to Lahore
        {
            {"Karachi", "21:00"},
            {"Hyderabad", "22:30"},
            {"Nawabshah", "01:00"},
            {"Rohri", "04:30"},
            {"Rahim Yar Khan", "07:00"},
            {"Bahawalpur", "10:00"},
            {"Khanewal", "13:00"},
            {"Sahiwal", "15:30"},
            {"Lahore", "(Destination)"}}};

    int priceA[] = {0, 1000, 2000, 3000, 4000, 5000, 6000};
    int priceB[] = {0, 1000, 2000, 3000, 4000, 5000, 6000};
    int priceC[] = {0, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500};
    int priceD[] = {0, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500};

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

        if (choice == 0)
        {
            break;
        }
        if (choice == 1)
        {
            displaySchedules(n, trains, departure, stops, schedules);
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
void displaySchedules(int n, char trains[], string departure[], int stops[], string schedules[4][10][2])
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
    }

    separator();
}