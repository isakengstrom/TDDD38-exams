/*
 * program9.cc
 */
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

// Define sort_insert_iterator and sort_inserter here!

int insert[] = { 9, 2, 7, 5, 1 };
int* const insert_end = insert + sizeof(insert) / sizeof(int);

int data_start[] = { 1, 1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 9 };
int* const data_end = data_start + sizeof(data_start) / sizeof(int);

int main()
{
   vector<int> v1;

   copy(insert, insert_end, sort_inserter(v1));

   cout << "After inserting 9, 2, 5, 7, 1 into an empty vector v1:\n";
   // Print content of v1!
   
   vector<int> v2(data_start, data_end);

   cout << "\nAnother vector, v2, before inserting:\n";
   // Print content of v2!

   copy(insert, insert_end, sort_inserter(v2));

   cout << "\nAfter inserting 9, 2, 5, 7, 1 into vector v2:\n";
   // Print content of v2!

   return 0;
}
