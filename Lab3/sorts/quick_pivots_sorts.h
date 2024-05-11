#ifndef __QUICK_PIV_H
#define __QUICK_PIV_H

// USING HOARE PARTITION AS DEFAULT (BECAUSE IT IS FASTEST IN 4th POINT)

void CentralPivot_sort(int* arr, const size_t n);
void MedianThreePivot_sort(int* arr, const size_t n);
void RandPivot_sort(int* arr, const size_t n);
void RandMedianPivot_sort(int* arr, const size_t n);

#endif
