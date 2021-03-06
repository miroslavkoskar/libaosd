/* aosd -- OSD with fake transparency, cairo, and pango.
 *
 * Copyright (C) 2006 Evan Martin <martine@danga.com>
 */

#include <aosd.h>

typedef struct {
  cairo_surface_t* foot;
  float alpha;
} RenderData;

static void
round_rect(cairo_t* cr, int x, int y, int w, int h, int r)
{
  cairo_new_path(cr);
  cairo_move_to(cr, x+r, y);
  cairo_line_to(cr, x+w-r, y); /* top edge */
  cairo_curve_to(cr, x+w, y, x+w, y, x+w, y+r);
  cairo_line_to(cr, x+w, y+h-r); /* right edge */
  cairo_curve_to(cr, x+w, y+h, x+w, y+h, x+w-r, y+h);
  cairo_line_to(cr, x+r, y+h); /* bottom edge */
  cairo_curve_to(cr, x, y+h, x, y+h, x, y+h-r);
  cairo_line_to(cr, x, y+r); /* left edge */
  cairo_curve_to(cr, x, y, x, y, x+r, y);
  cairo_close_path(cr);
}

#define RADIUS 40

static void
render(cairo_t* cr, void* data)
{
  RenderData* rdata = data;

  cairo_set_source_rgba(cr, rdata->alpha, 0, 0, 0.7);
  round_rect(cr, 0, 0, 180, 230, RADIUS);
  cairo_fill(cr);

  cairo_set_source_rgba(cr, 1, 1, 1, 1.0);
  round_rect(cr, 10, 10, 160, 210, RADIUS);
  cairo_stroke(cr);

  cairo_set_source_surface(cr, rdata->foot, 20, 20);
  cairo_paint(cr);
}

int main(int argc, char* argv[])
{
  Aosd* aosd;
  RenderData data = {0};

  const char* image = "/usr/share/pixmaps/gnome-background-image.png";
  data.foot = cairo_image_surface_create_from_png(image);
  data.alpha = 0.5;

  aosd = aosd_new();
  aosd_set_transparency(aosd, TRANSPARENCY_COMPOSITE);
  aosd_set_hide_upon_mouse_event(aosd, True);
  aosd_set_geometry(aosd, 50, 50, 180, 230);
  aosd_set_renderer(aosd, render, &data);

  aosd_show(aosd);

  aosd_loop_once(aosd);

  float dalpha = 0.05;

  do
  {
    data.alpha += dalpha;
    if (data.alpha >= 1.0)
    {
      data.alpha = 1.0;
      dalpha = -dalpha;
    }
    else if (data.alpha <= 0.0)
    {
      data.alpha = 0.0;
      dalpha = -dalpha;
    }

    aosd_render(aosd);
    aosd_loop_for(aosd, 100);
  } while (aosd_get_is_shown(aosd));

  cairo_surface_destroy(data.foot);
  aosd_destroy(aosd);

  return 0;
}

/* vim: set ts=2 sw=2 et : */
