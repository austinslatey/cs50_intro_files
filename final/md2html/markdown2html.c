#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256
#define MAX_OUTPUT_LENGTH 4096

// Function to convert a Markdown heading to HTML
void convertHeading(const char *line, char *output)
{
	int level = 0;
	while (line[level] == '#')
	{
		level++;
	}
	snprintf(output, MAX_LINE_LENGTH, "<h%d>%s</h%d>\n", level, line + level + 1, level);
}

// Function to convert a Markdown list item to HTML
void convertListItem(const char *line, char *output)
{
	snprintf(output, MAX_LINE_LENGTH, "<li>%s</li>\n", line + 2);
}

// Function to convert a .md link to HTML
void convertLink(const char *line, char *output)
{
	char *textStart = strchr(line, '[');
	char *textEnd = strchr(line, ']');
	char *urlStart = strchr(line, '(');
	char *urlEnd = strchr(line, ')');
	*textEnd = '\0';
	*urlEnd = '\0';
	snprintf(output, MAX_LINE_LENGTH, "<a href=\"%s\">%s</a>\n", urlStart + 1, textStart + 1);
}

// Function to convert a .md file to HTML
void convertMarkdownToHTML(const char *inputFilename, const char *outputFilename)
{
	FILE *inputFile = fopen(inputFilename, "r");
	if (!inputFile)
	{
		printf("Error: Unable to open input file '%s'\n", inputFilename);
		return;
	}

	FILE *outputFile = fopen(outputFilename, "w");
	if (!outputFile)
	{
		printf("Error: Unable to open output file '%s'\n", outputFilename);
		fclose(inputFile); // Close the input file
		return;
	}

	char line[MAX_LINE_LENGTH];
	char output[MAX_OUTPUT_LENGTH];

	// Flag to indicate if the previous line was a heading or list item
	int isPreviousLineHeading = 0;
	int isPreviousLineListItem = 0;

	while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL)
	{
		if (line[0] == '#')
		{
			if (isPreviousLineListItem)
			{
				fprintf(outputFile, "</li>\n");
				isPreviousLineListItem = 0;
			}

			convertHeading(line, output);
			fprintf(outputFile, "%s", output);
			isPreviousLineHeading = 1;
		}
		else if (line[0] == '-')
		{
			if (isPreviousLineHeading)
			{
				fprintf(outputFile, "</h%d>\n", isPreviousLineHeading);
				isPreviousLineHeading = 0;
			}

			convertListItem(line, output);
			fprintf(outputFile, "%s", output);
			isPreviousLineListItem = 1;
		}
		else if (line[0] == '[')
		{
			if (isPreviousLineHeading)
			{
				fprintf(outputFile, "</h%d>\n", isPreviousLineHeading);
				isPreviousLineHeading = 0;
			}

			convertLink(line, output);
			fprintf(outputFile, "%s", output);
		}
		else
		{
			if (isPreviousLineListItem)
			{
				fprintf(outputFile, "</li>\n");
				isPreviousLineListItem = 0;
			}

			if (line[0] != '\n') // Skip empty lines
			{
				fprintf(outputFile, "<p>%s</p>\n", line); // Wrap regular text in <p> tags
			}
		}
	}

	if (isPreviousLineHeading)
	{
		fprintf(outputFile, "</h%d>\n", isPreviousLineHeading);
	}
	else if (isPreviousLineListItem)
	{
		fprintf(outputFile, "</li>\n");
	}

	fclose(inputFile);
	fclose(outputFile);
	printf("Conversion method completed. HTML file '%s' generated.\n", outputFilename);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s input_file output_file\n", argv[0]);
		return 1;
	}

	const char *inputFilename = argv[1];
	const char *outputFilename = argv[2];

	convertMarkdownToHTML(inputFilename, outputFilename);

	return 0;
}