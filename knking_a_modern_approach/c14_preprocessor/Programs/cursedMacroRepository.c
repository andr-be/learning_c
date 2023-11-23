#include <stdio.h>
#include <math.h>

#define DISP( f, x )     printf(#f "(%g) = %g\n", x, f(x))
#define DISP2( f, x, y ) printf(#f "(%g, %g) = %g\n", x, y, f(x,y))

#define STRINGIZE(x) #x
#define EXPAND_AND_STRINGIZE(x) STRINGIZE(x)
#define LINE_FILE "Line " EXPAND_AND_STRINGIZE(__LINE__) " of file " __FILE__

#include <stdio.h>

#define CHECK( x, y, n )    ((x) >= 0 && (x) < n && (y) >= 0 && (y) < n)

#define MEDIAN( x, y, z )   ((x)>(y) ?                                \
                            ((y)>(z) ? (y) : ((x)>(z) ? (z) : (x))) : \
                            ((x)>(z) ? (x) : ((y)>(z) ? (z) : (y))))  \

#define POLYNOMIAL( x )     ( +3 * ((x) * (x) * (x) * (x) * (x))      \
                              +2 * ((x) * (x) * (x) * (x))            \
                              -5 * ((x) * (x) * (x))                  \
                              -1 * ((x) * (x))                        \
                              +7 * ((x))                              \
                              -6 )

#define ERROR(f_str, idx)   \
fprintf(stderr, f_str, idx) 

double add_together(double x, double y);
double times_ten(double x);

int main(void)
{
    DISP(times_ten, 16.0);
    DISP2(add_together, 2.0, 3.0);

    const char *str = LINE_FILE;

    printf("%s\n", str);
    printf("%s\n", CHECK(2,4,6)?"True!":"False!");
    printf("%d\n", MEDIAN( MEDIAN(CHECK(2,4,6),3,5),MEDIAN(3,5,7),MEDIAN(2,4,POLYNOMIAL(1))));
    printf("%d\n", POLYNOMIAL(1));

    ERROR("ERROR AT: %d", 1);

    return 0;
}

double add_together(double x, double y)
{
    return x + y;
}

double times_ten(double x)
{
    return 10 * x;
}