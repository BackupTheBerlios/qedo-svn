//
// CCM Container Implementation
// (C)2000-2001 Humboldt University Berlin, Department of Computer Science
//
// $Id: Output.cpp,v 1.1 2002/10/30 23:13:58 tom Exp $
//

static char rcsid[] = "$Id: Output.cpp,v 1.1 2002/10/30 23:13:58 tom Exp $";


#include "Output.h"


namespace HU_CCM_Container {

#if defined(HAVE_JTC) || defined(WIN32)
JTCMonitor* container_monitor = new JTCMonitor();
#else
#ifdef HAVE_PTHREAD_H
// if have to check for MICO and threads
MICOMT::Mutex* container_monitor = new MICOMT::Mutex(MICOMT::Mutex::Recursive);
#else
#error No threads configured
#endif /* HAVE_PTHREAD_H */
#endif /* HAVE_JTC */




} // namespace HU_CCM_Container

