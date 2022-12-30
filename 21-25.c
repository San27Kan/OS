
Slip 21

Write a C Program to create a child process using fork (), display parent and child process id. Child process will display the message “I am Child Process”and the parent process should display “I am Parent Process”.

#include<stdio.h>
void childprocess()
{
printf("\n I am Child Process");
}
void parentprocess()
{
printf("\n I am Parent Process");
}
main()
{
int pid;
pid=fork();
if(pid==0)
{
printf("Child Process ID=%d",pid);
childprocess();
}
else
{
printf("\n Parent Process Id=%d",pid);
parentprocess();
}
}

Write a C program to simulate Preemptive Priority scheduling. The arrival time and first CPU-burst and priority for different n number of processes should be input to the algorithm. Assume the fixed IO waiting time (2 units). The next CPU-burst should be generated randomly. The output should give Gantt chart, turnaround time and waiting time for each process. Also find the average waiting time and turnaround time.

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


Slip 22

Write a C program that demonstrates the use of nice() system call. After a child Process is started using fork (), assign higher priority to the child usingnice () system call.

#include<stdio.h>
main()
{
int pid,retnice,i;
pid=fork();
for(i=0;i<3;i++)
{
if(pid==0)
{
retnice=nice(-5);
printf("Child gets higher CPU priority%d\n",retnice);
sleep(1);
}
else
{
retnice=nice(4);
printf("Parent gets lower CPU Priority%d\n",retnice);
sleep(1);
}
}
}

Write a C program to simulate Non preemptive priority scheduling. The arrival time and first CPU-burst of different jobs should be input to the system. Accept no. of Processes, arrival time and burst time. The output should give Gantt chart, turnaround time and waiting time for each process. Also find the average waiting time and turnaround time.

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




Slip 23

Write a C program to illustrate the concept of orphan process. Parent process creates a child and terminates before child has finished its task. So child process becomes orphan process. (Use fork(), sleep(), getpid(), getppid()).

#include<stdio.h>
main()
{
int pid,a;
printf("\n the process id is%d",getpid());
pid=fork();
if(pid<0)
printf("\n Fork failed!");
else if(pid==0)
{
printf("\n I am Child process");
printf("\n Child process ID=%d",getpid());
}
else
{
wait(NULL);
sleep(5);
printf("\n I am Parent process");
printf("\n Child Parent ID=%d",getpid());
}
}

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






Slip 24

Write a C program to accept n integers to be sorted. Main function creates child process using fork system call. Parent process sorts the integers using bubble sort and waits for child process using wait system call. Child process sorts the integers using insertion sort. 

#include<stdio.h>
int n;
void display(int a[20])
{
int i;
printf("\n Array Element:");
for(i=0;i<n;i++)
printf("\t%d",a[i]);
}
void insertionsort(int a[20])
{
int i,key,j;
for(i=1;i<n;i++)
{
key=a[i];
for(j=i-1;j>=0 && a[j]>key;j--)
{
a[j+1]=a[j];
}
a[j+1]=key;
}
}
void bubblesort(int a[20])
{
int pass,i,temp;
for(pass=1;pass<n;pass++)
{
for(i=0;i<n-pass;i++)
{
if(a[i]>a[i+1])
{
temp=a[i];
a[i]=a[i+1];
a[i+1]=temp;
}
}
}
}
main()
{
int i,a[20],pid,Barr[20],Iarr[20];
printf("\n Enter value of n");
scanf("%d",&n);
printf("\n Enter arrray Elements");
for(i=0;i<n;i++)
{
printf("\n Enter Element:",i);
scanf("%d",&a[i]);
Barr[i]=a[i];
Iarr[i]=a[i];
}
display(a);
pid=fork();
if(pid==0)
{
printf("\n Child Process id=%d",getpid());
insertionsort(Iarr);
printf("\n Insertion Sort");
display(Iarr);
}
else if(pid>0)
{
wait(NULL);
sleep(5);
printf("\n Parent Process id=%d",getpid());
bubblesort(Barr);
printf("\nBubbleSort");
display(Barr);
}
}

Write a C program to implement the toy shell. It should display the command prompt “myshell$”. Tokenize the command line and execute the given command by creating the child process. Additionally it should interpret the following commands. 
count c filename :- To print number of characters in the file. 
count w filename :- To print number of words in the file. 
count l filename :- To print number of lines in the file.

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


Slip 25

Write a C program that accepts an integer array. Main function forks child process. Parent process sorts an integer array and passes the sorted array to child process through the command line arguments of execve() system call. The child process uses execve() system call to load new program that uses this sorted array for performing the binary search to search the particular item in the array. 

Write a programto implement the shell. It should display the command prompt “myshell$”. Tokenize the command line and execute the given command by creating the child process. Additionally it should interpret the following commands. myshell$ search f filename pattern :- To display first occurrence of pattern in the file.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
char *buff,*t1,*t2,*t3,*t4,ch;
FILE *fp;
int pid;
void search(char *t2,char *t3,char *t4)
{
int i=1,count=0;
char *p;
if((fp=fopen(t3,"r"))==NULL)
printf("File not found\n");
else
{
if(strcmp(t2,"f")==0)
{
while(fgets(buff,80,fp))
{
if((strstr(buff,t4))!=NULL)
{
printf("%d: %s\n",i,buff);
break;
}
}
i++;
}
else if(strcmp(t2,"c")==0)
{
while(fgets(buff,80,fp))
{
if((strstr(buff,t4))!=NULL)
{
count++;
}
}
printf("No of occurences of %s= %d\n",t3,count);
}
else if(strcmp(t2,"a")==0)
{
while(fgets(buff,80,fp))
{
if((strstr(buff,t4))!=NULL)
{
printf("%d: %s\n",i,buff);
}
i++;
}
}
else
printf("Command not found\n");
fclose(fp);
}
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
t4=(char *)malloc(80);
buff=(char *)malloc(80);
fgets(buff,80,stdin);
sscanf(buff,"%s %s %s %s",t1,t2,t3,t4);
if(strcmp(t1,"pause")==0)
exit(0);
else if(strcmp(t1,"search")==0)
search(t2,t3,t4);
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
 
