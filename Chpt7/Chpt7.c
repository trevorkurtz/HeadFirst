#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int NUM_ADS = 7;
char *ADS[] = {
  "William: SBM GSOH likes sports, TV, dining",
  "Matt: SWM NS likes art, movies, theater",
  "Luis: SLM ND likes books, theater, art",
  "Mike: DWM DS likes trucks, sports and bieber",
  "Peter: SAM likes chess, working out and art",
  "Josh: SJM likes sports, movies and theater",
  "Jed: DBM likes theater, books and dining"
};

int sports_no_bieber(char *s)
{
    return strstr(s, "sports") && !strstr(s, "bieber");
}

int sports_or_workout(char *s)
{
    return strstr(s, "sports") && strstr(s, "working out");
}

int ns_theater(char *s)
{
    return strstr(s, "ns") && strstr(s, "theater");
}

int arts_theater_or_dining(char *s)
{
    return strstr(s, "arts") || strstr(s, "theater") || strstr(s, "dining");
}

void find(int (*match)(char*))
{
    int i;
    puts("Search results:");
    puts("---");
    for(i = 0; i < NUM_ADS; i++) {
        if (match(ADS[i])) {
            printf("%s\n", ADS[i]);
        }
    }
}

/* void find()
{
    int i;
    puts("Search results:");
    puts("----------------------");

    for(i=0; i < NUM_ADS; i++)
    {
        if (strstr(ADS[i], "sports")
            && !strstr(ADS[i], "bieber")) {
            printf("%s\n", ADS[i]);
        }
    }
    puts("----------------------");
} */

int compare_scores(const void* score_a, const void* score_b)
{
    int a = *(int*)score_a;
    int b = *(int*)score_b;
    return a - b;
}

int compare_scores_desc(const void* score_a, const void* score_b)
{
    int a = *(int*)score_a;
    int b = *(int*)score_b;
    return b - a;
}

typedef struct {
    int width;
    int height;
} rectangle;

int compare_areas(const void* a, const void* b)
{
    rectangle* ra = (rectangle*)a;
    rectangle* rb = (rectangle*)b;
    return (ra->width * ra->height) - (rb->width * rb->height);
}

int compare_names(const void* a, const void* b)
{
    char** name_a = (char**)a;
    char** name_b = (char**)b;
    return strcmp(*name_a, *name_b);
}

int compare_areas_desc(const void* a, const void* b)
{
    rectangle* ra = (rectangle*)a;
    rectangle* rb = (rectangle*)b;
    return -1 * compare_areas(ra, rb);
}

int compare_names_desc(const void* a, const void* b)
{
    char** name_a = (char**)a;
    char** name_b = (char**)b;
    return compare_names(name_b, name_a);
}

int main()
{
    int scores[] = {543, 323, 32, 554, 11, 3,112};
    int i;

    qsort(scores, 7, sizeof(int), compare_scores_desc);
    puts("These are the scores in order:");
    for (i = 0; i < 7; i++) {
        printf("Score = %i\n", scores[i]);
    }

    char *names[] = {"Karen", "Mark", "Brett", "Molly"};
    qsort(names, 4, sizeof(char*), compare_names);
    puts("These are the names in order:");
    for (i = 0; i < 4; i++) {
        printf("%s\n", names[i]);
    }
    return 0;
}