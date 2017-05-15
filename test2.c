/***********************************************************/
/***********************************************************/
// FreeBSD 8.0 
// Xfce 4.6.1
// GTK 2.16.6 
// Glade 3.6.7
//
// gcc `pkg-config --cflags --libs gtk+-2.0` -export-dynamic -o hello hello.c
/***********************************************************/

#include "gtk/gtk.h"

/***********************************************************/

#define GLADE
// comment out this option to do it without Glade xml file

/***********************************************************/

// event handlers must be defined regardless 
// if their gadgets are generated in code or Glade

G_MODULE_EXPORT void on_window1_destroy( GtkWidget *widget, gpointer data )
{
gtk_main_quit ();
}

G_MODULE_EXPORT void on_button1_clicked( GtkWidget *widget, gpointer data ) 
{
g_print ("Hello!\n");
}

/***********************************************************/

int main( int argc, char *argv[] ) 
{
gtk_init (&argc, &argv);

#ifdef GLADE
GtkBuilder *builder = gtk_builder_new();
gtk_builder_add_from_file( builder, "hello.glade", NULL );
// need to open the resource

GtkWindow *window1 = GTK_WINDOW( gtk_builder_get_object( builder, "window1" ) );
// need to get reference to main widow
// but no packing individual gadgets
#else
GtkWidget *window1 = gtk_window_new( GTK_WINDOW_TOPLEVEL );
GtkWidget *box1 = gtk_vbox_new( FALSE, 0 );
GtkWidget *box2 = gtk_hbox_new( FALSE, 0 );
GtkWidget *label1 = gtk_label_new( "Enter Name" );
GtkWidget *entry1 = gtk_entry_new();
GtkWidget *button1 = gtk_button_new_with_label( "Hello" );
// this list counld be quite long ...
gtk_container_add( GTK_CONTAINER (window1), box1 );
gtk_box_pack_start( GTK_BOX(box1), box2, TRUE, TRUE, 10 );
gtk_box_pack_start( GTK_BOX(box2), label1, TRUE, TRUE, 10 );
gtk_box_pack_start( GTK_BOX(box2), entry1, TRUE, TRUE, 10 );
gtk_box_pack_start( GTK_BOX(box1), button1, TRUE, TRUE, 10 );
// this list counld be quite long ...
#endif

#ifdef GLADE 
gtk_builder_connect_signals( builder, NULL );
// connect all handlers via single call
#else
g_signal_connect( G_OBJECT (window1), "destroy", G_CALLBACK (on_window1_destroy), NULL );
g_signal_connect( G_OBJECT (button1), "clicked", G_CALLBACK (on_button1_clicked), NULL );
// this list counld be quite long ...
#endif

#ifdef GLADE
g_object_unref( G_OBJECT( builder ) );
// one line cleanup for builder
#endif

gtk_widget_show_all( window1 );

gtk_main ();

return 0;
}

/***********************************************************/
/***********************************************************/