#include<stdio.h> #include<string.h> #include<pthread.h> #include<stdlib.h> #include<time.h>


int st_size=0,tc_size=0; int chk=0;
int mini_avg_student=1000,stud_loc,mini_turn_reca=100; int mini_avg_teacher=1000,teac_loc;
int quant=20,size; int timer=0;


struct tm * time_information;


//structure for collection of all the details of the queue struct que
{

int priority_1;	//to differentiate b/w stent and teacher int burst_time;		//Burst_time
int rem_btime;	//Remaining burst time int arri_time; //arrival time of query
char per_name[20]; //Name of the counsumer int turn_rec;	//repeation record
};
 

//st_que array for student queries

//tc_que array for teacher queries struct que st_que[10],tc_que[10];


//function to get the system current time void gettime()
{

time_t rawtime;


time ( &rawtime );

time_information = localtime ( &rawtime );


}


//function to chk for the valid time to be loggeg in 1 for ture else 0 void chk_time()
{

gettime();

if(time_information->tm_hour>=10 && time_information->tm_hour<12)

{

chk=1;

}

}




//function will print all the details of the queries void print_data_1(struct que a[],int size)
{

printf("sr_no.\tName\t\tPosition\tArrival_time\tRemaining_Burst_time\tturn_rec\n");
 
char buff[20]; if(a[0].priority_1==1)
strcpy(buff,"Student"); else
strcpy(buff,"Teacher");


for(int i=0;i<size;i++)

{


printf("%-6d %-15s %-15s %-15d %-15d %- 10d\n",i+1,a[i].per_name,buff,a[i].arri_time,a[i].burst_time,a[i].turn_rec);
}




}


//funtion will find the best nxt student query for execution check both arrival time , burst time and repeation of querys
void pro_min_stent()

{mini_avg_student=1000; mini_turn_reca=10; for(int i=0;i<st_size;i++)
{

if(st_que[i].burst_time>0 && mini_turn_reca>st_que[i].turn_rec) if(mini_avg_student>=st_que[i].arri_time)
{

mini_avg_student=st_que[i].arri_time; stud_loc=i; mini_turn_reca=st_que[i].turn_rec;


// printf("%d",stud_loc);
 
//printf("yp\n");

}



}


// cout<<st_que[stud_loc].per_name<<endl;

}


//funtion will find the best nxt teacher query for execution chk both arrival time , burst time and repeation of querys
void pro_mini_teach()

{

mini_avg_teacher=1000; mini_turn_reca=10; for(int i=0;i<tc_size;i++)
{

if(tc_que[i].burst_time>0)

if(mini_avg_teacher>=tc_que[i].arri_time && mini_turn_reca>st_que[i].turn_rec)

{

mini_avg_teacher=tc_que[i].arri_time; teac_loc=i; mini_turn_reca=tc_que[i].turn_rec;
//printf("yoo\n");

}


}

//cout<<tc_que[teac_loc].per_name<<endl;

}


//function will remove the specified node fromm the que array
 
void rem_elem(struct que * temp)

{

int i=0;

if(temp->priority_1==2)

{

while(&st_que[i]!=temp) i++;


if(i!=st_size) while(i<st_size-1)
{

strcpy(st_que[i].per_name,st_que[i+1].per_name); st_que[i].arri_time=st_que[i+1].arri_time; st_que[i].burst_time=st_que[i+1].burst_time;
i++;

}

//else

st_size--;

}

if(temp->priority_1==1)

{

while(&tc_que[i]!=temp) i++;


if(i!=tc_size) while(i<tc_size-1)
{

strcpy(tc_que[i].per_name,tc_que[i+1].per_name); tc_que[i].arri_time=tc_que[i+1].arri_time; tc_que[i].burst_time=tc_que[i+1].burst_time;
 
i++;

}

//else

tc_size--;

}



}




//function will execute the que and update the que status void *pro(struct que *temp)
{

system("clear");

printf("\" %s \" your turn is here \n",temp->per_name);


sleep(4);

printf("\n\nProcessing your request\n\n"); sleep(4);
if ((temp->burst_time > 0))

{

temp->burst_time -= quant; if (temp->burst_time <=0)
{

timer+=temp->burst_time+quant; temp->burst_time=0;
printf("\" %s \" query is completly executed :\n",temp->per_name); rem_elem(temp);
//size--;

}

else
 
{

timer+=quant;

//printf("%d",temp->burst_time); printf("\nSorry for the inconvinance \n");
printf("\" %s \" query is to big you Wait for Your next turn_rec\n",temp->per_name); temp->turn_rec++;


}

sleep(5);





}

pthread_exit(NULL);

}


//main function int main()
{

pthread_t p2;


int Total_querytime=0,Query_count=0; float average_querytime=0;
//chk_time(); chk=1; system("clear");
printf("Suresh Welcome To Online Query System:\n"); sleep(3);
system("clear"); printf("Logging in .\n"); sleep(2);
 
system("clear"); printf("Logging in . .\n"); sleep(2); system("clear");
printf("Logging in . . .\n");




// chk the loggin in critaria if(chk==1)
{

int flag1=1; sleep(2); system("clear");
printf("Logged In Succesfull\n"); while(flag1)
{

char name[20],position[20]; int arival_time,bursst_time; sleep(1);
system("clear");

//taking query from the user


printf("\nEnter the query details in the form:\n"); printf("\nEnter your name: ");
scanf("%s",name);

printf("\nEnter your position(student/teacher): "); scanf("%s",position);
printf("\nEnter your arrival time: "); scanf("%d",&arival_time);
printf("\nEnter your query time needed: ");
 
scanf("%d",&bursst_time);


struct que *temp;


if(strcmp(position,"student")==0||strcmp(position,"STUDENT")==0)

{

temp=&st_que[st_size];

//printf("hello\n"); st_size++;
temp->priority_1=2;

}

else if(strcmp(position,"teacher")==0||strcmp(position,"TEACHER")==0)

{

temp=&tc_que[tc_size];

//printf("yoo\n"); tc_size++;
temp->priority_1=1;

}


temp->arri_time=arival_time; temp->burst_time=bursst_time; temp->rem_btime=bursst_time; strcpy(temp->per_name,name); temp->turn_rec=1;


Total_querytime+=bursst_time; Query_count++;



printf("\n\nAdd another form(Y/N)\n");
 
char ch; scanf("%c",&ch);
scanf("%c",&ch); if(ch=='y'||ch=='Y') flag1=1;
else flag1=0;




}

system("clear");


//printing of query table

printf("List Of the Student Query Submitted\n\n"); print_data_1(st_que,st_size);
printf("\n\nList Of the Teacher Query Submitted\n\n"); print_data_1(tc_que,tc_size);
//printf("%d\n",st_size);

//printf("%d\n",tc_size);


printf("NOTE:- Every Query will be given 20 time Quantum:-\n");


printf("\n\nWait till we call your name: \n\n ");


pro_min_stent(); pro_mini_teach(); sleep(6);


if(mini_avg_student<mini_avg_teacher )

{
 
timer=mini_avg_student;

}

else

{

timer=mini_avg_teacher;

}


//calling query according to there priority_1 and arrival time while(tc_size!=0||st_size!=0)
{


//printf("%d %d \n",mini_avg_student,mini_avg_teacher);






if(timer>=mini_avg_teacher)

{

pthread_create(&p2,NULL,pro,(void *)&tc_que[teac_loc]); pthread_join(p2,NULL);
//st_size--;

}

else

{

pthread_create(&p2,NULL,pro,(void *)&st_que[stud_loc]); pthread_join(p2,NULL);
// tc_size--;


}


//print_data_1(st_que,st_size);
 
//print_data_1(tc_que,tc_size);

//printf("%d\n",st_size);

//printf("%d\n",tc_size); pro_min_stent(); pro_mini_teach();


}

average_querytime=Total_querytime/Query_count; sleep(3);
system("clear");

printf("Todays query taking session has been Ended \n");

printf("\n\nTotal query taken today = %d \n\nTotal query time = %d\n\nAverage query time =
%f\n",Query_count,Total_querytime,average_querytime); sleep(3);
system("clear"); printf("Logging out .\n"); sleep(2); system("clear");
printf("Logging out . .\n"); sleep(2);
system("clear"); printf("Logging out . . .\n"); sleep(2);
system("clear"); printf("Logged out\n");





}

else
 
{

system("clear");

printf("log In Unsucessfull\n\n"); printf("Cannt login during this time of day\n");


}



}

