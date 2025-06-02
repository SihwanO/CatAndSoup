#define ROOM_WIDTH 10
#define HME_POS 1
#define BWL_PO (ROOM_WIDTH - 2)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // 유닉스용 / Windows = Windows.h 필요 || macos = unistd.h

/*
sleep(5) > Sleep(500)
sleep(2) > Sleep(2000)
clear > cls
scanf > scanf_s
*/

void getCatIntro(char* getCatName);
void getUserStat(int getCatMadeSoupValue, int getCpPoint, int getCatMood, int catAndUserAffinity, int diceAffinityValue);
int getStatsNextCatMoodAction(int getCatMood, int catAndUserAffinity, int diceAffinityValue, int posCatInitval, int diceSoupValue, int getCatMadeSoupValue);
void addCatRoom(int posCatInitval, int posCatDefault);

int main(void) {
    int getCatMadeSoupValue = 0; // 고양이가 만든 수프 갯수
    int catAndUserAffinity = 2; // 집사 친밀도
    int getCpPoint = 0; // CP 포인트
    int getCatMood = 0; // 고양이 기분
    int posCatInitval = 1; // 고양이 초기 위치
    int posCatDefault = 1; // 고양이 기존 위치 (전위치)
    char getCatName[100] = "쫀떡";
    srand(time(NULL));
    
    getCatIntro(getCatName);
    sleep(2); 
    system("clear");

    while (1) {
        int diceAffinityValue = rand() % 6 + 1;
        posCatDefault = posCatInitval;
        getUserStat(getCatMadeSoupValue, getCpPoint, getCatMood, catAndUserAffinity, diceAffinityValue);
        sleep(5);

        int diceSoupValue = rand() % 3;
        getStatsNextCatMoodAction(getCatMood, catAndUserAffinity, diceAffinityValue, posCatInitval, diceSoupValue, getCatMadeSoupValue);
        printf("\n");
        sleep(5); 

        addCatRoom(posCatInitval, posCatDefault);
        sleep(5);
        
        int catAndUserBetweenInter = 0;
        int dice = rand() % 6 + 1;
        printf("어떤 상호작용을 하시겠습니까?   0. 아무것도 하지 않음   1. 긁어 주기\n");
        printf(">> ");

        while (scanf("%d", &catAndUserBetweenInter) != 1 || (catAndUserBetweenInter != 0 && catAndUserBetweenInter != 1)) {
            while (getchar() != '\n');
            printf(">> ");
        }
        
        if (catAndUserBetweenInter == 1) {
            printf("%s의 턱을 긁어주었습니다.\n", getCatName);
            printf("2/6의 확률로 친밀도가 높아집니다.\n");
            printf("주사위를 굴립니다. 또르륵...\n");
            printf("%d이(가) 나왔습니다!\n", dice);
            
            if (dice >= 5) {
                if (catAndUserAffinity < 4) {
                    ++catAndUserAffinity;
                    printf("친밀도가 높아집니다.\n");
                } else {
                    printf("다행히 친밀도가 떨어지지 않았습니다.\n");
                }
            } else {
                printf("친밀도는 그대로입니다.\n");
            } 
            printf("현재 친밀도: %d\n", catAndUserAffinity);

        } else if (catAndUserBetweenInter == 0) {
            printf("아무것도 하지 않습니다.\n");
            printf("4/6의 확률로 친밀도가 떨어집니다.\n");
            printf("주사위를 굴립니다. 또르륵...\n");
            printf("%d이(가) 나왔습니다!\n", dice);

            if (dice <= 4) {
                if (catAndUserAffinity <= 0) {
                    printf("다행히 친밀도가 떨어지지 않았습니다.\n");
                } else {
                    --catAndUserAffinity;
                    printf("친밀도가 떨어집니다.\n");
                }
            } else {
                printf("친밀도는 그대로입니다.\n");
            } 
            printf("현재 친밀도: %d\n", catAndUserAffinity);
        }

            sleep(2); 
            system("clear");
        }

    return 0;
}

void getCatIntro(char* getCatName) {
    printf("****야옹이와 수프****\n\n");
    printf("      /\\_/\\ \n");
    printf(" /\\  / o o \\ \n");
    printf("//\\\\ \\~(*)~/\n");
    printf("`  \\/   ^ /\n");
    printf("   | \\|| ||\n");
    printf("   \\ `|| ||\n");
    printf("    \\)()-())\n\n");
    printf("야옹이의 이름은 %s 입니다.\n", getCatName);
}

void getUserStat(int getCatMadeSoupValue, int getCpPoint, int getCatMood, int catAndUserAffinity, int diceAffinityValue) {
    printf("============ 현재 상태 ============\n");
    printf("현재까지 만든 수프 : %d개\n", getCatMadeSoupValue);
    printf("CP: %d\n", getCpPoint);
    printf("쫀떡이 기분(0~3): %d\n", getCatMood);

    switch (getCatMood) {
        case 0: printf("기분이 매우 나쁩니다.\n"); break;
        case 1: printf("심심해합니다.\n"); break;
        case 2: printf("식빵을 굽습니다.\n"); break;
        case 3: printf("골골송을 부릅니다.\n"); break;
    }

    printf("집사와의 관계(0~4) : %d\n", catAndUserAffinity);

    switch (catAndUserAffinity) {
        case 0: printf("곁에 오는 것 조차 싫어합니다.\n"); break;
        case 1: printf("간신 자판기 취급입니다.\n"); break;
        case 2: printf("그럭저럭 쓸 만한 집사입니다.\n"); break;
        case 3: printf("훌륭한 집사로 인정 받고 있습니다.\n"); break;
        case 4: printf("집사 껌딱지입니다.\n"); break;
    }
    
    printf("===================================\n\n");
}

int getStatsNextCatMoodAction(int getCatMood, int catAndUserAffinity, int diceAffinityValue, int posCatInitval, int diceSoupValue, int getCatMadeSoupValue) {
    printf("쫀떡이 이동 : 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n");
        printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", 6 - catAndUserAffinity);
        printf("주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", diceAffinityValue);

        if (diceAffinityValue >= 6 - catAndUserAffinity) {
            printf("냄비 쪽으로 움직입니다!\n");
            if (posCatInitval < BWL_PO) {
                (posCatInitval)++;
            }
        } else {
            printf("집 쪽으로 이동합니다!\n");
            if (posCatInitval > 1) {
                (posCatInitval)--;
            }
        }

        if (posCatInitval == BWL_PO) {
            switch (diceSoupValue) {
                case 0: printf("쫀떡이(가) 감자수프 만들었습니다!\n"); break;
                case 1: printf("쫀떡이(가) 양송이 수프 만들었습니다!\n"); break;
                case 2: printf("쫀떡이(가) 브로콜리 수프 만들었습니다!\n"); break;
            }
            printf("현재까지 만든 수프: %d개\n", ++getCatMadeSoupValue);
        } else if (posCatInitval == HME_POS) {
            printf("쫀떡이은(는) 자신의 집에서 편안함을 느낍니다.\n");
        }
        printf("\n");

    return posCatInitval;
}

void addCatRoom(int posCatInitval, int posCatDefault) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < ROOM_WIDTH; x++) {
            if (y == 0 || y == 3) {
                printf("#");
            } else if (x == 0 || x == BWL_PO + 1) {
                printf("#");
            } else if (x == HME_POS && y == 1) {
                printf("H");
            } else if (x == BWL_PO && y == 1) {
                printf("B");
            } else if (x == posCatInitval && y == 2) {
                printf("C");
            } else if (x == posCatDefault && y == 2 && posCatDefault != posCatInitval) { 
                printf(".");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}