/*
 * File:    permute.c
 * Author:  Scott Douglass
 * Date:    2025-07-21
 * Purpose: Generate and print all permutations of a given string using recursion and backtracking.
 * 
 * Description:
 * This program demonstrates how to recursively generate all possible permutations 
 * of a string using a swapping technique. It uses a helper `swap` function and a 
 * `permute` function that explores each combination by fixing one character and 
 * permuting the rest. Backtracking is applied to restore the original state.
 * 
 * Example Output:
 * cat
 * cta
 * act
 * atc
 * t a c
 * t c a
 */

#include <stdio.h>
#include <string.h>

// Swap the values pointed to by x and y
void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

// Recursively generate permutations of the string from index l to r
void permute(char *str, int l, int r,int *count) {
    if (l == r) {
        // Base case: if the left index equals the right index, a permutation is complete
        printf("%s\n", str);
        (*count)++; // increment the counter
    } else {
        for (int i = l; i <= r; i++) {
            // Swap the current index with the loop index
            swap((str + l), (str + i));
            // Recurse on the rest of the string
            permute(str, l + 1, r, count);
            // Backtrack to restore original string before next iteration
            swap((str + l), (str + i));
        }
    }
}

int main() {
    char word[] = "catkjgdgkjnfjngd";            // String to permute
    int n = strlen(word);           // Get length of the string
    int count=0;
    permute(word, 0, n - 1,&count);        // Generate all permutations
    printf("%i! = %i\n",n,count);
    return 0;
}
