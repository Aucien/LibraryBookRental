// Name: Gordon Dan
//Section #02
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu()
{
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

void readBooks(vector<Book *> &myBooks)
{
    ifstream data;
    data.open("books.txt");
    int bookID;
    string title, author, category, line;
    if (data)
    {
        while (data >> bookID)
        {
            getline(data, line);
            getline(data, title);
            getline(data, author);
            getline(data, category);
            getline(data, line);
            Book *bookPtr = nullptr;
            bookPtr = new Book(bookID, title, author, category);
            myBooks.push_back(bookPtr);
        }
    }
    data.close();
}

int readPerson(vector<Person *> &myCardholders)
{
    ifstream data;
    data.open("persons.txt");
    int cardID;
    bool active;
    string fName, lName;
    if (data)
    {
        while (data >> cardID >> active >> fName >> lName)
        {
            Person *personPtr = nullptr;
            personPtr = new Person(cardID, active, fName, lName);
            myCardholders.push_back(personPtr);
        }
    }
    data.close();
    return myCardholders.back()->getId();
}

void readRentals(vector<Book *> &myBooks, vector<Person *> myCardHolders)
{
    ifstream data;
    data.open("rentals.txt");
    int bookID, cardID;
    Person *personPtr = nullptr;

    if (data)
    {
        while (data >> bookID >> cardID)
        {
            for (int x = 0; x < myCardHolders.size(); x++)
            {
                if (myCardHolders[x]->getId() == cardID)
                {
                    personPtr = myCardHolders[x];
                }
            }

            for (int x = 0; x < myBooks.size(); x++)
            {
                if (myBooks[x]->getId() == bookID)
                {
                    myBooks[x]->setPersonPtr(personPtr);
                }
            }
        }
    }
    data.close();
}

void openCard(vector<Person *> &myCardholders, int nextID)
{
    string fName, lName;
    cout << "Please enter the first name: ";
    cin >> fName;
    cout << "\nPlease enter the last name: ";
    cin >> lName;
    Person *personPtr = nullptr;
    nextID = myCardholders.back()->getId() + 1;
    personPtr = new Person(nextID, 1, fName, lName);
    myCardholders.push_back(personPtr);
}

Book *searchBook(vector<Book *> myBooks, int id)
{
    for (int x = 0; x < myBooks.size(); x++)
    {
        if (myBooks[x]->getId() == id)
        {
            return myBooks[x];
        }
    }
    cout << "Book ID not found" << endl;
    return nullptr;
}

Person *askCardID(vector<Person *> &myCardHolders)
{
    int cardID = 0;
    cout << "Please enter the cardID: ";
    cin >> cardID;
    for (int x = 0; x < myCardHolders.size(); x++)
    {
        if (myCardHolders[x]->getId() == cardID && myCardHolders[x]->isActive())
        {
            cout << "\nCardholder: " << myCardHolders[x]->fullName() << endl;
            return myCardHolders[x];
        }
    }
    cout << "Card ID not found" << endl;
    return nullptr;
}

int askbookID()
{
    int bookID;
    cout << "Please enter the book ID: ";
    cin >> bookID;
    return bookID;
}

void Bookcheckout(vector<Person *> &myCardHolders, vector<Book *> myBooks)
{
    Person *personPtr = askCardID(myCardHolders);
    if (personPtr != nullptr)
    {
        Book *bookPtr = searchBook(myBooks, askbookID());
        if (bookPtr != nullptr)
        {
            if (bookPtr->getPersonPtr() == nullptr)
            {
                cout << "Title: " << bookPtr->getTitle() << endl;
                bookPtr->setPersonPtr(personPtr);
                cout << "Rental Completed" << endl;
            }
            else
            {
                cout << "Book is already checked out" << endl;
            }
        }
    }
}

void Bookreturn(vector<Book *> &myBooks)
{
    Book *bookPtr = searchBook(myBooks, askbookID());
    if (bookPtr != nullptr)
    {
        if (bookPtr->getPersonPtr() != nullptr)
        {
            cout << "Title: " << bookPtr->getTitle() << endl;
            bookPtr->setPersonPtr(nullptr);
            cout << "Return Completed" << endl;
        }
        else
        {
            cout << "Book was not checked out" << endl;
        }
    }
}

void availableBooks(vector<Book *> &myBooks)
{
    int count = 0;
    for (int x = 0; x < myBooks.size(); x++)
    {
        if (myBooks[x]->getPersonPtr() == nullptr)
        {
            cout << "Book ID: " << myBooks[x]->getId() << endl
                 << "Title: " << myBooks[x]->getTitle() << endl
                 << "Author: " << myBooks[x]->getAuthor() << endl
                 << "Category: " << myBooks[x]->getCategory() << endl
                 << endl;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "No available books" << endl;
    }
}

void outRentals(vector<Book *> &myBooks, vector<Person *> &myCardholders)
{
    int count = 0;
    Person *personPtr = nullptr;
    for (int x = 0; x < myBooks.size(); x++)
    {
        personPtr = myBooks[x]->getPersonPtr();
        if (personPtr != nullptr)
        {
            cout << "Book ID: " << myBooks[x]->getId() << endl
                 << "Title: " << myBooks[x]->getTitle() << endl
                 << "Author: " << myBooks[x]->getAuthor() << endl
                 << "Category: " << myBooks[x]->getCategory() << endl
                 << "Cardholder: " << personPtr->fullName() << endl
                 << "Card ID: " << personPtr->getId() << endl
                 << endl;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "No outstanding books" << endl;
    }
}

void cardRentals(vector<Book *> &myBooks, vector<Person *> &myCardHolders)
{
    int count = 0;
    Person *personPtr = askCardID(myCardHolders);
    if (personPtr != nullptr)
    {
        for (int x = 0; x < myBooks.size(); x++)
        {
            if (myBooks[x]->getPersonPtr() == personPtr)
            {
                cout << "Book ID: " << myBooks[x]->getId() << endl
                     << "Title: " << myBooks[x]->getTitle() << endl
                     << "Author: " << myBooks[x]->getAuthor() << endl
                     << endl;
                count++;
            }
        }
        if (count > 0)
        {
            cout << "No books currently checked out" << endl;
        }
    }
}

void closeCard(vector<Person *> &myCardHolders)
{
    int cardID = 0;
    Person *personPtr = nullptr;
    cout << "Please enter the cardID: ";
    cin >> cardID;
    for (int x = 0; x < myCardHolders.size(); x++)
    {
        if (myCardHolders[x]->getId() == cardID && myCardHolders[x]->isActive())
        {
            cout << "\nCardholder: " << myCardHolders[x]->fullName() << endl;
            personPtr = myCardHolders[x];
        }
    }
    cout << "Card ID not found" << endl;
    char choice;
    if (personPtr != nullptr)
    {
        if (personPtr->isActive())
        {
            cout << "Are you sure you want to deactivate card (y/n)? ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                personPtr->setActive(0);
                cout << "\nCard ID deactivated" << endl;
            }
        }
        else
        {
            cout << "\nCard ID is already inactive" << endl;
        }
    }
}

int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int choice;
    int nextID;
    readBooks(books);
    nextID = readPerson(cardholders);
    readRentals(books, cardholders);
    do
    {
        printMenu();
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            Bookcheckout(cardholders, books);
            break;

        case 2:
            Bookreturn(books);
            break;

        case 3:
            availableBooks(books);
            break;

        case 4:
            outRentals(books, cardholders);
            break;

        case 5:
            cardRentals(books, cardholders);
            break;

        case 6:
            openCard(cardholders, nextID + 1);
            break;

        case 7:
            closeCard(cardholders);
            break;

        case 8:
            cout << "Closing Program" << endl;
            break;

        default:
            cout << "Invalid entry" << endl;
            break;
        }
        cout << endl;
    } while (choice != 8);
    return 0;
}