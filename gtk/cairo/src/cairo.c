/*
 ============================================================================
 Name        : cairo.c
 Author      : Butyaev A.Y.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <cairo.h>
#include <gtk/gtk.h>

const double M_PI = 3.14f;

static gboolean on_expose_event( GtkWidget* widget, GdkEventExpose* event,
    gpointer data) {
  cairo_t *cr;
  cr = gdk_cairo_create( widget->window );
#if 0
  cairo_set_source_rgb( cr, 0, 0, 0 );
  cairo_select_font_face( cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_NORMAL );
  cairo_set_font_size( cr, 40.0 );
  cairo_move_to( cr, 10.0, 50.0 );
  cairo_show_text( cr, "Disziplin ist Macht." );
#elif 1
  int w, h;
  cairo_surface_t *image;
  cairo_arc( cr, 200.0, 200.0, 200.0, 0, 2 * M_PI );
  cairo_clip (cr);
  cairo_new_path (cr); /* path not consumed by clip()*/
  image = cairo_image_surface_create_from_png ("ledy.png");
  w = cairo_image_surface_get_width (image);
  h = cairo_image_surface_get_height (image);
  cairo_scale( cr, 400.0/w, 400.0/h);
  cairo_set_source_surface (cr, image, 0, 0);
  cairo_paint( cr );
  cairo_surface_destroy( image );
#endif
  cairo_destroy( cr );
  return FALSE;
}

int main( int argc, char *argv[] ) {
  GtkWidget *window;
  gtk_init( &argc, &argv );
  window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
  g_signal_connect(window, "expose-event",
                    G_CALLBACK( on_expose_event ), NULL );
  g_signal_connect(window, "destroy",
                    G_CALLBACK( gtk_main_quit ), NULL );
  gtk_window_set_position( GTK_WINDOW( window ), GTK_WIN_POS_CENTER );
  gtk_window_set_default_size( GTK_WINDOW( window ), 400, 400 );
  gtk_widget_set_app_paintable( window, TRUE );
  gtk_widget_show_all( window );
  gtk_main();
  return 0;
}
