void xoakytu(char str[100],int vitri)
{
	int n=strlen(str);
	for(int i=vitri;i<n;i++)
	{
		str[i]=str[i+1];
	}

}
void xoakhoangtrangcuoichuoi(char str[100])
{
	int k=strlen(str)-1;
	while (str[k]==32)
	{
		xoakytu(str,k);
		k=strlen(str)-1;
	}
}

typedef struct{
	char* english;
	char* vietnam;
}data;
data listDic[3500];

void docfile(){
		// doc file
	char word1[100];
	char mean1[1500];
	FILE *f = fopen("library/data/data.txt","r");
	btinit();
	// mean *s;
	// int rsize,k=0,i;
	dic = btcrt("library/data/mytree",0,0);
	btpos(dic,1);
	while(fscanf(f,"%[^\t]\t%[^\n]\n",word1,mean1)>0){
		xoakhoangtrangcuoichuoi(word1);
		btins(dic,word1,mean1,strlen(mean1)*sizeof(char));
		// printf("%s\t%s\n",word1,mean1 );
		// k++;
	}
	fclose(f);	
}

void ghifile(){
	FILE *f=fopen("library/data/data2.txt","w");;
    char word[150];
    char mean[1500];
    int i,rsize;
    long j=0;
   //word=(char*)malloc(sizeof(char)*30);
   i=bfndky(dic,"1",&rsize);
   if(i==0){
    //printf("1\n");
    j++;
   } 
   //word=(char*)malloc(sizeof(char)*30);
   //mean=(char*)malloc(sizeof(char)*SIZE_MEAN);
   j=0;
   while(bnxtky(dic,word,&i)==0)
    {
        btsel(dic,word,mean,1500,&rsize);
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
	char s1[100],s2[1500];
	GtkEntryCompletion *completion;
	GtkListStore *store;
	GtkTreeIter iter;
	completion = gtk_entry_completion_new();
	store = gtk_list_store_new(1, G_TYPE_STRING);

	gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(store));
	g_object_unref(store);
	gtk_entry_completion_set_text_column(completion, 0);

	int size;
	gtk_list_store_clear(GTK_LIST_STORE(store));
	btpos(dic,1);
	while(btseln(dic,s1,s2,256,&size)==0){
		gtk_list_store_append(store,&iter);
		gtk_list_store_set(store,&iter,0,s1,-1);
	}
	return completion;
}