
/*******************************************************************************
*   File    : version.h
*   Author  : Harald Böhme
*   e-mail  : boehme@informatik.hu-berlin.de
*   Date    : Wed Jan 19 14:58:59 MET 2000
*   Remark  : provides version strings
*******************************************************************************/

#define __CIDL2CPP__ 0.9

#define AUTHOR "Harald Boehme"


#ifdef	__cplusplus
extern "C" {
#endif

/* this is defined in version.c to log version info */
extern char COMPILED_ON[];
extern char COMPILED_AT[];
extern char COMPILED_FLAGS[];

#ifdef	__cplusplus
}
#endif
