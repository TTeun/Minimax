#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <ctime>

#include "2048.h"
#include "play.h"
#include "playAIHard.h"


int main(){
    initTables();
    playGameAiHard(0);
    
    
    return 0;
}