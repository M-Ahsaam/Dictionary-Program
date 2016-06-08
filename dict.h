#ifndef DICT_H_INCLUDED
#define DICT_H_INCLUDED

#include <stdio.h>
#include<iostream>
#include <string.h>
#include <stdlib.h>
#include<ctime>
#include<iomanip>
#include<time.h>
#define LEFT  1
#define RIGHT 2
using namespace std;
struct node
{
    char word[20],meaning[100];
    node *left,*right;
};

node *maketree(char[],char[]);      /*** Declaring  function **/

node* treefromfile();
void filefromtree(node*);
void addword(node*,char[],char[]);
void seperateword(char[],char[],char[]);
void displayall(node*);
node* bsearch(node*,char[]);
void showmenu();
FILE *file_ptr;

void prog()                   /**function for checking file empty or not    **/
{

    system("CLS");
    char word[20],meaning[100];
    int menuchoice;
    node *temp;
    temp=treefromfile();
    if(temp==NULL)
    {
        printf("File does not exist or dictionary is empty...");
        system("pause");
    }
    while(1)
    {
        system("CLS");
        showmenu();
        scanf("%d",&menuchoice);
        switch(menuchoice)
        {
            case 1:
                cout<<"Enter word : ";
                fflush(stdin);
                gets(word);
                gets(word);
                cout<<"Enter meaning : " ;

                fflush(stdin);
                gets(meaning);
                if(temp==NULL)
                    temp=maketree(word,meaning);
                else
                    addword(temp,word,meaning);
                break;
            case 2:if(temp==NULL)
                cout<<"The dictionary is empty...";
            else
            {
                cout<<"Find meaning of : ";
                gets(word);
                node *t;
                t=bsearch(temp,word);
                if(t==NULL)
                    cout<<"Word not found...";
                else
                {
                    cout<<"%s : "<<t->word;
                    puts(t->meaning);
                }
            }
                system("pause");
                break;
            case 3:if(temp==NULL)
                cout<<"Dictionary is empty...";
            else
                displayall(temp);
                system("pause");

                exit(0);
                break;
            case 4:
                break;
            default:cout<<"Enter Again";
                //delay(1000);
                prog();
                break;
        }
    }
}
void showmenu()
{
    cout<<" DICTIONARY "<<endl;
    cout<<"[1].	Add a word."<<endl;
    cout<<"[2].	Find meaning."<<endl;
    cout<<"[3].	Display all."<<endl;
    cout<<"[4]. Save and Close.\n\n\tEnter Choice: ";
}
node* treefromfile()        /*** function of tree  ***/
{
    node *ptree=NULL;
    char word[20],meaning[100],str[120],*i;
    int flags=0;
    file_ptr=fopen("C:\dict.anu","r");
    if(file_ptr==NULL)
        ptree=NULL;
    else
    {

        while(!feof(file_ptr))
        {
            i=fgets(str,120,file_ptr);
            if(i==NULL)
                break;
            seperateword(str,word,meaning);
            if(flags==0)
            {
                ptree=maketree(word,meaning);
                flags=1;
            }
            else
                addword(ptree,word,meaning);
        }

        fclose(file_ptr);
    }
    return ptree;
}
node* maketree(char w[],char m[])      /***function of link list **/
{

    node *p;
    p=new node;
    strcpy(p->word,w);
    strcpy(p->meaning,m);
    p->left=NULL;
    p->right=NULL;
    return p;
}
void seperateword(char str[],char w[],char m[])
{
    int i,j;
    for(i=0;str[i]!=' ';i++)
        w[i]=str[i];
    w[i++]=NULL;
    for(j=0;str[i]!='\0';i++,j++)
    {
        m[j]=str[i];
    }
    m[j]=NULL;
}
void addword(node *tree,char word[],char meaning[])     /**adding words in files**/
{
    node *p,*q;
    p=q=tree;
    while(strcmp(word,p->word)!=0 && p!=NULL)
    {
        q=p;
        if(strcmp(word,p->word)<0)
            p=p->left;
        else
            p=p->right;
    }
    if(strcmp(word,q->word)==0)
    {
        cout<<"This word already exists...";

    }
    else if(strcmp(word,q->word)<0)
        q->left=maketree(word,meaning);
    else
        q->right=maketree(word,meaning);
}
node* bsearch(node *tree,char word[])
{
    node *q;
    q=tree;
    while(q!=NULL)
    {

        if(strcmp(word,q->word)<0)
            q=q->left;
        else if(strcmp(word,q->word)>0)
            q=q->right;
        if(strcmp(word,q->word)==0)
            break;
    }
    return q;
}
void filefromtree(node *tree)
{
    void travandwrite(node*);
    file_ptr=fopen("C:\dict.anu","w");
    if(file_ptr==NULL)
    {
        printf("Cannot open file for writing data...");
    }
    else
    {
        if(tree!=NULL)
        {
            travandwrite(tree);
        }
        fclose(file_ptr);  //Close the file anyway.
    }
}
void travandwrite(node *tree)
{
    if(tree!=NULL)
    {
        fprintf(file_ptr,"%s %s",tree->word,tree->meaning);
        travandwrite(tree->left);
        travandwrite(tree->right);
    }
}
void displayall(node *tree)
{
    if(tree!=NULL)
    {
        displayall(tree->left);
        printf("%s : %s",tree->word,tree->meaning);
        displayall(tree->right);
    }
}



#endif // DICT_H_INCLUDED
