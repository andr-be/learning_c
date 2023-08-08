#include <stdbool.h>
#include <stdio.h>

bool is_consec(int n, int a[n])
{
    for (int i = 0; i < n - 1; i++)
        if (a[i + 1] - a[i] != 1) return false; 

    return true;
}

int x_of_a_kind(int n, int a[n]) 
{
    int duplicates = 0, max = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (a[i] == a[j]) 
                duplicates++;
        
        max = (duplicates > max) ? duplicates : max;
        duplicates = 0;
    }
    return max;
}

// counts pairs of posiive numbers in an array of length n
int count_pairs(int n, int a[n])
{
    int found_pairs = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++)
            if (a[i] == a[j] && a[i] > -1 && a[j] > -1) {
                found_pairs++; 
                a[i] = a[j] = -1;
                break;
            }
    }

    return found_pairs;
}

int main(void)
{
    int a[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int b[9] = { 1, 2, 4, 3, 5, 6, 7, 8, 9 };

    int five[5] = { 1, 1, 1, 1, 1 };
    int four[5] = { 1, 1, 1, 1, 5 };
    int three[5] = { 1, 1, 1, 4, 5 };
    int two[5] = { 1, 1, 3, 4, 5 };
    int one[5] = { 1, 2, 3, 4, 5 };

    bool x = is_consec(9, a),
         y = is_consec(9, b);

    printf("x: %d, y: %d\n", x, y);

    printf("11111: %d\n", count_pairs(5, five));
    printf("11115: %d\n", count_pairs(5, four));
    printf("11145: %d\n", count_pairs(5, three));
    printf("11345: %d\n", count_pairs(5, two));
    printf("12345: %d\n", count_pairs(5, one));

    return 0;
}