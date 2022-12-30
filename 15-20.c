Slip 15

Write a C program to implement the shell. It should display the command prompt “myshell$”. Tokenize the command line and execute the given command by creating the child process. Additionally it should interpret the following ‘list’ commands as 
myshell$ list f dirname :- To print names of all the files in current directory.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
char *buff,*t1,*t2,*t3,ch;
int pid;
void list(char t2,char *t3)
{
 DIR *dir;
 struct dirent *entry;
 int cnt=0;
 dir=opendir(t3);
 if (dir==NULL)
 {
 printf("Directory %s not found",t3);
 return;
 }
 switch(t2)
 {
case 'f' : while((entry=readdir(dir))!=NULL)
 {
printf("%s\n",entry->d_name);
 }
 break;
case 'n' : while((entry=readdir(dir))!=NULL)
 cnt++;
 printf("Total No of Entries: %d\n",cnt);
 break;
case 'i' : while((entry=readdir(dir))!=NULL)
 {
printf("\n%s\t %d",entry->d_name,entry->d_ino);
 }
 break;
default : printf("Invalid argument");
 }
 closedir(dir);
}
main()
{
 while(1)
 {
printf("myshell$");
 fflush(stdin);
t1=(char *)malloc(80);
t2=(char *)malloc(80);
t3=(char *)malloc(80);
buff=(char *)malloc(80);
fgets(buff,80,stdin);
sscanf(buff,"%s %s %s",t1,t2,t3);
if(strcmp(t1,"pause")==0)
exit(0);
else if(strcmp(t1,"list")==0)
list(t2[0],t3);
else
{
pid=fork();
if(pid<0)
printf("Child process is not created\n");
else if(pid==0)
{
execlp("/bin",NULL);
if(strcmp(t1,"exit")==0)
exit(0);
system(buff);
}
else
{
wait(NULL);
exit(0);
}
}
 }
}


Write the program to simulate preemptive Shortest Job First (SJF) – scheduling. The arrival time and first CPU-burst of different jobs should be input to the system. Accept no. of Processes, arrival time and burst time. Theoutput should give Gantt chart, turnaround time and waiting time for each process. Also find the average waiting time and turnaround time

#include<stdio.h>
struct input
{
 char pname[10];
 int bt,at,tbt,ft;
}tab[10];
struct gantt
{
 int start,end;
 char pname[10];
}g[50],g1[10];
int n,i,k,time,prev;
void getinput()
{
 printf("\nEnter No of Processes: ");
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
 printf("\nProcess Name: ");
 scanf("%s",tab[i].pname);
 printf("Burst Time: ");
 scanf("%d",&tab[i].bt);
 tab[i].tbt=tab[i].bt;
 printf("Arrival Time:" );
 scanf("%d",&tab[i].at);
 }
}
void printinput()
{
 printf("\nPname\tBT\tAT");
 for(i=0;i<n;i++)
 printf("\n%s\t%d\t%d",tab[i].pname,tab[i].tbt,tab[i].at);
}
void sort()
{
 struct input temp;
 int j;
 for(i=1;i<n;i++)//pass
 for(j=0;j<n-1;j++)//Comp
 if(tab[j].at>tab[j+1].at)
 {
 temp=tab[j];
 tab[j]=tab[j+1];
 tab[j+1]=temp;
 }
}
int arrived(int time)
{
 for(i=0;i<n;i++)
 if(tab[i].at<=time && tab[i].tbt!=0)
 return 1;
 return 0;
}
int getsmallburst(int time)
{
 int min=99,mini;
 for(i=0;i<n;i++)
 {
 if(tab[i].tbt<min && tab[i].at<=time && tab[i].tbt!=0)
 {
 min=tab[i].tbt;
 mini=i;
 }
 }
 return mini;
}
 void processinput()
{
int j,finish=0;
// time=tab[0].at;
 while(finish!=n)
{
if(arrived(time))
{
i=getsmallburst(time);
 time++;
tab[i].tbt--;
 g[k].start=prev;
g[k].end=time;
// printinput();
prev=time;
tab[i].ft=time;
strcpy(g[k++].pname,tab[i].pname);
 if(tab[i].tbt==0)
 {
 finish++;
}
 }
else
 {
 time++;
 g[k].start=prev;
 g[k].end=time;
 prev=time;
 strcpy(g[k++].pname,"idle");
}
}
 // printinput();
}
void printoutput()
{
 int TTAT=0,TWT=0;
 float ATAT,AWT;
 printf("\n******Final Table*****");
 printf("\nPname\tAT\tBT\tFT\tTAT\tWT");
 for(i=0;i<n;i++)
 {
printf("\n%s\t%d\t%d\t%d\t%d\t%d",tab[i].pname,tab[i].at,tab[i].bt,tab[i].ft,tab[i].fttab[i].at,tab[i].ft-tab[i].at-tab[i].bt);
 TTAT=TTAT+(tab[i].ft-tab[i].at);
 TWT=TWT+(tab[i].ft-tab[i].at-tab[i].bt);
 }
 ATAT=(float)TTAT/n;
 AWT=(float)TWT/n;
 printf("\nTotal TAT=%d",TTAT);
 printf("\nTotal WT=%d",TWT);
 printf("\nAverage TAT=%f",ATAT);
 printf("\nAverage WT=%f",AWT);
}
void printganttchart()
{
 int j=0;
 g1[0]=g[0];
 for(i=1;i<k;i++)
 {
 if(strcmp(g1[j].pname,g[i].pname)==0)
 g1[j].end=g[i].end;
 else
{
j++;
 g1[j]=g[i];
 }
 }
 printf("\n******Each unit Gantt chart******");
 for(i=0;i<k;i++)
 printf("\n%d\t%s\t%d",g[i].start,g[i].pname,g[i].end);
 printf("\n******Final Gantt chart******");
 for(i=0;i<=j;i++)
 printf("\n%d\t%s\t%d",g1[i].start,g1[i].pname,g1[i].end);
 }
int main()
{
 getinput();
 printf("\nEntered data is: ");
 printinput();
 sort();
 printf("\nData after Sorting" );
 printinput();
 processinput();
 printoutput();
 printganttchart();
}


Slip 16

Write a programto implement the toy shell. It should display the command prompt “myshell$”. Tokenize the command line and execute the given command by creating the child process. Additionally it should interpret the following commands. 
count c filename :- To print number of characters in the file. 
count w filename :- To print number of words in the file.

#include<stdio.h>
char *buff,*t1,*t2,*t3,ch;
FILE *fp;
int pid;
void count(char *t2,char *t3)
{
int charcount=0,wordcount=0,linecount=0;
fp=fopen(t3,"r");
if(fp==NULL)
printf("\nError in opening the file");
else
{
while((ch=fgetc(fp))!=EOF)
{
if(ch==' ')
wordcount++;
else if(ch=='\n')
{
linecount++;
wordcount++;
}
else
charcount++;
}
}
fclose(fp);
if(strcmp(t2,"c")==0)
printf("\nTotal no of characters: %d",charcount);
else if(strcmp(t2,"w")==0)
printf("\nTotal no of Words: %d",wordcount);
else if(strcmp(t2,"l")==0)
printf("\nTotal no of lines: %d",linecount);
else
printf("Command not found");
}
main()
{
while(1)
{
printf("\nMyshell$");
buff=(char*)malloc(80);
t1=(char*)malloc(80);
t2=(char*)malloc(80);
t3=(char*)malloc(80);
fgets(buff,80,stdin);
sscanf(buff,"%s %s %s",t1,t2,t3);
if(strcmp(t1, "pause")==0)
exit(0);
if(strcmp(t1,"count")==0)
count(t2,t3);
else
{
pid=fork();
if(pid<0)
printf("\nchild Process is not craeted\n");
else if(pid==0)
{
execlp("/bin",NULL);
system(buff);
}
else
{
wait(NULL);
 exit(0);
}
}
}
}


Write the program to simulate Non preemptive priority scheduling. The arrival time and first CPU-burst of different jobs should be input to the system. Accept no. of Processes, arrival time and burst time. The output should give Gantt chart, turnaround time and waiting time for each process. Also find the average waiting time and turnaround time. 

#include<stdio.h>
struct input
{
char pname[10];
int bt,at,tbt,ft,p;
}tab[10];
struct gantt
{
 char pname[10];
 int start,end;
}g[30],g1[30];
int n,i,time,prev,k;
void getinput()
{
printf("\nEnter No of Process: ");
scanf("%d",&n);
for(i=0;i<n;i++)
{
printf("\nEnter Process Name: ");
scanf("%s",tab[i].pname);
printf("Arrival Time:");
scanf("%d",&tab[i].at);
printf("Burst Time: ");
scanf("%d",&tab[i].bt);
tab[i].tbt=tab[i].bt;
 printf("\nEnter the Priority:");
 scanf("%d",&tab[i].p);
}
}
void printinput()
{
 // int TWT=0,TTAT=0;
printf("\nPname\tAT\tBT");
for(i=0;i<n;i++)
printf("\n%s\t%d\t%d",tab[i].pname,tab[i].at,tab[i].bt);
}
void printoutput()
{
 int TWT=0,TTAT=0;
 float ATAT,AWT;
printf("\nPname\tAT\tBT\tFT\tWT\tTAT");
for(i=0;i<n;i++)
{
printf("\n%s\t%d\t%d\t%d\t%d\t%d",tab[i].pname,tab[i].at,tab[i].bt,tab[i].ft,tab[i].fttab[i].at-tab[i].bt,tab[i].ft-tab[i].at);
 TWT=TWT+(tab[i].ft-tab[i].at-tab[i].bt);
 TTAT=TTAT+(tab[i].ft-tab[i].at);
}
 printf("\nTotal WT: %d",TWT);
 printf("\nTotal TAT:%d",TTAT);
 AWT=(float)TWT/n;
 ATAT=(float)TTAT/n;
 printf("\nAverage WT: %f",AWT);
 printf("\nAverage TAT:%f",ATAT);
}
void sort()
{
int pass;
struct input temp;
for(pass=1;pass<n;pass++)
{
for(i=0;i<n-pass;i++)
{
if(tab[i].at>tab[i+1].at)
{
temp=tab[i];
tab[i]=tab[i+1];
tab[i+1]=temp;
}
}
}
}
int arrived(int time)
{
for(i=0;i<n;i++)
{
if(tab[i].at<=time && tab[i].tbt!=0)
return 1;
}
return 0;
}
int gethighpriority(int time)
{
 int processpos,min=99;
 for(i=0;i<n;i++)//i=0,1
 { // p1,p3 min=2
 if(tab[i].at<=time && tab[i].tbt!=0 && tab[i].p<min)
 {
 min=tab[i].p;
 processpos=i;
 }
 }
 return processpos;
}
void processinput()
{
int finish=0,j;
k=0;
while(finish!=n)
{
if(arrived(time))
{
 i=gethighpriority(time);
for(j=0;j<tab[i].bt;j++)
{
time++;
tab[i].tbt--;
g[k].start=prev;
g[k].end=time;
prev=time;
strcpy(g[k++].pname,tab[i].pname);
tab[i].ft=time;
if(tab[i].tbt==0)
{
finish++;
break;
}
}
}
else
{
time++;
g[k].start=prev;
g[k].end=time;
strcpy(g[k++].pname,"idle");
prev=time;
 }
// i++;
}
}
void ganttchart()
{
 int i,j=0;
 printf("\n******Each Unit Gantt chart******");
 printf("\nStart\tpname\tEnd");
 for(i=0;i<k;i++)
 {
 printf("\n%d\t%s\t%d",g[i].start,g[i].pname,g[i].end);
 }
 printf("\n********Final Gantt Chart*******");
 g1[0]=g[0];
 for(i=1;i<k;i++)
 {
 if(strcmp(g[i].pname,g1[j].pname)==0)
 g1[j].end=g[i].end;
 else
 {
 j++;
 g1[j]=g[i];
 }
 }
printf("\nStart\tpname\tEnd");
 for(i=0;i<=j;i++)
 {
 printf("\n%d\t%s\t%d",g1[i].start,g1[i].pname,g1[i].end);
 }
}
 int main()
{
getinput();
printinput();
sort();
printf("\nData After Sorting: ");
printinput();
processinput();
printoutput();
ganttchart();
for(i=0;i<n;i++)
{
 tab[i].tbt=tab[i].bt=rand()%10+1;
 tab[i].at=tab[i].ft+2;
 }
 printinput();
 processinput();
 printoutput();
 ganttchart();
}


Slip 17

Write the simulation program for demand paging and show the page scheduling and total number of page faults according the Optimal page replacement algorithm. Assume the memory of n frames. Reference String : 7, 5, 4, 8, 5, 7, 2, 3, 1, 3, 5, 9, 4, 6,

#include<stdio.h>
int nor,nof,refstring[30],F[10];
void accept()
{
 int i;
 printf("\nEnter the Reference String:\n ");
 for(i=0;i<nor;i++)
 {
 printf("[%d]: ",i);
 scanf("%d",&refstring[i]);
 }
}
int search(int page)
{
 int i;
 for(i=0;i<nof;i++)
 {
 if(page==F[i])
 return i;
 }
 return -1;
 }
int getfno(int i)
{
 int fno,prev,pos=0,fpos,flag;
 for(fno=0;fno<nof;fno++)
 {
 flag=0;
 for(prev=i+1;prev<nor;prev++)
 {
 if(F[fno]==refstring[prev])
 {
 flag=1;
 if(prev>pos) //2<3
 {
 pos=prev; //pos=2
 fpos=fno; //fpos=2
 }
 break;
 }
 }
 if(flag==0)
 {
 fpos=fno;
 break;
 }
 }
//printf("\nfpos=%d",fpos);
 return fpos;
}
void optimal()
{
 int i,j,k,fno,fault=0;
 for(fno=0,i=0;fno<nof && i<nor;i++)
 {
 printf("\n%d",refstring[i]);
 k=search(refstring[i]);
 //printf("\nk=%d",k);
 if(k==-1)
 {
 F[fno]=refstring[i];
 for(j=0;j<nof;j++)
 {
 if(F[j])
 printf("\t%d",F[j]);
 }
 fault++;
 fno++;
 }
 }
 while(i<nor)
 {
 printf("\n%d",refstring[i]);
 k=search(refstring[i]);
 //printf("\nk=%d",k);
 if(k==-1)
 {
 fno=getfno(i);
 F[fno]=refstring[i];
 for(j=0;j<nof;j++)
 {
 if(F[j])
 printf("\t%d",F[j]);
 }
 fault++;

 }
 i++;
 }
 printf("\nTotal no of Page fault: %d",fault);
 }
 main()
{
 printf("\nEnter the Length of the string: ");
 scanf("%d",&nor);
 printf("\nEnter no. of Frames: ");
 scanf("%d",&nof);
 accept();
 optimal();
}

Write the program to simulate FCFS CPU-scheduling. The arrival time and first CPU-burst of different jobs should be input to the system. Accept no. of Processes, arrival time and burst time. The output should give Gantt chart, turnaround time and waiting time for each process. Also find the average waiting time and turnaround time. 

#include<stdio.h>
struct input
{
 char pname[10];
 int bt,at,tbt,ft;
}tab[10];
struct gantt
{
 int start,end;
 char pname[10];
}g[50],g1[10];
int n,i,k,time,prev;
void getinput()
{
 printf("\nEnter No of Processes: ");
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
 printf("\nProcess Name: ");
 scanf("%s",tab[i].pname);
 printf("Burst Time: ");
 scanf("%d",&tab[i].bt);
 tab[i].tbt=tab[i].bt;
 printf("Arrival Time:" );
 scanf("%d",&tab[i].at);
 }
}
void printinput()
{
 printf("\nPname\tBT\tAT");
 for(i=0;i<n;i++)
 printf("\n%s\t%d\t%d",tab[i].pname,tab[i].tbt,tab[i].at);
}
void sort()
{
 struct input temp;
 int j;
 for(i=1;i<n;i++)//pass
 for(j=0;j<n-1;j++)//Comp
 if(tab[j].at>tab[j+1].at)
 {
 temp=tab[j];
 tab[j]=tab[j+1];
 tab[j+1]=temp;
 }
}
int arrived(int time)
{
 for(i=0;i<n;i++)
 if(tab[i].at<=time && tab[i].tbt!=0)
 return 1;
 return 0;
}
void processinput()
{
int j,finish=0;
// time=tab[0].at;
 while(finish!=n)
{
if(arrived(time))
{
 for(j=0;j<tab[i].bt;j++)
{
time++;
tab[i].tbt--;
 g[k].start=prev;
g[k].end=time;
// printinput();
prev=time;
tab[i].ft=time;
strcpy(g[k++].pname,tab[i].pname);
 if(tab[i].tbt==0)
 {
 finish++;
 break;
}
 }
}
else
 {
 time++;
 g[k].start=prev;
 g[k].end=time;
 prev=time;
 strcpy(g[k++].pname,"idle");
}
}
 // printinput();
}
void printoutput()
{
 int TTAT=0,TWT=0;
 float ATAT,AWT;
 printf("\n******Final Table*****");
 printf("\nPname\tAT\tBT\tFT\tTAT\tWT");
 for(i=0;i<n;i++)
 {
printf("\n%s\t%d\t%d\t%d\t%d\t%d",tab[i].pname,tab[i].at,tab[i].bt,tab[i].ft,tab[i].fttab[i].at,tab[i].ft-tab[i].at-tab[i].bt);
 TTAT=TTAT+(tab[i].ft-tab[i].at);
 TWT=TWT+(tab[i].ft-tab[i].at-tab[i].bt);
 }
 ATAT=(float)TTAT/n;
 AWT=(float)TWT/n;
 printf("\nTotal TAT=%d",TTAT);
 printf("\nTotal WT=%d",TWT);
 printf("\nAverage TAT=%f",ATAT);
 printf("\nAverage WT=%f",AWT);
}
void printganttchart()
{
 int j=0;
 g1[0]=g[0];
 for(i=1;i<k;i++)
 {
 if(strcmp(g1[j].pname,g[i].pname)==0)
 g1[j].end=g[i].end;
 else
{
j++;
 g1[j]=g[i];
 }
 }
 printf("\n******Each unit Gantt chart******");
 for(i=0;i<k;i++)
 printf("\n%d\t%s\t%d",g[i].start,g[i].pname,g[i].end);
 printf("\n******Final Gantt chart******");
 for(i=0;i<=j;i++)
 printf("\n%d\t%s\t%d",g1[i].start,g1[i].pname,g1[i].end);
 }
int main()
{
 getinput();
 printf("\nEntered data is: ");
 printinput();
 sort();
 printf("\nData after Sorting" );
 printinput();
 processinput();
 printoutput();
 printganttchart();
}

Slip 18

Write the simulation program for demand paging and show the page scheduling and total number of page faults according the LRU page replacement algorithm. Assume the memory of n frames. Reference String : 3, 4, 5, 6, 3, 4, 7, 3, 4, 5, 6, 7, 2, 4, 6

#include<stdio.h>
int nor,nof,refstring[30],F[10];
void accept()
{
 int i;
 printf("\nEnter the Reference String:\n ");
 for(i=0;i<nor;i++)
 {
 printf("[%d]: ",i);
 scanf("%d",&refstring[i]);
 }
}
int search(int page)
{
 int i;
 for(i=0;i<nof;i++)
 {
 if(page==F[i])
 return i;
 }
 return -1;
 }
int getfno(int i)
{
 int fno,prev,pos=99,fpos;
 for(fno=0;fno<nof;fno++)
 {
 for(prev=i-1;prev>=0;prev--)
 {
 if(F[fno]==refstring[prev])
 {
 if(prev<pos)
 {
 pos=prev;
 fpos=fno;
 }
 break;
 }
 }
 }
;
 return fpos;
}
void LRU()
{
 int i,j,k,fno,fault=0;
 for(fno=0,i=0;fno<nof && i<nor;i++)
 {
 printf("\n%d",refstring[i]);
 k=search(refstring[i]);
 if(k==-1)
 {
 F[fno]=refstring[i];
 for(j=0;j<nof;j++)
 {
 if(F[j])
 printf("\t%d",F[j]);
 }
 fault++;
 fno++;
 }
 }
 while(i<nor)
 {
 printf("\n%d",refstring[i]);
 k=search(refstring[i]);
 if(k==-1)
 {
 fno=getfno(i);
 F[fno]=refstring[i];
 for(j=0;j<nof;j++)
 {
 if(F[j])
 printf("\t%d",F[j]);
 }
 fault++;

 }
 i++;
 }
 printf("\nTotal no of Page fault: %d",fault);
 }
 main()
{
 printf("\nEnter the Length of the string: ");
 scanf("%d",&nor);
 printf("\nEnter no. of Frames: ");
 scanf("%d",&nof);
 accept();
 LRU();
}

Write a C program to simulate FCFS CPU-scheduling. The arrival time and first CPU-burst of different jobs should be input to the system. Accept no. of Processes, arrival time and burst time. The output should give Gantt chart, turnaround time and waiting time for each process. Also find the average waiting time and turnaround time.

#include<stdio.h>
struct input
{
 char pname[10];
 int bt,at,tbt,ft;
}tab[10];
struct gantt
{
 int start,end;
 char pname[10];
}g[50],g1[10];
int n,i,k,time,prev;
void getinput()
{
 printf("\nEnter No of Processes: ");
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
 printf("\nProcess Name: ");
 scanf("%s",tab[i].pname);
 printf("Burst Time: ");
 scanf("%d",&tab[i].bt);
 tab[i].tbt=tab[i].bt;
 printf("Arrival Time:" );
 scanf("%d",&tab[i].at);
 }
}
void printinput()
{
 printf("\nPname\tBT\tAT");
 for(i=0;i<n;i++)
 printf("\n%s\t%d\t%d",tab[i].pname,tab[i].tbt,tab[i].at);
}
void sort()
{
 struct input temp;
 int j;
 for(i=1;i<n;i++)//pass
 for(j=0;j<n-1;j++)//Comp
 if(tab[j].at>tab[j+1].at)
 {
 temp=tab[j];
 tab[j]=tab[j+1];
 tab[j+1]=temp;
 }
}
int arrived(int time)
{
 for(i=0;i<n;i++)
 if(tab[i].at<=time && tab[i].tbt!=0)
 return 1;
 return 0;
}
void processinput()
{
int j,finish=0;
// time=tab[0].at;
 while(finish!=n)
{
if(arrived(time))
{
 for(j=0;j<tab[i].bt;j++)
{
time++;
tab[i].tbt--;
 g[k].start=prev;
g[k].end=time;
// printinput();
prev=time;
tab[i].ft=time;
strcpy(g[k++].pname,tab[i].pname);
 if(tab[i].tbt==0)
 {
 finish++;
 break;
}
 }
}
else
 {
 time++;
 g[k].start=prev;
 g[k].end=time;
 prev=time;
 strcpy(g[k++].pname,"idle");
}
}
 // printinput();
}
void printoutput()
{
 int TTAT=0,TWT=0;
 float ATAT,AWT;
 printf("\n******Final Table*****");
 printf("\nPname\tAT\tBT\tFT\tTAT\tWT");
 for(i=0;i<n;i++)
 {
printf("\n%s\t%d\t%d\t%d\t%d\t%d",tab[i].pname,tab[i].at,tab[i].bt,tab[i].ft,tab[i].fttab[i].at,tab[i].ft-tab[i].at-tab[i].bt);
 TTAT=TTAT+(tab[i].ft-tab[i].at);
 TWT=TWT+(tab[i].ft-tab[i].at-tab[i].bt);
 }
 ATAT=(float)TTAT/n;
 AWT=(float)TWT/n;
 printf("\nTotal TAT=%d",TTAT);
 printf("\nTotal WT=%d",TWT);
 printf("\nAverage TAT=%f",ATAT);
 printf("\nAverage WT=%f",AWT);
}
void printganttchart()
{
 int j=0;
 g1[0]=g[0];
 for(i=1;i<k;i++)
 {
 if(strcmp(g1[j].pname,g[i].pname)==0)
 g1[j].end=g[i].end;
 else
{
j++;
 g1[j]=g[i];
 }
 }
 printf("\n******Each unit Gantt chart******");
 for(i=0;i<k;i++)
 printf("\n%d\t%s\t%d",g[i].start,g[i].pname,g[i].end);
 printf("\n******Final Gantt chart******");
 for(i=0;i<=j;i++)
 printf("\n%d\t%s\t%d",g1[i].start,g1[i].pname,g1[i].end);
 }
int main()
{
 getinput();
 printf("\nEntered data is: ");
 printinput();
 sort();
 printf("\nData after Sorting" );
 printinput();
 processinput();
 printoutput();
 printganttchart();
}


Slip 19

Write a C program to implement the shell. It should display the command prompt “myshell$”. Tokenize the command line and execute the given command by creating the child process. Additionally it should interpret the following ‘list’ commands as 
myshell$ list f dirname :- To print names of all the files in current directory.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
char *buff,*t1,*t2,*t3,ch;
int pid;
void list(char t2,char *t3)
{
 DIR *dir;
 struct dirent *entry;
 int cnt=0;
 dir=opendir(t3);
 if (dir==NULL)
 {
 printf("Directory %s not found",t3);
 return;
 }
 switch(t2)
 {
case 'f' : while((entry=readdir(dir))!=NULL)
 {
printf("%s\n",entry->d_name);
 }
 break;
case 'n' : while((entry=readdir(dir))!=NULL)
 cnt++;
 printf("Total No of Entries: %d\n",cnt);
 break;
case 'i' : while((entry=readdir(dir))!=NULL)
 {
printf("\n%s\t %d",entry->d_name,entry->d_ino);
 }
 break;
default : printf("Invalid argument");
 }
 closedir(dir);
}
main()
{
 while(1)
 {
printf("myshell$");
 fflush(stdin);
t1=(char *)malloc(80);
t2=(char *)malloc(80);
t3=(char *)malloc(80);
buff=(char *)malloc(80);
fgets(buff,80,stdin);
sscanf(buff,"%s %s %s",t1,t2,t3);
if(strcmp(t1,"pause")==0)
exit(0);
else if(strcmp(t1,"list")==0)
list(t2[0],t3);
else
{
pid=fork();
if(pid<0)
printf("Child process is not created\n");
else if(pid==0)
{
execlp("/bin",NULL);
if(strcmp(t1,"exit")==0)
exit(0);
system(buff);
}
else
{
wait(NULL);
exit(0);
}
}
 }
}

Write the simulation program for Round Robin scheduling for given time quantum. The arrival time and first CPU-burst of different jobs should be input to the system. Accept no. of Processes, arrival time and burst time. The output should give the Gantt chart, turnaround time and waiting time for each process. Also display the average turnaround time and average waiting time.

#include<stdio.h>
struct input
{
char pname[10];
int bt,at,tbt,ft;
}tab[10];
struct gantt
{
 char pname[10];
 int start,end;
}g[30],g1[30];
int n,time,prev,k,tq;
void getinput()
{
 int i;
printf("\nEnter No of Process: ");
scanf("%d",&n);
printf("\nEnter Time quantum: ");
scanf("%d",&tq);
for(i=0;i<n;i++)
{
printf("\nEnter Process Name: ");
scanf("%s",tab[i].pname);
printf("Arrival Time:");
scanf("%d",&tab[i].at);
printf("Burst Time: ");
scanf("%d",&tab[i].bt);
tab[i].tbt=tab[i].bt;
}
}
void printinput()
{
 // int TWT=0,TTAT=0;
 int i;
printf("\nPname\tAT\tBT");
for(i=0;i<n;i++)
printf("\n%s\t%d\t%d",tab[i].pname,tab[i].at,tab[i].tbt);
}
void printoutput()
{
 int TWT=0,TTAT=0,i;
 float ATAT,AWT;
printf("\nPname\tAT\tBT\tFT\tWT\tTAT");
for(i=0;i<n;i++)
{
printf("\n%s\t%d\t%d\t%d\t%d\t%d",tab[i].pname,tab[i].at,tab[i].bt,tab[i].ft,tab[i].ft-tab[i].at-tab[i].bt,tab[i].ft-tab[i].at);
 TWT=TWT+(tab[i].ft-tab[i].at-tab[i].bt);
 TTAT=TTAT+(tab[i].ft-tab[i].at);
}
 printf("\nTotal WT: %d",TWT);
 printf("\nTotal TAT:%d",TTAT);
 AWT=(float)TWT/n;
 ATAT=(float)TTAT/n;
 printf("\nAverage WT: %f",AWT);
 printf("\nAverage TAT:%f",ATAT);
}
void sort()
{
int pass,i;
struct input temp;
for(pass=1;pass<n;pass++)
{
for(i=0;i<n-pass;i++)
{
if(tab[i].at>tab[i+1].at)
{
temp=tab[i];
tab[i]=tab[i+1];
tab[i+1]=temp;
}
}
}
}
int arrived(int time)
{
int i;
for(i=0;i<n;i++)
{
if(tab[i].at<=time && tab[i].tbt!=0)
return 1;
}
return 0;
}
void processinput()
{
int finish=0,j;
int i=0;
k=0;
while(finish!=n)
{
if(arrived(time))
{
if(tab[i].tbt!=0)
{
for(j=0;j<tq;j++)
{
time++;
tab[i].tbt--;
g[k].start=prev;
g[k].end=time;
prev=time;
strcpy(g[k++].pname,tab[i].pname);
tab[i].ft=time;
if(tab[i].tbt==0)
{
finish++;
break;
}
}
}
}
else
{
time++;
g[k].start=prev;
g[k].end=time;
strcpy(g[k++].pname,"idle");
prev=time;
}
if(time<tab[(i+1)%n].at)
i=0;
else
i=(i+1)%n;
}
}
void ganttchart()
{
 int i,j=0;
 printf("\n******Each Unit Gantt chart******");
 printf("\nStart\tpname\tEnd");
 for(i=0;i<k;i++)
 {
 printf("\n%d\t%s\t%d",g[i].start,g[i].pname,g[i].end);
 }
 printf("\n********Final Gantt Chart*******");
 g1[0]=g[0];
 for(i=1;i<k;i++)
 {
 if(strcmp(g[i].pname,g1[j].pname)==0)
 g1[j].end=g[i].end;
 else
 {
 j++;
 g1[j]=g[i];
 }
 }
printf("\nStart\tpname\tEnd");
 for(i=0;i<=j;i++)
 {
 printf("\n%d\t%s\t%d",g1[i].start,g1[i].pname,g1[i].end);
 }
}
 int main()
{
getinput();
printinput();
sort();
printf("\nData After Sorting: ");
printinput();
processinput();
printoutput();
ganttchart();
for(i=0;i<n;i++)
{
 tab[i].tbt=tab[i].bt=rand()%10+1;
 tab[i].at=tab[i].ft+2;
 }
 printinput();
 processinput();
 printoutput();
 ganttchart();
}

Slip 20

Write a C program to implement the shell which displays the command prompt “myshell$”. It accepts the command, tokenize the command line and execute it by creating the child process. Also implement the additional command ‘typeline’ as 
typeline -a filename :- To print all lines in the file.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
char *buff,*t1,*t2,*t3,ch;
FILE *fp;
int pid;
void typeline(char *t2,char *t3)
{
int i,n,count=0,num;
if((fp=fopen(t3,"r"))==NULL)
printf("File not found\n");
if(strcmp(t2,"a")==0)
{
while((ch=fgetc(fp))!=EOF)
printf("%c",ch);
fclose(fp);
return;
}
n=atoi(t2);
if(n>0)
{
i=0;
while((ch=fgetc(fp))!=EOF)
{
if(ch=='\n')
i++;
if(i==n)
break;
printf("%c",ch);
}
printf("\n");
}
else
{
count=0;
while((ch=fgetc(fp))!=EOF)
if(ch=='\n')
count++;
fseek(fp,0,SEEK_SET);
i=0;
while((ch=fgetc(fp))!=EOF)
{
if(ch=='\n')
i++;
if(i==count+n-1)
break;
}
while((ch=fgetc(fp))!=EOF)
printf("%c",ch);
}
fclose(fp);
}
main()
{
while(1)
{
printf("myshell$");
fflush(stdin);
t1=(char *)malloc(80);
t2=(char *)malloc(80);
t3=(char *)malloc(80);
buff=(char *)malloc(80);
fgets(buff,80,stdin);
sscanf(buff,"%s %s %s",t1,t2,t3);
if(strcmp(t1,"pause")==0)
exit(0);
else if(strcmp(t1,"typeline")==0)
typeline(t2,t3);
else
{
pid=fork();
if(pid<0)
printf("Child process is not created\n");
else if(pid==0)
{
execlp("/bin",NULL);
if(strcmp(t1,"exit")==0)
exit(0);
system(buff);
}
else
{
wait(NULL);
exit(0);
}
}
}
}

Write the program to simulate Non-preemptive Shortest Job First (SJF) – scheduling. The arrival time and first CPU-burst of different jobs should be input to the system. Accept no. of Processes, arrival time and burst time. The output should give Gantt chart, turnaround time and waiting time for each process. Also find the average waiting time and turnaround time

#include<stdio.h>
struct input
{
 char pname[10];
 int bt,at,tbt,ft;
}tab[10];
struct gantt
{
 int start,end;
 char pname[10];
}g[50],g1[10];
int n,i,k,time,prev;
void getinput()
{
 printf("\nEnter No of Processes: ");
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
 printf("\nProcess Name: ");
 scanf("%s",tab[i].pname);
 printf("Burst Time: ");
 scanf("%d",&tab[i].bt);
 tab[i].tbt=tab[i].bt;
 printf("Arrival Time:" );
 scanf("%d",&tab[i].at);
 }
}
void printinput()
{
 printf("\nPname\tBT\tAT");
 for(i=0;i<n;i++)
 printf("\n%s\t%d\t%d",tab[i].pname,tab[i].tbt,tab[i].at);
}
void sort()
{
 struct input temp;
 int j;
 for(i=1;i<n;i++)//pass
 for(j=0;j<n-1;j++)//Comp
 if(tab[j].at>tab[j+1].at)
 {
 temp=tab[j];
 tab[j]=tab[j+1];
 tab[j+1]=temp;
 }
}
int arrived(int time)
{
 for(i=0;i<n;i++)
 if(tab[i].at<=time && tab[i].tbt!=0)
 return 1;
 return 0;
}
int getsmallburst(int time)
{
 int min=99,mini;
 for(i=0;i<n;i++)
 {
 if(tab[i].tbt<min && tab[i].at<=time && tab[i].tbt!=0)
 {
 min=tab[i].tbt;
 mini=i;
 }
 }
 return mini;
}
 void processinput()
{
int j,finish=0;
// time=tab[0].at;
 while(finish!=n)
{
if(arrived(time))
{
i=getsmallburst(time);
 for(j=0;j<tab[i].bt;j++)
{
time++;
tab[i].tbt--;
 g[k].start=prev;
g[k].end=time;
// printinput();
prev=time;
tab[i].ft=time;
strcpy(g[k++].pname,tab[i].pname);
 if(tab[i].tbt==0)
 {
 finish++;
 break;
}
 }
}
else
 {
 time++;
 g[k].start=prev;
 g[k].end=time;
 prev=time;
 strcpy(g[k++].pname,"idle");
}
}
 // printinput();
}
void printoutput()
{
 int TTAT=0,TWT=0;
 float ATAT,AWT;
 printf("\n******Final Table*****");
 printf("\nPname\tAT\tBT\tFT\tTAT\tWT");
 for(i=0;i<n;i++)
 {
printf("\n%s\t%d\t%d\t%d\t%d\t%d",tab[i].pname,tab[i].at,tab[i].bt,tab[i].ft,tab[i].fttab[i].at,tab[i].ft-tab[i].at-tab[i].bt);
 TTAT=TTAT+(tab[i].ft-tab[i].at);
 TWT=TWT+(tab[i].ft-tab[i].at-tab[i].bt);
 }
 ATAT=(float)TTAT/n;
 AWT=(float)TWT/n;
 printf("\nTotal TAT=%d",TTAT);
 printf("\nTotal WT=%d",TWT);
 printf("\nAverage TAT=%f",ATAT);
 printf("\nAverage WT=%f",AWT);
}
void printganttchart()
{
 int j=0;
 g1[0]=g[0];
 for(i=1;i<k;i++)
 {
 if(strcmp(g1[j].pname,g[i].pname)==0)
 g1[j].end=g[i].end;
 else
{
j++;
 g1[j]=g[i];
 }
 }
 printf("\n******Each unit Gantt chart******");
 for(i=0;i<k;i++)
 printf("\n%d\t%s\t%d",g[i].start,g[i].pname,g[i].end);
 printf("\n******Final Gantt chart******");
 for(i=0;i<=j;i++)
 printf("\n%d\t%s\t%d",g1[i].start,g1[i].pname,g1[i].end);
 }
int main()
{
 getinput();
 printf("\nEntered data is: ");
 printinput();
 sort();
 printf("\nData after Sorting" );
 printinput();
 processinput();
 printoutput();
 printganttchart();
}

