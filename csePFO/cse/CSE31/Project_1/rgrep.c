#include <stdio.h>
#define MAXSIZE 4096

int c = sizeof(char); //stores the size of a char for future use.

/*helper functions for next and previous characters in an array*/

int bool = 0;

char next(char *arr)
{
    return *(arr + c);
}

char previous(char *arr)
{
    return *(arr - c);
}

/*checks what type of pattern it is*/

int plus(char* pattern) /*for plus modifier*/
{
    if(next(pattern) == '+') /*if the next char after pattern[0] is a + it is a + modifier*/
    {
        return 1;
    }

    return 0;
}

int question(char* pattern) /*for question modifier*/
{
    if(next(pattern) == '\?')
    {
        return 1;
    }

    return 0;
}

int escape(char* pattern)
{
    if(previous(pattern) == '\\') /*if the one before the character is a \ it is a \ modifier*/
    {
        return 1;
    }

    return 0;
}

int identifier(char pattern) /*identifies the type of pattern. Returns 1 if the char fulfills one of the cases */
{
    switch(pattern)
    {
        default:
            return 0;
        case '.':
            return 1;
        case '+':
            return 2;
        case '\?':
            return 3;
        case '\\':
            return 4;
    }
}

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */


int matches_leading(char *partial_line, char *pattern) {
  // Implement if desire

  if(*partial_line == *pattern && !(identifier(*pattern))) //if partial_line and pattern are pointing to the same thing, return 1
    {
        return 1;
    }

    if(*pattern == '.' && !(escape(pattern))) //if the pattern has a period
    {
        return 1;
    }

        /*if line and pattern are pointing to the same thing, and escape and identifier return true then
       */
    if((*partial_line == *pattern) && escape(pattern) && identifier(*pattern))
    {
        return 1;
    }

    if(*pattern == '\\')
    {
        if(*partial_line != '\0')
            return matches_leading(partial_line, pattern + c);

        return 0;
    }

    if(question(pattern)) //
    {
        return 1;
    }


    return 0;
}



/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {

    //
    // Implement me
    //

      static int index = 0; //the index of character array, to keep track of pattern depth

            if(*(pattern + 2 * c) == '\?' && *(pattern + 3 * c) == '\0' && *pattern == *(line + 2 * c)) //bb? == aab checks if there is a question mark at the end
            {
                return 1;
            }

//BASE CASE 1

    /*if you reach the null pointer of the pattern array, then a match has been found since you wouldn't go through the whole pattern character array if there weren't
    any consecutive matches found in the line. If a match is found, and the line is a new line resets the pointer and indexes. */

    if(*pattern == '\0') //if you're at the end of the pattern there is a match so return 1
    {
        //if there is a '\n', it means we're at the end of one line and going to another one

            pattern -= index * c; //moves the pointer back to the beginning of the pattern


        index = 0; //resets index
        return 1; //true
    }


//BASE CASE 2

    /*if the pointer is pointing to the end of the line, you have already gone through the line without finding a match so there is no match. Resets pointer and indexes after. */

    if(*line == '\0') //if you're at the end of the line there is  no match so return 0
    {
        return 0;
    }

    if(*line == '\n')
    {
        pattern -= index * c;
        index = 0;
        return 0;
    }


//BASE CASE 3

    //if pattern[0] is equal to '\' and the next character fulfills one of the cases

    if((*pattern == '\\') && identifier(next(pattern))) //identifier(next(pattern)) returns 1 if the next char after '\' fulfills one of the cases
    {
        pattern += c; //increments pattern and index to skip over '/'
        index++;
    }

//checking for matching

    if(matches_leading(line,pattern)) //increments through the pattern and index only if matches_leading is fulfilled
    {

        if(plus(pattern)) //if it matches plus pattern
        {
            int counter = 1;
            if(*pattern == *(pattern + 2 * c))
                counter = 2;
            while(*(line + counter * c) == *pattern && !(*pattern == '.' && !escape(pattern)))
            {
                line += c;
            }
            if(*(pattern ) == '.' && *(pattern + c) == '+')
            {
                //printf("HI");
                while(*line != *(pattern + 2 * c))
                {
                        line += c;
                  //      printf("HI");
                }

                bool = 1; //represents that a .+_ has been found

                return rgrep_matches(line, pattern + 2 * c);
            }
            pattern += c; //skips over the + since + doesnt count as a character in the string
            index++;

            if(bool == 1)
            {
                line+= c;
            }

        }

        if(question(pattern)) //if it matches the question pattern
        {
            // if(*line == *pattern && *(line + c) == *(pattern + 3 * c) && !escape(pattern))
            // {
            //     index+= 3;
            //     return rgrep_matches(line + c, pattern + 3 * c);
            // }
            // else if(*line == *pattern && *(line + c) == *(pattern + 2 * c) && !escape(pattern)) //wo?t == wot
            // {
            //     index+= 2;
            //     return rgrep_matches(line + c, pattern + 2 * c);
            // }
            // else if((*line != *pattern) && *line == *(pattern + 2 * c) && !escape(pattern)) //wo?t = wt
            // {
            //     index +=2;
            //     return rgrep_matches(line, pattern + 2 * c);
            // }
            // else if((*line == *pattern) && *(line + c) == '\0' && (*line == *(pattern + 2 * c) && !escape(pattern))) //a?a == 'a'
            // {
            //     index += 2;
            //     return rgrep_matches(line-= c, pattern + 2 * c);
            // }
            // else
            // {
            //     return 0;
            // }

            if(*line == *pattern && *(line + c) == *(pattern + 2 * c) && !(escape(pattern))) //wo?t == wot either there
            {
                index+= 2;
                return rgrep_matches(line + c, pattern + 2 * c); 
            }
            else if (*line == *pattern && *(line + c) != *(pattern + 2 * c) && !(escape(pattern))) //a?a == a or not there
            {
                index+= 2;
                return rgrep_matches(line, pattern + 2 * c);
            }
            else if(*line != *pattern && *line == *(pattern + 2 * c) && !(escape(pattern))) //wo?t == wt
            {
                index+= 2;
                return rgrep_matches(line, pattern + 2 * c);
            }


            else if (*(pattern + c) == '\\' && *(pattern + 2 * c) == '.') // presence of '\.'
            {
                index += 2;
                return rgrep_matches(line, pattern + c); //since the \\ already increments by one, only increment by one
            }

            else if (*pattern == '.' && *(pattern + c) == '\?') //presence of a '.?', skip over 3
            {
                index += 3;
                return rgrep_matches(line, pattern + 3 * c);
            }

            else if (*(pattern + c) == '\\' && *(pattern + 2 * c) == '.' && *(pattern + 3 * c) == '\?') // presence of a '\.?'
            {
                index += 3;
                return rgrep_matches(line, pattern + 3 * c);
            }
            else
            {
                return 0;
            }


        }

        pattern += c;
        index++;
    }

    //Resets the pattern if partial matches occur so we only get consecutive matches
    else if(*(pattern - index * c) != '\0' && index != 0)
    {
        pattern -= index * c;
        index = 0;
    }

       if(line != '\0')
            line += c;

    return rgrep_matches(line, pattern); //recursive call so it will increment each time
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
