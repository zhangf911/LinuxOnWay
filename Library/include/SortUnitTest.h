#ifndef LIBRARY_UNITTEST_SORTUNITTEST_H
#define LIBRARY_UNITTEST_SORTUNITTEST_H

#include <iostream>

#include "Sort.h"

using std::cout;
using std::endl;

template <class DataType>
void PrintArray(DataType* INdata, UInt32 INdataSize)
{
	for(UInt32 i = 0; i < INdataSize; ++i)
	{
		cout << INdata[i] << "  ";
	}
	cout << endl;
}

void InsertSortTest()
{
	int intArr[10] = {2,34,5,7,68,35,46,77,25,9};

	double floatArr[10] = {2.4, 23.4, 9.8, 3.5, 45.3, 36.5, 8.9, 1.1, 12.6, 29.4};

	InsertSort(intArr, 10);

	InsertSort(floatArr, 10);

	PrintArray(intArr, 10);

	PrintArray(floatArr, 10);
}

void SwapTest()
{
	int leftIntVal = 3;
	int rightIntVal = 6;

	double leftFloatVal = 2.3;
	double rightFloatVal = 3.1;

	cout << leftIntVal << "\t" << rightIntVal << endl;

	cout << leftFloatVal << "\t" << rightFloatVal << endl;

	swap(&leftIntVal, &rightIntVal);

	cout << leftIntVal << "\t" << rightIntVal << endl;

	swap(&leftFloatVal, &rightFloatVal);

	cout << leftFloatVal << "\t" << rightFloatVal << endl;
}

void SelectSortTest()
{
	int intArr[10] = {2,34,5,7,68,35,46,77,25,9};

	double floatArr[10] = {2.4, 23.4, 9.8, 3.5, 45.3, 36.5, 8.9, 1.1, 12.6, 29.4};

	SelectSort(intArr, 10);

	SelectSort(floatArr, 10);

	PrintArray(intArr, 10);

	PrintArray(floatArr, 10);
}

void CombineSortTest()
{
	int intArr[10] = {2,34,5,7,68,35,46,77,25,9};

	double floatArr[10] = {2.4, 23.4, 9.8, 3.5, 45.3, 36.5, 8.9, 1.1, 12.6, 29.4};

	CombineSort(intArr, 0, 9);

	CombineSort(floatArr, 0, 9);

	PrintArray(intArr, 10);

	PrintArray(floatArr, 10);
}

void InsertSortByRecursiveTest()
{
	int intArr[10] = {2,34,5,7,68,35,46,77,25,9};

	double floatArr[10] = {2.4, 23.4, 9.8, 3.5, 45.3, 36.5, 8.9, 1.1, 12.6, 29.4};

	InsertSortByRecursive(intArr, 10);

	InsertSortByRecursive(floatArr, 10);

	PrintArray(intArr, 10);

	PrintArray(floatArr, 10);
}

void BinarySearchTest()
{
	int intArr[10] = {2,34,5,7,68,35,46,77,25,9};

	double floatArr[10] = {2.4, 23.4, 9.8, 3.5, 45.3, 36.5, 8.9, 1.1, 12.6, 29.4};

	int intvalue = 2;
	CombineSort(intArr, 0, 9);
	PrintArray(intArr, 10);
	UInt32 pos = BinarySearch(intArr, 10, intvalue);
	cout << "the pos of '" << intvalue << "' in the intArr is : " << pos << endl;
	intvalue = 77;
	pos = BinarySearch(intArr, 10, intvalue);
	cout << "the pos of '" << intvalue << "' in the intArr is : " << pos << endl;
	intvalue = 9;
	pos = BinarySearch(intArr, 10, intvalue);
	cout << "the pos of '" << intvalue << "' in the intArr is : " << pos << endl;
	intvalue = 3;
	pos = BinarySearch(intArr, 10, intvalue);
	cout << "the pos of '" << intvalue << "' in the intArr is : " << pos << endl;

	double floatvalue = 9.8;
	CombineSort(floatArr, 0, 9);
	PrintArray(floatArr, 10);
	pos = BinarySearch(floatArr, 10, floatvalue);
	cout << "the pos of '" << floatvalue << "' in the intArr is : " << pos << endl;
	floatvalue = 1.1;
	pos = BinarySearch(floatArr, 10, floatvalue);
	cout << "the pos of '" << floatvalue << "' in the intArr is : " << pos << endl;
	floatvalue = 45.3;
	pos = BinarySearch(floatArr, 10, floatvalue);
	cout << "the pos of '" << floatvalue << "' in the intArr is : " << pos << endl;
	floatvalue = 12.8;
	pos = BinarySearch(floatArr, 10, floatvalue);
	cout << "the pos of '" << floatvalue << "' in the intArr is : " << pos << endl;

}


#endif