/* GStreamer
 * Copyright (C) 2020 FIXME <fixme@example.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _Ugst_Usavefilesink_H_
#define _Ugst_Usavefilesink_H_

% prototypes
#include <gst/base/gstbasesink.h>

G_BEGIN_DECLS

#define Ugst_TYPE_Usavefilesink   (gst_Lsavefilesink_get_type())
#define Ugst_Usavefilesink(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),Ugst_TYPE_Usavefilesink,UgstUsavefilesink))
#define Ugst_Usavefilesink_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),Ugst_TYPE_Usavefilesink,UgstUsavefilesinkClass))
#define Ugst_IS_Usavefilesink(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),Ugst_TYPE_Usavefilesink))
#define Ugst_IS_Usavefilesink_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),Ugst_TYPE_Usavefilesink))

typedef struct _UgstUsavefilesink UgstUsavefilesink;
typedef struct _UgstUsavefilesinkClass UgstUsavefilesinkClass;

struct _UgstUsavefilesink
{
  GstBaseSink base_Lsavefilesink;

% prototypes
};

struct _UgstUsavefilesinkClass
{
  GstBaseSinkClass base_Lsavefilesink_class;
};

GType gst_Lsavefilesink_get_type (void);

G_END_DECLS

#endif
