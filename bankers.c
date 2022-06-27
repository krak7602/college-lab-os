// Banker's Algorithm
#include <stdio.h>
int main()
{
    int proc_count, res_count;
    printf("Enter the number of processes: ");
    scanf("%d", &proc_count);

    printf("Enter the number of types of resources:");
    scanf("%d", &res_count);

	int alloc[proc_count][res_count];
	int max[proc_count][res_count];
	int avail[res_count];
    for(int i=0; i<proc_count; i++)
    {
        printf("Enter the resource allocation for process P%d: \n", i);
        for(int j=0; j<res_count; j++)
        {
            scanf("%d", &alloc[i][j]);
        }
    }

    for(int i=0; i<proc_count; i++)
    {
        printf("Enter the maximum resource request for process P%d: \n", i);
        for(int j=0; j<res_count; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    for(int i=0; i<res_count; i++)
    {
        printf("Enter the available resource of type R%d: \n", i);
        scanf("%d", &avail[i]);
    }

    int proc;
    printf("Enter the process requesting more resource: \n");
    scanf("%d", &proc);
    int req[res_count];
    printf("Enter the resource request for process P%d: \n", proc);
    for(int i=0; i<res_count; i++)
    {
        scanf("%d", &req[i]);
    }

    for(int i=0; i<res_count; i++)
    {
        if(req[i] > max[proc][i])
        {
            printf("Requested resource is greater than maximum resource.\n");
            printf("Request not granted.\n");
            return 0;
        }
    }

    for(int i=0; i<res_count; i++)
    {
        if(req[i] > avail[i])
        {
            printf("Requested resource is greater than available resource.\n");
            printf("Request not granted.\n");
            return 0;
        }
    }

    for(int i=0; i<res_count; i++)
    {
        avail[i] -= req[i];
    }
    
    for(int i=0; i<proc_count; i++)
    {
        for(int j=0; j<res_count; j++)
        {
            alloc[i][j] += req[j];
        }
    }

	int check[proc_count], ans[proc_count], ind = 0;
	for (int k = 0; k < proc_count; k++) {
		check[k] = 0;
	}
	int need[proc_count][res_count];
	
    for (int i = 0; i < proc_count; i++) {
		for (int j = 0; j < res_count; j++)
			need[i][j] = max[i][j] - alloc[i][j];
	}

	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < proc_count; i++) {
			if (check[i] == 0) {

				int flag = 0;
				for (int j = 0; j < res_count; j++) {
					if (need[i][j] > avail[j]){
						flag = 1;
						break;
					}
				}

				if (flag == 0) {
					ans[ind++] = i;
					for (int y = 0; y < res_count; y++)
						avail[y] += alloc[i][y];
					check[i] = 1;
				}
			}
		}
	}

	int flag = 1;
	
	for(int i=0;i<proc_count;i++)
	{
	    if(check[i]==0)
    	{
	    	flag=0;
	    	printf("Immediate allocation of resource resulted in deadlock.\n");
            printf("Request not granted.\n");
	    	break;
    	}
	}
	
	if(flag==1)
	{
	    printf("Request granted\n");
        printf("Processes exectued in order: \n");
	    for (int i = 0; i < proc_count - 1; i++)
	    	printf(" P%d ->", ans[i]);
    	printf(" P%d", ans[proc_count - 1]);
	}
    printf("\n");
}
