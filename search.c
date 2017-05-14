void search_message(GtkWidget *widget,gpointer data){
	GtkBuilder *builder;
	GtkWidget *window_mess;
	GtkWidget *label;
	GtkWidget *label_nghia;

	char *s;	
	int rsize;
	int i;
	s=(mean*)malloc(M*sizeof(mean));
	gchar *text;

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "library/data/giaodien.glade", NULL);

	window_mess = GTK_WIDGET(gtk_builder_get_object(builder, "window_mess"));
	gtk_window_set_title (GTK_WINDOW (window_mess), "KQ Search");
	label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
	label_nghia = GTK_WIDGET(gtk_builder_get_object(builder, "label_nghia"));

	gtk_label_set_text(GTK_LABEL(label), gtk_entry_get_text(GTK_ENTRY(widget)));

	text = gtk_entry_get_text(GTK_ENTRY(widget));
	xoakhoangtrangcuoichuoi(text);

	if(btsel(dic,text,(char *)s,256,&rsize)==0){
		// printf("%s\n",s->list[i] );
		gtk_label_set_text(GTK_LABEL(label),text);
		gtk_label_set_text(GTK_LABEL(label_nghia),s);
	}
	else{
		gtk_label_set_text(GTK_LABEL(label),text);
		gtk_label_set_text(GTK_LABEL(label_nghia),"Kết quả tìm kiếm:________________________________\n\n        -Không tồn tại từ này");

	}

	gtk_widget_show_all(window_mess);

}
void window_search(GtkWidget *widget) {
	GtkBuilder *builder;
	GtkWidget *window_search;
	GtkWidget *search_btn_search;
	GtkWidget *input_search;


	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "library/data/giaodien.glade", NULL);
	window_search = GTK_WIDGET(gtk_builder_get_object(builder, "window_search"));
	gtk_window_set_title (GTK_WINDOW (window_search), "Search");
	search_btn_search = GTK_WIDGET(gtk_builder_get_object(builder, "search_btn_search"));
	input_search = GTK_WIDGET(gtk_builder_get_object(builder, "input_search"));

	completion = create_completion_widget();
	gtk_entry_set_completion(GTK_ENTRY(input_search),completion);
	g_object_unref(completion);

	g_signal_connect_swapped(G_OBJECT(search_btn_search), "clicked", G_CALLBACK(search_message),input_search);
	gtk_widget_show_all(window_search);
}