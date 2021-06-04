// Bstein326

// This is so we can have access to functions such as scanf() and printf()
// scanf() is to take in user input and printf() is to print.
// scanf: https://www.cplusplus.com/reference/cstdio/scanf/
// printf: https://www.cplusplus.com/reference/cstdio/printf/
#include <stdio.h>

// This is the start of the code and it might confuse you
// that I put `int main(void)` instead of `int main()`
// the reason for that is in C when you declare a function
// with just the parentheses you are not specifying how
// many parameters there are. In C++ and other languages
// by default they make functions with just parentheses
// have zero parameters, but in C this is undefined behavior
// because we never told the compiler that this function
// had no parameters.
//
// `int function_name(void);` declares a function with no parameters.
// `int function_name();` declares a function with an unknown number of parameters.
int main(void) {
    // This is our int array of 5 elements
    int scores[5];

    // This for loop will iterate 5 times so we can take user input
    for (int i = 0; i < 5; ++i) {
        // This scanf will take in user input and store it to the array
        scanf("%d", &scores[i]);
    }

    // These two variables are going to be used for our max and min values
    // in the array of user input. It is important that you declare them equal
    // to values in the array because if you put 0 in there the code will not
    // work all of the time.
    // Here is an example of it not working if you put 0 for it:
    //
    // int scores[5] = {-5, -3, -1, -3, -4}
    // int highest = 0;
    // int lowest = 0;
    //
    // after the for loop the values would be:
    //
    // highest == 0 and lowest == -5.
    //
    // This is because all of the values are less then 0 so highest will never
    // get changed. The same can happen in other cases too.
    int highest = scores[0];
    int lowest = scores[0];

    // This will iterate through the user input array and will make sure
    // that the highest and lowest variables are assigned properly
    for (int i = 0; i < 5; ++i) {
        // This if statement compares the value at index i of the scores
        // array to the current value of the highest variable.
        if (scores[i] > highest) {
            // If the condition was true then the value of highest
            // will get changed to the value of the scores array
            // at index i
            highest = scores[i];
        }
        // This if statement compares the value at index i of the scores
        // array to the current value of the lowest variable.
        if (scores[i] < lowest) {
            // If the condition was true then the value of lowest
            // will get changed to the value of the scores array
            // at index i
            lowest = scores[i];
        }
    }

    // This then prints out the values of highest and lowest
    // Somethings that might confuse you are the %d and the \n
    // the \n means a new line and therefore will print a new line
    // the %d is a special thing that means it will expect an int to
    // be passed in after the "".
    //
    // There are many codes lets say I had a string I would do this:
    //
    // char *x = "this is a string";
    //
    // printf("%s", x);
    //
    // if I wanted to print the string, check this out for more details:
    // https://www.cplusplus.com/reference/cstdio/printf/
    printf("Highest: %d\nLowest: %d\n", highest, lowest);

    return 0;
}
