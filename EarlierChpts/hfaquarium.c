typedef struct {
    unsigned int first_visit:1;
    unsigned int come_again:1;
    unsigned int fingers_lost:4;
    unsigned int shark_attack:1; 
    unsigned int days_a_week:3;
} survey;




struct exercise {
    const char *description;
    float duration;
};

struct meal {
    const char *ingredients;
    float weight;
};

struct preferences {
    struct meal food;
    struct exercise exercise;
};

struct fish {
    const char *name;
    const char *species;
    int teeth;
    int age;
    struct preferences care;
};

struct fish snappy = {"Snappy", "Piranha", 0, 0, 
    {{"meat", 0.2},{"swim in the jacuzzi", 7.5}}};

void label(struct fish a)
{
    printf("Name:%s\nSpecies:%s\n%i years old, %i teeth\n",
        a.name, a.species, a.teeth, a.age);
    printf("Feed with %2.2f lbs of %s and allow to %s for %2.2f hours\n",
        a.care.food.weight, a.care.food.ingredients,
        a.care.exercise.description, a.care.exercise.duration);
}