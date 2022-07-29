#include<stdio.h>
#include<math.h>

int REQ_COUNT, REQ[100], REQ_TEMP[100], INIT, DISK_SIZE;

void getRequest() {
    printf("Enter the number of requests in disk queue: ");
    scanf("%d", &REQ_COUNT);
    printf("Enter the requests in order: \n");
    for(int i = 0; i < REQ_COUNT; i++){
        scanf("%d", &REQ[i]);
    }
    printf("Enter the initial position of head: ");
    scanf("%d", &INIT);

    printf("Enter the number of cylinders in the disk: ");
    scanf("%d", &DISK_SIZE);
}

void sort(){
    int t;
    for(int i = 0; i < REQ_COUNT-1; i++)
        for(int j = i+1; j < REQ_COUNT; j++)
            if(REQ_TEMP[i]>REQ_TEMP[j]){
                t = REQ_TEMP[i];
                REQ_TEMP[i] = REQ_TEMP[j];
                REQ_TEMP[j] = t;
            }
}

void fcfs(){
    // abs => absolute func.. (aka negative->positive)
    int stime = abs(REQ[0]-INIT);
    printf("\n\nOrder:\n\t%d -> %d", INIT, REQ[0]);
    for(int i = 1; i < REQ_COUNT; i++){
        stime += abs(REQ[i]-REQ[i-1]);
        printf(" -> %d", REQ[i]);
    }
    printf("\nTotal Seek time is: %d\n\n", stime);
}

void scan(){
    int start, stime=0;
    sort();
    
    for(int i = 0; i < REQ_COUNT; i++)
        if(REQ_TEMP[i]>INIT){
            start = i;
            break;
        }
    
    if(start==0){
        stime = REQ_TEMP[REQ_COUNT-1] - INIT;
    }
    else 
        stime = (DISK_SIZE-1)*2 - INIT - REQ_TEMP[0];

    printf("\n\nOrder:\n\t%d", INIT);
    for(int i = start; i < REQ_COUNT; i++)
        printf(" -> %d", REQ_TEMP[i]);
    for(int i=start-1; i>=0; i--)
        printf(" -> %d", REQ_TEMP[i]);

    printf("\nTotal Seek time is: %d\n\n", stime);
}


void cscan(){
    int start, stime=0;
    sort();
    
    for(int i = 0; i < REQ_COUNT; i++)
        if(REQ_TEMP[i]>INIT){
            start = i;
            break;
        }
    
    if(start==0)
        stime = REQ_TEMP[REQ_COUNT-1] - INIT;
    else 
        stime = DISK_SIZE-1 - INIT + REQ_TEMP[start-1];

    printf("\n\nOrder:\n\t%d", INIT);
    for(int i = start; i < REQ_COUNT; i++)
        printf(" -> %d", REQ_TEMP[i]);
    for(int i=0; i<start; i++)
        printf(" -> %d", REQ_TEMP[i]);

    printf("\nTotal Seek time is: %d\n\n", stime);
}


void main() {
    getRequest();
    int choice;
    do {
        for(int i = 0; i < REQ_COUNT; i++)
            REQ_TEMP[i] = REQ[i];

        printf("\n\n\t\tMENU");
        printf("\n1. FCFS");
        printf("\n2. SCAN");
        printf("\n3. C-SCAN");
        printf("\n4. Exit");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1: printf("\n\nFCFS Disk Scheduling\n");
                    fcfs();
                    break;

            case 2: printf("\n\nSCAN Disk Scheduling\n");
                    scan();
                    break;
                
            case 3: printf("\n\nC-SCAN Disk Scheduling\n");
                    cscan();
                    break;

            case 4: printf("\n\nExiting...\n\n");
                    break;

            default:
                    printf("\n\nEnter a valid choice...\n\n"); 
        }
    } while(choice!=4);
}