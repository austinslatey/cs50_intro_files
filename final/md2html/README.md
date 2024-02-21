# Markdown to HTML Converter Documentation
## Introduction
The Markdown to HTML Converter is a command-line program that allows you to convert Markdown files into HTML files. It parses the Markdown syntax and generates the corresponding HTML output. This documentation provides an overview of how to use the converter and explains the available command-line options.

## Usage
`markdown2html [options] input_file output_file`


The Markdown to HTML Converter supports the following command-line options:

`-h, --help: Display the help message and usage instructions.
-v, --version: Display the version information of the converter.`

input_file:

The path to the input Markdown file that you want to convert to HTML.
output_file:

The path to the output HTML file where the converted HTML will be written. If the file already exists, it will be overwritten.


### Convert a Markdown file to HTML:

`markdown2html input.md output.html`


This command will convert the input.md file to HTML and write the output to output.html.

### Display help message:
`markdown2html --help`


This command will display the help message and usage instructions.


### Display version information:

`markdown2html --version`


This command will display the version information of the converter.

## Output
The Markdown to HTML Converter will generate an HTML file containing the converted content of the input Markdown file. The output file will have the same structure and hierarchy as the Markdown file, with the appropriate HTML tags for each Markdown element.

## Error Handling
If any errors occur during the conversion process, the Markdown to HTML Converter will display informative error messages indicating the nature of the error. Please ensure that the input Markdown file follows valid Markdown syntax to avoid potential parsing errors.