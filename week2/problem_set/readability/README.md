## Specification
Design and implement a program, readability, that computes the Coleman-Liau index of text.

Implement your program in a file called readability.c in a directory called readability.
Your program must prompt the user for a string of text using get_string.
Your program should count the number of letters, words, and sentences in the text. You may assume that a letter is any lowercase character from a to z or any uppercase character from A to Z, any sequence of characters separated by spaces should count as a word, and that any occurrence of a period, exclamation point, or question mark indicates the end of a sentence.
Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.
If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of giving the exact index number. If the index number is less than 1, your program should output "Before Grade 1".
## Getting User Input
Let’s first write some C code that just gets some text input from the user, and prints it back out. Specifically, implement in readability.c a main function that prompts the user with "Text: " using get_string and then prints that same text using printf. And remember, as you work through this program, that if you make use of any library functions, be sure to #include any corresponding header files.

The program should behave per the below.

$ `./readability


Text: In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since.
In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since.`
## Letters
Now that you’ve collected input from the user, let’s begin to analyze that input by first counting the number of letters in the text. Consider letters to be uppercase or lowercase alphabetical character, not punctuation, digits, or other symbols.

Add to readability.c, below main, a function called count_letters that takes one argument, a string of text, and that returns an int, the number of letters in that text. Be sure to add the function’s prototype, too, atop your file, so that main knows how to call it. Odds are the prototype should resemble the below:

` int count_letters(string text) `
Then call that function in main so that, instead of printing out the text itself, your program now prints the number of letters in the text.

The program should now behave per the below.

$ `./readability


Text: Alice was beginning to get very tired of sitting by her sister on the bank, and of having nothing to do: once or twice she had peeped into the book her sister was reading, but it had no pictures or conversations in it, "and what is the use of a book," thought Alice "without pictures or conversation?"


235 letters`

## Words
The Coleman-Liau index cares not only about the number of letters but also about the number of words in a sentence. For the purpose of this problem, we’ll consider any sequence of characters separated by a space to be a word (so a hyphenated word like "sister-in-law" should be considered one word, not three).

Add to readability.c, below main, a function called count_words that takes one argument, a string of text, and that returns an int, the number of words in that text. Be sure to add the function’s prototype, too, atop your file, so that main knows how to call it. (We leave its prototype to you!)

Then call that function in main so that your program also prints the number of words in the text.

You may assume that a sentence:

    will contain at least one word;
    will not start or end with a space; and
    will not have multiple spaces in a row.
    You are, of course, welcome to attempt a solution that will tolerate multiple spaces between words or indeed, no words!

The program should now behave per the below.

$ `./readability


Text: It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him.


250 letters


55 words

`
## Sentences
The last piece of information that the Coleman-Liau formula cares about, in addition to the number of letters and words, is the number of sentences. Determining the number of sentences can be surprisingly trickly. You might first imagine that a sentence is just any sequence of characters that ends with a period, but of course sentences could end with an exclamation point or a question mark as well. But of course, not all periods necessarily mean the sentence is over. For instance, consider the sentence below.

Mr. and Mrs. Dursley, of number four Privet Drive, were proud to say that they were perfectly normal, thank you very much.
This is just a single sentence, but there are three periods! For this problem, we’ll ask you to ignore that subtlety: you should consider any sequence of characters that ends with a . or a ! or a ? to be a sentence (so for the above “sentence”, you should count it as three sentences). In practice, sentence boundary detection needs to be a little more intelligent to handle these cases, but we’ll not worry about that for now.

Add to readability.c, below main, a function called count_sentences that takes one argument, a string of text, and that returns an int, the number of sentences in that text. Be sure to add the function’s prototype, too, atop your file, so that main knows how to call it. (We again leave its prototype to you!)

Then call that function in main so that your program also prints the number of sentences in the text.

The program should now behave per the below.

$ ` ./readability


Text: When he was nearly thirteen, my brother Jem got his arm badly broken at the elbow. When it healed, and Jem's fears of never being able to play football were assuaged, he was seldom self-conscious about his injury. His left arm was somewhat shorter than his right; when he stood or walked, the back of his hand was at right angles to his body, his thumb parallel to his thigh.


295 letters


70 words


3 sentences`
## Putting it All Together
Now it’s time to put all the pieces together! Recall that the Coleman-Liau index is computed using the formula:

` index = 0.0588 * L - 0.296 * S - 15.8 `
where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.

Modify main in readability.c so that instead of outputting the number of letters, words, and sentences, it instead outputs (only) the grade level as defined by the Coleman-Liau index (e.g. "Grade 2" or "Grade 8" or the like). Be sure to round the resulting index number to the nearest int!

## Hints
If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output "Grade 16+" instead of outputting an exact index number. If the index number is less than 1, your program should output "Before Grade 1".