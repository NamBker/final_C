gboolean search_message(GtkWidget *widget,gpointer data){
	GtkBuilder *builder;
	GtkWidget *window_mess;
	GtkWidget *label;
	GtkWidget *label_nghia;
	int rsize,rsize2;
	int i;
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];
	char thongBao[MAXLEN_MEAN];
	char goiy[MAXLEN_WORD];
	char temp[MAXLEN_WORD];
	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "library/data/giaodien.glade", NULL);

	window_mess = GTK_WIDGET(gtk_builder_get_object(builder, "window_mess"));
	gtk_window_set_title (GTK_WINDOW (window_mess), "KQ Search");
	label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));
	label_nghia = GTK_WIDGET(gtk_builder_get_object(builder, "label_nghia"));

	gtk_label_set_text(GTK_LABEL(label), gtk_entry_get_text(GTK_ENTRY(widget)));

	strcpy(word,(char *)gtk_entry_get_text(GTK_ENTRY(widget)));
	xoakhoangtrangcuoichuoi(word);

	if(strlen(word) == 0){
		strcpy(thongBao,"Bạn chưa nhập từ vào ô tìm kiếm!");
	}
	else{
		xoakhoangtrangcuoichuoi(word);
		if(btsel(dic,word,mean,MAXLEN_MEAN*sizeof(char),&rsize)!=0){
			strcpy(thongBao,"Xin lỗi! Không tìm thấy\n");

			soundEx(goiy,word,MAXLEN_WORD,1);
			if(btsel(sou,goiy,temp, MAXLEN_WORD*sizeof(char), &rsize2)==0) {
				strcat(thongBao, "Có phải bạn muốn tìm:\n");
				strcat(thongBao,temp );
			}
		} 
		else{
			strcpy(thongBao,mean);
		} 
	}

	// -1 la cho no vao cuoi
	gtk_text_buffer_get_iter_at_offset(buffer, &iter2,-1);
	gtk_text_buffer_insert(buffer, &iter2,thongBao, -1);
	strcpy(thongBao,"\0") ;
	return TRUE;
}

gboolean check(GtkWidget *widget,gpointer data){

	int rsize,rsize2;
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];
	char thongBao[MAXLEN_MEAN];
	char goiy[MAXLEN_WORD];
	char temp[MAXLEN_WORD];
	strcpy(word,(char *)gtk_entry_get_text(GTK_ENTRY(widget)));
	xoakhoangtrangcuoichuoi(word);
	if(strlen(word) == 0){
		strcpy(thongBao,"Bạn chưa nhập từ vào ô tìm kiếm!\n");
	}
	else{
		xoakhoangtrangcuoichuoi(word);
		if(btsel(dic,word,mean,MAXLEN_MEAN*sizeof(char),&rsize)!=0){
			strcpy(thongBao,"\nXin lỗi! Không tìm thấy\n");
			soundEx(goiy,word,MAXLEN_WORD,1);
			if(btsel(sou,goiy,temp, MAXLEN_WORD*sizeof(char), &rsize2)==0) {
				strcat(thongBao, "Có phải bạn muốn tìm:");
				strcat(thongBao,temp );
			}
		} 
		else{
			strcpy(thongBao,mean);
			strcat(thongBao,"\n");
		} 
	}
	gtk_text_buffer_set_text(buffer,"", -1);
	gtk_text_buffer_get_iter_at_offset(buffer, &iter2,-1);
	gtk_text_buffer_insert_with_tags_by_name (buffer, &iter2, thongBao, -1, "italic","lmarg",  NULL);
	return TRUE;
}
void window_Search(GtkWidget *widget) {
	GtkBuilder *builder;
	GtkWidget *search_btn_search;
	GtkWidget *separtor;
	GtkWidget *label_kq;
	GtkWidget *input_search;

	GtkWidget *scrolledwindow;

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "library/data/giaodien.glade", NULL);
	window_search = GTK_WIDGET(gtk_builder_get_object(builder, "window_search"));
	gtk_window_set_title (GTK_WINDOW (window_search), "Search");
	search_btn_search = GTK_WIDGET(gtk_builder_get_object(builder, "search_btn_search"));
	input_search = GTK_WIDGET(gtk_builder_get_object(builder, "input_search"));
	separtor = GTK_WIDGET(gtk_builder_get_object(builder, "separtor"));



	// text views
	show_search = GTK_WIDGET(gtk_builder_get_object(builder, "show_search"));
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(show_search),GTK_WRAP_WORD);

	label_kq = GTK_WIDGET(gtk_builder_get_object(builder, "label_kq"));
	buffer=gtk_text_view_get_buffer(GTK_TEXT_VIEW(show_search));

	scrolledwindow = GTK_WIDGET(gtk_builder_get_object(builder, "scrolledwindow"));


	gtk_text_buffer_create_tag(buffer, "italic", "style", PANGO_STYLE_ITALIC, NULL);
	gtk_text_buffer_create_tag(buffer, "lmarg", "left_margin", 5, NULL);



	completion = create_completion_widget();
	gtk_entry_set_completion(GTK_ENTRY(input_search),completion);
	g_object_unref(completion);

	g_signal_connect_swapped(G_OBJECT(search_btn_search), "clicked", G_CALLBACK(check),input_search);
	gtk_widget_show_all(window_search);
}

