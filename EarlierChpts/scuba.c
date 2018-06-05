#include <stdio.h>

  typedef struct {
  float tank_capacity;
  int tank_psi;
  const char *suit_material;
} equipment;

  typedef struct scuba {
  const char *name;
  equipment kit;
} diver;

typedef struct {
   const char *name;
   const char *species;
   int age; 
} turtle;


void badge(diver d)
{
  printf("Name: %s Tank: %2.2f(%i) Suit: %s\n",
    d.name, d.kit.tank_capacity, d.kit.tank_psi, d.kit.suit_material);
}

void happy_birthday(turtle *t)
{
    //(*t).age = (*t).age + 1;
    t->age = t->age + 1;
    printf("Happy Birthday %s! You are now %i years old!\n",
         //(*t).name, (*t).age);
         t->name, t->age);
}

int main()
{
  diver randy = {"Randy", {5.5, 3500, "Neoprene"}};
  badge(randy);
  return 0;
}

