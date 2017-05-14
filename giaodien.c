 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include "library/inc/bt.h"
#include <time.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>


BTA *dic;

GtkWidget *tu;
GtkWidget *add_tu;
GtkWidget *nghia;
GtkWidget *add_nghia;
GtkListStore *store;
GtkTreeIter iter;
GtkWidget * completion;

#define M 50
#define BACKSP_LINE "\b \b"
static struct termios orig_termios;
static int ttyfd = STDIN_FILENO;
typedef char str[100];
typedef struct{
	str list[10];
	int count;
}mean;
#include "func.h"
#include "search.h"
#include "delete.h"
#include "add.h"

int main(int argc, char** argv){

	// doc file 
	docfile();
	// giao dien chinh(MENU)
	GtkBuilder *builder;
	GtkWidget *window,*btn_search,*btn_add,*btn_delete,*btn_exit,*btn_ghifile;
	GtkWidget *entry;
	gtk_init(&argc,&argv);
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "library/data/giaodien.glade", NULL);
	window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	gtk_window_set_title (GTK_WINDOW (window), "Menu");
	gtk_window_set_icon_from_file (GTK_WINDOW(window),"library/data/icon/dictionary.png",NULL);

	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
	btn_search = GTK_WIDGET(gtk_builder_get_object(builder, "btn_search"));
	btn_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add"));
	btn_exit = GTK_WIDGET(gtk_builder_get_object(builder, "btn_exit"));
	btn_delete = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete"));
	entry = GTK_WIDGET(gtk_builder_get_object(builder, "entry"));
	btn_ghifile = GTK_WIDGET(gtk_builder_get_object(builder, "btn_ghifile"));

	// Bat su kien  button
	g_signal_connect_swapped(G_OBJECT(btn_exit), "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect_swapped(G_OBJECT(btn_search), "clicked", G_CALLBACK(window_search), NULL);
	g_signal_connect_swapped(G_OBJECT(btn_add), "clicked", G_CALLBACK(window_add), NULL);
	g_signal_connect_swapped(G_OBJECT(btn_delete), "clicked", G_CALLBACK(window_delete), NULL);
	g_signal_connect(G_OBJECT(btn_ghifile), "clicked", G_CALLBACK(ghifile), NULL);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}

// gcc `pkg-config --cflags gtk+-3.0` -o giaodien giaodien.c `pkg-config --libs gtk+-3.0` libbt.a -w
