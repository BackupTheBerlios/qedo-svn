/*******************************************************************************
*   
*   File    : version.c
*   Author  : Harald Böhme
*             Humboldt University Berlin
*             Department of Computer Science / System Analysis
*   e-mail  : boehme@informatik.hu-berlin.de
*   Remark  : this file contains information about date of build
*             of the executable, the host it was built on and the
*             flags used; it is compiled when executable is linked
*   $Date: 2002/10/11 07:36:26 $
*   $Revision: 1.1 $
*
*******************************************************************************/

#include "version.h"

#ifndef WIN32
static char id[] __attribute__((unused)) = "$Id: version.c,v 1.1 2002/10/11 07:36:26 neubauer Exp $";
#endif

#ifdef COMPILED
char COMPILED_AT[] = COMPILED;
#else
#ifdef __TIMESTAMP__
char COMPILED_AT[] = __TIMESTAMP__;
#else
char COMPILED_AT[] = "today now";
#endif
#endif

#ifdef HOST
char COMPILED_ON[] = HOST;
#else
char COMPILED_ON[] = "";
#endif

#if (defined(CFLAGS) && defined(CG_CONFIG))
char COMPILED_FLAGS[] = "config="CG_CONFIG" flags="CFLAGS;
#else
char COMPILED_FLAGS[] = "";
#endif
