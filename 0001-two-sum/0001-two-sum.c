#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 20003

typedef struct {
    int key;
    int value;
    int used;
} HashEntry;

int hash(int key) {
    int h = key % TABLE_SIZE;

    if (h < 0)
        h += TABLE_SIZE;

    return h;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

    HashEntry* table = calloc(TABLE_SIZE, sizeof(HashEntry));

    int* result = malloc(2 * sizeof(int));

    for (int i = 0; i < numsSize; i++) {

        int complement = target - nums[i];
        int index = hash(complement);

        // Check if complement already exists
        while (table[index].used) {

            if (table[index].key == complement) {

                result[0] = table[index].value;
                result[1] = i;

                *returnSize = 2;

                free(table);

                return result;
            }

            index = (index + 1) % TABLE_SIZE;
        }

        // Store current number
        index = hash(nums[i]);

        while (table[index].used) {
            index = (index + 1) % TABLE_SIZE;
        }

        table[index].key = nums[i];
        table[index].value = i;
        table[index].used = 1;
    }

    free(table);

    *returnSize = 0;
    free(result);

    return NULL;
}