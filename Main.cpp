#include <iostream>
#include <iomanip>
using namespace std;

void displaySchedules(int, char trains[], string departure[], int stops[], string schedules[4][10]);

int main()
{
    int n = 4; // Number of trains
    char trains[n] = {'A', 'B', 'C', 'D'};
    string departure[n] = {"05:00", "10:00", "16:00", "21:00"};
    int avalaibleBerths[n] = {40, 40, 40, 40};
    int stops[] = {7, 7, 9, 9}; // Number of places the trains are going to stop at as shown in the following array. Each entry corresponds to trains[i]

    string schedules[4][10] = {
        // Train A
        {"Rawalpindi", "Lahore", "Khanewal", "Bahawalpur", "Rohri", "Hyderabad", "Karachi"},

        // Train B
        {"Karachi", "Hyderabad", "Rohri", "Bahawalpur", "Khanewal", "Lahore", "Rawalpindi"},

        // Train C
        {"Lahore", "Sahiwal", "Khanewal", "Bahawalpur", "Rahim Yar Khan", "Rohri", "Nawabshah", "Hyderabad", "Karachi"},

        // Train D
        {"Karachi", "Hyderabad", "Nawabshah", "Rohri", "Rahim Yar Khan", "Bahawalpur", "Khanewal", "Sahiwal", "Lahore"}};

    int priceA[] = {0, 1000, 2000, 3000, 4000, 5000, 6000};
    int priceB[] = {0, 1000, 2000, 3000, 4000, 5000, 6000};
    int priceC[] = {0, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500};
    int priceD[] = {0, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500};

    int choice;
    cout << "=> Press 1 to view train schedules" << endl;
    cout << "=> Press 2 to book tickets" << endl;
    cout << "=> Press 3 to view your ticket" << endl;
    cout << "=> Press 4 to exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
    {
        displaySchedules(n, trains, departure, stops, schedules);
    }

    return 0;
}

void displaySchedules(int n, char trains[], string departure[], int stops[], string schedules[4][10])
{
    cout << setw(15) << left << "Name" << setw(25) << left << "Departure Time" << setw(30) << left << "Schedule" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << left << "Train " << setw(5) << left << trains[i] << setw(4) << "" << setw(25) << left << departure[i];
        for (int j = 0; j < stops[i]; j++)
        {
            cout << schedules[i][j];
            if (j != stops[i] - 1)
            {
                cout << " => ";
            }
        }
        cout << endl;
    }
}