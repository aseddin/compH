/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

void sort(int values[], int n);
bool search(int value, int values[], int n);
void selection_sort(int values[], int n);
void bubble_sort(int values[], int n);
bool binary_search(int value, int values[], int low, int high);


/**
 * Recursive binary search
 * Takes an array, the value to look for, and the low/high indices
 */
bool binary_search(int value, int values[], int low, int high)
{
    if (high < low)
        return false;

    int middle = (low + high) / 2;

    if ( value < values[middle])
        return binary_search(value, values, low, middle - 1);
    else if ( value > values[middle])
        return binary_search(value, values, middle + 1, high);
    else
        return true;
}


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Implementing a linear searching algorithm
    //
    // N should be a positive number
    if (n < 0)
        return false;

    return binary_search(value, values, 0, n);


}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    selection_sort(values, n);
}

/**
 * Bubble sort implementation
 */
void bubble_sort(int values[], int n)
{
    // bubble up the highest value numbers
    for(int i = 0; i < n; i++)
        for(int j = 0; j < (n - i - 1); j++)
            if(values[j] > values[j + 1])
            {
                int swap = values[j];
                values[j] = values[j + 1];
                values[j + 1] = swap;
            }
}

/** 
 * Selection sort implementation
 */
void selection_sort(int values[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        // look for the minimum value in the array and put it
        // in the sorted list
        int min = i;
        for( int j = i + 1; j < n; j++)
            if(values[j] < values[min] )
                min = j;
     
        if(min != i)
        {
            int swap = values[i];
            values[i] = values[min];
            values[min] = swap;
        }
    }
}

