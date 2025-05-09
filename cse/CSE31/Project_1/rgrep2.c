#include <stdio.h>
#define MAXSIZE 4096

char next_char(char *string) {
	return *(string + sizeof(char));
}

char prev_char(char *string) {
	return *(string - sizeof(char));
}

//Accepts char, not pointer
int is_operator(char pattern) {
	switch(pattern) {
		case '.' :
			return 1;
		case '\\' :
			return 2;
		case '+' :
			return 3;
		case '\?' :
			return 4;
		default :
			return 0;
	}
}

int plus_modified(char *pattern) {
	if(next_char(pattern) == '+')
		return 1;
	return 0;
}

int question_modified(char *pattern) {
	if(next_char(pattern)  == '\?')
		return 1;
	return 0;
}

int escape_modified(char *pattern) {
	if(prev_char(pattern) == '\\')
		return 1;
	return 0;
}

/**
 * You can use this recommended helper function 
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */

int matches_leading(char *line, char *pattern) {
	//Check direct match
	if(*line == *pattern && !is_operator(*pattern)) {
		return 1;
	}
	//Check wildcard match
	if(*pattern == '.' && !escape_modified(pattern)) {
		return 1;
	}
	//Check escaped operator match
	if(*line == *pattern && is_operator(*pattern) && escape_modified(pattern)) {
		return 1;
	}
	//Check escape character
	if(*pattern == '\\')
		return matches_leading(line, pattern + sizeof(char));
	//Check for absent case of ? operator
	if(question_modified(pattern))
		return 1;
	return 0;
}

/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {

	static int pattern_depth = 0;



	//Base cases
	if(*pattern == '\0') {
		//Reset pattern for new line	
		if(*line == '\n') {
			pattern -= pattern_depth * sizeof(char);
		}
		pattern_depth = 0;
		return 1;
	}
	
	if(*line == '\0')
		return 0;

	//Reset pattern for new line	
	if(*line == '\n') {
		pattern -= pattern_depth * sizeof(char);
		pattern_depth -= pattern_depth;
		return 0;
	}

	//Check for escape
	if((*pattern == '\\') && is_operator(next_char(pattern))) {
		pattern += sizeof(char);
		pattern_depth++;
	}



	//Check for match
	if(matches_leading(line, pattern)) {
		//For + modifier
		if(plus_modified(pattern)) {
			int chars_before = 1;
			if(*pattern == *(pattern + 2 * sizeof(char)))
				chars_before = 2;
			//Go to next nonmatching character
			//Stops one before because there is a line increment at the end of rgrep_matches
			while(*(line + chars_before * sizeof(char)) == *pattern && !(*pattern == '.' && !escape_modified(pattern)))
				line += sizeof(char);
			//Handle .+
			if(*pattern == '.' && escape_modified(pattern)) {
				char wildcard = *line;
				while(*(line + chars_before * sizeof(char)) == wildcard)
					line += sizeof(char);			
			}
			if(*pattern == '.' && !escape_modified(pattern)) {
				//while(*(line + chars_before * sizeof(char)) != *(pattern + 2 * sizeof(char)))
				while(!matches_leading(line + chars_before * sizeof(char), pattern + 2 * sizeof(char))){
					line += sizeof(char);
					if((*line == '\0' || *line == '\n') && *(pattern + 2 * sizeof(char)) != '\0')
						return 0;
				}
			}
			//Compensate for the character that the operator took
			pattern += sizeof(char);
			pattern_depth++;
		}
		//For ? modifier
		if(question_modified(pattern)) {
			//
			if (*pattern == '.' && !escape_modified(pattern) && escape_modified(pattern + 3 * sizeof(char)) && *line == *(pattern + 3 * sizeof(char)) && *(line + sizeof(char)) != *(pattern + 3 * sizeof(char))) {
				pattern_depth += 4;
				return rgrep_matches(line + sizeof(char), pattern + 4 * sizeof(char));
			}
			//
			else if(*pattern == '.' && !escape_modified(pattern) && *line == *(pattern + 2 * sizeof(char))) {
				pattern_depth += 2;
				return rgrep_matches(line, pattern + 2 * sizeof(char));
			}
			//
			else if(*pattern == '.' && !escape_modified(pattern) && *line != *(pattern + 2 * sizeof(char))) {
				pattern_depth += 2;
				return rgrep_matches(line + sizeof(char), pattern + 2 * sizeof(char));
			}
			//
			else if(*line == *pattern && *line == *(pattern + 2 * sizeof(char))) {
				pattern_depth += 2;
				return rgrep_matches(line, pattern + 2 * sizeof(char));
			}
			//
			else if(*line == *pattern && next_char(line) == *(pattern + 2 * sizeof(char))){}
			//
			else if(*line == *pattern && next_char(line) != *(pattern + 2 * sizeof(char)) && *line != *(pattern + 2 * sizeof(char)))
				{}//return 0;
			//
			else if(*line != *pattern && *line != *(pattern + 2 * sizeof(char)))
				return 0;
			//
			else if(*line == *pattern && *pattern == '.' && escape_modified(pattern)){} 	
			//
			else if(!(*pattern == '.' && !escape_modified(pattern)) || *line != *pattern)
				line -= sizeof(char);
			//Compensate for the character that the operator took
			pattern += sizeof(char);
			pattern_depth++;
		}
		pattern += sizeof(char);
		pattern_depth++;
	}

	//Reset the pattern on partial match so that we only get contiguous matches
	else if(pattern_depth != 0 && *(pattern - pattern_depth * sizeof(char)) != '\0') {
		pattern -= pattern_depth * sizeof(char);
		pattern_depth -= pattern_depth;
	}

	//if(*line != '\n')
		line += sizeof(char);

	

	//Recurse
	return rgrep_matches(line, pattern);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}