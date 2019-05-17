#include<stdlib.h> 
#include<stdio.h> 
#include<time.h>
#include<pthread.h>
#include<math.h>
#include<sys/time.h>


long MAX;
int* arr;
int* aug;
int NUM_THREADS;
int power;

struct msg{
  int l;
  int r; 
};


double time_substract(struct timeval *begin,struct timeval *end)
{
    if(begin->tv_sec > end->tv_sec)    return -1;
    if((begin->tv_sec == end->tv_sec) && (begin->tv_usec > end->tv_usec))    return -2;

    return (end->tv_sec-begin->tv_sec) * 1000 + (end->tv_usec-begin->tv_usec)/(double)1000;
}

// Merges two subarrays of arr[]. 
// First subarray is arr[l..m] 
// Second subarray is arr[m+1..r] 
void merge(int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
  
    /* Copy data to augment array */
    for (i = 0; i < n1; i++) 
        aug[l + i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        aug[m + 1 + j] = arr[m + 1 + j]; 
  
    /* Merge the aug arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (aug[l + i] <= aug[m + 1 + j]) 
        { 
            arr[k] = aug[l + i]; 
            i++; 
        } 
        else
        { 
            arr[k] = aug[m + 1 + j]; 
            j++; 
        } 
        k++; 
    } 
  

    while (i < n1) 
    { 
        arr[k] = aug[l + i]; 
        i++; 
        k++; 
    } 
  

    while (j < n2) 
    { 
        arr[k] = aug[m + 1 + j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
void merge_sort(struct msg *arg) 
{ 
    int l = arg->l;
    int r = arg->r;
    
    if (l < r) 
    {        
        int m = l+(r-l)/2; 
        struct msg l_arg = (struct msg){l, m};
        struct msg r_arg = (struct msg){m+1, r};
        merge_sort(&l_arg); 
        merge_sort(&r_arg); 
  
        merge(l, m, r); 
    } 
} 





void merge_sort_thread()
{
    struct timeval st, end;

    // fisrt split it to sub array to merge sort
    int d = MAX/NUM_THREADS;
    
    struct msg arg[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS - 1; i++)
    {
        
        arg[i] = (struct msg){i*d, (i+1)*d - 1};
        
    }
    arg[NUM_THREADS - 1] = (struct msg){d * (NUM_THREADS - 1), MAX - 1};

    printf("split into : ");
    for(int i = 0; i < NUM_THREADS; i++)
    {
        printf("[%d %d] ", arg[i].l, arg[i].r);
    }
    printf("\n");

    pthread_t threads[NUM_THREADS];
    for(int t=0;t<NUM_THREADS;t++){
        printf("Creating thread %d\n", t);
        pthread_create(&threads[t], NULL, &merge_sort, &arg[t]);
    }    

    // wait for all threads finish the work
    for(int t=0;t<NUM_THREADS;t++)
        pthread_join(threads[t], NULL);
    
    // merge all
    gettimeofday(&st,0);

    for(int i = 2; i <= NUM_THREADS; i *= 2)
    {
        printf("%d sub array(s)\n", NUM_THREADS/i * 2);
        for(int j = 0; j < NUM_THREADS/i; j++)
        {
            int l = arg[j*i].l;
            int m = arg[j*i + i/2 - 1].r;
            int r = arg[(j+1)*i - 1].r;
            printf("merge [%d, %d] and [%d, %d]\n",l, m, m+1, r);
            merge(l, m, r);
        }


    }
    
    gettimeofday(&end,0);
    printf("The merge time for %d threads : %f ms \n", NUM_THREADS, time_substract(&st, &end));
}


void show_arr()
{
    if(MAX > 100)
    {
        printf("array is too long (>100), do not print \n");
        return;
    }
    for(int i = 0; i < MAX; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// fill the array with randome generated integer with range lb ~ up
// random seed will the time() if the rand_seed < 0
void generate_rand_arr(int rand_seed, int lb, int up)
{


    for(int i = 0; i < MAX; i++)
    {
        arr[MAX - 1 - i] = i;
        
    }

}

void usage()
{
	printf("Usage:  <runfile> <l> <thread_num>\n"
		"\tl\t\tarray length=1^l\n\tthread_num\t\t thread number:1,2,4...\n");
}



int main (int argc, char *argv[])
{
    int random_seed = 0;
    char *pend;
    struct timeval st;
    struct timeval end;
    
    if (argc != 3) 
	{
		usage();
		return 1;
	}
    
    power = strtol(argv[1],&pend,10);
    MAX = (long)pow(10,power);
    pend = NULL;
    NUM_THREADS = strtol(argv[2],&pend,10);

    printf("array length : %ld thread number: %d\n", MAX, NUM_THREADS);
    arr = malloc(sizeof(int) * MAX);// array for multi thread
    aug = malloc(sizeof(int) * MAX); // array for one thread
    

    // generate 2 array randmoly
    generate_rand_arr(random_seed, 0, 10*MAX);
    // for(int i = 0; i < MAX; i++)
    // {
    //     arr2[i] = arr[i];
    // }


    // multi-thread merge sort
    printf("befor multithread sorting \n");
    //show_arr(arr, MAX);
    gettimeofday(&st,0);
    //merge_sort(arr, 0, MAX - 1);
    merge_sort_thread();
    gettimeofday(&end,0);
    printf("the multi-thread sorting cost: %f ms\n", time_substract(&st, &end));
    show_arr();


    // // one thread merge sort
    // printf("befor one-thread sorting \n");
 
    // norm_st = clock();
    // //merge_sort(arr, 0, MAX - 1);
    // merge_sort(&(struct msg){0, MAX - 1});
    // norm_end = clock();
    // printf("the one-thread sorting cost: %f ms\n", (double)(norm_end - norm_st)/1000);
    // //show_arr();

    pthread_exit(NULL);
    return 0;
}   