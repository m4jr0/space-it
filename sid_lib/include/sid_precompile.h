#ifndef SID_PRECOMPILE_H
#define SID_PRECOMPILE_H

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>
#include <time.h>
#include <wchar.h>
#include <wctype.h>

#ifdef SID_WINDOWS
#include <windows.h>
#endif  // SID_WINDOWS

#ifdef SID_UNIX
#include <sys/time.h>
#endif  // SID_UNIX

#include "sid/define.h"

#include "sid/compilers.h"
#include "sid/debug.h"
#include "sid/os.h"
#include "sid/type.h"

#include "sid/log.h"

#include "sid/allocator.h"
#include "sid/memory.h"

#endif /* SID_PRECOMPILE_H */
