// -*- C++ -*-

#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H
const double EPSILON = 1.00e-07;
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))

#define FLOAT_EQUAL(x, y) (abs((x) - (y)) < 0.01)

#define RANDOM_PERCENT() ((int)rand()%100)

#define RANDOM_To(num) ((int)rand()%(num) + 1)

#include "json/json_header.h"
#include "string"
#include "vector"

namespace Utils
{
  int write_json_to_file(const char* file_name, Json::Value& v);
  int get_value_by_file(const char* file_name, Json::Value& data);
  std::string int_to_string( int n );
  int string_to_int(const std::string& str);
  int split_string_with_token(const char *src, char token, std::vector<std::string> &vec_result);
  int split_string_with_pre_and_end(const char *src, char pre_token, char end_token, std::vector<std::string> &vec_result);
};


#endif /* UTILS_H */
