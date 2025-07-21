//Filename: Library.cpp
//Author: Aliyah Gesicki
/************************************************************/
// System includes
#include "Book.h"
#include "Date.h"
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale.h>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
/************************************************************/
//Using Statements
using std::cin;
using std::cout;
using std::endl;
using std::find_if;
using std::ifstream;
using std::left;
using std::ofstream;
using std::queue;
using std::setw;
using std::sort;
using std::string;
using std::stringstream;
using std::vector;
/************************************************************/

Book
addBook ()
{
  //creates a book and returns it so it can be added to the shelf
  string title;
  string author;
  cout << "Please enter the title of the book:" << endl;
  cin.ignore ();
  getline (cin, title);

  cout << "\n" << "Please enter the author's first and last name:" << endl;
  getline (cin, author);
  cout << "Please enter today's date: " << endl;

  cout << "M: " << endl;
  int month;
  cin >> month;

  cout << "D: " << endl;
  int day;
  cin >> day;

  cout << "YYYY: " << endl;
  int year;
  cin >> year;

  Date d (month, day, year);
  Book b (title, author, d);
  return b;
}
/************************************************************/
Book
chooseBook (vector<Book>& shelf)
{
  int choice;
  for (int i = 0; i < shelf.size (); ++i)
  {
    cout << " ( " << i << " ) " << " " << shelf[i] << " - ";
  }
  cout << "\n" << "Choose a book to grab: ";
  cin >> choice;
  //selection is the shelf at index choice
  //it then removes that specific book from the shelf using erase and returns it
  Book selection = shelf[choice];
  shelf.erase (shelf.begin () + choice);
  return selection;
}
/************************************************************/
bool
compareRecentDate (Book& a, Book& b)
{
  return b.getStart () < a.getStart ();
}
/************************************************************/
void
displayShelf (vector<Book>& shelf)
{
  sort (shelf.begin (), shelf.end (), compareRecentDate);
  cout << left << setw (20) << "Title" << setw (40) << "Author" << setw (60)
       << "Date of Last Reading" << endl;
  cout << left << setw (20) << "-----" << setw (40) << "------" << setw (60)
       << "--------------------" << endl;

  for (auto e : shelf)
  {
    cout << left << setw (20) << e.getTitle () << setw (40) << e.getAuthor ()
         << e.getStart ().getMonth () << " - " << e.getStart ().getDay ()
         << " - " << e.getStart ().getYear () << endl;
  }
}
/************************************************************/
void
saveShelf (vector<Book>& shelf, string filename)
{
  ofstream outFile (filename);
  if(shelf.empty())
  if (!outFile)
  {
    cout << "Error saving file" << endl;
  }
  for (auto e : shelf)
  {
    outFile << e.getTitle () << "|" << e.getAuthor () << "|"
            << e.getStart ().getMonth () << "-" << e.getStart ().getDay ()
            << "-" << e.getStart ().getYear () << endl;
  }
  outFile.close ();
  cout << "Shelf saved successfully." << endl;
}
/************************************************************/
void
loadShelf (vector<Book>& shelf, string filenamename)
{
  ifstream inFile (filenamename);
  //string stream wraps each line(string) into a singular continuous string
  //getline gets the strings in inFile s is the wrapped string, title is the first item (string) to parse before the delimiter '|'
  //then author and so on...
  //sdate is a date object that is wrapped into a string
  //continue skips if line is malformed or empty
  //parse sdate for integers use sscanf and sdate.cstr()
  string line;

  while (getline (inFile, line))
  {
    if (line.empty ())
      continue;
    stringstream s (line);
    string title, author, sdate;
    if (!getline (s, title, '|'))
      continue;
    if (!getline (s, author, '|'))
      continue;
    if (!getline (s, sdate, '|'))
      continue;
    int month, day, year;
    //sscanf scans the converted c string of sdate for 3 integers specifically month,date,and year(by reference)
    //'-' is the delimiter between the integers
    sscanf (sdate.c_str (), "%d-%d-%d", &month, &day, &year);
    //the book constructed from month,date,and year is then pushed onto the shelf;
    Date d (month, day, year);
    Book b (title, author, d);
    shelf.push_back (b);
  }
  inFile.close ();
}
/************************************************************/
void
saveDropbox (queue<Book>& dropbox, string dropname)
{
  queue<Book>copy = dropbox;
  ofstream outFile (dropname);
  if (!outFile)
  {
    cout << "Error Saving file";
  }
  while (!copy.empty ())
  {
    Book b = copy.front ();
    outFile << b.getTitle () << "|" << b.getAuthor () << "|"
            << b.getStart ().getMonth () << "-" << b.getStart ().getDay ()
            << "-" << b.getStart ().getYear () << endl;
    copy.pop ();
  }
  outFile.close ();
  cout << "return box saved successfully" << endl;
}
/************************************************************/
void
loadDropbox (queue<Book>& dropbox, string dbfilename)
{

  ifstream inFile (dbfilename);
  string line;
  while (getline (inFile, line))
  {
    if (line.empty ())
      continue;
    stringstream s (line);
    string title, author, sdate;
    if (!getline (s, title, '|'))
      continue;
    if (!getline (s, author, '|'))
      continue;
    if (!getline (s, sdate, '|'))
      continue;
    int month, day, year;
    sscanf (sdate.c_str (), "%d-%d-%d", &month, &day, &year);
    Date d (month, day, year);
    Book b (title, author, d);
    dropbox.push (b);
  }
  inFile.close ();
}
void
accessShelf (int option, vector<Book>& shelf, queue<Book>& dropbox,string filename, string dbfilename)
{
  if (option == 0)
  {
    cout << "Thank you, goodbye!" << "\n" << endl;
    exit (0);
  }
  else if (option == 1)
  {
    shelf.push_back (addBook ());
    for (auto e : shelf)
    {
      cout << e << " ";
    }
  }

  else if (option == 2)
  {
    if (!shelf.empty ())
    {
      Book b = chooseBook (shelf);
      cout << "You chose: " << b << "\n" << endl;
      dropbox.push (b);
    }
    else
    {
      cout << "Sorry, the shelf is empty!" << "\n" << endl;
    }
  }

  else if (option == 3)
  {
    if (!dropbox.empty ())
    {
      Book returnitem = dropbox.front ();
      dropbox.pop ();
      shelf.push_back (returnitem);
      cout << "You returned" << returnitem << "\n" << endl;

    }
    else
    {
      cout << "There are no items to return." << "\n" << endl;
    }
  }
  else if (option == 4)
  {
    string item;
    cout << "Enter the title of the book you are looking for: " << endl;
    cin.ignore ();
    getline (cin, item);

    //searches from shelf.begin() to shelf.end()
    //captures item (user input string from outside lambda)
    //takes a book by reference and returns true if it matches item

    auto it = find_if (shelf.begin (), shelf.end (),[item] (Book& b)
     { return b.getTitle () == item; 
     });
    if (it != shelf.end ())
    {
      cout << *it << " is on the shelf";
    }
    else
    {
      cout << "Book not found";
    }
  }
  
  else if (option == 5)
  {
    if (!shelf.empty ())
    {
      displayShelf (shelf);
    }
    else
    {
      cout << "No books to display.";
    }
  }
  saveShelf(shelf,filename);
  if(!dropbox.empty())
  {
     saveDropbox(dropbox,dbfilename);
  }
 
}

void
printIntro (vector<Book>& shelf, queue<Book>&dropbox,string filename,string dbfilename)
{
  int option;
  cout << "\n"
       << "Welcome to the Digital Bookshelf!" << "\n"
       << "Your options are as follows:" << endl;
  cout << "\n"
       << "[1] Add a new book to the shelf" << "\n"
       << "[2] Grab a book off the shelf" << "\n"
       << "[3] Return a book" << "\n"
       << "[4] Search for a book" << "\n"
       << "[5] Display shelf" << "\n"
       << "[0] Exit" << endl;
  cout << "Enter option:  ";
  cin >> option;
  //create function called access shelf that accesses the vector where books are stored
  accessShelf (option, shelf,dropbox,filename,dbfilename);
}

int
main ()
{
  queue<Book> dropbox;
  vector<Book> shelf;
  string filename;
  cout << "Please Enter the name of the file you are using to store the shelf "
          "(include .txt) at the end"
       << endl;
  cin >> filename;
  string dbfilename;
  cout << "Please Enter the name of the file you are using to store the books "
       << "to be returned (include .txt) at the end" << endl;
  cin >> dbfilename;
  loadShelf (shelf, filename);
  loadDropbox (dropbox, dbfilename);
  while (true)
  {
    printIntro (shelf, dropbox,filename,dbfilename);
  }
}