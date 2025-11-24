#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void info(void);
void menu(void);
int initNums(int* const, int* const, int, const int, const int);
int mode(void);
void guess(int* const, int* const, int, int, int);

int main()
{

    int* nums = NULL;
    int hashNumsLen = 10;

    int* noHashNums = NULL;
    int noHashNumsLen = 4;

    int RandLimit = 9;

    int count = 8;

    int gameMode = 0;
    int statusCode = 0;

    info();

    while (1) {

        menu();

        switch (gameMode = mode()) {
        case 1: case 2: {

        InputAgain:

            free(nums);
            free(noHashNums);
            if ((nums = (int*)calloc(hashNumsLen, sizeof(int))) == NULL) return -1;
            if ((noHashNums = (int*)calloc(noHashNumsLen, sizeof(int))) == NULL) return -1;

            statusCode = initNums(nums, noHashNums, noHashNumsLen, gameMode, RandLimit);

            switch (statusCode) {
            case 0: {
                guess(nums, noHashNums, noHashNumsLen, count, RandLimit);
                break;
            }
            case -1: {
                printf("输入错误!\n\n");
                goto InputAgain;
                break;
            }
            case -2: {
                printf("输入不符合范围!\n");
                goto InputAgain;
                break;
            }
            case -3: {
                printf("输入数字不能重复\n");
                goto InputAgain;
                break;
            }
            default:
                break;
            }
            break;
        }


        case 3: {
            printf("\n退出游戏\n");
            exit(0);
            break;
        }

        default:
            printf("未知输入请重试\n\n");
            break;
        }
    }

    return 0;
}

void info(void) {
    printf("\t猜数字 ()\n\n");
}

void menu(void) {
    printf(
        "%s%s%s%s%s",
        "--------------START----------\n",
        "1.随机产生数据\n",
        "2.用户输入数据\n",
        "3.退出游戏\n",
        "\n"
    );
}

int mode(void) {
    printf("请选择:");
    int mode = 0;
    scanf("%d", &mode);
    rewind(stdin);
    return mode;
}

int initNums(int* const hashNums, int* const noHashNums, const int noHashNumsLen, const int mode, const int limit) {
    int status = 0;
    switch (mode) {

    case 1: {
        int num = 0, unique = 0;
        for (int i = 0; i < noHashNumsLen; i++) {


            srand(time(0) + (i + 1) * 87843);

            do {
                num = rand() % limit + 1;
                unique = 1;
                for (int j = 0; j < i; j++) {
                    if (noHashNums[j] == num) {
                        unique = 0;
                        break;
                    }
                }
            } while (!unique);

            hashNums[num]++;
            noHashNums[i] = num;
        }
        break;
    }

    case 2: {
        printf("\n输入4个数字用空格分割:");
        int input = 0;

        for (int i = 0; i < noHashNumsLen; i++) {
            if (scanf("%d", &input) != 1) {
                status = -1;
                break;
            }

            if (input > limit || input < 0) {
                status = -2;
                break;
            }

            for (int c = 0; c < noHashNumsLen; c++) {
                if (noHashNums[c] == input) {
                    status = -3;
                    break;
                }
            }

            if (status != 0) break;

            hashNums[input]++;
            noHashNums[i] = input;
        }
        break;
    }
    }

    rewind(stdin);
    return status;
}

void guess(int* const hashNums, int* const noHashNums, const int noHashNumsLen, const int count, const int limit) {

    int guess = 0;
    int wincount = 0;

    for (int i = 0; i < count; i++) {
        printf("第%d次猜想:", i + 1);
        if (scanf("%d", &guess) != 1) {
            rewind(stdin);
            printf("输入出错请重试, ");
            i--;
            continue;
        }

        if (guess < 0 || guess > limit) {
            printf("-> 不在范围内哦!\n");
            continue;
        }

        if (hashNums[guess] > 1) {
            printf("-> %d猜过了哦!\n", guess);
            continue;
        }

        if (hashNums[guess] == 1) {

            printf(noHashNums[i] == guess ? "-> A\n" : "-> B\n");

            hashNums[guess]++;
            wincount++;

        }
        else printf("-> 没有这个数哦!\n");

        if (wincount == noHashNumsLen) {
            printf("你猜到了全部的数!\n\n");
            break;
        }
    }

    if (wincount != noHashNumsLen) printf("你没有猜到全部的数!\n\n");
}
