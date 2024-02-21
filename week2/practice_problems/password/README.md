## Implementation Details
Your function will iterate through the password that’s supplied to it as an argument. Since you have to find at least one lower case letter, one upper case letter, one number and one symbol, you may want to create a boolean variable for each and set each to false before you iterate through the string. If you then find a number, for instance you can set that boolean to true. If all booleans are true at the end of the function, it means all criteria are met, and you would return true.

## Thought Question
How many different passwords do you think can be made that are 8 letters long, can use any of 95 printable ASCII characters?
How to Test Your Code
Your program should behave per the examples below.

`password/ $ ./password
Enter your password: hello
Your password needs at least one uppercase letter, lowercase letter, number and symbol!`


` password/ $ ./password
Enter your password: h3ll(
Your password needs at least one uppercase letter, lowercase letter, number and symbol! `

` password/ $ ./password
Enter your password: h3LL0!
Your password is valid! `