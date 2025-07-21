// Filename: Date.h
//   Author: Aliyah Gesicki

#ifndef DATE_H
#define DATE_H
/************************************************************/
// System includes
#include "Book.h"
#include <iostream>
#include <string>
/************************************************************/
using std::cin;
using std::cout;
using std::string;
class Date
{
public:
  Date (int month, int day, int year) : month (month), day (day), year (year)
  {
  }

  bool
  operator== (const Date& d)
  {
    return (month == d.month && day == d.day && year == d.year);
  }

  bool
  isBefore (const Date& other) const
  {
    if (year < other.year)
    {
      return true;
    }

    else if (year == other.year && month < other.month)
    {
      return true;
    }

    else if (year == other.year && month == other.month && day < other.day)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  bool
  operator< (const Date& other) const
  {
    return (isBefore (other));
  }

  void
  setMonth (int m)
  {
    month = m;
  }

  void
  setDay (int d)
  {
    day = d;
  }

  void
  setYear (int y)
  {
    year = y;
  }

  int
  getMonth ()
  {
    return month;
  }

  int
  getDay ()
  {
    return day;
  }

  int
  getYear ()
  {
    return year;
  }

  friend std::ostream&
  operator<< (std::ostream& os, const Date& d)
  {
    os << d.month << "-" << d.day << "-" << d.year;
    return os;
  }

private:
  int month;
  int day;
  int year;
};
#endif
