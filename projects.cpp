#include <bits/stdc++.h>
#include <conio.h>
#include <string>

using namespace std;

const int firstRoom=81;
const int lastRoom = 580;

bool roomOccupied[lastRoom+1];
int guestCount = 0;
char Continue;

struct Guest
{
    string name;
    int startDate;
    int startMonth;
    int endDate;
    int endMonth;
    string address;
    string goingTo;
    int age;
    int roomNo;
};

queue<Guest> Guests;

void swap(Guest *a, Guest *b)
{
    Guest t = *a;
    *a = *b;
    *b = t;
}

int partition(Guest arr[], int low, int high, int choice)
{
    int pivotInt = arr[high].roomNo;
    string pivotStr = arr[high].name;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (choice == 1)
        {
            if (arr[j].roomNo < pivotInt)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        else if (choice == 0)
        {

            if (arr[j].name.compare(pivotStr) < 0)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Guest arr[], int low, int high, int choice)
{
    if (low < high)
    {
        int pi = partition(arr, low, high, choice);
        quickSort(arr, low, pi - 1, choice);
        quickSort(arr, pi + 1, high, choice);
    }
}

int binarySearch(Guest arr[], int n, int roomNo, string x, int choice,bool searchFirst)
{
    int left = 0;
    int right = n - 1;
    int result=-1;
    while (left <= right)
    {
        int mid= left + (right - left) / 2;

        int compare = x.compare(arr[mid].name);

        if ((compare == 0 && choice == 0) || (roomNo == arr[mid].roomNo && choice == 1))
            {
                result=mid;

                if(searchFirst)
                    right=mid-1;
                else
                    left=mid+1;
            }

        else if ((compare > 0 && choice == 0) || (roomNo > arr[mid].roomNo && choice == 1))
            left = mid + 1;

        else
            right = mid - 1;
    }

    return result;
}

void initializeRooms()
{
    for (int i = firstRoom; i <= lastRoom; i++)
    {
        roomOccupied[i] = false;
    }
}

int calcDate(int day, int month)
{
    return 100 * month + day;
}

void filter(int date, int month)
{
    while (!Guests.empty())
    {
        if (calcDate(Guests.front().endDate, Guests.front().endMonth) < calcDate(date, month))
        {
            roomOccupied[Guests.front().roomNo] = false;
            guestCount -= 1;
            Guests.pop();
        }
        else
            break;
    }
}

void checkIn()
{
    Guest newGuest;
    string name;
    int startDate;
    int startMonth;
    int endDate;
    int endMonth;
    string address;
    string goingTo;
    int age;
    int roomNo;

    cout << "Please enter the following data with regards to the guest details" << endl;
    cout << endl;

    cout << "Enter Guest Name -> ";
    getline(cin >> ws, name);

    cout << "Enter guest check in date (dd mm)-> ";
    cin >> startDate >> startMonth;
    if (startDate > 31 || startDate < 1 || startMonth > 12 || startMonth < 1)
    {
        do
        {
            cout << "Please enter a valid date" << endl;
            cout << "Enter date again -> ";
            cin >> startDate >> startMonth;
        } while (startDate > 31 || startDate < 1 || startMonth > 12 || startMonth < 1);
    }

    cout << "Enter guest release date (dd mm) -> ";
    cin >> endDate >> endMonth;
    if (endDate > 31 || endDate < 1 || endMonth > 12 || endMonth < 1 || (endMonth < startMonth) || (endDate < startDate && endMonth <= startMonth))
    {
        do
        {
            cout << "Please enter a valid date" << endl;
            cout << "Enter date again -> ";
            cin >> endDate >> endMonth;
        } while (endDate > 31 || endDate < 1 || endMonth > 12 || endMonth < 1 || (endMonth < startMonth) || (endDate < startDate && endMonth <= startMonth));
    }
    cout << "Enter Guest Address -> ";
    getline(cin >> ws, address);

    cout <<"Enter where Guest is going to -> ";
    getline(cin>>ws, goingTo);

    cout << "Enter guest age -> ";
    cin >> age;

    cout << "Please choose a room from the following list of unoccupied rooms -> ";

    int count = 0;
    for (int i = firstRoom; i <= lastRoom && count < 10; i++)
    {
        if (!roomOccupied[i])
        {
            cout << i << " ";
            count += 1;
        }
    }
    cout << endl;
    cout << "Enter the Room Number --> ";
    cin >> roomNo;
    if (roomOccupied[roomNo] || roomNo < 81 || roomNo > 580)
    {
        do
        {
            cout << "This Room is not available. Please enter a Room Number again ->";
            cin >> roomNo;
        } while (roomOccupied[roomNo]);
    }

    newGuest.name = name;
    newGuest.startDate = startDate;
    newGuest.startMonth = startMonth;
    newGuest.endDate = endDate;
    newGuest.endMonth = endMonth;
    newGuest.address = address;
    newGuest.goingTo = goingTo;
    newGuest.age = age;
    newGuest.roomNo = roomNo;

    roomOccupied[roomNo] = true;

    Guests.push(newGuest);
    cout << endl;
    cout << "The guest " << name << " was succesfully checked in" << endl;
    cout << endl;
    
    guestCount += 1;
    cout << "##########################################################" << endl;
    cout << endl;
}

void sortGuests()
{
    int n = Guests.size();
    Guest GuestsArray[n];
    Guest GuestsArray2[n];
    for (int i = 0; i < n; i++)
    {
        GuestsArray[i] = Guests.front();
        GuestsArray2[i]=Guests.front();
        Guests.pop();
    }
    
    
    int choice;
    cout << "Enter 0 if you want to sort on the basis of name" << endl;
    cout << "Enter 1 if you want to sort on the basis of Room No" << endl;
    cout << endl;
    cout << "Enter your choice here-> ";
    cin >> choice;
    quickSort(GuestsArray, 0, n - 1, choice);
    cout << endl;
     bool showName = true, showDates = true, showAddress = true, showRoomNo = true, showAge = true;

    char info;
    
    cout << "Would you like to see all information about the guests? (y/n) -> ";
    cin >> info;
    cout << endl;

    
    if (info == 'n')
    {
        cout << "Enter the information youd like to display(y/n) " << endl;

        cout << "name -> ";
        cin >> info;
        if (info == 'n')
            showName = false;

        cout << "Room No -> ";
        cin >> info;
        if (info == 'n')
            showRoomNo = false;

        cout << "Check in and Check out Dates ->";
        cin >> info;
        if (info == 'n')
            showDates = false;

        cout << "Address and Going To -> ";
        cin >> info;
        if (info == 'n')
            showAddress = false;

        cout << "Age -> ";
        cin >> info;
        if (info == 'n')
            showAge = false;
    }

    cout << "The sorted list is " << endl;
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        if (showName)
            cout << "Name:      " << GuestsArray[i].name << endl;
        if (showRoomNo)
            cout << "Room No:   " << GuestsArray[i].roomNo << endl;
        if (showDates)
        {
            cout << "Check in:  " << GuestsArray[i].startDate << "/" << GuestsArray[i].startMonth << endl;
            cout << "Check Out: " << GuestsArray[i].endDate << "/" << GuestsArray[i].endMonth << endl;
        }
        if (showAddress)
        {
            cout << "Address: " << GuestsArray[i].address << endl;
            cout << "Going TO:  "<< GuestsArray[i].goingTo <<endl;
        }
        if (showAge)
            cout << "Age:       " << GuestsArray[i].age << endl;
        cout << endl;
    }
    cout << "##########################################################" << endl;
    cout << endl;

    for (int i = 0; i < n; i++)
    {
        Guests.push(GuestsArray2[i]);
    }
}

void searchGuest()
{
    int n = Guests.size();
    Guest GuestsArray[n];
    Guest GuestsArray2[n];
    for (int i = 0; i < n; i++)
    {
        GuestsArray[i] = Guests.front();
        GuestsArray2[i]= Guests.front();
        Guests.pop();
    }

    int result;
    cout << "Enter 0 if you want to search on the basis of name " << endl;
    cout << "Enter 1 if you want to search on the basis of Room No " << endl;
    cout<<endl;
    int choice;
    cout << "Enter your choice here -> ";
    cin >> choice;
    cout << endl;
    quickSort(GuestsArray, 0, n - 1, choice);
    if (choice == 0)
    {
        string name;
        cout << "Enter the name you want to search-> ";
        getline(cin >> ws, name);
        cout << endl;
        result = binarySearch(GuestsArray, n, 0, name, choice,true);
        if (result == -1)
        {
            cout << "No such person exists in the system " << endl;
        }
        else
        {   
            int firstIndex=result;
            int lastIndex=binarySearch(GuestsArray, n, 0, name, choice,false);
            cout<<"There is/are "<<lastIndex-firstIndex+1<<" items that match your search"<<endl;
            cout<<endl;
            for(int i=firstIndex;i<=lastIndex;i++)
            {

                cout << "Name           :" << GuestsArray[i].name << endl;
                cout << "Room no        :" << GuestsArray[i].roomNo << endl;
                cout << "Check in date  :" << GuestsArray[i].startDate << "/" << GuestsArray[i].startMonth << endl;
                cout << "Release date   :" << GuestsArray[i].endDate << "/" << GuestsArray[i].endMonth << endl;
                cout << "Address        :" << GuestsArray[i].address << endl;
                cout << "Going to       :"<< GuestsArray[i].goingTo <<endl;
                cout << "Age            :" << GuestsArray[i].age << endl;
                cout<<endl;
            }
        }
    }
    else if (choice == 1)
    {
        int roomNo;
        cout << "Enter the Room no you want to search -> ";
        cin >> roomNo;
        cout << endl;
        result = binarySearch(GuestsArray, n, roomNo, "", choice,true);
        if (result == -1)
        {
            cout << "This Room has not been alloted to anyone " << endl;
        }
        else
        {
            cout << "Your requested details are -> " << endl;
            cout << endl;
            cout << "Name          : " << GuestsArray[result].name << endl;
            cout << "Room no       : " << GuestsArray[result].roomNo << endl;
            cout << "Check in date : " << GuestsArray[result].startDate << "/" << GuestsArray[result].startMonth << endl;
            cout << "Release date  : " << GuestsArray[result].endDate << "/" << GuestsArray[result].endMonth << endl;
            cout << "Address       : " << GuestsArray[result].address << endl;
            cout << "Going to      : "<<GuestsArray[result].goingTo<<endl; 
            cout << "Age           : " << GuestsArray[result].age << endl;
        }
    }
    cout << endl;
    cout << "##########################################################" << endl;
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        Guests.push(GuestsArray2[i]);
    }
}

void displayRooms()
{
    cout << "Currently " << guestCount << " rooms are occupied and " << 500 - guestCount << " rooms are availabele " << endl;
    cout << endl;
    cout << "The occupied rooms are " << endl;
    for (int i = firstRoom; i <= lastRoom; i++)
    {
        if (roomOccupied[i])
            cout << i << " ";
    }
    cout << endl;

    cout << "The unoccupied rooms are " << endl;

    for (int i = firstRoom; i <= lastRoom; i++)
    {
        if (!roomOccupied[i])
            cout << i << " ";

        if (i % 20 == 0)
            cout << endl;
    }
    cout << endl;
    cout << "##########################################################" << endl;
    cout << endl;
}

void displayAll()
{
    
    int n = Guests.size();
    Guest GuestsArray[n];
    for (int i = 0; i < n; i++)
    {
        GuestsArray[i] = Guests.front();
        Guests.pop();
    }
    cout<<"Here are the details of all the Guests in the facility : "<<endl;
    cout<<endl;
    for(int i=0;i<n;i++)
            {

                cout << "Name          : " << GuestsArray[i].name << endl;
                cout << "Room no       : " << GuestsArray[i].roomNo << endl;
                cout << "Check in date : " << GuestsArray[i].startDate << "/" << GuestsArray[i].startMonth << endl;
                cout << "Release date  : " << GuestsArray[i].endDate << "/" << GuestsArray[i].endMonth << endl;
                cout << "Address       : " << GuestsArray[i].address << endl;
                cout << "Going to      : "<< GuestsArray[i].goingTo<<endl;
                cout << "Age           : " << GuestsArray[i].age << endl;
                cout<<endl;
            }
    
    for (int i = 0; i < n; i++)
    {
        Guests.push(GuestsArray[i]);
    }

}
void display()
{
    bool end = false;
    int day;
    int month;
    cout << "Enter today's date (dd mm) --> ";
    cin >> day >> month;
    if (day > 31 || day < 1 || month > 12 || month < 1)
    {
        do
        {
            cout << "Please enter a valid date" << endl;
            cout << "Enter date again -> ";
            cin >> day >> month;
        } while (day > 31 || day < 1 || month > 12 || month < 1);
    }
    cout << endl;
    filter(day, month);

    cout << "Please choose among the following options" << endl;
    cout << endl;
    cout << "1. Check in a New Guest" << endl;
    cout << "2. Sort The Guest List" << endl;
    cout << "3. Search for a guest" << endl;
    cout << "4. Display vacant and Occupied rooms" << endl;
    cout << "5. Display information about all guests in the facility "<<endl;
    cout << "6. Exit the portal" << endl;
    cout << endl;
    cout << "Enter your choice here --> ";
    int choice;
    cin >> choice;
    cout << endl;
    if (choice == 1)
    {
        if (guestCount < 500)
            checkIn();
        else
            cout << "There are no more empty rooms" << endl;
    }
    else if (choice == 2)
    {
        sortGuests();
    }
    else if (choice == 3)
    {
        searchGuest();
    }
    else if (choice == 4)
    {
        displayRooms();
    }
    else if (choice == 5)
    {
        displayAll();
    }
    else if (choice == 6)
    {
        cout << "Are you sure you want to exit? (y/n)" << endl;
        char confirmation;
        cin >> confirmation;
        if (confirmation == 'y')
        {
            cout << "Thank you for using the portal " << endl;
            cout<<endl;
            cout << "###########################################################" << endl;
            end = true;
        }
    }
    else
    {
        cout << "INVALID INPUT" << endl;
    }

    if (!end)
        display();
}

int main()
{
    cout << "###########################################################" << endl;
    cout << endl;
    cout << "WELCOME TO THE NIT SILCHAR QUARRENTINE FACILITY PORTAL" << endl;
    cout << endl;
    cout << "###########################################################" << endl;
    cout << endl;

    int password;
    password = 12345;
    int userpass;
    string username;
    username = "nits";
    string vername;
    
    cout<<endl;
    cout<<"Enter the username and password to login"<<endl;
    cout<<endl;
    cout << "Enter username:";
        cin >> vername;
        cout << endl;
        cout << "Enter password:";
        cin >> userpass;
        cout << endl;
        
        if (vername == username && userpass == password)
        {
            cout<<"Login Succesfull !!"<<endl;
            cout<<endl;
            cout << "###########################################################" << endl;
            cout << endl;

            initializeRooms();    

            display();
        }

        else
        {
            do
            {   cout<<endl;
                cout<<"The username/password you entered was incorrect. Enter again "<<endl;
                cout<<endl;
                cout << "Enter username: ";
                cin >> vername;
                cout << endl;
                cout << "Enter password: ";
                cin>>userpass;
                cout<<endl;
            } while (vername != username || userpass != password);
             
            cout<<"Login Succesfull !!"<<endl;
            cout<<endl;
            cout << "###########################################################" << endl;
            cout << endl;

            initializeRooms();    

            display();
        }

    
}
