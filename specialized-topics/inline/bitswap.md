Given the following:

    Mask: 0b1010

    Array 1: [0b1010, 0b1100, 0b1111]
    Array 2: [0b0110, 0b0011, 0b0000]

How would you use prompt engineering to generate a transformation procedure that produces the following result for arrays of equal length?

    Array 1: [0b0010, 0b0110, 0b0101]
    Array 2: [0b1110, 0b1001, 0b1010]

``` C
// gcc -std=c99 -Wall -Wextra -o bitswap sample-transformation/bitswap.c

#include <stdio.h>
#include <assert.h>

/*
Generate a function 'conditionalBitSwap' that takes the following arguments:
- 'arr1': an array of char 
- 'arr2': an array of char 
- 'mask': a char that represents a char bit mask.
- 'arrLen': a size_t that represents the length of the array.

Implementation details:
- the conditionalBitSwap function swaps the bits in the same positions
   of the elements of two char arrays, but only if the corresponding bit
   in the mask is set and the bits to be swapped are different.
- the conditionalBitSwap function should not return anything.
Example with 2 elements in the arrays:
    arr1 = [0b1010, 0b1100]
    arr2 = [0b0110, 0b0011]
    mask = 0b1010

    After calling conditionalBitSwap(arr1, arr2, mask), arr1 and arr2 should be:
    arr1 = [0b0010, 0b0110]
    arr2 = [0b1110, 0b1001]
Example with 3 elements in the arrays:
    arr1 = [0b1010, 0b1100, 0b1111]
    arr2 = [0b0110, 0b0011, 0b0000]
    mask = 0b1010

    After calling conditionalBitSwap(arr1, arr2, mask), arr1 and arr2 should be:
    arr1 = [0b0010, 0b0110, 0b0101]
    arr2 = [0b1110, 0b1001, 0b1010]

*/

void conditionalBitSwap(char arr1[], char arr2[], char m, size_t arrLen) {
    // iterate over the arrays
    for (size_t i = 0; i < arrLen; i++) {
        // get the bits to be swapped
        char bitsToSwap = arr1[i] ^ arr2[i];

        // get the bits to be swapped that are different
        char bitsToSwapDiff = bitsToSwap & m;

        // swap the bits
        arr1[i] = arr1[i] ^ bitsToSwapDiff;
        arr2[i] = arr2[i] ^ bitsToSwapDiff;
    }
}

/*
 Implement a robust test for the 'conditionalBitSwap' function named 'test_conditionalBitSwap'. The test should:
- test three (3) different cases with mask values of 0b1010, 0b0011, 0b1100 and array sizes 2, 3, 4
- use assert statements to check that the output of the function is as expected
- print a message indicating that all tests pass if all tests pass, along with a formatted mask value and array size
*/

void test_conditionalBitSwap() {
    // Test case 1
    char arr1_1[] = {0b1010, 0b1100};
    char arr2_1[] = {0b0110, 0b0011};
    char mask_1 = 0b1010;
    size_t arrLen_1 = sizeof(arr1_1) / sizeof(arr1_1[0]);
    conditionalBitSwap(arr1_1, arr2_1, mask_1, arrLen_1);
    assert(arr1_1[0] == 0b0010);
    assert(arr1_1[1] == 0b0110);
    assert(arr2_1[0] == 0b1110);
    assert(arr2_1[1] == 0b1001);

    // Test case 2
    char arr1_2[] = {0b1010, 0b1100, 0b1111};
    char arr2_2[] = {0b0110, 0b0011, 0b0000};
    char mask_2 = 0b0011;
    size_t arrLen_2 = sizeof(arr1_2) / sizeof(arr1_2[0]);
    conditionalBitSwap(arr1_2, arr2_2, mask_2, arrLen_2);
    assert(arr1_2[0] == 0b1010);
    assert(arr1_2[1] == 0b1111);
    assert(arr1_2[2] == 0b1100);
    assert(arr2_2[0] == 0b0110);
    assert(arr2_2[1] == 0b0000);
    assert(arr2_2[2] == 0b0011);

    // Test case 3
    char arr1_3[] = {0b1010, 0b1100, 0b1111, 0b0000};
    char arr2_3[] = {0b0110, 0b0011, 0b0000, 0b1111};
    char mask_3 = 0b1100;
    size_t arrLen_3 = sizeof(arr1_3) / sizeof(arr1_3[0]);
    conditionalBitSwap(arr1_3, arr2_3, mask_3, arrLen_3);
    assert(arr1_3[0] == 0b0110);
    assert(arr1_3[1] == 0b0000);
    assert(arr1_3[2] == 0b0011);
    assert(arr1_3[3] == 0b1100);
    assert(arr2_3[0] == 0b1010);
    assert(arr2_3[1] == 0b1111);
    assert(arr2_3[2] == 0b1100);
    assert(arr2_3[3] == 0b0011);

}

int main() {
    // call the test function
    test_conditionalBitSwap();

    printf("All tests pass\n");

    return 0;
}
```








