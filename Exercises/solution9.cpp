
#include<stdio.h>
#include<stdbool.h>
typedef struct Film{
    char name[100];
    int time;
    float price;
    bool discount;
} Film;

typedef struct FilmFestival{
    char name[100];
    char place[100];
    Film films[100];
    int no;
} FilmFestival;

void print(FilmFestival ff){
    printf("%s %s\n", ff.name, ff.place);
    for(int i = 0; i<ff.no; i++){
        printf("%s %d %.2f\n", ff.films[i].name, ff.films[i].time, ff.films[i].price);
    }
}

void bestFestival(FilmFestival ff[],int n){

    int best_index = 0;
    int most_discounts = 0;
    for(int i=0; i<n; i++){
    int current_discounts = 0;
    for(int j = 0; j<ff[i].no; j++){
        if(ff[i].films[j].discount)
            current_discounts++;
    }

        if(most_discounts < current_discounts)
        {
             best_index = i;
            most_discounts = current_discounts;
        }
    }

    printf("Najdobar festival: %s %s", ff[best_index].name, ff[best_index].place);
}


int main()
{
	int i, j, n, broj;
	FilmFestival ff[50];
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		/* name of the festival */
		scanf("%s", ff[i].name);
        /* place it is held */
		scanf("%s", ff[i].place);
		/* number of movies */
		scanf("%d", &ff[i].no);

		for (j = 0; j < ff[i].no; j++){
			scanf("%s", ff[i].films[j].name);  		/* title of the movie */
			scanf("%d", &ff[i].films[j].time); 		/* duration */
			scanf("%f", &ff[i].films[j].price); 	/* price */
            scanf("%d", &ff[i].films[j].discount);	/* discount */
		}
	}

    for(i=0; i<n; ++i){
    	print(ff[i]);
    }

    bestFestival(ff, n);


	return 0;
}
