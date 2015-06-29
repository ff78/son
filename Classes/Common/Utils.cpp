// -*- C++ -*-


#include "Common/Utils.h"
#include <sstream>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

namespace Utils
{


  int write_json_to_file( const char* file_name, Json::Value& v )
  {

    return 0;
  }

  std::string int_to_string( int n )
  {
    std::ostringstream stream;
    //stream.setf(10);
    stream << n;
    return stream.str();
  }

  int string_to_int(const std::string& str){
	  stringstream stream;
	  stream<<str;
	  int n;
	  stream>>n;
	  return n;
  }

  int get_value_by_file( const char* file_name, Json::Value& data )
  {
	  //unsigned long size = 0;
	  ssize_t size = 0;
	  unsigned char* pData = 0;

	  std::string path_name = 
		  FileUtils::getInstance()->fullPathForFilename(file_name);



	  pData = cocos2d::FileUtils::getInstance()->getFileData
		  (file_name, "rb", &size);

	  Json::Reader reader;

	  if (!reader.parse((const char*) pData,(const char*) (pData+size), data))
	  {
		  CCLog("{ can not parse %s file: %d }", file_name,-1);
		  CC_SAFE_DELETE_ARRAY(pData);  
		  return -1;

	  };
	  CC_SAFE_DELETE_ARRAY(pData);  

	  return 0;
  }

  int split_string_with_token( const char *src, char token, std::vector<std::string> &vec_result )
  {

	  assert(src != NULL);

	  char *start = (char *)src;
	  char *find_pos = NULL;
	  char * pre_find_pos;
	  char * end = start + strlen(src);
	  int count = 0;

	  while ( (find_pos = strchr(start, token)) != NULL )
	  {
		  if ( find_pos != start )
		  {
			  std::string buffer(start, find_pos - start);
			  vec_result.push_back(buffer);
			  ++count;
			  pre_find_pos = find_pos;
		  }

		  start = find_pos + 1;
	  }
	  if(pre_find_pos != NULL && ++pre_find_pos < end){
		  std::string buffer(pre_find_pos, end);
		  vec_result.push_back(buffer);
		  ++count;
	  }

	  return count;
  }

  int split_string_with_pre_and_end( const char *src, char pre_token, char end_token, std::vector<std::string> &vec_result )
  {
	  assert(src != NULL);

	  char *start = (char *)src;
	  char *find_pos_pre = NULL;
	  char *find_pos_end = NULL;
	  int count = 0;

	  while ( (find_pos_pre = strchr(start, pre_token)) != NULL )
	  {
		  if ( find_pos_pre != start )
		  {
			  find_pos_pre++;
			  find_pos_end = strchr(find_pos_pre, end_token);
			  if(!find_pos_end){
				  break;
			  }
			  std::string buffer(find_pos_pre, find_pos_end);
			  vec_result.push_back(buffer);
			  ++count;
			  find_pos_pre = find_pos_end;
		  }

		  start = find_pos_pre + 1;
	  }
	  return count;
  }


};
