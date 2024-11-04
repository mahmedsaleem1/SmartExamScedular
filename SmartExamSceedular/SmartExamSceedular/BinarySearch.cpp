#include "BinarySearch.h"
#include <iostream>
#include <vector>
int binarySearch(vector<int> eID, int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if target is at mid
        if (eID[mid] == target) {
            return mid;
        }

        // If target is greater, ignore the left half
        if (eID[mid] < target) {
            left = mid + 1;
        }
        // If target is smaller, ignore the right half
        else {
            right = mid - 1;
        }
    }
    // If the target is not present in the array
    return -1;
}