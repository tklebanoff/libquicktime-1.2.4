/*******************************************************************************
 lqt_private.h

 libquicktime - A library for reading and writing quicktime/avi/mp4 files.
 http://libquicktime.sourceforge.net

 Copyright (C) 2002 Heroine Virtual Ltd.
 Copyright (C) 2002-2011 Members of the libquicktime project.

 This library is free software; you can redistribute it and/or modify it under
 the terms of the GNU Lesser General Public License as published by the Free
 Software Foundation; either version 2.1 of the License, or (at your option)
 any later version.

 This library is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 details.

 You should have received a copy of the GNU Lesser General Public License along
 with this library; if not, write to the Free Software Foundation, Inc., 51
 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*******************************************************************************/

#ifndef LQT_PRIVATE_H
#define LQT_PRIVATE_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef __GNUC__
#  define __attribute__(x)
#endif

/* Translation for static strings
   this macro does nothing but allows xgettext to extrack statically
   initialized strings */

#define TRS(s) (s)

#include "lqt_funcprotos.h"
#include <quicktime/qtprivate.h>

#endif
