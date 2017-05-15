void xoakytu(char str[100],int vitri){
	int n=strlen(str);
	for(int i=vitri;i<n;i++){
		str[i]=str[i+1];
	}

}
void xoakhoangtrangcuoichuoi(char str[100]){
	int k=strlen(str)-1;
	while (str[k]==32){
		xoakytu(str,k);
		k=strlen(str)-1;
	}
}

void docfile(){
	// doc file
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];
	FILE *f = fopen("library/data/Portuguese.txt","r");
	btinit();
	dic = btcrt("library/data/mytree",0,0);
	btpos(dic,1);
	while(fscanf(f,"%[^\t]\t%[^\n]\n",word,mean)>0){
		xoakhoangtrangcuoichuoi(word);
		btins(dic,word,mean,strlen(MAXLEN_MEAN)*sizeof(char));
	}
	fclose(f);	
}

void ghifile(){
	FILE *f=fopen("library/data/data3.txt","w");;
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];
	int i,rsize;
	long j=0;
	i=bfndky(dic,"1",&rsize);
	if(i==0){
		j++;
	} 
	j=0;
	while(bnxtky(dic,word,&i)==0){
		btsel(dic,word,mean,MAXLEN_MEAN*sizeof(char),&rsize);
		if(j==0){
			j=1;
		}
		else{
			fprintf(f,"%s\t%s\n",word,mean);
		}
		j++;
	}
	fclose(f);
}
static GtkEntryCompletion* create_completion_widget(void)
{
	GtkEntryCompletion *completion;
	GtkListStore *store;
	GtkTreeIter iter;
	completion = gtk_entry_completion_new();
	store = gtk_list_store_new(1, G_TYPE_STRING);
	char word[MAXLEN_WORD];
	char mean[MAXLEN_MEAN];

	gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(store));
	g_object_unref(store);
	gtk_entry_completion_set_text_column(completion, 0);

	int size;
	gtk_list_store_clear(GTK_LIST_STORE(store));
	btpos(dic,1);
	while(btseln(dic,word,mean,MAXLEN_MEAN*sizeof(char),&size)==0){
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,word,-1);
	}
	return completion;
}