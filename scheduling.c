#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

// Function to find the waiting time for all
// processes
struct process
{
    int pid;
    int bt;
    int at;
    int wt;
    int tat;
    int priority;
};

int TIME_SLICE = 2;

typedef struct process process;

void findWaitingTimeFCFS(int n, process proc[])
{
	// waiting time for first process is 0
	proc[0].wt = 0;

	// calculating waiting time
	for (int i = 1; i < n ; i++ )
		proc[i].wt = proc[i-1].bt + proc[i-1].wt ;
}

void findWaitingTimeSJF(int n, process proc[])
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(proc[i].bt>proc[j].bt)
            {
                process temp=proc[i];
                proc[i]=proc[j];
                proc[j]=temp;
            }
        }
    }
    proc[0].wt=0;
    for(int i=1;i<n;i++)
    {
        proc[i].wt=proc[i-1].wt+proc[i-1].bt;
    }
}

void findWaitingTimeRR(int n, process proc[])
{
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] = proc[i].bt;
 
    int t = 0;
 
    while (1)
    {
        int done = 1;
        for (int i = 0 ; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = 0; 
 
                if (rem_bt[i] > TIME_SLICE)
                {
                    t += TIME_SLICE;
                    rem_bt[i] -= TIME_SLICE;
                }
                else
                {
                    t = t + rem_bt[i];
                    proc[i].wt = t - proc[i].bt;
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
}

void findWaitingTimePriority(int n, process proc[])
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(proc[i].priority>proc[j].priority)
            {
                process temp=proc[i];
                proc[i]=proc[j];
                proc[j]=temp;
            }
        }
    }
    proc[0].wt=0;
    for(int i=1;i<n;i++)
    {
        proc[i].wt=proc[i-1].wt+proc[i-1].bt;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int n, process proc[])
{
    // calculating turnaround time by adding
    // bt[i] + wt[i]
    for (int i = 0; i < n ; i++)
        proc[i].tat = proc[i].bt + proc[i].wt;
}

//Function to calculate average time
void findavgTimeAndDisplay(int choice, int n, process proc[])
{
    int total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    if(choice == 1)
        findWaitingTimeFCFS(n, proc);
    else if(choice == 2)
        findWaitingTimeSJF(n, proc);
    else if(choice == 3)
        findWaitingTimeRR(n, proc);
    else if(choice == 4)
        findWaitingTimePriority(n, proc);

    //Function to find turn around time for all processes
    findTurnAroundTime(n, proc);

    // Display processes along with all details
    printf("PID\tBurst Time\tWaiting Time\tTurn Around Time\n");

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n ; i++)
    {
        total_wt = total_wt + proc[i].wt;
        total_tat = total_tat + proc[i].tat;
        printf("\n%d\t\t%d\t\t%d\t\t%d", proc[i].pid, proc[i].bt, proc[i].wt, proc[i].tat);
    }

    printf("\n\nAverage waiting time = %f ", (float)total_wt / (float)n);
    printf("\nAverage turn around time = %f ", (float)total_tat / (float)n);
}

// Driver code
int main()
{
    while(1) {
        printf("\n\nCHOOSE SCHEDULING ALGORITHM:\n");
        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. Round Robin\n");
        printf("4. Priority\n");
        printf("5. Exit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if(choice==1) {
            printf("Enter number of processes:\n");
            int n;
            scanf("%d", &n);
            process proc[n];
            for(int i=0; i<n; i++) {
                printf("Enter Burst time and PID of process %i:\n", i+1);
                scanf("%d %d", &proc[i].bt, &proc[i].pid);
            }
            findavgTimeAndDisplay(choice, n, proc);
            printf("\nSimulating FCFS Scheduling....\n");
            for(int i=0; i<n; i++) {
                printf("Executing process %i\n", proc[i].pid);
                sleep(proc[i].bt/10);
            }
        } 
        else if(choice==2) {
            printf("Enter number of processes:\n");
            int n;
            scanf("%d", &n);
            process proc[n];
            for(int i=0; i<n; i++) {
                printf("Enter Burst time and PID of process %i:\n", i+1);
                scanf("%d %d", &proc[i].bt, &proc[i].pid);
            }
            findavgTimeAndDisplay(choice, n, proc);
            printf("\nSimulating SJF Scheduling....\n");
            for(int i=0; i<n; i++) {
                printf("Executing process %i\n", proc[i].pid);
                sleep(proc[i].bt/10);
            }
        }   
        else if(choice==3) {
            printf("Enter number of processes:\n");
            int n;
            scanf("%d", &n);
            process proc[n];
            for(int i=0; i<n; i++) {
                printf("Enter Burst time and PID of process %i:\n", i+1);
                scanf("%d %d", &proc[i].bt, &proc[i].pid);
            }
            findavgTimeAndDisplay(choice, n, proc);
            printf("\nSimulating Round Robin Scheduling....\n");
            int rem_bt[n], wt[n];
            for (int i = 0 ; i < n ; i++)
                rem_bt[i] = proc[i].bt;
            int t = 0;
            while (1)
            {
                int done = 1;
                for (int i = 0 ; i < n; i++)
                {
                    if (rem_bt[i] > 0)
                    {
                        printf(" pr %i ->", proc[i].pid);
                        done = 0; 
                        if (rem_bt[i] > TIME_SLICE)
                        {
                            t += TIME_SLICE;
                            rem_bt[i] -= TIME_SLICE;
                        }
                        else
                        {
                            t = t + rem_bt[i];
                            wt[i] = t - proc[i].bt;
                            rem_bt[i] = 0;
                        }
                    }
                }
                if (done == 1) {
                    printf(" END\n");
                    break;
                }
            }
            
        }
        else if(choice==4) {
            printf("Enter number of processes:\n");
            int n;
            scanf("%d", &n);
            process proc[n];
            for(int i=0; i<n; i++) {
                printf("Enter Burst time, PID and priority of process %i:\n", i+1);
                scanf("%d %d %d", &proc[i].bt, &proc[i].pid, &proc[i].priority);
            }
            findavgTimeAndDisplay(choice, n, proc);
            printf("\nSimulating Priority Scheduling....\n");
            for(int i=0; i<n; i++) {
                printf("Executing process %i\n", proc[i].pid);
                sleep(proc[i].bt/10);
            }
        }
        else if(choice==5) {
            break;
        }
        else {
            printf("Invalid choice\n");
        }
    }
}   
