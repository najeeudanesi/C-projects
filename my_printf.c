#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

//function to reverse string
char* my_strrev(char* param)
{
    int i, j = 0, len = strlen(param) - 1;
    char* newStr = malloc(len);
    if (!param) return NULL;

    for (i = len; i >= 0; i--)
    {
        newStr[j] = param[i];
        j++;
    }

    return newStr;
}

//a convert function.. does same as itoa function
char* conv(int y, char* out, int b)
{
    int i = (int)y;
    char* st = out;
    int num, mark = 0;
    if (i < 0)
    {
        mark = 1;
        i = -i;
    }

    while (i)
    {
        num = i % b;
        *st = (num > 9) ? ('A' + num - 10) : '0' + num;
        i = i / b;
        st++;
    }
    if (mark)
    {
        *st++ = '-';
    }
    *st = '\0';
    char* newstr = my_strrev(out);
    return newstr;
}

//my printf function
int my_printf(char* param, ...)
{
    va_list val;
    int i = 0;
    int j = 0;
    char* arg;
    char buffer[100] = {0}, temp[20];

    va_start(val, param);
    while (param && param[i])
    {
        if (param[i] == '%')
        {
            i++;

            switch (param[i])
            {
                case 'c':
                {
                    buffer[j] = (char)va_arg(val, int);
                    j++;
                    break;
                }
                case 's':
                {
                    arg = va_arg(val, char*);
                    strcpy(&buffer[j], arg);
                    j = j + strlen(arg);
                    break;
                }
                case 'd':
                {
                    conv(va_arg(val, int), temp, 10);
                    strcpy(&buffer[j], temp);
                    j = j + strlen(temp);
                    break;
                }
                case 'u':
                {
                    conv(va_arg(val, int), temp, 10);
                    char* nTemp = my_strrev(temp);
                    strcpy(&buffer[j], nTemp);
                    j = j + strlen(nTemp);
                    break;
                }

                case 'x':
                {
                    conv(va_arg(val, int), temp, 16);
                    strcpy(&buffer[j], temp);
                    j = j + strlen(temp);
                    break;
                }

                case 'o':
                {
                    conv(va_arg(val, int), temp, 8);
                    strcpy(&buffer[j], temp);
                    j = j + strlen(temp);
                    break;
                }

                case 'p':
                {
                    conv(va_arg(val, int), temp, 16);
                    strcpy(&buffer[j], temp);
                    j = j + strlen(temp);
                    break;
                }
            }
        }
        else
        {
            buffer[j] = param[i];
            j++;
        }
        i++;
    }
    fwrite(buffer, j, 1, stdout);
    va_end(val);
    return j;
}

int main()
{
   int ret;
    unsigned int nm = 77777777;
    
    char* s = "tell em";
    char c = 'C';

    printf("%p\n",s);
}