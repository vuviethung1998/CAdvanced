/*
    Algorithms. "I like this program very much"
1) Reverse the individual words, we get the below string.
     "i ekil siht margorp yrev hcum"
2) Reverse the whole string from start to end and you get the desired output.
     "much very program this like i"
*/
/*Function to reverse any sequence starting with pointer
  begin and ending with pointer end  */

void reverse(char *begin, char *end)
{
    char temp;

    while (begin < end) {
        temp = *begin;
        *begin = *end;
        *end = temp;
        begin++;
        end--;
    }

    return;
}

void reverseWords(char *s)
{
    char *word_begin = s;
    char *temp = s;

    /*STEP 1 of the above algorithm */
    while (*temp != '\0')
    {
        temp++;
        if (*temp == '\0')
        {
            reverse(word_begin, temp - 1);
        }
        else if (*temp == ' ')
        {
            reverse(word_begin, temp - 1);
            word_begin = temp + 1;
        }
    }

    /*STEP 1 of the above algorithm */
    reverse(s, temp - 1);
    return;
}
