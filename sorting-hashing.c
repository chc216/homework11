/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	printf("[-----[2022078014]	[최 현 철]-----]");
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}/**
 * @brief 배열을 초기화하는 함수입니다.
 * 
 * @param a 초기화할 배열의 이중 포인터입니다.
 * @return int 성공적으로 배열을 초기화했을 경우 0을 반환합니다.
 */
int initialize(int** a)
{
    int *temp = NULL;

    /* array가 NULL인 경우 메모리 할당 */
    if (*a == NULL) {
        temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
    } else {
        temp = *a;
    }

    /* 랜덤값을 배열의 값으로 저장 */
    for (int i = 0; i < MAX_ARRAY_SIZE; i++) {
        temp[i] = rand() % MAX_ARRAY_SIZE;
    }

    return 0;
}

/**
 * @brief 배열을 해제하는 함수입니다.
 * 
 * @param a 해제할 배열의 포인터입니다.
 * @return int 배열을 성공적으로 해제했을 경우 0을 반환합니다.
 */
int freeArray(int *a)
{
    if (a != NULL)
        free(a);
    return 0;
}
/**
 * @brief 배열을 출력하는 함수입니다.
 * 
 * @param a 출력할 배열의 포인터입니다.
 */
void printArray(int *a)
{
    if (a == NULL) {
        printf("nothing to print.\n");
        return;
    }

    // 배열 인덱스 출력
    for (int i = 0; i < MAX_ARRAY_SIZE; i++) {
        printf("a[%02d] ", i);
    }
    printf("\n");

    // 배열 요소 출력
    for (int i = 0; i < MAX_ARRAY_SIZE; i++) {
        printf("%5d ", a[i]);
    }
    printf("\n");
}

/**
 * @brief 선택 정렬을 수행하는 함수입니다.
 * 
 * @param a 선택 정렬을 수행할 배열의 포인터입니다.
 * @return int 정렬에 성공하면 0을 반환합니다.
 */
int selectionSort(int *a)
{
    int min;
    int minindex;
    int i, j;

    printf("Selection Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        minindex = i;
        min = a[i];

        // 현재 위치부터 배열의 끝까지 최솟값을 탐색합니다.
        for (j = i + 1; j < MAX_ARRAY_SIZE; j++)
        {
            if (min > a[j])
            {
                min = a[j];
                minindex = j;
            }
        }

        // 현재 위치의 요소와 최솟값을 교환합니다.
        a[minindex] = a[i];
        a[i] = min;
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);
    return 0;
}
/**
 * @brief 삽입 정렬을 수행하는 함수입니다.
 * 
 * @param a 삽입 정렬을 수행할 배열의 포인터입니다.
 * @return int 정렬에 성공하면 0을 반환합니다.
 */
int insertionSort(int *a)
{
    int i, j, t;

    printf("Insertion Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);  // 정렬 이전의 배열을 출력합니다.

    for (i = 1; i < MAX_ARRAY_SIZE; i++)
    {
        t = a[i];  // 현재 값을 임시 변수에 저장합니다.
        j = i;

        // 현재 요소를 이전 요소들과 비교하여 적절한 위치에 삽입합니다.
        while (a[j - 1] > t && j > 0)
        {
            a[j] = a[j - 1];  // 이전 요소를 한 칸씩 오른쪽으로 이동합니다.
            j--;
        }

        a[j] = t;  // 삽입할 위치에 현재 값을 저장합니다.
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  // 정렬 이후의 배열을 출력합니다.

    return 0;
}

/**
 * @brief 버블 정렬을 수행하는 함수입니다.
 * 
 * @param a 버블 정렬을 수행할 배열의 포인터입니다.
 * @return int 정렬에 성공하면 0을 반환합니다.
 */
int bubbleSort(int *a)
{
    int i, j, t;

    printf("Bubble Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);  // 정렬 이전의 배열을 출력합니다.

    for (i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        for (j = 1; j < MAX_ARRAY_SIZE; j++)
        {
            if (a[j - 1] > a[j])  // 이웃한 두 요소를 비교하여 정렬 순서를 조정합니다.
            {
                t = a[j - 1];  // 임시 변수에 현재 요소의 이전 값을 저장합니다.
                a[j - 1] = a[j];  // 이전 값을 현재 위치로 이동시킵니다.
                a[j] = t;  // 현재 값을 이전 위치로 이동시킵니다.
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  // 정렬 이후의 배열을 출력합니다.

    return 0;
}
/**
 * @brief 셸 정렬을 수행하는 함수입니다.
 * 
 * @param a 셸 정렬을 수행할 배열의 포인터입니다.
 * @return int 정렬에 성공하면 0을 반환합니다.
 */
int shellSort(int *a)
{
    int i, j, k, h, v;

    printf("Shell Sort: \n");
    printf("----------------------------------------------------------------\n");

    printArray(a);  // 정렬 이전의 배열을 출력합니다.

    for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)
    {
        for (i = 0; i < h; i++)
        {
            for (j = i + h; j < MAX_ARRAY_SIZE; j += h)
            {
                v = a[j];  // 현재 요소를 임시 변수에 저장합니다.
                k = j;
                while (k > h - 1 && a[k - h] > v)
                {
                    a[k] = a[k - h];  // h 간격만큼 떨어진 이전 요소를 현재 위치로 이동시킵니다.
                    k -= h;
                }
                a[k] = v;  // 임시 변수에 저장된 값을 현재 위치에 삽입합니다.
            }
        }
    }

    printf("----------------------------------------------------------------\n");
    printArray(a);  // 정렬 이후의 배열을 출력합니다.

    return 0;
}

/**
 * @brief 퀵 정렬을 수행하는 함수입니다.
 * 
 * @param a 퀵 정렬을 수행할 배열의 포인터입니다.
 * @param n 배열의 크기입니다.
 * @return int 정렬에 성공하면 0을 반환합니다.
 */
int quickSort(int *a, int n)
{
    int v, t;
    int i, j;

    if (n > 1)
    {
        v = a[n - 1];  // 피벗으로 배열의 마지막 요소를 선택합니다.
        i = -1;
        j = n - 1;

        while (1)
        {
            while (a[++i] < v);  // 피벗보다 큰 값을 찾습니다.
            while (a[--j] > v);  // 피벗보다 작은 값을 찾습니다.

            if (i >= j)
                break;

            t = a[i];    // 큰 값과 작은 값을 교환합니다.
            a[i] = a[j];
            a[j] = t;
        }

        t = a[i];
        a[i] = a[n - 1];
        a[n - 1] = t;  // 피벗을 정렬된 위치로 이동합니다.

        quickSort(a, i);          // 피벗 왼쪽 부분 배열에 대해 재귀적으로 퀵 정렬을 수행합니다.
        quickSort(a + i + 1, n - i - 1);  // 피벗 오른쪽 부분 배열에 대해 재귀적으로 퀵 정렬을 수행합니다.
    }

    return 0;
}

/**
 * @brief 주어진 키의 해시 코드를 계산하는 함수입니다.
 * 
 * @param key 해시 코드를 계산할 키입니다.
 * @return int 계산된 해시 코드를 반환합니다.
 */
int hashCode(int key) {
    return key % MAX_HASH_TABLE_SIZE;
}

/**
 * @brief 주어진 배열을 해시 테이블에 해싱하는 함수입니다.
 * 
 * @param a 해싱할 배열입니다.
 * @param ht 해시 테이블의 이중 포인터입니다.
 * @return int 해싱에 성공하면 0을 반환합니다.
 */
int hashing(int *a, int **ht)
{
    int *hashtable = NULL;

    /* hash table이 NULL인 경우 메모리 할당 */
    if (*ht == NULL) {
        hashtable = (int *)malloc(sizeof(int) * MAX_ARRAY_SIZE);
        *ht = hashtable; /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할 수 있도록 함 */
    } else {
        hashtable = *ht; /* hash table이 NULL이 아닌 경우, table 재활용, reset to -1 */
    }

    for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
        hashtable[i] = -1;

    int key = -1;
    int hashcode = -1;
    int index = -1;
    for (int i = 0; i < MAX_ARRAY_SIZE; i++)
    {
        key = a[i];
        hashcode = hashCode(key);

        if (hashtable[hashcode] == -1)
        {
            hashtable[hashcode] = key;  // 해당 위치에 키를 저장합니다.
        }
        else
        {
            index = hashcode;

            while (hashtable[index] != -1)
            {
                index = (++index) % MAX_HASH_TABLE_SIZE;  // 충돌이 발생한 경우 다음 위치로 이동합니다.
            }
            hashtable[index] = key;  // 충돌이 발생하지 않은 위치에 키를 저장합니다.
        }
    }

    return 0;
}
/**
 * @brief 주어진 키를 해시 테이블에서 검색하는 함수입니다.
 * 
 * @param ht 해시 테이블의 포인터입니다.
 * @param key 검색할 키입니다.
 * @return int 키를 찾은 경우 해당 인덱스를 반환하고, 찾지 못한 경우 -1을 반환합니다.
 */
int search(int *ht, int key)
{
    int index = hashCode(key);  // 키의 해시 코드를 계산합니다.

    if (ht[index] == key)  // 해시 테이블의 해당 인덱스에 키가 있는 경우
        return index;

    while (ht[++index] != key)  // 충돌이 발생한 경우 다음 위치로 이동하며 키를 찾습니다.
    {
        index = index % MAX_HASH_TABLE_SIZE;
    }
    return index;  // 키를 찾은 경우 해당 인덱스를 반환합니다.
}
