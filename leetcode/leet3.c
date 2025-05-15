#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int lengthOfLongestSubstring(char* s) {
   int n = strlen(s);
   int char_set[128];
   memset(char_set,0,sizeof(char_set));
   int max_len = 0;
   char *start = s, *end = s;
   while(end < s + n){
    if(char_set[*end] == 0){
        char_set[*end] = 1;
        end++;
        if(end - start > max_len) max_len = end - start;
    }else{
        char_set[*start] = 0;
        start++;
    }
   }
   return max_len;
}