// #include<iostream>
#include <stdio.h>
#include <string.h>
#define WEEKS 4
#define DAYS 5
// using namespace std;
// here the struct WorkingWeek

int weeks_number[4] = {0,0,0,0};

struct WorkingWeek{
    int hours[DAYS];
};


typedef struct WorkingWeek WW;

// here the struct Worker


struct Worker{
    char name[50];
    WW weeks[WEEKS];
};



typedef struct Worker W;

// here the functions

void table(W *w, int n){
    int i;
    int j;
    int k;
    printf("Wor\t");
        printf("1\t2\t3\t4\tTotal\n");

    for( i = 0; i<n; i++){
        //loop for workers
        int total= 0;
        // cout<<w[i].name<<"\t";
        printf("%s\t", w[i].name);
        int week[4] = {0,0,0,0};

        for( j = 0; j<WEEKS; j++){
            //Weeks for the worker[i];
            for( k = 0; k<DAYS; k++){
                //working hours for the days of the WEEK number j
                week[j]+=w[i].weeks[j].hours[k];


            }
            // cout<<week[j]<<"\t";
            printf("%d\t", week[j]);
            total+=week[j];

        }



        // cout<<total<<endl;
        printf("%d\n", total);
    }
}

int maxWeek(W *w){
     //sort the array weeks_number
        //this function is u get a worker adn then print
        //the week where he worked more
    int week[4] = {0,0,0,0};
     for(int  j = 0; j<WEEKS; j++){
            //Weeks for the worker[i];
            for(int k = 0; k<DAYS; k++){
                //working hours for the days of the WEEK number j
                week[j]+=w->weeks[j].hours[k];
            }
        }
    //now that we have the total of each week
    int best_week = 0;

    for(int i = 0; i<4; i++)
    {
        if(week[i] > week[best_week])
        {
            best_week = i;
        }
    }
    return best_week+1;
}



int
main ()
{
  int n;
  scanf ("%d", &n);
  W workers[n];
  int i;
  for (i = 0; i < n; ++i)
    {
      scanf ("%s", workers[i].name);
      int j;
      for (j = 0; j < WEEKS; ++j)
	{
	  int k;
	  for (k = 0; k < DAYS; ++k)
	    {
	      scanf ("%d", &workers[i].weeks[j].hours[k]);
	    }

	}
    }
  printf ("TABLE\n");
  table (workers, n);
  printf ("MAX WEEK OF WORKER: %s\n", workers[n / 2].name);
  printf ("%d\n", maxWeek (&workers[n / 2]));
  return 0;
}

