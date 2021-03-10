#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cctype> // for isdigit
#include "User.h"
#include "HashFriend.h"
#include "HashInterest.h"
#include "Graph.h"
#include <algorithm>

 
using namespace std;
 
int logIn();
int mainMenu();
void viewFriends(int id);
void searchNewFriends(HashFriend& hf, HashInterest& hi, int id);
void removeFriends(int id);
void readFile(HashFriend& hf, HashInterest& hi);
void friendRecs();
void searchByFriend(HashFriend& hf, int id);
void searchByInterest(HashInterest& hi, int id);
string createAccount();
void viewProfile(int id);
void friendRecs(int id, HashFriend& hf);
void outputFile();
 
vector<User> userID;
 
void readFile(HashFriend& hf, HashInterest& hi)
{
        string firstName, lastName, userName, passWord, city, state, friendName, interest;
        string filename;
        unsigned id = 1;
 
        User empty;
        userID.push_back(empty); // index 0 is a empty user
 
        filename = "data.txt";
        ifstream inputfile;
        inputfile.open(filename);
 
        assert(inputfile);
 
        while(inputfile)
        {
        inputfile >> firstName;
        inputfile >> lastName;
        inputfile >> userName;
        inputfile >> passWord;
        inputfile.get(); // go to next line
        getline(inputfile, city, ',');
        getline(inputfile, state);
 
        User user(firstName, lastName, userName, passWord, city, state, id);
 
        getline(inputfile, friendName);
        istringstream tempF(friendName);
        while(tempF)
        {
            getline(tempF, friendName, ',');
            if(tempF.peek() == ' ')
                tempF.get();
            user.setALL(friendName);
        }
 
        getline(inputfile, interest);
        istringstream tempI(interest);
        while(tempI)
        {
            getline(tempI, interest, ',');
            if(tempI.peek() == ' ')
                tempI.get();
            user.setInterests(interest);
        }
 
        while(inputfile.peek() == '\n')
            inputfile.get(); // go to next line
        while(inputfile.peek() == ' ')
            inputfile.get(); // go to next line
 
        userID.push_back(user); // insert to the id vector
        hf.insert(user);// insert to hashFriend
        hi.insert(user);// insert to hashInterest
        id ++;
        }
}
 
int main()
{
	HashFriend hf;
	HashInterest hi;
    string name;
    int choice;
    int id = 0;
    readFile(hf,hi);
 
 
    // Log in validation
    while (id <= 0)
            id = logIn();
 
    name = "<" + userID[id].getFirstname() + " " + userID[id].getLastname()  + ">";
    cout << "\n\nWelcome, " << name << "!\n";
 
 
 
    do{
        choice = mainMenu();
 
        switch(choice)
        {
            case 1:     // view friends
                viewFriends(id);
                break;
 
            case 2:     // search for new friends
                searchNewFriends(hf, hi, id);
                break;
 
            case 3:     // friends rec
                friendRecs(id, hf);
                break;
 
 
            case 4:      //quit
            {
            	outputFile();
 
                cout << "     You are signed out"
                     << "\n\t- GOODBYE! -" << endl;
            }
        }
 
    }while(choice != 4);
 
    return 0;
}
 
 
/// Returns bool for whether or not username & password combo are matched
int logIn()
{
    string un, pw, fn, ln, city, state;
    int choice = 0;
    int id;
    bool option = false;
 
    while (!option)
    {
        while (choice != 1 && choice != 2 && choice != 3)
        {
                cout << "\t- WELCOME TO SPONGEBOOK -" << endl;
                cout << "1. Log in " << endl;
                cout << "2. Create an account " << endl;
                cout << "3. Quit " << endl;
                cout << "\nEnter choice: ";
                cin >> choice;
                cout << endl;
        }
 
        if (choice == 1)
        {
            int count = 0;
 
            while (true)
            {
                string userInput;
 
                cout << "\t- LOG IN -" << endl
                         << "Username: ";
                    cin >> un;
                    cout << "Password: ";
                    cin >> pw;
 
                    for (unsigned i = 1; i <= userID.size(); i++)
                    {
                        if (un == userID[i].getUsername() && pw == userID[i].getPassword())
                        {
                            cout << "\n\t*** Login successful ***\n" << endl;
                            id = i;
                            option = true;
                            return id;
                        }
                    }
 
                    cout << "\n\t*** Incorrect username or password. Please try again **" << endl;
                    count ++;
 
                    if (count > 3)
                    {
                        while (userInput != "YES" && userInput != "NO")
                        {
                            cout << "\nMultiple failed attempts. Would you like to go back to the main menu? ";
                            cin >> userInput;
                            transform(userInput.begin(), userInput.end(), userInput.begin(),::toupper);
                        }
 
                        if (userInput == "YES")
                        {
                            cout << endl;
                            choice = 0;
                            option = true;
                            return false;
                        }
                        else if (userInput == "NO")
                        {
                            choice = 1;
                            count = 0;
                        }
                    }
                }
        }
 
        else if (choice == 2)
        {
        	string temp = createAccount();
        	choice = atoi(temp.c_str());
        }
        else if (choice == 3)
        {
            cout << "\t- GOODBYE! -" << endl;
            exit(0);
        }
    }
    return id;
 
}
 
string createAccount()
{
    string un, pw, fn, ln, city, state, choice;
    int id;
    cout << "\t- CREATE AN ACCOUNT -" << endl
         << "First name: ";
    cin >> fn;
 
    cout << "Last name: ";
    cin >> ln;
 
    cout << "Username: ";
    cin >> un;
 
    cout << "Password: ";
    cin >> pw;
 
    cout << "City: ";
    cin.ignore();
    getline(cin, city);
 
    cout << "State: ";
    cin >> ws;
    cin >> state;
 
    id = userID.size() + 1;
 
    User newUser(fn, ln, un, pw, city, state, id);
    userID.push_back(newUser);
 
    bool more = true;
    string interests;
 
    while (more)
    {
        cout << "Enter interest or 'stop' to finish: ";
        cin >> interests;
 
        transform(interests.begin(), interests.end(), interests.begin(),::toupper);
 
        if (interests == "STOP")
            more = false;
        else
        {
            transform(interests.begin(), interests.end(), interests.begin(),::tolower);
            newUser.setInterests(interests);
        }
    }
 
    cout << "\n\t*** Account successfully created. You may now log in ***\n" << endl;
 
    return choice = "0";
}
 
/// Main Menu :)
int mainMenu()
{
    string input = "0";
    do{
        cout << "\n\t - MENU -" << endl
             << "1. View Friends" << endl
             << "2. Search for New Friends" << endl
             << "3. Friends Recommendations" << endl
             << "4. Quit\n\n"
             << "Enter choice: ";
        cin >> input;
 
        if(!isdigit(input[0]))
        {
            cout << "Please enter numbers only.\n";
            input = "0";
        }
        else if(!(input == "1" || input == "2" || input == "3" || input == "4"))
        {
            cout << "Invalid input.\n";
            input = "0";
        }
 
    }while(input == "0");
 
    cout << endl;
    int choice = atoi(input.c_str());
 
    return choice;
}
 
 
/// Menu option to view friends
void viewFriends(int id)
{
    string input = "0";
 
    cout << "     - View Friends -" << endl;
 
        cout << "1. View all friends\n"
             << "2. View a friend's profile\n"
             << "3. Remove a friend\n\n"
             << "Enter choice or 'm' for menu: ";
        cin >> input;
 
     do{   if(input[0] == 'm')
                return;
        else if(!isdigit(input[0]))
        {
            cout << "Please enter numbers or 'm' only.\n\n";
            input = "0";
        }
        else if(!(input == "1" || input == "2" || input == "3"))
        {
            cout << "Invalid input.\n\n";
            input = "0";
        }
        else if (input == "2")
        {
        	viewProfile(id);
        }
        else if (input == "3")
        {
            removeFriends(id);
        }
        else        // input == 1 2 or 3
        {
            cout << "Your friends printing below:";
            cout << "\n-----------------------------------------\n";
            userID[id].printFriends();
            cout << "-----------------------------------------\n";
            cout << "1. View a friend's profile\n"
                 << "2. Remove a friend\n\n"
                 << "Enter choice or 'm' for menu: ";
            cin >> input;
 
            if (input == "1")
            {
                viewProfile(id);
            }
            else if (input == "2")
            {
                removeFriends(id);
            }
            else
            {
                cout << "Invalid input. Please try again.\n" << endl;
            }
 
        }
 
    }while(input == "0");
    cout << endl;
}
 
void viewProfile(int id)
{
    string name, fn, ln, input;
    bool results;
    bool option = true;
 
    User u = userID[id];
 
    while (option)
        {
            bool find = true;
            while (find)
            {
                cout << "\nEnter the name of the friend you'd like to view: " << endl;
 
                cout << "   First Name: ";
                cin >> fn;
                cout << "   Last Name: ";
                cin >> ln;
 
                name = fn + " " + ln;
                results = u.searchFriend(name);
 
                if (results == 0)
                {
                    cout << "Friend not found. Please try again. \n";
                }
                else
                {
                    for(unsigned i = 1; i <= userID.size(); i++)
                    {
                        if (fn == userID[i].getFirstname() && ln == userID[i].getLastname())
                        {
                                User u = userID[i];
                                List<string> interest = u.getInterest();
                            cout << "\n-----------------------------------------";
                            cout << "\nProfile of ";
                            cout << u.getFirstname() << " " << u.getLastname() << endl << endl;
                            cout << "Location: ";
                            cout << u.getCity() << endl << endl;
                            cout << "Friends: " << endl;
                            u.printFriends();
                            cout << "Interests: " ;
                            interest.printList(cout);
                            cout << "-----------------------------------------\n";
                        }
                    }
                    find = false;
                }
            }
 
            bool more = true;
 
            while (more)
            {
                cout << "\nWould you like to view more friends? ";;
                cin >> input;
                transform(input.begin(), input.end(), input.begin(), ::toupper);
 
                if (input == "NO")
                {
                    cout << "Back to the main menu. " << endl;
                    //mainMenu();
                    more = false;
                    option = false;
                }
                else if (input == "YES")
                {
                    more = false;
                }
                else
                {
                    cout << "Please enter only yes or no " << endl;
                }
            }
        }
}
 
/// Menu option to search for new friends
void searchNewFriends(HashFriend& hf, HashInterest& hi, int id)
{
    string input = "0";
    cout << " - Search for New Friends -" << endl;
    do{
        cout << "1. Search by Name\n"
             << "2. Search by Interest\n\n"
             << "Enter choice or 'm' for menu: ";
        cin >> input;
 
        if(input[0] == 'm')
                return;
        else if(!isdigit(input[0]))
        {
            cout << "Please enter numbers or 'm' only.\n\n";
            input = "0";
        }
        else if(!(input == "1" || input == "2"))
        {
            cout << "Invalid input.\n\n";
            input = "0";
        }
        else if(input == "1")    // input == 1 or 2
        {
        	searchByFriend(hf, id);
        }
        else
        {
        	searchByInterest(hi, id);
        }
 
    }while(input == "0");
    cout << endl;
}
 
 
 
void removeFriends(int id)
{
    string name, input;
    bool results;
    bool option = true;
 
 
    while (option)
    {
        bool find = true;
        while (find)
        {
            cout << "Enter the name of the friend you'd like to remove: " << endl;
            cin.ignore();
            getline(cin, name);
            results = userID[id].getBST().search(name);
 
            if (results == 0)
           {
              cout << "Friend not found. Please try again. \n" << endl;
           }
            else
           {
             userID[id].removeFriend(name);
             cout << endl << "Friend successfully removed." << endl;
             cout << "Here is your updated list: ";
             cout << "\n-----------------------------------------\n";
             userID[id].printFriends();
             cout << "-----------------------------------------\n";
             find = false;
             }
        }
        bool more = true;
 
        while (more)
        {
            cout << "Would you like to remove more friends? ";;
            cin >> input;
            transform(input.begin(), input.end(), input.begin(), ::toupper);
 
            if (input == "NO")
            {
                cout << "Back to the main menu. " << endl;
                mainMenu();
                more = false;
                option = false;
            }
            else if (input == "YES")
            {
                more = false;
            }
            else
            {
                cout << "Please enter only yes or no " << endl;
            }
        }
    }
}
 
void friendRecs(int id, HashFriend& hf)
{
    Graph g(userID.size());
 
    cout << "--------------------------------\n";
    cout << "\n - Friend Recommendations -\n" << endl;
 
    for (unsigned i = 1; i < userID.size(); i++)
    {
 
        List<string> friendList = userID[i].getFriend();
        friendList.startIterator();
 
        while (!friendList.offEnd())
        {
            string name = friendList.getIterator();  //Returns a variable
            for (unsigned x = 1; x < userID.size(); x++)
            {
                string friendName = userID[x].getFirstname() + " " + userID[x].getLastname();
                if (friendName == name)
                {
                    g.addEdge(i, x);
                }
            }
            friendList.advanceIterator();
        }
    }
 
    g.BFS(id, userID);
    g.rankingAlgorithm(id, userID);
 
    cout << "--------------------------------\n";
    searchByFriend(hf, id);
    return;
}
 
//search friend by name, this will find the correct id in terms of firstname and lastname
void searchByFriend(HashFriend& hf, int id)
{
	string firstN, lastN;
	cout << "Enter the first name or m to menu:";
	cin >> firstN;
	if(firstN == "m" || firstN == "M")
		return;
 
	cout << "Enter the last name or m to menu:";
 
	if(lastN == "m" || lastN == "M")
		return;
	cin >> lastN;
 
	while(userID[id].getFirstname() + userID[id].getLastname() == firstN + lastN) // can't search the same name to self
	{
		cout << "Sorry, you can not search for yourself!\n";
		return searchByFriend(hf, id);
	}
	for(unsigned i = 0; i < firstN.length(); i++) // first name can't have any integer
	{
		if(isdigit(firstN[i]))
		{
			cout <<"User's name can not contain any integer\n";
			return searchByFriend(hf, id);
		}
	}
	for(unsigned i = 0; i < lastN.length(); i++)// last name can't have any integer
	{
		if(isdigit(lastN[i]))
		{
			cout <<"User's name can not contain any integer\n";
			return searchByFriend(hf, id);
		}
	}
 
	int index = hf.search(firstN + lastN); //get the index of the bucket
 
	if(index == -1) // can't find a user
		{
			cout << "\nUser does not exist!\n\n";
			return searchByFriend(hf, id);
		}
	else                 // found a user
	{
		if(userID[id].getFriend().linearSearch(firstN + " " + lastN) != -1) // verify whether the user is your friend already
		{
			cout << "\n" <<firstN << " "<< lastN << " is your friend already!\n";
			return searchByFriend(hf, id);
		}
 
		List<int> temp = hf.getBucket(index);// get the list of the bucket
 
			temp.startIterator();
			for(int i = 0; i < temp.getLength(); i++) // each bucket might have collision
			{
				int searchid = temp.getIterator();
				if(userID[searchid].getFirstname() + userID[searchid].getLastname() == firstN + lastN)
				{
 
					cout << "\n" << userID[searchid].getFirstname() << " " << userID[searchid].getLastname() << " is found!\n";
					cout << "\nDo you want to add the user to your friend list, Yes or No?\n";
					string choice;
					cin >> choice;
					if(choice == "YES" || choice == "yes")
					{
						cout << "\nThe user, " << firstN << " " << lastN << ", has been added to your list.\n";
						userID[id].setALL(firstN + " " + lastN);
						userID[searchid].setALL(userID[id].getFirstname() + " " + userID[id].getLastname());
						return;
					}
					else if(choice == "NO" || choice == "no")
					{
						return;
					}
					else
					{
						cout <<"Invalid input!\n";
						return;
					}
				}
				else
				{
					if(i == temp.getLength() - 1) // make sure go through all the collison
					{
						cout << "\nUser does not exist!\n\n";
						return searchByFriend(hf, id);
					}
				}
				temp.advanceIterator();
			}
 
	}
}
 
//searching user by interest
void searchByInterest(HashInterest& hi, int id)
{
 
	string interest;
	cout << "\nEnter the name of the interest or me to menu:";
	if(interest == "m" || interest == "M")
		return;
 
	cin.ignore();
	getline(cin, interest);
	cout << endl;
 
	int index = hi.search(interest);  //get the index of the bucket
 
	if(index == -1) // can't find a user with that interest
		{
			cout << "\nNo user has this interest!\n\n";
			return;
		}
	else                 // found a user
	{
		List<int> temp = hi.getBucket(index);// get the list of the bucket
		vector<int> listInterest;
		int listIndex = 1;
		temp.startIterator();
 
		for(int i = 0; i < temp.getLength(); i++)
		{
			int searchid = temp.getIterator();
			if(searchid != id) // not including user himself
			{
				if(userID[searchid].getInterest().linearSearch(interest) != -1) //minimize collisions by making sure only show the user has that interest
				{
					cout << listIndex << ". " <<userID[searchid].getFirstname() << " " << userID[searchid].getLastname() << " has the interest!\n";
					listInterest.push_back(searchid);
					listIndex++;
				}
 
			}
			temp.advanceIterator();
		}
 
		cout << "\nDo you want to add the user to your friend list, Yes or No?\n";
		string choice;
		cin >> choice;
		if(choice == "YES" || choice == "yes")
		{
			cout << "Enter the number of the user you want to add:";
			unsigned index;
			cin >> index;
 
			if(index < 1 || index > listInterest.size())
			{
				cout << "\nnumber is out of range!\n";
				return;
			}
 
			string tempName = userID[listInterest[index - 1]].getFirstname() + " " + userID[listInterest[index - 1]].getLastname();
			if(!userID[id].getBST().search(tempName)) // make sure is not friend already
			{
				userID[id].setALL(tempName);
				userID[listInterest[index - 1]].setALL(userID[id].getFirstname() + " " + userID[id].getLastname());
 
				cout << "\nThe user, " << tempName << ", has been added in your friend list.\n";
			}
			else
			{
				cout << "\nThe user, " << tempName << ", is your friend already!\n";
			}
 
		}
		else if(choice == "NO" || choice == "no")
		{
			return;
		}
		else
		{
			cout <<"Invalid input!\n";
			return;
		}
	}
}
 
 
void outputFile()
{
 
    ofstream outfile;
    outfile.open("userinfo.txt");
 
    for(unsigned i = 1; i < userID.size(); i++)
    {
    	outfile << userID[i] << endl;
    }
 
    outfile.close();
 
}