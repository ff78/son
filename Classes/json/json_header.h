#ifndef __JSON_HEADER_H__
#define __JSON_HEADER_H__

#ifdef GAME_CLIENT
#include "json_lib.h"
namespace Json = CSJson;
#else
#include "json/json.h"
#endif

#endif
