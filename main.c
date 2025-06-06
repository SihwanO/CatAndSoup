#define ROOM_WIDTH 10
#define HME_POS 1
#define BWL_PO (ROOM_WIDTH - 2)
#define MAX(a, b) ((a) >= (b) ? (a) : (b))

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
void getUserStat(int getCatMadeSoupValue, int getCpPoint, int catAndUserAffinity, int diceAffinityValue);
int getStatsNextCatMoodAction(int catAndUserAffinity, int diceAffinityValue, int posCatInitval, int diceSoupValue, int getCatMadeSoupValue, int purchasedItems[5], int gameHomeTurn);
int getUserInput(int dice, int catAndUserBetweenInter, int catAndUserAffinity, int purchasedItems[5]);
int openShop(int getShopChoice, char shopItems[5][20], int itemPrice[5], int purchasedItems[5], int getCpPoint);
void addCatRoom(int posCatInitval, int posCatDefault);

int scratcher_POS = 0; // 스크래처 위치
int catTowerPOS = 0; // 캣타워 위치
int getCatMood = 3; // 고양이 기분

int main(void) {
    int gameTurn = 0; // 게임 턴
    int gameHomeTurn = 0; // 집 턴
    int catAndUserAffinity = 2; // 집사 친밀도
    int getCpPoint = 7; // CP 포인트
    int getCatMadeSoupValue = 0; // 고양이가 만든 수프 갯수
    int posCatInitval = 1; // 고양이 초기 위치
    int posCatDefault = 1; // 고양이 기존 위치 (전위치)
    int getShopChoice = 0; // 상점 선택
    char getCatName[100] = "쫀떡";
    
    char shopItems[5][20] = { // 아이템 목록
        "아무것도 사지 않음",
        "장난감 쥐",
        "레이저 포인터",
        "스크래처",
        "캣 타워"
    };
    int itemPrice[5] = {0, 1, 2, 4, 6}; // 아이템 가격
    int purchasedItems[5] = {0, 0, 0, 0, 0}; // 구매한 아이템
    srand(time(NULL));
    
    getCatIntro(getCatName);
    sleep(2); 
    system("clear");

    while (1) {
        int diceAffinityValue = rand() % 6 + 1;
        posCatDefault = posCatInitval;
        getUserStat(getCatMadeSoupValue, getCpPoint, catAndUserAffinity, diceAffinityValue);
        sleep(5);

        int diceSoupValue = rand() % 3;
        posCatInitval = getStatsNextCatMoodAction(catAndUserAffinity, diceAffinityValue, posCatInitval, diceSoupValue, getCatMadeSoupValue, purchasedItems, gameHomeTurn);
        printf("\n");
        sleep(5); 

        addCatRoom(posCatInitval, posCatDefault);
        sleep(5);
        
        int catAndUserBetweenInter = 0;
        int dice = rand() % 6 + 1;
        catAndUserAffinity = getUserInput(dice, catAndUserBetweenInter, catAndUserAffinity, purchasedItems);

        int PrvPoint = (MAX(0, getCatMood - 1) + catAndUserAffinity);
        getCpPoint += PrvPoint;
        printf("쫀떡의 기분과 친밀도에 따라서 CP가 %d 포인트 생산되었습니다.\n", PrvPoint);
        printf("보유 CP: %d\n", getCpPoint);

        getCpPoint = openShop(getShopChoice, shopItems, itemPrice, purchasedItems, getCpPoint);

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

void getUserStat(int getCatMadeSoupValue, int getCpPoint, int catAndUserAffinity, int diceAffinityValue) {
    printf("============ 현재 상태 ============\n");
    printf("현재까지 만든 수프 : %d개\n", getCatMadeSoupValue);
    printf("CP: %d 포인트\n", getCpPoint);
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

int getStatsNextCatMoodAction(int catAndUserAffinity, int diceAffinityValue, int posCatInitval, int diceSoupValue, int getCatMadeSoupValue, int purchasedItems[5], int gameHomeTurn) {
    printf("6-%d: 주사위 눈이 %d이하이면 그냥 기분이 나빠집니다..\n", catAndUserAffinity, 6 - catAndUserAffinity);
    // printf("주사위를 굴립니다. 또르륵...\n");
    // printf("%d이(가) 나왔습니다!\n", diceAffinityValue);

    if (getCatMood > 0 || getCatMood < 4) {
        if (6 - catAndUserAffinity > diceSoupValue) {
            printf("쫀떡의 기분이 나빠집니다: %d->%d\n", getCatMood, getCatMood - 1);
            --getCatMood;
        }
    }

    if (getCatMood == 0) {
        printf("기분이 매우 나쁜 쫀떡은(는) 집으로 향합니다.\n");
        if (posCatInitval > 1) {
            posCatInitval--;
        }
    } else if (getCatMood == 1) {
        printf("쫀떡은(는) 심심해서 놀이기구 쪽으로 이동합니다.\n");

        if (!purchasedItems[3] && !purchasedItems[4]) {
            printf("놀 거리가 없어서 기분이 매우 나빠집니다.\n");
            if (getCatMood > 0 || getCatMood < 4) {
                --getCatMood;
            }
        }

        if (posCatInitval > 1 || posCatInitval < BWL_PO) {
            if (posCatInitval < scratcher_POS) {
                posCatInitval++;
            } else if (posCatInitval < catTowerPOS) {
                posCatInitval++;
            }    
        } 

    } else if (getCatMood == 2) {
        printf("쫀떡은(는) 기분좋게 식빵을 굽고 있습니다.\n");
    } else if (getCatMood == 3) {
        printf("쫀떡은(는) 골골송을 부르며 수프를 만들러 갑니다.\n");

        if (posCatInitval < BWL_PO) {
            posCatInitval++;
        }
    }

    if (posCatInitval == scratcher_POS) {
        printf("쫀떡이(는) 스크래처를 긁고 놀았습니다.\n");

        if (getCatMood > 0 || getCatMood < 4) {
            printf("기분이 조금 좋아졌습니다: %d->%d\n", getCatMood, getCatMood + 1);
            ++getCatMood;
        } else {
            printf("기분이 최대치로 좋습니다!\n");
        }

    } else if (posCatInitval == catTowerPOS) {
        printf("쫀떡이(는) 캣타워를 뛰어다닙니다.\n");

        if (getCatMood > 0 || getCatMood < 4) {
            printf("기분이 제법 좋아졌습니다: %d->%d\n", getCatMood, getCatMood + 2);
            getCatMood += 2;
            
            if (getCatMood > 3) {
                getCatMood = 3;
            }
        } else {
            printf("기분이 최대치로 좋습니다!\n");
        }
    }

    if (posCatInitval == BWL_PO) {
        switch (diceSoupValue) {
            case 0: printf("쫀떡이(가) 감자수프 만들었습니다!\n"); break;
            case 1: printf("쫀떡이(가) 양송이 수프 만들었습니다!\n"); break;
            case 2: printf("쫀떡이(가) 브로콜리 수프 만들었습니다!\n"); break;
        }
        printf("현재까지 만든 수프: %d개\n", ++getCatMadeSoupValue);
    } 
    
    if (posCatInitval == HME_POS) {
        gameHomeTurn++;
        if (gameHomeTurn >= 2 && getCatMood < 3) {
            ++getCatMood;
            printf("쫀떡이은(는) 자신의 집에서 편안함을 느낍니다.\n");
        }
    } else {
        gameHomeTurn = 0;
    }
    printf("\n");

    return posCatInitval;
}

int getUserInput(int dice, int catAndUserBetweenInter, int catAndUserAffinity, int purchasedItems[5]) {
    printf("어떤 상호작용을 하시겠습니까?\n");
    printf("    0. 아무것도 하지 않음\n");
    printf("    1. 긁어 주기\n");

    int inputNum = 2; // 초기 상호작용 번호
    int toyItemsMouse = 0; // 장난감 쥐
    int toyItemsLaserPointer = 0; // 레이저 포인터

    if (purchasedItems[1]) {
        printf("    %d. 장난감 쥐로 놀아 주기\n", inputNum);
        toyItemsMouse = inputNum;
        inputNum++;
    }
    
    if (purchasedItems[2]) {
        printf("    %d. 레이저 포인터로 놀아 주기\n", inputNum);
        toyItemsLaserPointer = inputNum;
        inputNum++;
    }

    printf(">> ");

    while (scanf("%d", &catAndUserBetweenInter) != 1 || (catAndUserBetweenInter < 0 || catAndUserBetweenInter >= inputNum)) {
        while (getchar() != '\n');
        printf(">> ");
    }

    if (catAndUserBetweenInter == 1) {
        printf("쫀떡이의 턱을 긁어주었습니다.\n");
        printf("쫀떡이의 기분은 그대로입니다: %d\n", getCatMood);
        
        if (dice >= 5 && catAndUserAffinity < 4) {
            ++catAndUserAffinity;
            printf("친밀도가 높아집니다.\n");
        } else {
            printf("친밀도는 그대로입니다.\n");
        } 
        // printf("현재 친밀도: %d\n", catAndUserAffinity);

    } else if (catAndUserBetweenInter == 0) {
        printf("아무것도 하지 않습니다.\n");

        if (getCatMood > 0 || getCatMood < 4) {
            printf("쫀떡이의 기분이 나빠집니다: %d->%d\n", getCatMood, getCatMood - 1);
            --getCatMood;
        }

        if (dice < 5 && catAndUserAffinity > 0) {
            --catAndUserAffinity;
            printf("친밀도가 떨어집니다.\n");
        } else {
            printf("친밀도는 그대로입니다.\n");
        } 
        // printf("현재 친밀도: %d\n", catAndUserAffinity);
        
    } else if (catAndUserBetweenInter == toyItemsMouse) {
        printf("장난감 쥐로 쫀떡이와 놀아 주었습니다.\n");
        
        if (getCatMood > 0 || getCatMood < 4) {
            printf("쫀떡이의 기분이 조금 좋아졌습니다: %d->%d\n", getCatMood, getCatMood + 1);
            ++getCatMood;
        }

        if (dice >= 4 && catAndUserAffinity < 4) {
            ++catAndUserAffinity;
            printf("친밀도가 높아집니다.\n");
        } else {
            printf("친밀도는 그대로입니다.\n");
        } 
        // printf("현재 친밀도: %d\n", catAndUserAffinity);

    } else if (catAndUserBetweenInter == toyItemsLaserPointer) {
        printf("레이저 포인터로 쫀떡이와 신나게 놀아 주었습니다.\n");

        if (getCatMood > 0 || getCatMood < 4) {
            printf("쫀떡이의 기분이 꽤 좋아졌습니다: %d->%d\n", getCatMood, getCatMood + 2);
            getCatMood += 2;

            if (getCatMood > 3) {
                getCatMood = 3;
            }
        }

        if (dice >= 2 && catAndUserAffinity < 4) {
            ++catAndUserAffinity;
            printf("친밀도가 높아집니다.\n");
        } else {
            printf("친밀도는 그대로입니다.\n");
        }
    }

    return catAndUserAffinity;
}

int openShop(int getShopChoice, char shopItems[5][20], int itemPrice[5], int purchasedItems[5], int getCpPoint) {
    printf("상점에서 물건을 살 수 있습니다.\n");
    printf("어떤 물건을 구매할까요?\n");
    for (int i = 0; i < 5; i++) {
        if (purchasedItems[i] > 0) {
            printf("    %d. %s: %d CP (품절) \n", i, shopItems[i], itemPrice[i]);
        } else {
            printf("    %d. %s: %d CP\n", i, shopItems[i], itemPrice[i]);
        }
    }
    printf(">> ");

    while(scanf("%d", &getShopChoice) != 1 || (getShopChoice < 0 || getShopChoice > 4)) {
        while (getchar() != '\n');
        printf(">> ");
    }

    if (getShopChoice == 0) {
        printf("아무것도 사지 않습니다.\n");
    } else if (getShopChoice >= 1 && getShopChoice <= 4) {
        if (purchasedItems[getShopChoice] > 0) {
            printf("%s는 이미 구매했습니다.\n", shopItems[getShopChoice]);
        } else if (getCpPoint < itemPrice[getShopChoice]) {
            printf("CP가 부족합니다. 구매할 수 없습니다.\n");
        } else {
            purchasedItems[getShopChoice]++;
            getCpPoint -= itemPrice[getShopChoice];
            printf("%s를 구매했습니다. 현재 보유 CP: %d\n", shopItems[getShopChoice], getCpPoint);

            if (getShopChoice == 3) {
                scratcher_POS = rand() % (BWL_PO - HME_POS - 1) + HME_POS + 1;
            } else if (getShopChoice == 4) {
                catTowerPOS = rand() % (BWL_PO - HME_POS - 1) + HME_POS + 1;
            }
        }
    }

    return getCpPoint;
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
            }  else if (x == scratcher_POS && y == 1) {
                printf("S");
            } else if (x == catTowerPOS && y == 1) {
                printf("T");
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