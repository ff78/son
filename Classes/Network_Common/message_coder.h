    // -*- C++ -*-


#ifndef MESSAGE_CODER_H_
#define MESSAGE_CODER_H_

#include "Game_Interface/common.h"
#include <list>
#include <string>
#include <string.h>
#include <assert.h>
#include "Network_Common/message_stream.h"
#include "Network/msg_manager.h"
#ifdef GAME_CLIENT
#include "cocos2d.h"
#endif
class msg_head
{
public:
  msg_head(int id, int result = 0, int param = 0, int err_no = 0)
  : msg_id_(id),
  result_(result),
  param_(param),
  errno_(err_no)
  { }
  
  int msg_id_;
  int result_;
  int param_;
  int errno_;
};

/**
 * @class message_coder
 *
 * @brief code/decode message
 */

typedef unsigned int DWORD_RE;

const DWORD_RE EncodeMiniValue = 0x3C3C3C3C;
#define DWORD_SIZE sizeof(DWORD_RE)

namespace help 
{
  extern int split_msg(const char *bf, 
                       int bf_len, 
                       std::list<std::string> &msg_list);
  extern int split_msg2(const char *bf, int bf_len, std::list<Msg_Data> &msg_list);

  inline extern void enclose_msg(char *bf, int msg_len)
  {
    bf[0] = '#';
    bf[msg_len + 1] = '!';
  }

  extern int encode_24bit_buf(DWORD_RE *src, 
                       int src_unit, 
                       DWORD_RE *dest, 
                       int dest_unit);

  extern int decode_24bit_buf(DWORD_RE *src, 
                       int src_unit, 
                       DWORD_RE *dest, 
                       int dest_unit);

  extern inline int calc_source_unit(int size)
  {
    return (size % DWORD_SIZE) ? 
      (size / DWORD_SIZE + 1) : (size / DWORD_SIZE);
  }
  extern inline int calc_encode_unit(int de_unit)
  {
    int en_unit = de_unit / 3 * 4;
    int rm_unit = de_unit % 3;
    if (rm_unit > 0)
      en_unit += rm_unit + 1;
    return en_unit;
  }
  extern inline int calc_decode_unit(int en_unit)
  {
    int rm_unit = en_unit & 3;
    int de_unit = en_unit >> 2;
    de_unit += de_unit << 1;
    return (rm_unit > 0) ? (de_unit + rm_unit - 1) : de_unit;
  }
  //
  extern inline int calc_encode_size(int de_size)
  { 
    return calc_encode_unit(calc_source_unit(de_size)) 
      * DWORD_SIZE; 
  }
  //
  extern inline int calc_decode_size(int en_size)
  { 
    return calc_decode_unit(calc_source_unit(en_size)) 
      * DWORD_SIZE; 
  }
}


/**
 * @brief encode msg
 */
class message_encode
{
public:
  message_encode(char *en_bf, int en_bf_len)
    : buff_len_(en_bf_len),
    offset_(0),
    buff_(en_bf)
  {

  }

  // encode
  message_encode & operator <<(message_stream &v)
  {
    if (this->offset_ + v.length() < this->buff_len_)
    {
      
      if (v.length() == 0 
          || v.length() > (this->buff_len_ - this->offset_))
        return *this;

  
      int en_len = help::calc_encode_size(v.length());


//assert(en_len < (this->buff_len_ - this->offset_));
      this->encode(v.rd_ptr(),
                   v.length(),
                   this->buff_ + this->offset_,
                   en_len);
     
      v.rd_ptr(v.length());
      this->offset_ += en_len;
    }
  
    return *this;
  }

  int length() const
  { return this->offset_; }
protected:
  // return the length of encoded content
  int encode(const char *src, 
             int src_len, 
             char *dest, 
             int dest_len)
  {
    if (src == 0 
        || dest == 0 
        || help::calc_encode_size(src_len) > dest_len)
      return -1;


    
    int src_unit = help::calc_source_unit(src_len);

    return help::encode_24bit_buf((DWORD_RE*)src, 
                                  src_unit, 
                                  (DWORD_RE*)dest, 
                                  help::calc_encode_unit(src_unit)) * DWORD_SIZE;
  }
private:
  int buff_len_;
  int offset_;
  char *buff_;
}; // end of message_encode

class message_decode
{
public:
  message_decode(const char *en_bf, int en_bf_len)
    : buff_len_(en_bf_len),
    offset_(0),
    buff_(en_bf)
  { }
  void operator >>(message_stream &v)
  {
    if (this->offset_ < this->buff_len_)
    {
      int h_len = help::calc_encode_size(sizeof(msg_head));
      // decode head
      this->decode(this->buff_ + this->offset_,
                   h_len,
                   v.wr_ptr(),
                   sizeof(msg_head));
      v.wr_ptr(sizeof(msg_head));
      this->offset_ += h_len;

      // decode body
      int len = this->decode(this->buff_ + this->offset_,
                             this->buff_len_ - h_len,
                             v.wr_ptr(),
                             v.space());
      v.wr_ptr(len);
    }
    //return *this;
  }
protected:
  // return the length of decoded content
  int decode(const char *src, int src_len, char *dest, int dest_len)
  {
    if (src == 0 
        || dest == 0 
        || help::calc_decode_size(src_len) > dest_len)
      return -1;

    int src_unit = help::calc_source_unit(src_len);
    return help::decode_24bit_buf((DWORD_RE*)src, 
                                  src_unit,
                                  (DWORD_RE*)dest, 
                                  help::calc_decode_unit(src_unit)) * DWORD_SIZE;
  }
private:
  int buff_len_;
  int offset_;
  const char *buff_;
}; // end of message_decode

#undef DWORD_SIZE
#endif

