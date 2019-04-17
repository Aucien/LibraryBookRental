#include "person.h"

Person::Person(int cardNo, bool act, string fName, string lName){
    firstName = fName;
    lastName = lName;
    cardID = cardNo;
    active = act;
}

string Person::getFirstName(){
    return firstName;
}

string Person::getLastName(){
    return lastName;
}

int Person::getId(){
    return cardID;
}

void Person::setActive(bool act){
    active = act;
}

bool Person::isActive(){
    return active;
}

string Person::fullName(){
    string fullName = firstName + " " + lastName;
    return fullName;
}