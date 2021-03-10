/*
 * User.h
 *
 *  Created on: Mar 9, 2018
 *      Author: joewy
 */

#ifndef USER_H_
#define USER_H_

#include <string>
#include "List.h"
#include "BST.h"

class User
{
private:
	string firstName;
	string lastName;
	string userName;
	string passWord;
	string city;
	string state;
	unsigned ID;
	BST<string> FriendList;
	List<string> friends;
	List<string> interests;

public:
	/**Constructors*/
	User();
	User(string f, string l, string u, string p, string c, string s, unsigned i);
	~User(){};

    /**Access Functions*/

	string getFirstname() const;
	string getLastname() const;
	string getUsername() const;
	string getPassword() const;
	string getCity() const;
	string getState() const;
	unsigned getID() const;
	List<string> getInterest() const;
	List<string> getFriend() const;
	BST<string> getBST();

	/**Manipulation Procedures*/

	void setFirstname(string f);
	void setLastname(string l);
	void setUsername(string u);
	void setPassword(string p);
	void setCity(string c);
	void setState(string s);
	void setID(unsigned i);
	void setFriends(string fr);
	void setInterests(string i);
	void setFriendList(string u);


	/**Additional Functions*/
	friend ostream& operator<<(ostream & out, const User& user);
	bool operator==(const User& user);
	bool operator<(const User& user);
	bool operator>(const User& user);
	//void printFriends(ostream& out) const;

};


#endif /* USER_H_ */
