# Generative Chaotic Literature
### Nigh-incomprehensible stories written with Markov Chains in C++
---------------------------------------

This is a simple C++ implementation of a Markov Chain, used to generate arbitrary text using a supplied "corpus" of material. I am currently using it to generate a title, and three paragraphs of text, which are output to stdout. As it stands, you will need to supply your own corpus, by creating a directory called "corpus" at the root of the repository. After creating this directory, fill it with all manner of well-formatted text files.

In this case, "well-formatted" is kind of ambiguous. The generator will work on most any plaintext. However, to see the best results, I would suggest formatting the files such that each line is a single sentence with a period at the end. There can be an arbitrary amount of blank lines, these will not be processed by the chain.

For testing purposes, I have been downloading plaintext files of books from [Project Gutenberg](http://gutenberg.org/wiki/Main_Page) and using a series of vim commands to format the files how I want. The most useful commands have been the following:

`:%s/.\zs\n\ze./` which finds all newline characters surrounded by a regular character and eliminates the newline; and
`:%s/\.\ /\.\r/g` which finds all periods that precede a space and turns that space into a newline.

Of course, you can use whatever means you wish to achieve the desired formatting.

---------------------------------------

## Compilation and Execution

To run the generator, first compile it with `make`, then either run `make run` or execute it manually with `./markovbook`.
