int compare(const void *a, const void *b) {
    int *envelopeA = *(int **)a;
    int *envelopeB = *(int **)b;
    if (envelopeA[0] == envelopeB[0]) {
        return envelopeB[1] - envelopeA[1];
    }
    return envelopeA[0] - envelopeB[0];
}

int lower_bound(int* array, int size, int value) {
    int left = 0, right = size;
    while (left < right) {
        int mid = (left + right) / 2;
        if (array[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize) {
    // Sort envelopes by width in ascending order. 
    // If two envelopes have the same width, sort by height in descending order.
    qsort(envelopes, envelopesSize, sizeof(int*), compare);

    // Extract the heights into a separate list.
    int heights[envelopesSize];
    for (int i = 0; i < envelopesSize; i++) {
        heights[i] = envelopes[i][1];
    }

    // The 'ans' array will store the increasing subsequence of heights.
    int ans[envelopesSize];
    int ansSize = 0;

    for (int i = 0; i < envelopesSize; i++) {
        int height = heights[i];
        // Find the position where 'height' can be placed in 'ans' using binary search.
        int pos = lower_bound(ans, ansSize, height);

        // If 'height' is greater than all elements in 'ans', append it.
        if (pos == ansSize) {
            ans[ansSize++] = height;
        } 
        // Otherwise, replace the element at the found position with 'height'.
        else {
            ans[pos] = height;
        }
    }

    // The size of 'ans' represents the length of the longest increasing subsequence.
    return ansSize;
}