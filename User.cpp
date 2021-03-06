/*
 * User.cpp
 *
 *  Created on: Mar 9, 2018
 *      Author: joewy
 */

#include "User.h"
#include "BST.h"

	/**Constructors*/
User::User():firstName(""), lastName(""), userName(""), passWord(""), city(""), state(""), ID(-1){};

User::User(string f, string l, string u, string p, string c, string s, unsigned id)
{
	firstName = f;
	lastName = l;
	userName = u;
	passWord = p;
	city = c;
	state = s;
	ID = id;

}

/**Access Functions*/
unsigned User::getID() const
{
	return ID;
}

string User::getFirstname() const
{
	return firstName;
}

string User::getLastname() const
{
	return lastName;
}

string User::getCity() const
{
	return city;
}

string User::getUsername() const
{
	return userName;
}

string User::getPassword() const
{
	return passWord;
}

List<string> User::getInterest() const
{
	return interests;
}

List<string> User::getFriend() const
{
	return friends;
}
bool User::searchFriend(string name) const
{
	bool searchFr;
	searchFr = friendBST.search(name);
	return searchFr;
}

void User::printFriends() const
{
	friendBST.inOrderPrint(cout);
}

/**Manipulation Procedures*/


void User::setFirstname(string f)
{
	firstName = f;
}

void User::setLastname(string l)
{
	lastName = l;;
}

void User::setFriends(string fr)
{
	friends.insertLast(fr);
	friendBST.insert(fr);
}

void User::removeFriend(string fr)
{
	friendBST.remove(fr);
}

void User::setBST(User u)
{
	friendUser.insert(u);
}
BST<User> User::getBST()
{
	//friendUser.inOrderPrint(cout);
	return friendUser;
}

void User::setInterests(string i)
{
	interests.insertLast(i);
}

/**Additional Functions*/

ostream& operator<<(ostream& out, const User &user)
{
	out << user.firstName << " " << user.lastName << endl;
	out << "From: " << user.city << ", " << user.state << endl;
	out << "friends: ";
	user.friends.printList(out);
	out << "interests: ";
	user.interests.printList(out);
	return out;
}

bool User::operator==(const User& user)
{
	return (firstName == user.firstName && lastName == user.lastName);
}

bool User::operator<(const User& user)
{
	if(firstName < user.firstName)
		return true;
	else if(firstName == user.firstName)
	{
		if(lastName < user.lastName)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool User::operator>(const User& user)
{
	if(firstName > user.firstName)
		return true;
	else if(firstName == user.firstName)
	{
		if(lastName > user.lastName)
			return true;
		else
			return false;
	}
	else
		return false;
}

