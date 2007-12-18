/* aosd -- OSD with transparency, cairo, and pango.
 *
 * Copyright (C) 2007 Eugene Paskevich <eugene@raptor.kiev.ua>
 */

#ifndef __AOSD_TEXT_H__
#define __AOSD_TEXT_H__

#include "pango/pangocairo.h"

// Tiny Pango API augmentation
// Way more convenient for aosd.
PangoLayout* pango_layout_new_aosd(void);
void pango_layout_unref_aosd(PangoLayout* lay);

void pango_layout_get_size_aosd(PangoLayout* lay,
    unsigned* width, unsigned* height, int* lbearing);

void pango_layout_set_attr_aosd(PangoLayout* lay, PangoAttribute* attr);
void pango_layout_set_font_aosd(PangoLayout* lay, char* font_desc);

typedef struct
{
  PangoLayout* lay;

  int lbearing;

  struct
  {
    char* color;
    guint8 opacity;
  } back;

  struct
  {
    char* color;
    guint8 opacity;
    gint8 x_offset;
    gint8 y_offset;
  } shadow;

  struct
  {
    char* color;
    guint8 opacity;
  } fore;
} TextRenderData;

void aosd_text_renderer(cairo_t* cr, TextRenderData* data);

#endif /* __AOSD_TEXT_H__ */

/* vim: set ts=2 sw=2 et : */
