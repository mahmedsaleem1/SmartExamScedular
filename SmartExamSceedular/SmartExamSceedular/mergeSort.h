// MergeSort.h
#pragma once
#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <string>

using namespace std;

void mergeSort(vector<pair<vector<int>, vector<string>>>& exams, int left, int right);
void merge(vector<pair<vector<int>, vector<string>>>& exams, int left, int mid, int right);

#endif // MERGESORT_H