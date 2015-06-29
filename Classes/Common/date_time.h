// -*- C++ -*-


#ifndef CUTE_DATE_TIME_H_
#define CUTE_DATE_TIME_H_

#include <ctime>
#include <cstdio>
#include <cstring>

namespace cute
{
  /**
   * @class date_time
   *
   * @brief 
   */
  class date_time
  {
  public:
    date_time()
    {
        time_ = ::time(NULL);
        tm_ = localtime(&time_);
    }

    explicit date_time(const time_t tt)
    {
        time_ = tt; 
        tm_ = localtime(&time_);
    }

    // Override operator
    inline date_time& operator = (const date_time &dt)
    {
      if (this != &dt)
      {
        this->time_ = dt.time_;
        this->tm_   = dt.tm_;
      }
      return *this;
    }
    
    inline int year  (void) const {return tm_->tm_year + 1900;}
    inline int month (void) const {return tm_->tm_mon  + 1;}
    inline int wday  (void) const {return tm_->tm_wday ;}
    inline int mday  (void) const {return tm_->tm_mday ;}
    inline int hour  (void) const {return tm_->tm_hour ;}
    inline int minute  (void) const {return tm_->tm_min ;}
    inline int second   (void) const {return tm_->tm_sec ;}

  private:
    time_t    time_;
    struct tm* tm_;
  };
} // namespace cute

#endif // CUTE_DATE_TIME_H_

