void delete_message(GtkWidget *widget,gpointer data){
	GtkBuilder *builder;
	GtkWidget *window_delete_mess;
	GtkWidget *label_tuxoa;
	GtkWidget *label_nghiaxoa;
	GtkWidget *label_thongbao;
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];
	int rsize;

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "library/data/giaodien.glade", NULL);
	window_delete_mess = GTK_WIDGET(gtk_builder_get_object(builder, "window_delete_mess"));
	gtk_window_set_title (GTK_WINDOW (window_delete_mess), "KQ Delete");

	label_tuxoa = GTK_WIDGET(gtk_builder_get_object(builder, "label_tuxoa"));
	label_nghiaxoa = GTK_WIDGET(gtk_builder_get_object(builder, "label_nghiaxoa"));
	label_thongbao = GTK_WIDGET(gtk_builder_get_object(builder, "label_thongbao"));
	gtk_label_set_text(GTK_LABEL(label_tuxoa), gtk_entry_get_text(GTK_ENTRY(widget)));
	strcpy(word,(char *)gtk_entry_get_text(GTK_ENTRY(widget)));
	xoakhoangtrangcuoichuoi(word);

	// tim kiem de lay du lieu
	if(btsel(dic,word,mean,MAXLEN_MEAN*sizeof(char),&rsize)==0){
		if( btdel(dic,word)){
			gtk_label_set_text(GTK_LABEL(label_tuxoa),word);
			gtk_label_set_text(GTK_LABEL(label_thongbao),"_____________________________\n\n     Kết quả xoá:\n\n      Không tồn tại từ này\n");
		}
		else{
			gtk_label_set_text(GTK_LABEL(label_tuxoa),word);
			gtk_label_set_text(GTK_LABEL(label_nghiaxoa),mean);
			gtk_label_set_text(GTK_LABEL(label_thongbao),"_____________________________\n\n      Kết quả xoá:\n\n     Đã xoá thành công\n");
		}
	}
	else{
		gtk_label_set_text(GTK_LABEL(label_tuxoa),word);
		gtk_label_set_text(GTK_LABEL(label_nghiaxoa),"Kết quả tìm kiếm:________________________________\n\n        -Không tồn tại từ này");
	}
	gtk_widget_show_all(window_delete_mess);
}

void window_delete(GtkWidget *widget) {
	GtkBuilder *builder;
	GtkWidget *window_delete;
	GtkWidget *search,*delete;
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "library/data/giaodien.glade", NULL);
	window_delete = GTK_WIDGET(gtk_builder_get_object(builder, "window_delete"));
	gtk_window_set_title (GTK_WINDOW (window_delete), "Delete");
	
	search = GTK_WIDGET(gtk_builder_get_object(builder, "search_delete"));
	delete = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete2"));

	completion = create_completion_widget();
	gtk_entry_set_completion(GTK_ENTRY(search),completion);
	g_object_unref(completion);

	g_signal_connect_swapped(G_OBJECT(delete), "clicked", G_CALLBACK(delete_message),search);
	gtk_widget_show_all(window_delete);
}