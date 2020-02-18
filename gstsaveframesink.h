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

#ifndef _GST_SAVEFRAMESINK_H_
#define _GST_SAVEFRAMESINK_H_

#include <gst/base/gstbasesink.h>

G_BEGIN_DECLS

#define GST_TYPE_SAVEFRAMESINK   (gst_saveframesink_get_type())
#define GST_SAVEFRAMESINK(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_SAVEFRAMESINK,GstSaveframesink))
#define GST_SAVEFRAMESINK_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_SAVEFRAMESINK,GstSaveframesinkClass))
#define GST_IS_SAVEFRAMESINK(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_SAVEFRAMESINK))
#define GST_IS_SAVEFRAMESINK_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_SAVEFRAMESINK))

typedef struct _GstSaveframesink GstSaveframesink;
typedef struct _GstSaveframesinkClass GstSaveframesinkClass;

struct _GstSaveframesink
{
  GstBaseSink base_saveframesink;

};

struct _GstSaveframesinkClass
{
  GstBaseSinkClass base_saveframesink_class;
};

GType gst_saveframesink_get_type (void);

G_END_DECLS

#endif
