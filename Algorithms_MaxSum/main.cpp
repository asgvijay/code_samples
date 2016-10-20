#include <iostream>
#include <time.h>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <sstream>
#include <typeinfo>

using namespace std;

int enumMS(int a[], int n, int *low, int *high);
int iterationMS(int a[], int n, int *low, int *high);
int dandcMS(int a[], int *low, int *high);
int linearTime(int a[], int n, int *low, int *high);
void printSubArr(int a[], int low, int high, ofstream& readfile);
timespec diff(timespec start, timespec end);

int main()
{
    srand(time(NULL));
    int *arr;
    int low = 0;
    int high = 0;
    int left = 0;

    int numItems;
    timespec time1, time2;


    ifstream file("MSS_Problems.txt");
    ofstream outputFile;
    outputFile.open("MSS_Results.txt");

    int i = 0;
    int k =0;
    int arraynum = 1;

    if(file.is_open())
    {
        std::string line;
        while ( getline( file, line ) )
        {
            low = 0;
            high = 0;
            left = 0;

            string s;
            int j;
            int arr[50];
            int i = 0;
            line.erase(0,1);
            stringstream ssin(line);
            while (ssin.good()){
                ssin >> s;
                j = atoi(s.c_str());
                //cout << "J is: " << j << endl;
                arr[i] = j;
                //cout << "arr[i] " << arr[i] << endl;
                ++i;
            }

            // run all the tests/algorithms here....
            --i;
            int right = i-1;
            if (i == 0) {
            	break;
            }

            outputFile << "Array number: " << arraynum << endl;;
            outputFile << "------------------------------" << endl;

            //Linear Time Function
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
            int maxSum = linearTime(arr, i, &low, &high);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
            outputFile << "total sum (linear) = " << maxSum << "\nstart = " << low << "\nend = " << high << endl;
            outputFile<<"Linear time function took " << diff(time1,time2).tv_sec<<" full seconds to run and "<<diff(time1,time2).tv_nsec<< " nano seconds." << endl;
            printSubArr(arr, low, high, outputFile);
            outputFile << endl;

            //Enumerated  Function
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
            maxSum = enumMS(arr, i, &low, &high);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
            outputFile << "total sum (enum) = " << maxSum << "\nstart = " << low << "\nend = " << high << endl;
            outputFile<<"Enumerated function took " << diff(time1,time2).tv_sec<<" full seconds to run and "<<diff(time1,time2).tv_nsec<< " nano seconds." << endl;
            printSubArr(arr, low, high, outputFile);
            outputFile << endl;

            //Divide and Conquer Function
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
            maxSum = dandcMS(arr, &left, &right);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
            outputFile << "total sum (recursive) = " << maxSum << "\nstart = " << left << "\nend = " << right << endl;
            outputFile <<"Divide and Conquer function took " << diff(time1,time2).tv_sec<<" full seconds to run and "<<diff(time1,time2).tv_nsec<< " nano seconds." << endl;
            printSubArr(arr, left, right, outputFile);
            outputFile << endl;

            //Iterative Function
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
            maxSum = iterationMS(arr, i, &low, &high);
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
            outputFile << "total sum (iterative) = " << maxSum << "\nstart = " << low << "\nend = " << high << endl;
            outputFile<<"Iterative function took " << diff(time1,time2).tv_sec<<" full seconds to run and "<<diff(time1,time2).tv_nsec<< " nano seconds." << endl;
            printSubArr(arr, low, high, outputFile);
            outputFile << endl;


            arraynum++;
        }

    }

    outputFile.close();
    file.close();

    return 0;
}

void printSubArr(int a[], int low, int high, ofstream& readfile)
{

  readfile << "Max sub-array = ";
    for (int i = low; i < high + 1; i++)
    {
      readfile << "|" << a[i];
    }
    readfile << "|" << endl;
}

int enumMS(int a[], int n, int *low, int *high)
{
    int maxSum = 0;
    int testSum = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            testSum = 0;
            for(int k = i; k <= j; k++)
            {
                //cout << testSum << " , " << a[k] << endl;
                testSum += a[k];
                if(testSum > maxSum)
                {
                    maxSum = testSum;
                    *low = i;
                    *high = k;
                }
            }
        }
    }
    return maxSum;
}

int iterationMS(int a[], int n, int *low, int *high)
{
    int maxSum = 0;
    int testSum = 0;
    for (int i = 0; i < n; i++)
    {
        testSum = 0;
        for (int j = i; j < n; j++)
        {
            testSum += a[j];
            if (testSum > maxSum)
            {
                maxSum = testSum;
                *low = i;
                *high = j;
            }
        }
    }
    return maxSum;
}

int dandcMS(int a[], int *low, int *high)
{
    if (*low == *high)
    {
        return a[*low];
    }

    int k = ((*high + *low)/2);

    int leftLow = *low;
    int leftHigh = k;
    int lower = dandcMS(a, &leftLow, &leftHigh);

    int rightLow = k + 1;
    int rightHigh = *high;
    int upper = dandcMS(a, &rightLow, &rightHigh);

    int maxSuffix = a[k];
    int testSuffix = 0;
    int crossLow = k;
    int crossHigh = k + 1;
    //crossHigh;
    for (int i = k; i >= 0; i--)
    {
        testSuffix += a[i];
        if (testSuffix >= maxSuffix)
        {
            maxSuffix = testSuffix;
            crossLow = i;
        }
    }

    int maxPrefix = a[k+1];
    int testPrefix = 0;
    for(int i = k + 1; i <= *high; i++)
    {
        testPrefix += a[i];
        if (testPrefix >= maxPrefix)
        {
            maxPrefix = testPrefix;
            crossHigh = i;
        }
    }
    int crossOverArray = maxSuffix + maxPrefix;
    if (lower >= upper && lower >= crossOverArray)
    {
        *low = leftLow;
        *high = leftHigh;
        return lower;
    }
    else if (upper >= lower && upper >= crossOverArray)
    {
        *low = rightLow;
        *high = rightHigh;
        return upper;
    }
    *low = crossLow;
    *high = crossHigh;
    return crossOverArray;
}

int linearTime(int a[], int n, int *low, int *high )
{
    *low = 0;
    int len = 1;
    int sum = a[0];

    int testStart = 0;
    int testLen = 1;
    int testSum = a[0];

    for (int i = 1; i < n; i++)
    {
        if (a[i] >= testSum + a[i])
        {
            testStart = i;
            testLen = 1;
            testSum = a[i];
        }
        else
        {
            testLen += 1;
            testSum += a[i];
        }
        if ((testSum > sum) || (testSum == sum && testLen < len))
        {
            sum = testSum;
            *low = testStart;
            len = testLen;
        }
    }
    *high = *low + len - 1;
    return sum;
}



timespec diff(timespec start, timespec end)
{

    timespec temp; // set up temp time variable
    if((end.tv_nsec-start.tv_nsec)<0) // this allows us to calculate an absolute value
    {
        temp.tv_sec=end.tv_sec-start.tv_sec-1;
        temp.tv_nsec=1000000000+end.tv_nsec-start.tv_nsec;

    }
    else
    {
        temp.tv_sec=end.tv_sec-start.tv_sec; // calculate end time - start time for seconds
        temp.tv_nsec=end.tv_nsec-start.tv_nsec; // calculate end time - start time for nanoseconds
    }

    return temp;

}
