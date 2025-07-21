// Filename: Book.hpp
//   Author: Aliyah Gesicki
#ifndef BOOK_H
#define BOOK_H
/************************************************************/
// System includes
#include "Date.h"
#include <iostream>
#include <string>
#include <vector>
/************************************************************/
// Using Statements
using std::cin;
using std::cout;
using std::string;

class Book
{
public:
  Book (string title, string author, Date start)
    : title (title), author (author), start (start)
  {
  }

  void
  setTitle (string t)
  {
    title = t;
  }

  void
  setAuthor (string a)
  {
    author = a;
  }

  void
  setStart (Date s)
  {
    start = s;
  }

  string
  getTitle ()
  {
    return title;
  }

  string
  getAuthor ()
  {
    return author;
  }

  Date
  getStart ()
  {
    return start;
  }

  friend std::ostream&
  operator<< (std::ostream& os, const Book& b)
  {
    os << " " << b.title << " , " << b.author << " , " << b.start;
    return os;
  }

private:
  string author;
  string title;
  Date start;
};
#endif
