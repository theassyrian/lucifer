#include <stdio.h>
#include <assert.h>
#include <string.h>
#define MAXTOKENLEN 255
#define MAXTOKENS 255

struct token {
	char type;
	char string[MAXTOKENLEN];
};

struct token stack[MAXTOKENS];
struct token this;
const char *input;

void classify_string()
{
	static const char *qualifiers[] = {
		"const",
		"static",
		"volatile",
		"long",
		"unsigned"
	};

	static const char *types[] = {
		"struct",
		"enum",
		"union",
		"int",
		"char",
		"float",
		"double",
	};

	for (int i = 0; i < sizeof(qualifiers) / (sizeof *qualifiers); ++i) {
		if (!strcmp(qualifiers[i], this.string)) {
			this.type = 'q';
			return;
		}
	}

	for (int i = 0; i < sizeof(types) / (sizeof *types); ++i) {
		if (!strcmp(types[i], this.string)) {
			this.type = 't';
			return;
		}
	}

	this.type = 'i';
	return;

}

void gettoken()
{
	const char *st = input;
	const char *en = input;

	int i;
	for (i = 0; *en && *en != ' '; ++en, ++i) {
		this.string[i] = *en;
	}
	this.string[i] = '\0';

	if (st == en)
		return;

	/* Single character. */
	if (en - st == 1 
		/* Not [0-9] */
		&& !(*st > 47 && *st < 58)
		/* Not [A-Z] */
		&& !(*st > 64 && *st < 91)
		/* Not [a-z] */
		&& !(*st > 96 && *st < 123)) {

		this.type = *st;
	} else {
		
		classify_string();
	}

	printf("Token: %s is a %c\n", this.string, this.type);

	input = *en? en + 1 : en;
}

void read_to_first_identifier()
{

}

int main(int argc, char **argv)
{
	assert(argc == 2);
	input = argv[1];
	
	while (*input)
		gettoken();

}
