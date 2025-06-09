#define ROOM_WIDTH 10
#define HME_POS 1
#define BWL_PO (ROOM_WIDTH - 2)
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h> // ���н��� / Windows = Windows.h �ʿ� || macos = unistd.h

/*
sleep(5) > Sleep(500)
sleep(2) > Sleep(2000)
clear > cls
scanf_s > scanf_s
*/

void getCatIntro(char* getCatName);
void getUserStat(int getCatMadeSoupValue, int getCpPoint, int catAndUserAffinity, int diceAffinityValue);
int getStatsNextCatMoodAction(int catAndUserAffinity, int diceAffinityValue, int posCatInitval, int diceSoupValue, int getCatMadeSoupValue, int purchasedItems[5], int gameHomeTurn);
int getUserInput(int dice, int catAndUserBetweenInter, int catAndUserAffinity, int purchasedItems[5]);
int openShop(int getShopChoice, char shopItems[5][40], int itemPrice[5], int purchasedItems[5], int getCpPoint);
void suddenQuest(int getCatMood);
void addCatRoom(int posCatInitval, int posCatDefault);

int scratcher_POS = 0; // ��ũ��ó ��ġ
int catTowerPOS = 0; // ĹŸ�� ��ġ
int getCatMood = 3; // ����� ���

int main(void) {
    int gameTurn = 0; // ���� ��
    int gameHomeTurn = 0; // �� ��
    int catAndUserAffinity = 2; // ���� ģ�е�
    int getCpPoint = 0; // CP ����Ʈ
    int getCatMadeSoupValue = 0; // ����̰� ���� ���� ����
    int posCatInitval = 1; // ����� �ʱ� ��ġ
    int posCatDefault = 1; // ����� ���� ��ġ (����ġ)
    int getShopChoice = 0; // ���� ����
    char getCatName[100] = "�˶�";

    char shopItems[5][40] = { // ������ ���
        "�ƹ��͵� ���� ����",
        "�峭�� ��",
        "������ ������",
        "��ũ��ó",
        "Ĺ Ÿ��"
    };

    int itemPrice[5] = { 0, 1, 2, 4, 6 }; // ������ ����
    int purchasedItems[5] = { 0, 0, 0, 0, 0 }; // ������ ������
    srand(time(NULL));

    getCatIntro(getCatName);
    Sleep(2000);
    system("cls");

    while (1) {
        gameTurn++;

        int diceAffinityValue = rand() % 6 + 1;
        posCatDefault = posCatInitval;
        getUserStat(getCatMadeSoupValue, getCpPoint, catAndUserAffinity, diceAffinityValue);
        Sleep(500);

        int diceSoupValue = rand() % 3;
        posCatInitval = getStatsNextCatMoodAction(catAndUserAffinity, diceAffinityValue, posCatInitval, diceSoupValue, getCatMadeSoupValue, purchasedItems, gameHomeTurn);
        printf("\n");
        Sleep(500);

        addCatRoom(posCatInitval, posCatDefault);
        Sleep(500);

        int catAndUserBetweenInter = 0;
        int dice = rand() % 6 + 1;
        catAndUserAffinity = getUserInput(dice, catAndUserBetweenInter, catAndUserAffinity, purchasedItems);

        int PrvPoint = (MAX(0, getCatMood - 1) + catAndUserAffinity);
        getCpPoint += PrvPoint;
        printf("\n");
        printf("�˶��� ��а� ģ�е��� ���� CP�� %d ����Ʈ ����Ǿ����ϴ�.\n", PrvPoint);
        printf("���� CP: %d\n\n", getCpPoint);

        getCpPoint = openShop(getShopChoice, shopItems, itemPrice, purchasedItems, getCpPoint);
        printf("\n");

        if (gameTurn == 3) {
            suddenQuest(getCatMood);
            Sleep(2000);
        }

        Sleep(2000);
        system("cls");
    }

    return 0;
}

void getCatIntro(char* getCatName) {
    printf("****�߿��̿� ����****\n\n");
    printf("      /\\_/\\ \n");
    printf(" /\\  / o o \\ \n");
    printf("//\\\\ \\~(*)~/\n");
    printf("`  \\/   ^ /\n");
    printf("   | \\|| ||\n");
    printf("   \\ `|| ||\n");
    printf("    \\)()-())\n\n");
    printf("�߿����� �̸��� %s �Դϴ�.\n", getCatName);
}

void getUserStat(int getCatMadeSoupValue, int getCpPoint, int catAndUserAffinity, int diceAffinityValue) {
    printf("============ ���� ���� ============\n");
    printf("������� ���� ���� : %d��\n", getCatMadeSoupValue);
    printf("CP: %d ����Ʈ\n", getCpPoint);
    printf("�˶��� ���(0~3): %d\n", getCatMood);

    switch (getCatMood) {
    case 0: printf("    ����� �ſ� ���޴ϴ�.\n"); break;
    case 1: printf("    �ɽ����մϴ�.\n"); break;
    case 2: printf("    �Ļ��� �����ϴ�.\n"); break;
    case 3: printf("    ������ �θ��ϴ�.\n"); break;
    }

    printf("������� ����(0~4) : %d\n", catAndUserAffinity);

    switch (catAndUserAffinity) {
    case 0: printf("    �翡 ���� �� ���� �Ⱦ��մϴ�.\n"); break;
    case 1: printf("    ���� ���Ǳ� ����Դϴ�.\n"); break;
    case 2: printf("    �׷����� �� ���� �����Դϴ�.\n"); break;
    case 3: printf("    �Ǹ��� ����� ���� �ް� �ֽ��ϴ�.\n"); break;
    case 4: printf("    ���� �������Դϴ�.\n"); break;
    }

    printf("===================================\n\n");
}

int getStatsNextCatMoodAction(int catAndUserAffinity, int diceAffinityValue, int posCatInitval, int diceSoupValue, int getCatMadeSoupValue, int purchasedItems[5], int gameHomeTurn) {
    printf("6-%d: �ֻ��� ���� %d�����̸� �׳� ����� �������ϴ�..\n", catAndUserAffinity, 6 - catAndUserAffinity);
    printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
    // printf("%d��(��) ���Խ��ϴ�!\n", diceAffinityValue);

    if (getCatMood > 0) {
        if (6 - catAndUserAffinity > diceSoupValue) {
            printf("�˶��� ����� �������ϴ�: %d->%d\n", getCatMood, getCatMood - 1);
            --getCatMood;
        }
    }
    else {
        printf("�˶��� ����� �־��̱� ������ �� �������� �ʽ��ϴ�!\n");
    }

    if (getCatMood == 0) {
        printf("����� �ſ� ���� �˶���(��) ������ ���մϴ�.\n");
        if (posCatInitval > 1) {
            posCatInitval--;
        }
    }
    else if (getCatMood == 1) {
        printf("�˶���(��) �ɽ��ؼ� ���̱ⱸ ������ �̵��մϴ�.\n");

        if (!purchasedItems[3] && !purchasedItems[4]) {
            printf("�� �Ÿ��� ��� ����� �ſ� �������ϴ�.\n");
            if (getCatMood > 0) {
                --getCatMood;
            }
            else {
                printf("�˶��� ����� �־��̱� ������ �� �������� �ʽ��ϴ�!\n");
            }
        }
        else {
            int dist;

            if (purchasedItems[3] && !purchasedItems[4]) {
                dist = scratcher_POS;
            }
            else if (!purchasedItems[3] && purchasedItems[4]) {
                dist = catTowerPOS;
            }
            else {
                int distScratcher, distCatTower;

                if (posCatInitval > scratcher_POS)
                    distScratcher = posCatInitval - scratcher_POS;
                else
                    distScratcher = scratcher_POS - posCatInitval;

                if (posCatInitval > catTowerPOS)
                    distCatTower = posCatInitval - catTowerPOS;
                else
                    distCatTower = catTowerPOS - posCatInitval;

                if (distScratcher <= distCatTower)
                    dist = scratcher_POS;
                else
                    dist = catTowerPOS;
            }
            if (posCatInitval > 1 || posCatInitval < BWL_PO) {
                if (posCatInitval < dist) {
                    posCatInitval++;
                }
                else if (posCatInitval > dist) {
                    posCatInitval--;
                }
            }
        }


    }
    else if (getCatMood == 2) {
        printf("�˶���(��) ������� �Ļ��� ���� �ֽ��ϴ�.\n");
    }
    else if (getCatMood == 3) {
        printf("�˶���(��) ������ �θ��� ������ ���鷯 ���ϴ�.\n");

        if (posCatInitval < BWL_PO) {
            posCatInitval++;
        }
    }

    if (posCatInitval == scratcher_POS) {
        printf("�˶���(��) ��ũ��ó�� �ܰ� ��ҽ��ϴ�.\n");

        if (getCatMood < 4) {
            printf("����� ���� ���������ϴ�: %d->%d\n", getCatMood, getCatMood + 1);
            ++getCatMood;
        }
        else {
            printf("����� �ִ�ġ�� �����ϴ�!\n");
        }

    }
    else if (posCatInitval == catTowerPOS) {
        printf("�˶���(��) ĹŸ���� �پ�ٴմϴ�.\n");

        if (getCatMood < 4) {
            int beforeCatMood = getCatMood;
            getCatMood += 2;

            if (getCatMood > 3) {
                getCatMood = 3;
                printf("�˶����� ����� �ִ�ġ�� �����ϴ�\n");
            }
            else {
                printf("����� ���� ���������ϴ�: %d->%d\n", beforeCatMood, getCatMood);
            }
        }
        else {
            printf("����� �ִ�ġ�� �����ϴ�!\n");
        }
    }

    if (posCatInitval == BWL_PO) {
        switch (diceSoupValue) {
        case 0: printf("�˶���(��) ���ڼ��� ��������ϴ�!\n"); break;
        case 1: printf("�˶���(��) ����� ���� ��������ϴ�!\n"); break;
        case 2: printf("�˶���(��) ����ݸ� ���� ��������ϴ�!\n"); break;
        }
        printf("������� ���� ����: %d��\n", ++getCatMadeSoupValue);
    }

    if (posCatInitval == HME_POS) {
        ++gameHomeTurn;
        printf("�˶�����(��) �ڽ��� ������ ������� �����ϴ�.\n");
        if (gameHomeTurn >= 2) {
            if (getCatMood < 3) {
                printf("�˶�����(��) �ڽ��� ������ ������� ������ ����� �������ϴ�: %d->%d\n", getCatMood, getCatMood + 1);
                ++getCatMood;
            }
            else {
                printf("�˶�����(��) �ڽ��� ������ ������� �������� ����� �ſ� ���� �� �̻� ����� �������� �ʽ��ϴ�.\n");
            }
        }
    }
    else {
        gameHomeTurn = 0;
    }
    printf("\n");

    return posCatInitval;
}

int getUserInput(int dice, int catAndUserBetweenInter, int catAndUserAffinity, int purchasedItems[5]) {
    printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?\n");
    printf("    0. �ƹ��͵� ���� ����\n");
    printf("    1. �ܾ� �ֱ�\n");

    int inputNum = 2; // �ʱ� ��ȣ�ۿ� ��ȣ
    int toyItemsMouse = 0; // �峭�� ��
    int toyItemsLaserPointer = 0; // ������ ������

    if (purchasedItems[1]) {
        printf("    %d. �峭�� ��� ��� �ֱ�\n", inputNum);
        toyItemsMouse = inputNum;
        inputNum++;
    }

    if (purchasedItems[2]) {
        printf("    %d. ������ �����ͷ� ��� �ֱ�\n", inputNum);
        toyItemsLaserPointer = inputNum;
        inputNum++;
    }

    printf(">> ");

    while (scanf_s("%d", &catAndUserBetweenInter) != 1 || (catAndUserBetweenInter < 0 || catAndUserBetweenInter >= inputNum)) {
        while (getchar() != '\n');
        printf(">> ");
    }

    if (catAndUserBetweenInter == 1) {
        printf("�˶����� ���� �ܾ��־����ϴ�.\n");
        printf("�˶����� ����� �״���Դϴ�: %d\n", getCatMood);

        if (dice >= 5 && catAndUserAffinity < 4) {
            printf("���� �ܾ��־� ģ�е��� �������ϴ�: %d->%d\n", catAndUserAffinity, catAndUserAffinity + 1);
            ++catAndUserAffinity;
        }
        else {
            printf("���� �ܾ��־����� �̹� �ſ� �ŷ��ϴ� ���Դϴ�.\n");
        }
        // printf("���� ģ�е�: %d\n", catAndUserAffinity);

    }
    else if (catAndUserBetweenInter == 0) {
        printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");

        if (getCatMood > 0) {
            printf("�˶����� ����� �������ϴ�: %d->%d\n", getCatMood, getCatMood - 1);
            --getCatMood;
        }
        else {
            printf("�˶��� ����� �־��̱� ������ �� �������� �ʽ��ϴ�!\n");
        }

        if (dice < 5 && catAndUserAffinity > 0) {
            --catAndUserAffinity;
            printf("ģ�е��� �������ϴ�.\n");
        }
        else {
            printf("ģ�е��� �״���Դϴ�.\n");
        }
        // printf("���� ģ�е�: %d\n", catAndUserAffinity);

    }
    else if (catAndUserBetweenInter == toyItemsMouse) {
        printf("�峭�� ��� �˶��̿� ��� �־����ϴ�.\n");

        if (getCatMood < 4) {
            printf("�˶����� ����� ���� ���������ϴ�: %d->%d\n", getCatMood, getCatMood + 1);
            ++getCatMood;
        }
        else {
            printf("�˶��� ����� �ִ�ġ�� �����ϴ�!\n");
        }

        if (dice >= 4 && catAndUserAffinity < 4) {
            ++catAndUserAffinity;
            printf("ģ�е��� �������ϴ�.\n");
        }
        else {
            printf("ģ�е��� �״���Դϴ�.\n");
        }
        // printf("���� ģ�е�: %d\n", catAndUserAffinity);

    }
    else if (catAndUserBetweenInter == toyItemsLaserPointer) {
        printf("������ �����ͷ� �˶��̿� �ų��� ��� �־����ϴ�.\n");

        if (getCatMood < 4) {
            int beforeCatMood = getCatMood;
            getCatMood += 2;

            if (getCatMood > 3) {
                getCatMood = 3;
                printf("�˶����� ����� �ִ�ġ�� �����ϴ�\n");
            }
            else {
                printf("�˶����� ����� �� ���������ϴ�: %d->%d\n", beforeCatMood, getCatMood);
            }
        }
        else {
            printf("�˶��� ����� �ִ�ġ�� �����ϴ�!\n");
        }

        if (dice >= 2 && catAndUserAffinity < 4) {
            ++catAndUserAffinity;
            printf("ģ�е��� �������ϴ�.\n");
        }
        else {
            printf("ģ�е��� �״���Դϴ�.\n");
        }
    }

    return catAndUserAffinity;
}

int openShop(int getShopChoice, char shopItems[5][40], int itemPrice[5], int purchasedItems[5], int getCpPoint) {
    printf("�������� ������ �� �� �ֽ��ϴ�.\n");
    printf("� ������ �����ұ��?\n");
    for (int i = 0; i < 5; i++) {
        if (purchasedItems[i] > 0) {
            printf("    %d. %s: %d CP (ǰ��) \n", i, shopItems[i], itemPrice[i]);
        }
        else {
            printf("    %d. %s: %d CP\n", i, shopItems[i], itemPrice[i]);
        }
    }
    printf(">> ");

    while (scanf_s("%d", &getShopChoice) != 1 || (getShopChoice < 0 || getShopChoice > 4)) {
        while (getchar() != '\n');
        printf(">> ");
    }

    if (getShopChoice == 0) {
        printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
    }
    else if (getShopChoice >= 1 && getShopChoice <= 4) {
        if (purchasedItems[getShopChoice] > 0) {
            printf("%s�� �̹� �����߽��ϴ�.\n", shopItems[getShopChoice]);
        }
        else if (getCpPoint < itemPrice[getShopChoice]) {
            printf("CP�� �����մϴ�. ������ �� �����ϴ�.\n");
        }
        else {
            purchasedItems[getShopChoice]++;
            getCpPoint -= itemPrice[getShopChoice];
            printf("%s�� �����߽��ϴ�. ���� ���� CP: %d\n", shopItems[getShopChoice], getCpPoint);

            if (purchasedItems[3] && scratcher_POS == 0) {
                scratcher_POS = rand() % (BWL_PO - HME_POS - 1) + HME_POS + 1;
                if (catTowerPOS == scratcher_POS) {
                    scratcher_POS = (scratcher_POS + 1) % (ROOM_WIDTH - 1);
                    if (scratcher_POS == 0) scratcher_POS = 1;
                }
            }
            else if (getShopChoice == 4) {
                catTowerPOS = rand() % (BWL_PO - HME_POS - 1) + HME_POS + 1;
                if (scratcher_POS == catTowerPOS) {
                    catTowerPOS = (catTowerPOS + 1) % (ROOM_WIDTH - 1);
                    if (catTowerPOS == 0) catTowerPOS = 1;
                }
            }
        }
    }

    return getCpPoint;
}

void suddenQuest(int getCatMood) {
    printf("============ ���� ����Ʈ �߻�!! ============\n\n");

    int hidingSpot = rand() % 3 + 1;
    int playerGuess;

    printf("�˶��̰� ������Ƚ��ϴ�! ��� �������?\n");
    printf("1. Ŀư ��\n2. ���� ��\n3. ���� ��\n");
    printf(">> ");

    while (scanf_s("%d", &playerGuess) != 1 || (playerGuess < 1 || playerGuess > 3)) {
        while (getchar() != '\n');
        printf(">> ");
    }

    if (playerGuess == hidingSpot) {
        printf("�˶��̸� ã�ҽ��ϴ�!\n");
        printf("�˶��̰� ���ͼ� �ڲ��̸� �մϴ�.\n");
        printf("�˶��̰� �⻵�ϸ� ����� ���� �������ϴ�.\n\n");
        ++getCatMood;

        if (getCatMood > 3) {
            getCatMood = 3;
        }

    }
    else {
        printf("�˶��̸� �� ã�ҽ��ϴ�.\n");
        printf("�˶��̴� %d���� ���ݽ��� ���ɴϴ�.\n", hidingSpot);
        printf("�˶��̰� ������ �ϸ� ����� ���� �������ϴ�.\n\n");
        --getCatMood;

        if (getCatMood < 0) {
            getCatMood = 0;
        }
    }

    printf("============ ���� ����Ʈ ���� ============\n");

    Sleep(2000);
}

void addCatRoom(int posCatInitval, int posCatDefault) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < ROOM_WIDTH; x++) {
            if (y == 0 || y == 3) {
                printf("#");
            }
            else if (x == 0 || x == BWL_PO + 1) {
                printf("#");
            }
            else if (x == HME_POS && y == 1) {
                printf("H");
            }
            else if (x == BWL_PO && y == 1) {
                printf("B");
            }
            else if (x == scratcher_POS && y == 1) {
                printf("S");
            }
            else if (x == catTowerPOS && y == 1) {
                printf("T");
            }
            else if (x == posCatInitval && y == 2) {
                printf("C");
            }
            else if (x == posCatDefault && y == 2 && posCatDefault != posCatInitval) {
                printf(".");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}