#include <stdio.h>
#include <stdlib.h>

//function to make a copy of an array
void makeArrayCopy (int fromArray[], int toArray[], int size) {
 //copy elements of the array one element at a time
 int i;
 for(i=0; i<size; i++)
    {toArray[i] = fromArray[i];}
}

//function to sort the array in ascending order
void myFavorateSort (int arr[], int size){
 int temp[size];
 int hold, i, j;

 for(j=0; j<size; j++) {
     //set the first unsorted element to be the smallest
     int small = arr[j];
     //compare small to following elements
     for(i=j+1; i<size; i++) {
        //if a smaller number is found, assign it to small
        if(arr[i]<small)
         {
             hold = small;
             small = arr[i];
             arr[i] = hold;
         }
     }
     //move small to its correct place in the array
     temp[j] = small;
 }
 //copy the temporary ordered array to actual array
 makeArrayCopy(temp, arr, size);
}

//function to perform linear search on an array
int linSearch (int arr[], int size, int target, int* numComparisons) {
 int i;

 //go through the array element by element
 for(i=0; i<size; i++) {
    //if the current element is the one were looking for, return it
    if(arr[i] == target){
        *numComparisons = i + 1;
        return i;
    }
 }
 //if the value was not found, return -1
 *numComparisons = size;
 return -1;
}

//function to perform binary search on an array
int binSearch (int arr[], int size, int target, int* numComparisons){
 *numComparisons = 0;
 int start = 0;
 int end = size-1;
 int mid = (start+end) / 2;

 //continue dividing the array in half until the element is found
 while(start <= end) {
    //check if target is in second half of array
    if(target > arr[mid]){
        *numComparisons = *numComparisons + 1;
         start = mid + 1;
    }
    //check if target is the middle element
    else if(target == arr[mid]) {
        *numComparisons = *numComparisons + 1;
        return mid;
    }
    //if target is in first half of array
    else{
        *numComparisons = *numComparisons + 1;
        end = mid - 1;
    }

    //update mid
    mid = (start + end) / 2;
 }
 //if value is not found, return -1
 return -1;
}

int main (int argc, char** argv)
{
 int val;
 int size=0;
 int numComparisons;
 int location;

 //start the array size at 100
 int *store;
 int allocated = 100;
 store = (int *) malloc (allocated * sizeof(int) );

 /* prompt the user for input */
 printf ("Enter in a list of numbers to be stored in a dynamic array.\n");
 printf ("End the list with the terminal value of -999\n");

 /* loop until the user enters -999 */
 scanf ("%d", &val);
 while (val != -999)
   {
//check if the array needs more space
    if(size == allocated) {
        //grow the array
        int *temp;
        temp = (int *) malloc ( allocated * 2 * sizeof(int) );
        int i;
        for ( i = 0 ; i < allocated ; i++)
            {temp[i] = store[i];}
        free (store);
        store = temp;
        allocated = allocated * 2;
    }
    /* store the value into an array */
    store[size] = val;

    /* get next value */
    scanf("%d", &val);

    size++;
   }

 /* make a copy of the array of values */
 int copy[size];
 makeArrayCopy(store, copy, size);

 /* sort one of the arrays */
 myFavorateSort (copy, size);

 /* loop until the user enters -999 */
 printf ("Enter in a list of numbers to use for searching.  \n");
 printf ("End the list with a terminal value of -999\n");
 scanf ("%d", &val);
 while (val != -999)
   {
    /* use the value in a linear search on the unsorted array */
    location = linSearch(store, size, val, &numComparisons);
    /* print out info about the linear search results  */
    if(location == -1)
        {printf("\nUsing linear search %d is NOT FOUND\n", val);}
    else {
        printf("\nUsing linear search %d is FOUND\n", val);
        printf("Found at position: %d\n", location);
    }
     printf("Number of Comparisons: %d\n", numComparisons);

    /* use the value in a binary search on the sorted array */
    location = binSearch(copy, size, val, &numComparisons);
    /* print out info about the binary search results  */
    if(location == -1)
        {printf("\nUsing binary search %d is NOT FOUND\n", val);}
    else {
printf("\nUsing binary search %d is FOUND\n", val);
        printf("Found at position: %d\n", location);
    }
     printf("Number of Comparisons: %d\n", numComparisons);

    /* get next value */
    scanf("%d", &val);
   }

 printf ("Good bye\n");
 return 0;
}

