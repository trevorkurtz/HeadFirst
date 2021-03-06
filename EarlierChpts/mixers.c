typedef union {
  float lemon;
  int lime_pieces;
} lemon_lime;

typedef struct {
  float tequila;
  float cointreau;
  lemon_lime citrus;
} margarita;

int main() {
    margarita m = {2.0, 1.0, {2.0}};
    printf("___%2.1f measures of tequila\n%2.1f measures of cointreau\n%2.1f measures of juice\n", 
        m.tequila, m.cointreau, m.citrus.lemon);

    //2.0 measures of tequila
    //1.0 measures of cointreau
    //2.0 measures of juice

    margarita m = {2.0, 1.0, {0.5}};
    printf("%2.1f measures of tequila\n%2.1f measures of cointreau\n%2.1f measures of juice\n", 
        m.tequila, m.cointreau, m.citrus.lemon);

    //2.0 measures of tequila
    //1.0 measures of cointreau
    //0.5 measures of juice
    margarita m= {2.0, 2.0, {.lime_pieces = 1}};
    printf("%2.1f measures of tequila\n%2.1f measures of cointreau\n%i pieces of lime\n", 
        m.tequila, m.cointreau, m.citrus.lime_pieces);

    //2.0 measures of tequila
    //1.0 measures of cointreau
    //1 pieces of lime

}