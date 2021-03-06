#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <ctime>
#include <limits>

#include "2048.h"
#include "play.h"
#include "playAIHard.h"


int main(){
    initTables();
    int runs = 1;
    int results[15] = { 0 };
    int i = 0;
    for (i = 0; i < runs; i++)
    	results[playGameAiHard(2)]++;
    
    for (i = 0; i < 15; i++)
    	printf("%d \t\t %d \n", (1 << i), results[i]);
    
    return 0;
}