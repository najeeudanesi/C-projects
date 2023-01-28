#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int arg_index = 0;
int max_rounds = 0;
int rounds = 0;
int flag = 0;

//function to check args when passed on initialization
void checkArgs(int argc, char **argv)
{
    if (argc > 2)
    {
        if (argv[1][1] == 'c')
        {
            arg_index = 2;
        }
        else if (argv[1][1] == 't')
        {
            max_rounds = atoi(argv[2]);
        }

        if (argc > 3)
        {
            if (argv[3][1] == 'c')
            {
                arg_index = 4;
            }
            else if (argv[3][1] == 't')
            {
                max_rounds = atoi(argv[4]);
            }
        }
    }
}

//function for get input
char *getInput()
{
    char buffer[999];

    flag = read(0, buffer, 5);

    if (flag == 0)
    {
        rounds = max_rounds;    //handling ctrl +d
    }

    buffer[4] = '\0';
    char *r = buffer;
    return r;
}
//check if guess is a valid guess
int is_valid(char *guess)
{
    int isvalid = -1;
    char *validnums = "012345678";
    for (int i = 0; i < 4; i++)
    {
        if (!strchr(validnums, guess[i]) || flag != 5)
        {
            isvalid = -1;
            i = 4;
        }
        else
        {
            isvalid = 1;
        }
    }
    if (isvalid == -1) printf("wrong input!\n");

    return isvalid;
}
//generate random number
char *generate()
{
    char str[4];
    int num[4];
    int max = 7;
    time_t t1;

    srand((unsigned)time(&t1));
    do
    {
        num[0] = rand() % max + 1;
        num[1] = rand() % max + 1;
        num[2] = rand() % max + 1;
        num[3] = rand() % max + 1;
    } while (num[0] == num[1] || num[0] == num[2] || num[0] == num[3] ||
             num[1] == num[2] || num[1] == num[3] || num[2] == num[3]);

    for (int i = 0; i < 4; i++)
    {
        str[i] = num[i] + '0';
    }
    char *st = str;
    return st;
}

//run game and match users valid guess
void run(char *pattern)
{
    char *hiddenpattern = pattern;
    int wellplaced = 0, misplaced = 0, isvalid = -1;

    if (max_rounds <= 0)
    {
        max_rounds = 10;
    }

    char *guess;

    printf("Will you find the secret code? \n");
    printf("Please enter a valid guess\n");

    while (rounds < max_rounds)
    {
        wellplaced = 0;
        misplaced = 0;
        printf("----\n");
        printf("Round: %d\n", rounds);
        do
        {
            guess = getInput();
            if (rounds == max_rounds) break;
            isvalid = is_valid(guess);

        } while (isvalid == -1);

        if (rounds == max_rounds) break;

        for (int i = 0; i < 4; i++)
        {
            if (guess[i] == hiddenpattern[i]) wellplaced++;

            if ((strchr(guess, hiddenpattern[i])) &&
                guess[i] != hiddenpattern[i])
                misplaced++;
        }
        if (wellplaced == 4)
        {
            printf("Congratz! You did it!\n");
            break;
        }

        printf("Wellplaced pieces: %d\n", wellplaced);
        printf("Misplaced pieces: %d\n", misplaced);
        rounds++;
        isvalid = -1;
    }
}

int main(int argc, char **argv)
{
    char *nums;
    if (argc < 2)
    {
        nums = generate();
    }
    else
    {
        checkArgs(argc, argv);
        nums = argv[arg_index];
    }
   
    run(nums);
}
