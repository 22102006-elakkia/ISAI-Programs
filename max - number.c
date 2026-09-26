#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int start;
    int end;
} Interval;

// Comparison function to sort intervals by their end times
int compareIntervals(const void* a, const void* b) {
    Interval* ia = (Interval*)a;
    Interval* ib = (Interval*)b;
    if (ia->end != ib->end) {
        return ia->end - ib->end;
    }
    return ib->start - ia->start; // If end times match, prefer the shorter interval
}

char** maxNumOfSubstrings(char* s, int* returnSize) {
    int len = strlen(s);
    
    // Arrays to track the first and last occurrence of each character
    int first[26];
    int last[26];
    for (int i = 0; i < 26; i++) {
        first[i] = -1;
        last[i] = -1;
    }
    
    for (int i = 0; i < len; i++) {
        int idx = s[i] - 'a';
        if (first[idx] == -1) {
            first[idx] = i;
        }
        last[idx] = i;
    }
    
    Interval validIntervals[26];
    int intervalCount = 0;
    
    // Step 1: Expand windows around each character's first and last occurrences
    for (int i = 0; i < 26; i++) {
        if (first[i] == -1) continue;
        
        int start = first[i];
        int end = last[i];
        int isValid = 1;
        
        for (int j = start; j <= end; j++) {
            int innerIdx = s[j] - 'a';
            
            // If an internal character starts earlier than our current window's start,
            // this choice is invalid because it splits that inner character's group.
            if (first[innerIdx] < start) {
                isValid = 0;
                break;
            }
            end = MAX(end, last[innerIdx]);
        }
        
        if (isValid) {
            validIntervals[intervalCount].start = start;
            validIntervals[intervalCount].end = end;
            intervalCount++;
        }
    }
    
    // Step 2: Sort valid intervals by end time to run a greedy choice algorithm
    qsort(validIntervals, intervalCount, sizeof(Interval), compareIntervals);
    
    // Step 3: Choose non-overlapping substrings greedily
    Interval resultIntervals[26];
    int resultCount = 0;
    int lastEnd = -1;
    
    for (int i = 0; i < intervalCount; i++) {
        // Because the intervals are sorted by end time, checking for inclusion 
        // or selecting non-overlapping intervals can be done sequentially
        if (validIntervals[i].start > lastEnd) {
            resultIntervals[resultCount++] = validIntervals[i];
            lastEnd = validIntervals[i].end;
        }
    }
    
    // Step 4: Allocate strings for LeetCode's multi-pointer structure
    char** result = (char**)malloc(resultCount * sizeof(char*));
    for (int i = 0; i < resultCount; i++) {
        int subLen = resultIntervals[i].end - resultIntervals[i].start + 1;
        result[i] = (char*)malloc((subLen + 1) * sizeof(char));
        strncpy(result[i], s + resultIntervals[i].start, subLen);
        result[i][subLen] = '\0';
    }
    
    *returnSize = resultCount;
    return result;
}
