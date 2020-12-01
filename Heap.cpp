// Heap.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Program asks for 100 random integers and genertaes a max heap based on input
// Author: Pranav Sharma
// Date: 11/28/20

#include <iostream>
#include <math.h>
#include<fstream>
#include "string.h"
#include <sstream>
using namespace std;
// functions of the program
void printArray(int array[], int n);
void createHeap(int array[], int n);
void organize(int array[], int n, int i);
void sort(int arr[], int n);
void visualprint(int arr[], int n);
int main()
{
    bool running = true;
    char* input = new char();
    int array[100];
    for (int i = 0; i < 100; i++)
    {
        array[i] = -1;
    }
    // introduces program
    cout << "Hello! This program reads in an input of 100 numbers and sorts them using a max binary tree\n";
    cout << "You may either enter 100 integers by typing INPUT or have the program read a file by typing FILE\n";
    cin.getline(input, 80, '\n');
    // if user wnats to input
    if (strcmp(input, "INPUT") == 0) {
        cout << "You really want to enter 100 integers? Okay go ahead and get started\n";
        for (int i = 0; i < 100; i++) {
            cout << "Enter number " << i + 1 << ": ";
            cin >> array[i];
            //array[i] = rand() % 1000; - For generating random numbers
        }
    }
    // if user wnats to read from file
    else if (strcmp(input, "FILE") == 0) {
        cout << "Enter the file you would like to open, in this progrma there is a file called 'Number.txt'\n";
        char file[20];
        cin.getline(file, 80, '\n');
        FILE* pfile = NULL;
        char line[1000];
        // opesn the file with the given name from user
        pfile = fopen(file, "r");
        // alerts if file is unreadable
        if (pfile == NULL)
        {
            cout << "Error in opening the file Numbers.txt";
            return 0;
        }

        // goes through each line, and stores whats beween the commas in the integer array
        int index = 0;
        while (fgets(line, 1000, pfile)) {
            char* buffer = new char[20];
            memset(buffer, '\0', 20);
            int pos = 0;
            while (buffer != NULL) {                
                buffer = strchr(line + pos, ',');
                if (buffer != NULL) {
                    char lineBuffer[20];
                    memset(lineBuffer, '\0', 20);
                    strncpy(lineBuffer, line + pos, sizeof(line - buffer));
                    array[index++] = stoi(lineBuffer);
                    pos = (buffer-line) + 1;
                }
            }
        }

    }
    else {
        cout << "Oops! You didn't enter a proper command :(";
        running = false;
    }
    // establishes heap and prints
    if (running) {
        createHeap(array, 100);
        sort(array, 100);
        cout << endl;
        visualprint(array, 100);
    }

}
void pr(float times) {
    int time = floor(times);
    for (int j = 0; j < time; j++) {
        cout << " ";
    }
}
// outputs heap based on the sorted integer array
void visualprint(int arr[], int n) {
    //get number of rows total
    int totalrows = 0;
    for (int k = 0; k < 100; k++) {
        if (arr[k] != 0) {
            totalrows = (int)floor(log2(k + 1)) + 1;
        }
    }
    /*if (totalrows > 5) {
        cout << "I can only print things with at most 5 rows, sorry";
    }*/
    if (totalrows == 0) {
        cout << "The heap is empty!";
    }
    else for (int i = 0; i < 100; i++) {
        int rownum = (int)floor(log2(i + 1));
        int width = ceil(exp2(totalrows + 2 - rownum));
        if (i == 0 || i == 1 || i == 3 || i == 7 || i == 15 || i == 31 || i == 63) {
            width = (int)ceil(width / 2);
        };
        width = width - (int)floor(log10(arr[i] + 1));
        cout << string(width - 1, ' ');
        if (arr[i] != 0) {
            cout << arr[i] << " ";
        }
        if (arr[i] == 0) {
            cout << "  ";
        }
        if (i == 0 || i == 2 || i == 6 || i == 14 || i == 30 || i == 62) {
            cout << endl << endl;
        }
    }
    cout << endl;
}
// sorts the integer array from greatest to least, idea on how to sort from Omar Nassar
void sort(int arr[], int n) {
    int counter = n;
    int* temp = arr;
    arr = new int[n];
    for (int i = 0; i < n; i++) {//taking the head of the array and adding it to the final array
        arr[i] = temp[0];
        //removing the head
        int* temp2 = new int[counter - 1];
        for (int i = 0; i < counter - 1; i++) {
            temp2[i] = temp[i + 1];
        }
        counter = counter - 1;
        temp = temp2;
        //rebuilding heap so the largest number will be the head
        createHeap(temp, counter);
    }
    printArray(arr, n);
}
// "heapifys" the integer array to make sorting easier, moves the greater number to the top, idea on how to heapify from codegeeks.com
void organize(int array[], int n, int i) {
    int largestnum = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left < n && array[left] > array[largestnum]) {
        largestnum = left;
    }
    if (right < n && array[right] > array[largestnum]) {
        largestnum = right;
    }
    if (largestnum != i) {
        swap(array[i], array[largestnum]);
        organize(array, n, largestnum);
    }
   
}
// establishes heap
void createHeap(int array[], int n) {
    int start = (n/2) -1;
    for (int i = start; i >= 0; i--) {
        organize(array, n, i);
    }
}
// prints the organized integer array from least to greatest
void printArray(int array[], int n) {
    cout << "The organized heap is as follows:\n";
    for (int i = 0; i < n; ++i) {
        cout << array[i] << ", ";
    }
}


