
#ifndef MUDUO_BASE_DATE_H
#define MUDUO_BASE_DATE_H

#include "./copyable.h"
#include "./Types.h"

struct tm;
namespace muduo
{
class Date : public muduo::copyable
{
     public:
        struct YearMonthDay
        {
            int year; // [1900..2500]
            int month;  // [1..12]
            int day;  // [1..31]
        };
    static const int kDaysPerWeek = 7;
    static const int kJulianDayOf1970_01_01;
    Date() : julianDayNumber_(0)
    {

    }

    Date(int year, int month, int day);

    explicit Date(int julianDayNum): julianDayNumber_(julianDayNum)
    {

    }

    explicit Date(const struct tm&);

    void swap(Date& that)
    {
        std::swap(julianDayNumber_, that.julianDayNumber_);
    }

    bool valid() const { return julianDayNumber_ > 0; }

/// Converts to yyyy-mm-dd format.
    std::string toIsoString() ;

    struct YearMonthDay yearMonthDay();

    int year() 
  {
    return yearMonthDay().year;
  }

   int month() 
  {
    return yearMonthDay().month;
  }

  int day() 
  {
    return yearMonthDay().day;
  }

  // [0, 1, ..., 6] => [Sunday, Monday, ..., Saturday ]
  int weekDay() 
  {
    return (julianDayNumber_+1) % kDaysPerWeek;
  }

int julianDayNumber() const { return julianDayNumber_; }

 private:
   int julianDayNumber_;

};
}
#endif  