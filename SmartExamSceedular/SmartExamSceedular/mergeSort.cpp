#include "mergeSort.h"

void mergeSort(vector<pair<vector<int>, vector<string>>>& exams, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort the first and second halves
        mergeSort(exams, left, mid);
        mergeSort(exams, mid + 1, right);

        // Merge the sorted halves
        merge(exams, left, mid, right);
    }
}

void merge(vector<pair<vector<int>, vector<string>>>& exams, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary vectors
    vector<pair<vector<int>, vector<string>>> leftExams(n1);
    vector<pair<vector<int>, vector<string>>> rightExams(n2);

    // Copy data to temporary vectors
    for (int i = 0; i < n1; i++)
        leftExams[i] = exams[left + i];
    for (int j = 0; j < n2; j++)
        rightExams[j] = exams[mid + 1 + j];

    // Merge the temporary vectors back into exams
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftExams[i].second[1] <= rightExams[j].second[1]) {
            exams[k] = leftExams[i];
            i++;
        }
        else {
            exams[k] = rightExams[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftExams, if any
    while (i < n1) {
        exams[k] = leftExams[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightExams, if any
    while (j < n2) {
        exams[k] = rightExams[j];
        j++;
        k++;
    }
}
