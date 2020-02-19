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
 * SECTION:element-gstsaveframesink
 *
 * The saveframesink element does FIXME stuff.
 *
 * <refsect2>
 * <title>Example launch line</title>
 * |[
 * gst-launch-1.0 -v fakesrc ! saveframesink ! FIXME ! fakesink
 * ]|
 * FIXME Describe what the pipeline does.
 * </refsect2>
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/base/gstbasesink.h>
#include "gstsaveframesink.h"

GST_DEBUG_CATEGORY_STATIC (gst_saveframesink_debug_category);
#define GST_CAT_DEFAULT gst_saveframesink_debug_category

/* prototypes */


static void gst_saveframesink_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec);
static void gst_saveframesink_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec);
static void gst_saveframesink_dispose (GObject * object);
static void gst_saveframesink_finalize (GObject * object);

static GstCaps *gst_saveframesink_get_caps (GstBaseSink * sink, GstCaps * filter);
static gboolean gst_saveframesink_set_caps (GstBaseSink * sink, GstCaps * caps);
static GstCaps *gst_saveframesink_fixate (GstBaseSink * sink, GstCaps * caps);
static gboolean gst_saveframesink_activate_pull (GstBaseSink * sink, gboolean active);
static void gst_saveframesink_get_times (GstBaseSink * sink, GstBuffer * buffer,
    GstClockTime * start, GstClockTime * end);
static gboolean gst_saveframesink_propose_allocation (GstBaseSink * sink,
    GstQuery * query);
static gboolean gst_saveframesink_start (GstBaseSink * sink);
static gboolean gst_saveframesink_stop (GstBaseSink * sink);
static gboolean gst_saveframesink_unlock (GstBaseSink * sink);
static gboolean gst_saveframesink_unlock_stop (GstBaseSink * sink);
static gboolean gst_saveframesink_query (GstBaseSink * sink, GstQuery * query);
static gboolean gst_saveframesink_event (GstBaseSink * sink, GstEvent * event);
static GstFlowReturn gst_saveframesink_wait_event (GstBaseSink * sink,
    GstEvent * event);
static GstFlowReturn gst_saveframesink_prepare (GstBaseSink * sink,
    GstBuffer * buffer);
static GstFlowReturn gst_saveframesink_prepare_list (GstBaseSink * sink,
    GstBufferList * buffer_list);
static GstFlowReturn gst_saveframesink_preroll (GstBaseSink * sink,
    GstBuffer * buffer);
static GstFlowReturn gst_saveframesink_render (GstBaseSink * sink,
    GstBuffer * buffer);
static GstFlowReturn gst_saveframesink_render_list (GstBaseSink * sink,
    GstBufferList * buffer_list);

enum
{
  PROP_0
};

/* pad templates */

static GstStaticPadTemplate gst_saveframesink_sink_template =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("video/x-raw,format=I420")
    );


/* class initialization */

G_DEFINE_TYPE_WITH_CODE (GstSaveframesink, gst_saveframesink, GST_TYPE_BASE_SINK,
  GST_DEBUG_CATEGORY_INIT (gst_saveframesink_debug_category, "saveframesink", 0,
  "debug category for saveframesink element"));

static void
gst_saveframesink_class_init (GstSaveframesinkClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstBaseSinkClass *base_sink_class = GST_BASE_SINK_CLASS (klass);

  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. */
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS(klass),
      &gst_saveframesink_sink_template);

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS(klass),
      "get iframe and save", "Frame/Samle", "description dayo",
      "kambayashia <kambayashia@gmail.com>");

  gobject_class->set_property = gst_saveframesink_set_property;
  gobject_class->get_property = gst_saveframesink_get_property;
  gobject_class->dispose = gst_saveframesink_dispose;
  gobject_class->finalize = gst_saveframesink_finalize;
  base_sink_class->get_caps = GST_DEBUG_FUNCPTR (gst_saveframesink_get_caps);
  base_sink_class->set_caps = GST_DEBUG_FUNCPTR (gst_saveframesink_set_caps);
  base_sink_class->fixate = GST_DEBUG_FUNCPTR (gst_saveframesink_fixate);
  base_sink_class->activate_pull = GST_DEBUG_FUNCPTR (gst_saveframesink_activate_pull);
  base_sink_class->get_times = GST_DEBUG_FUNCPTR (gst_saveframesink_get_times);
  base_sink_class->propose_allocation = GST_DEBUG_FUNCPTR (gst_saveframesink_propose_allocation);
  base_sink_class->start = GST_DEBUG_FUNCPTR (gst_saveframesink_start);
  base_sink_class->stop = GST_DEBUG_FUNCPTR (gst_saveframesink_stop);
  base_sink_class->unlock = GST_DEBUG_FUNCPTR (gst_saveframesink_unlock);
  base_sink_class->unlock_stop = GST_DEBUG_FUNCPTR (gst_saveframesink_unlock_stop);
  base_sink_class->query = GST_DEBUG_FUNCPTR (gst_saveframesink_query);
  base_sink_class->event = GST_DEBUG_FUNCPTR (gst_saveframesink_event);
  base_sink_class->wait_event = GST_DEBUG_FUNCPTR (gst_saveframesink_wait_event);
  base_sink_class->prepare = GST_DEBUG_FUNCPTR (gst_saveframesink_prepare);
  base_sink_class->prepare_list = GST_DEBUG_FUNCPTR (gst_saveframesink_prepare_list);
  base_sink_class->preroll = GST_DEBUG_FUNCPTR (gst_saveframesink_preroll);
  base_sink_class->render = GST_DEBUG_FUNCPTR (gst_saveframesink_render);
  base_sink_class->render_list = GST_DEBUG_FUNCPTR (gst_saveframesink_render_list);

}

static void
gst_saveframesink_init (GstSaveframesink *saveframesink)
{
}

void
gst_saveframesink_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (object);

  GST_DEBUG_OBJECT (saveframesink, "set_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_saveframesink_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (object);

  GST_DEBUG_OBJECT (saveframesink, "get_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_saveframesink_dispose (GObject * object)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (object);

  GST_DEBUG_OBJECT (saveframesink, "dispose");

  /* clean up as possible.  may be called multiple times */

  G_OBJECT_CLASS (gst_saveframesink_parent_class)->dispose (object);
}

void
gst_saveframesink_finalize (GObject * object)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (object);

  GST_DEBUG_OBJECT (saveframesink, "finalize");

  /* clean up object here */

  G_OBJECT_CLASS (gst_saveframesink_parent_class)->finalize (object);
}

static GstCaps *
gst_saveframesink_get_caps (GstBaseSink * sink, GstCaps * filter)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "get_caps");

  return NULL;
}

/* notify subclass of new caps */
static gboolean
gst_saveframesink_set_caps (GstBaseSink * sink, GstCaps * caps)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "set_caps");

  return TRUE;
}

/* fixate sink caps during pull-mode negotiation */
static GstCaps *
gst_saveframesink_fixate (GstBaseSink * sink, GstCaps * caps)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "fixate");

  return NULL;
}

/* start or stop a pulling thread */
static gboolean
gst_saveframesink_activate_pull (GstBaseSink * sink, gboolean active)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "activate_pull");

  return TRUE;
}

/* get the start and end times for syncing on this buffer */
static void
gst_saveframesink_get_times (GstBaseSink * sink, GstBuffer * buffer,
    GstClockTime * start, GstClockTime * end)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "get_times");

}

/* propose allocation parameters for upstream */
static gboolean
gst_saveframesink_propose_allocation (GstBaseSink * sink, GstQuery * query)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "propose_allocation");

  return TRUE;
}

/* start and stop processing, ideal for opening/closing the resource */
static gboolean
gst_saveframesink_start (GstBaseSink * sink)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "start");

  return TRUE;
}

static gboolean
gst_saveframesink_stop (GstBaseSink * sink)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "stop");

  return TRUE;
}

/* unlock any pending access to the resource. subclasses should unlock
 * any function ASAP. */
static gboolean
gst_saveframesink_unlock (GstBaseSink * sink)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "unlock");

  return TRUE;
}

/* Clear a previously indicated unlock request not that unlocking is
 * complete. Sub-classes should clear any command queue or indicator they
 * set during unlock */
static gboolean
gst_saveframesink_unlock_stop (GstBaseSink * sink)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "unlock_stop");

  return TRUE;
}

/* notify subclass of query */
static gboolean
gst_saveframesink_query (GstBaseSink * sink, GstQuery * query)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "query");

  return TRUE;
}

/* notify subclass of event */
static gboolean
gst_saveframesink_event (GstBaseSink * sink, GstEvent * event)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "event");

  return TRUE;
}

/* wait for eos or gap, subclasses should chain up to parent first */
static GstFlowReturn
gst_saveframesink_wait_event (GstBaseSink * sink, GstEvent * event)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "wait_event");

  return GST_FLOW_OK;
}

/* notify subclass of buffer or list before doing sync */
static GstFlowReturn
gst_saveframesink_prepare (GstBaseSink * sink, GstBuffer * buffer)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "prepare");

  return GST_FLOW_OK;
}

static GstFlowReturn
gst_saveframesink_prepare_list (GstBaseSink * sink, GstBufferList * buffer_list)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "prepare_list");

  return GST_FLOW_OK;
}

/* notify subclass of preroll buffer or real buffer */
static GstFlowReturn
gst_saveframesink_preroll (GstBaseSink * sink, GstBuffer * buffer)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "preroll");

  return GST_FLOW_OK;
}

static GstFlowReturn
gst_saveframesink_render (GstBaseSink * sink, GstBuffer * buffer)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "render");

  return GST_FLOW_OK;
}

/* Render a BufferList */
static GstFlowReturn
gst_saveframesink_render_list (GstBaseSink * sink, GstBufferList * buffer_list)
{
  GstSaveframesink *saveframesink = GST_SAVEFRAMESINK (sink);

  GST_DEBUG_OBJECT (saveframesink, "render_list");

  return GST_FLOW_OK;
}

static gboolean
plugin_init (GstPlugin * plugin)
{

  /* FIXME Remember to set the rank if it's an element that is meant
     to be autoplugged by decodebin. */
  return gst_element_register (plugin, "saveframesink", GST_RANK_NONE,
      GST_TYPE_SAVEFRAMESINK);
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
    saveframesink,
    "FIXME plugin description",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)

