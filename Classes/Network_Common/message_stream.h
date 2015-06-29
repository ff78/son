// -*- C++ -*-


#ifndef MESSAGE_STREAM_H_
#define MESSAGE_STREAM_H_

#include <string>
#include <string.h>
#include "Network_Common/global_macros.h"
/**
 * @class message_stream
 * 
 * @brief
 */
class message_stream
{
public:
  enum
  {
    big_endian      = 1,
    little_endian   = 2
  };
public:

  message_stream(char *bf, int len, int endian_type = little_endian)
  : endian_type_(endian_type),
  buff_len_(len),
  rd_ptr_(0),
  wr_ptr_(0),
  buff_(bf)
  { }

  void reset(char *bf, int len)
  {
    this->buff_     = bf;
    this->buff_len_ = len;
    this->rd_ptr_   = 0;
    this->wr_ptr_   = 0;
  }
  //= attribute method
  char *rd_ptr() const
  { return this->buff_ + this->rd_ptr_; }
  void rd_ptr(int val)
  { this->rd_ptr_ += val; }
  void set_rd_ptr(int val)
  { this->rd_ptr_ = val; }

  char *wr_ptr()
  { return this->buff_ + this->wr_ptr_; }
  void wr_ptr(int val)
  { this->wr_ptr_ += val; }
  void set_wr_ptr(int val)
  { this->wr_ptr_ = val; }

  char *get_ptr()
  { return this->buff_; }

  int space()
  { return this->buff_len_ - this->wr_ptr_; }

  int get_rd_ptr()
  {return this->rd_ptr_;}

  int length() const
  { return this->wr_ptr_ - this->rd_ptr_; }

  //= stream operator
  message_stream & operator <<(const char v)
  {
    if ((this->wr_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_in(&v, sizeof(v));
    return *this;
  }
  message_stream & operator <<(const short v)
  {
    if ((this->wr_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_in((const char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator <<(const int v)
  {
    if ((this->wr_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_in((const char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator <<(const unsigned int v)
  {
    if ((this->wr_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_in((const char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator <<(const double v)
  {
    if ((this->wr_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_in((const char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator <<(const sint64 v)
  {
    if ((this->wr_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_in((const char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator <<(const uint64 v)
  {
      if ((this->wr_ptr_ + (int)sizeof(v)) <= this->buff_len_)
          this->copy_in((const char *)&v, sizeof(v));
      return *this;
  }
  message_stream & operator <<(const char *v)
  {
    short len = ::strlen(v);
    if ((this->wr_ptr_ + (int)sizeof(short) + len) <= this->buff_len_)
    {
      this->copy_in((const char *)&len, sizeof(len));
      this->copy_in(v, len);
    }
    return *this;
  }
  message_stream & operator <<(const std::string &v)
  {
    if ((this->wr_ptr_ + (int)sizeof(short) + (int)v.length()) 
        <= this->buff_len_)
    {
      short len = v.length();
      this->copy_in((const char *)&len, sizeof(len));
      this->copy_in(v.data(), len);
    }
    return *this;
  }
  message_stream & operator <<(const message_stream &v)
  {
    if ((this->wr_ptr_ + v.length()) <= this->buff_len_)
      this->copy_in(v.rd_ptr(), v.length());
    return *this;
  }

  // out
  message_stream & operator >>(char &v)
  {
    if (this->rd_ptr_ + (int)sizeof(v) <= this->buff_len_)
      this->copy_out((char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator >>(short &v)
  {
    if ((this->rd_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_out((char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator >>(int &v)
  {
    if ((this->rd_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_out((char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator >>(unsigned int &v)
  {
    if ((this->rd_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_out((char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator >>(double &v)
  {
    if ((this->rd_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_out((char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator >>(sint64 &v)
  {
    if ((this->rd_ptr_ + (int)sizeof(v)) <= this->buff_len_)
      this->copy_out((char *)&v, sizeof(v));
    return *this;
  }
  message_stream & operator >>(uint64 &v)
  {
      if ((this->rd_ptr_ + (int)sizeof(v)) <= this->buff_len_)
          this->copy_out((char *)&v, sizeof(v));
      return *this;
  }
  message_stream & operator >>(std::string &v)
  {
    if ((this->rd_ptr_ + (int)sizeof(short)) <= this->buff_len_)
    {
      short len = *((short *)(this->buff_ + this->rd_ptr_));
      this->rd_ptr_ += sizeof(short);
      if (this->rd_ptr_ + len <= this->buff_len_)
      {
        v.assign(this->buff_ + this->rd_ptr_, len);
        this->rd_ptr_ += len;
      }
    }
    return *this;
  }
protected:
  void copy_in(const char *p, int len)
  {
    if (this->endian_type_ == big_endian)
    {
      for (int i = 0; i < len; ++i)
      {
        ::memcpy(this->buff_ + this->wr_ptr_ + i,
                 p + len - i - 1, 
                 sizeof(char));
      }
    }else
      ::memcpy(this->buff_ + this->wr_ptr_, p, len);
    this->wr_ptr_ += len;
  }
  void copy_out(char *p, int len)
  {
    if (this->endian_type_ == big_endian)
    {
      for (int i = 0; i < len; ++i)
      {
        ::memcpy(p + len - i - 1, 
                 this->buff_ + this->rd_ptr_ + i, 
                 sizeof(char));
      }
    }else
      ::memcpy(p, this->buff_ + this->rd_ptr_, len);
    this->rd_ptr_ += len;
  }
private:
  int endian_type_;
  int buff_len_;
  int rd_ptr_;
  int wr_ptr_;

  char *buff_;
};

#endif // MESSAGE_STREAM_H_

