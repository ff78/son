#include "Network_Common/message_coder.h"
#include <stdio.h>
#include "Network/msg_manager.h"

namespace help 
{
int split_msg(const char *bf, 
              int bf_len, 
              std::list<std::string> &msg_list)
{
  static char head_ = '#'; 
  static char tail_ = '!';

  if (*bf != head_) 
  {
    //printf("split [%d][%s]\n", bf_len, bf);
    // skip this incompleted msg.
    char *p = ::strchr(const_cast<char *>(bf), tail_);
    if (p != NULL && p - bf < bf_len) return p - bf + 1;
    return 0;
  }

  int offset = 0;
  const char *iter = bf + 1;
  if (*iter == tail_) return 2;/* #! */

  const char *msg_begin = iter;
  while (*iter && (iter - bf < bf_len))
  {
    if (*iter == tail_)
    {
      if (msg_begin != iter && iter > msg_begin)
        msg_list.push_back(std::string(msg_begin, 
                                       iter - msg_begin));
      offset += iter - msg_begin + 2;
      if (*(iter + 1) == tail_) break;  // add by cuisw 2011-05-03
      msg_begin = iter + 2; // skip !#
    }
    ++iter;
  }
  return offset;
}

int split_msg2(const char *bf, int bf_len, std::list<Msg_Data> &msg_list)
{
	long left_length = bf_len;
	int offset = 0;
	while(left_length > 0){
		if (left_length <= sizeof(int))	
			return offset;
		const char* _pack_ptr = bf + offset;
		int _pack_len = *((int*)(_pack_ptr));
		if (_pack_len <= sizeof(int)){
			// 如果程序跑到这里，肯定协议出问题，最好出现日志
			printf("split_msg2 error 777! _pack_len=%d \n", _pack_len);
		}
		//如果是半包，返回已经处理的偏移指针
		if (left_length < _pack_len)
			return offset;
		// 解析协议
		Msg_Data _msg;
		_msg.reset();
		_msg.set_buff2(_pack_ptr + sizeof(int), _pack_len - sizeof(int));
		msg_list.push_back(_msg);
		offset = offset + _pack_len;
		left_length = left_length - _pack_len;
	}
	return offset;
}


int encode_24bit_buf(DWORD_RE *src, 
                     int src_unit, 
                     DWORD_RE *dest, 
                     int dest_unit)
{
  const DWORD_RE FrontMasks[3] =
  { 0x00000000, 0xC0C0C0C0, 0xF0F0F0F0 };
  const DWORD_RE BeHindMasks[3] =
  { 0x3F3F3F3F, 0x0F0F0F0F, 0x03030303 };
  const DWORD_RE ExhaustMasks[3] =
  { 0xC0C0C0C0, 0x30303030, 0x0C0C0C0C };

 //cocos2d::CCLog("{1   encode_24bit_buf}\n" );
  
  DWORD_RE dwIdx, dwFront, dwBehind, dwExhaust, dwNewCode;
  int result = 0;
  dwIdx = dwNewCode = dwExhaust = 0;
  while (src_unit > 0)
  {
    //cocos2d::CCLog("{2   encode_24bit_buf src unit %d }\n", src_unit ); 
    if (dest_unit <= 0)
      break;
    dwFront = *src & FrontMasks[dwIdx];
    dwBehind = *src & BeHindMasks[dwIdx];
    dwExhaust = *src & ExhaustMasks[dwIdx];
     //cocos2d::CCLog("{3   encode_24bit_buf}\n" );
    if (dwIdx == 0)
    {
        //cocos2d::CCLog("{41   encode_24bit_buf} dwFront %d dwBehind %d  EncodeMiniValue  % \n", dwFront, dwBehind, EncodeMiniValue ); 
      *dest = dwBehind + EncodeMiniValue;
      dwNewCode = dwExhaust;
      dwIdx = 1;
       //cocos2d::CCLog("{42  encode_24bit_buf}\n" );
    }
    else if (dwIdx == 1)
    {
        //cocos2d::CCLog("{51   encode_24bit_buf} dwFront %d dwBehind %d  EncodeMiniValue  % \n", dwFront, dwBehind, EncodeMiniValue ); 
      *dest = ((dwFront >> 2) | (dwBehind)) + EncodeMiniValue;
      dwNewCode = dwNewCode | dwExhaust;
      dwIdx = 2;
       //cocos2d::CCLog("{52   encode_24bit_buf}\n" );
    }
    else
    {
      //cocos2d::CCLog("{61   encode_24bit_buf} dwFront %d dwBehind %d  EncodeMiniValue  % \n", dwFront, dwBehind, EncodeMiniValue ); 
      *dest = ((dwFront >> 2) | (dwBehind)) + EncodeMiniValue;
             //cocos2d::CCLog("{62   encode_24bit_buf}\n" );
      result++;
      dest++;
      dest_unit--;

       //cocos2d::CCLog("{63   encode_24bit_buf}\n" );
       

      if (!dest_unit)
        break;

      *dest = ((dwNewCode | dwExhaust) >> 2) + EncodeMiniValue;
      dwIdx = 0;
       //cocos2d::CCLog("{7   encode_24bit_buf}\n" );
    }
    result++;
    src_unit--;
    dest_unit--;
    src++;
    dest++;
  }
   //cocos2d::CCLog("{8   encode_24bit_buf}\n" );
  if (dwIdx && dest_unit > 0)
  {
    *dest = ((dwNewCode | dwExhaust) >> 2) + EncodeMiniValue;
    result++;
  }
  return result;
}

int decode_24bit_buf(DWORD_RE *src, 
                     int src_unit, 
                     DWORD_RE *dest, 
                     int dest_unit)
{
  const DWORD_RE FrontMasks[3] =
  { 0x00000000, 0x30303030, 0x3C3C3C3C };
  const DWORD_RE BeHindMasks[3] =
  { 0x3F3F3F3F, 0x0F0F0F0F, 0x03030303 };
  const DWORD_RE IncludeMasks[3] =
  { 0xC0C0C0C0, 0x30303030, 0x0C0C0C0C };

  DWORD_RE dwIdx, dwFront, dwBehined, dwInclude, dwThisCode;
  int result = 0;
  if (src_unit < 1)
    return result;
  dwIdx = dwInclude = 0;
  while (src_unit > 0)
  {
    if (dest_unit <= 0)
      break;
    dwThisCode = *src - EncodeMiniValue;
    if (dwIdx == 0)
    {
      dwInclude = src_unit > 3 ? src[3] : src[src_unit - 1];
      dwInclude = (dwInclude - EncodeMiniValue) << 2;
      src_unit--;

      *dest = dwThisCode | (dwInclude & IncludeMasks[0]);
      dwIdx = 1;
    }
    else if (dwIdx == 1)
    {
      dwFront = (dwThisCode & FrontMasks[1]) << 2;
      dwBehined = dwThisCode & BeHindMasks[1];

      *dest = dwFront | dwBehined | (dwInclude & IncludeMasks[1]);

      dwIdx = 2;
    }
    else if (dwIdx == 2)
    {
      dwFront = (dwThisCode & FrontMasks[2]) << 2;
      dwBehined = dwThisCode & BeHindMasks[2];

      *dest = dwFront | dwBehined | (dwInclude & IncludeMasks[2]);
      dwIdx = 0;

      src++;
    }
    result++;
    src++;
    dest++;
    src_unit--;
    dest_unit--;
  }
  return result;
}
}
