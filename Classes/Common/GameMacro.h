#ifndef __GAME_MACRO_H__
#define __GAME_MACRO_H__

#ifdef YN_WINDOWS
#define	SPRINTF			sprintf_s
#else
#define	SPRINTF			sprintf
#endif

#define GET_STRING(id) (DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(id))

#endif /* __GAME_MACRO_H__ */
