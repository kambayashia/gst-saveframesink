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
 * Free Software Foundation, Inc., 51 Franklin Street, Suite 500,
 * Boston, MA 02110-1335, USA.
 */
/**
 * SECTION:element-gstLsavefilesink
 *
 * The Lsavefilesink element does FIXME stuff.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch-1.0 -v fakesrc ! Lsavefilesink ! FIXME ! fakesink
 * ]|
 * FIXME Describe what the pipeline does.
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
% prototypes
#include <gst/base/gstbasesink.h>
#include "gstLsavefilesink.h"

GST_DEBUG_CATEGORY_STATIC (gst_Lsavefilesink_debug_category);
#define GST_CAT_DEFAULT gst_Lsavefilesink_debug_category

/* prototypes */


static GstCaps *gst_Lsavefilesink_get_caps (GstBaseSink * sink, GstCaps * filter);
% pad-template

enum
{
  PROP_0
};

/* pad templates */

static GstStaticPadTemplate gst_Lsavefilesink_sink_template =

/* class initialization */

G_DEFINE_TYPE_WITH_CODE (UgstUsavefilesink, gst_Lsavefilesink, GST_TYPE_BASE_SINK,
  GST_DEBUG_CATEGORY_INIT (gst_Lsavefilesink_debug_category, "Lsavefilesink", 0,
  "debug category for Lsavefilesink element"));

static void
gst_Lsavefilesink_class_init (UgstUsavefilesinkClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstBaseSinkClass *base_sink_class = GST_BASE_SINK_CLASS (klass);

  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. */
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS(klass),

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS(klass),
      "FIXME Long name", "Generic", "FIXME Description",
      "FIXME <fixme@example.com>");

  gobject_class->set_property = gst_Lsavefilesink_set_property;
  base_sink_class->get_caps = GST_DEBUG_FUNCPTR (gst_Lsavefilesink_get_caps);

}

static void
gst_Lsavefilesink_init (UgstUsavefilesink *Lsavefilesink)
{
% methods
}

static GstCaps *
% end

static gboolean
plugin_init (GstPlugin * plugin)
{

  /* FIXME Remember to set the rank if it's an element that is meant
     to be autoplugged by decodebin. */
  return gst_element_register (plugin, "Lsavefilesink", GST_RANK_NONE,
      Ugst_TYPE_Usavefilesink);
}

/* FIXME: these are normally defined by the GStreamer build system.
   If you are creating an element to be included in gst-plugins-*,
   remove these, as they're always defined.  Otherwise, edit as
   appropriate for your external plugin package. */
#ifndef VERSION
#define VERSION "0.0.FIXME"
#endif
#ifndef PACKAGE
#define PACKAGE "FIXME_package"
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME "FIXME_package_name"
#endif
#ifndef GST_PACKAGE_ORIGIN
#define GST_PACKAGE_ORIGIN "http://FIXME.org/"
#endif

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    Lsavefilesink,
    "FIXME plugin description",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)

