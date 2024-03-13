#ifndef __QUADRATIC_H
#define __QUADRATIC_H

#include <stdio.h>

#include "common.h"

//---------------------------------------------------

void Insertion_sort(int* arr, size_t n)
{
    for (size_t i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > arr[j + 1])
        {
            Swap(&arr[j + 1], &arr[j]);
            j--;
        }
    }
}

//---------------------------------------------------

void Bubble_sort(int* arr, size_t n)
{
    if (n <= 0)
        return;

    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                Swap(&arr[j], &arr[j + 1]);
        }
    }
}

//---------------------------------------------------

void Selection_sort(int* arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
                Swap(&arr[i], &arr[j]);
        }
    }
}

//---------------------------------------------------

void Shell_sort(int* arr, size_t n)
{
    int step = 1;

    while (step <= n / 9)
        step = step * 3 + 1;

    for (; step > 0; step /= 3)
    {
        for (int i = step; i < n; i += step)
        {
            int j   = i;
            int key = arr[i];

            for (; j >= step && arr[j - step] > key; j -= step)
                arr[j] = arr[j - step];

            arr[j] = key;
        }
    }
}

#endif
