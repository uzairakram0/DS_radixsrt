/*UZAIR AKRAM -- CSCE3110*/
#include<string>
#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include<time.h>

#define BILLION 1000000000L
#define HEX 16
#define passes 10

//function prototypes
void generate(int arr[], int n);
void CountingSort(int arr[], int n, int exp, int base);
void RadixSort(int arr[], int n, int base);
void printArray(int arr[], int n);
void checkSort(int arr[], int n);
void exec(int arr[], int n, int base);

using namespace std;

int main(int argc, char **argv){
    //check for argument included
    if(argc < 2){
        cout << "usage: ./a.out <base>" << endl;
        exit(0);
    }
    
    int base = atoi(argv[1]);
    
    // integer array initialization size n
    int size10[10];
    int size100[100];
    int size1000[1000];
    int size10000[10000];
    
    // execute the sorting and record time
    exec(size10, 10, base);
    exec(size100, 100, base);
    exec(size1000, 1000, base);
    exec(size10000, 10000, base);
    
    return 0;
}

//execution and time
void exec(int arr[], int n, int base){
    struct timespec start, stop;
    double accum;
    double average;
    
    cout << "Radix Sort: base = " << base << " size = " << n << endl;
    
    generate(arr, n);

    if (n > 10);
        //checkSort(arr, n);
    else{
        cout << "Unsorted: ";
        printArray(arr, n);
        cout << endl;
    }
    
    RadixSort(arr, n, base);
    
    if (n > 10);
        //checkSort(arr, n);
        else{
            cout << "Sorted: ";
            printArray(arr, n);
            cout << endl;
        }
    
    // do 10 passes
    for(int i = 1 ; i <= passes; i++){
        cout << "Pass" << i << ":\t";
        
        generate(arr, n);       //generate array of random numbers
        
        if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }
    
        RadixSort(arr, n, base);
    
    
        if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
            perror( "clock gettime" );
            exit( EXIT_FAILURE );
        }

        accum = ( stop.tv_sec - start.tv_sec ) + ( stop.tv_nsec - start.tv_nsec );
        printf( " %.1f nanoseconds\n", accum );
        average += accum;
    }
    
    printf("Average:\t %.1f nanoseconds\n", average/passes);
    cout << endl;
    
//    cout << "RESULT: RADIX SORT" << endl;
//
//    if (n > 10)
//        checkSort(arr, n);
//    else{
//        printArray(arr, n);
//        cout << endl;
//    }
//
//    cout << "==============================================" << endl;
    
}

// generates an array of size n with random integers range 0-9999
void generate(int arr[], int n){
    for(int i=0; i < n; i++)
        arr[i] = rand()%10000;
}

// auxilarry function returns maximum value
int getMax(int arr[], int n){
    int max = arr[0];
    for (int i=1; i < n; i++){
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

// COUNTING SORT ALGORITHM
void CountingSort(int arr[], int n, int exp, int base){
    int result[n];                  // stores the result of count sort
    int count[HEX] = {0};           // stores the count of each digit
    
    // stores count of occurances of the number
    for (int i = 0; i < n; i++)
        count[ (arr[i]/exp) % base ]++;
    
    //It adds to offset of the
    for (int i = 1; i < base; i++)
        count[i]+= count[i-1];
    
    // place the contents of array in the result array as determined by count
    for(int i = n-1; i >= 0; i--){
        result[ count[ (arr[i]/exp) % base ] -1] = arr[i];
        count[(arr[i]/exp) %  base]--;
    }
    
    // copy result back into array
    for (int i = 0; i < n; i++){
        arr[i] = result[i];
    }
}

// RADIX SORT ALGORITHM
void RadixSort(int arr[], int n, int base){
    int max = getMax(arr, n);     // to get the number of the highest number of digits in the array
    
    // Count Sort every digit of the integer for all digits in array
    for(int exp = 1; max/exp > 0; exp *= base){
        CountingSort(arr, n, exp, base);
    }
}

// prints an integer array
void printArray(int arr[], int n){
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}

// check if int array is sorted in ascending
void checkSort(int arr[], int n){
    cout << "output too large to display. \nChecking if array is sorted..." << endl;
    
    bool sorted = true;     /*sorted flag*/
    
    for(int i = 1; i < n; i++){
        if (arr[i] < arr[i-1]){
            cout << "\tArray is not sorted" << endl;
            sorted = false;
            break;
        }
    }
    if (sorted)
        cout << "\tArray is sorted" << endl;
    
}
