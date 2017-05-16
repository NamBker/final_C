gboolean show_info(GtkWidget *widget,gpointer database){
  GdkPixbuf *pixbuf=gdk_pixbuf_new_from_file("images/thongtin.ico",NULL);
  GtkWidget *dialog=gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog),"Từ điển tên-email");
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog),"Version 0.0");
  gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),
    "(c) Việt Nhật \nNguyễn Văn Nam 20132696\nTrần Thị Như Hoa 20131520\nLê Đăng Thành 20133515\nPhan Văn Huy 20131786\n");
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"Giao diện chương trình được tham khảo code từ trang zetcode.com\n");
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog),pixbuf);
  g_object_unref(pixbuf),pixbuf=NULL;
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

gboolean show_guide(GtkWidget *widget,gpointer database){
  GtkWidget *dialog,*window;
  window=mainwindow;
  dialog=gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,"Chương trình gồm 8 chức năng \n1. Tra từ cần tìm \n2. Thêm từ vào từ điển \n3. Chỉnh sửa nghĩa của từ \n4. Xoá từ khỏi từ điển \n5. Lưu lại những thay đổi \n 6. Giúp đỡ sử dụng \n7. Thông tin phát hành \n8. Thoát chương trình \n");
  gtk_window_set_title(GTK_WINDOW(dialog),"Hướng dẫn sử dụng");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

