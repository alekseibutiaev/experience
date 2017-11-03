/*
 ============================================================================
 Name        : jigsaw.c
 Author      : Butyaev A.Y.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <cairo.h>
#include <gtk/gtk.h>

const double M_PI = 3.14f;

static void curve( cairo_t* cairo ) {
  double x=25.6,  y=128.0;
  double x1=102.4, y1=230.4,
         x2=153.6, y2=25.6,
         x3=230.4, y3=128.0;

  cairo_move_to( cairo, x, y);
  cairo_curve_to( cairo, x1, y1, x2, y2, x3, y3);

  cairo_set_line_width( cairo, 10.0 );
  cairo_stroke( cairo );

  cairo_set_source_rgba( cairo, 1, 0.2, 0.2, 0.6 );
  cairo_set_line_width( cairo, 6.0 );
  cairo_move_to( cairo, x, y );
  cairo_line_to( cairo, x1, y1 );
  cairo_move_to( cairo, x2, y2 );
  cairo_line_to( cairo, x3, y3 );
  cairo_stroke( cairo );

}

enum face {
  left, top, right, bottom, facecount
};

struct point {
  double x;
  double y;
};

struct jigsawpath {
  struct point control1;
  struct point control2;
  struct point end;
};

static void jigsaw( cairo_t* cairo ) {
  struct point begin = { 0, 200 };
  struct jigsawpath path[] = {
      { { 50, 177 }, { 107, 231 }, { 135, 207 } },
      { { 157, 186 }, { 84, 161 }, { 106, 95 } },
      { { 127, 51 }, { 218, 51 }, { 250, 107 } },
      { { 277, 131 }, { 241, 187 }, { 276, 209 } },
      { { 304, 223 }, { 371, 176 }, { 400, 207 } },
  };
  int i;
  cairo_move_to( cairo, begin.x, begin.y );
  for( i = 0; i < 5; ++i )
    cairo_curve_to( cairo, path[ i ].control1.x, path[ i ].control1.y,
        path[ i ].control2.x, path[ i ].control2.y,
        path[ i ].end.x, path[ i ].end.y );
  cairo_stroke( cairo );

}

static gboolean on_expose_event( GtkWidget* widget, GdkEventExpose* event,
    gpointer data) {
  cairo_t* cairo;
  cairo = gdk_cairo_create( widget->window );
//  curve( cairo );
  jigsaw( cairo );
  cairo_destroy( cairo );
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
