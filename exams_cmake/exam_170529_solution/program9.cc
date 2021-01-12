/*
 * program9.cc
 */
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

// Define sort_insert_iterator and sort_inserter here!

template <class Container>
class sort_insert_iterator
{
public:
    using value_type = void;
    using difference_type = void;
    using reference = void;
    using pointer = void;
    using iterator_category = std::output_iterator_tag;
    sort_insert_iterator(Container & c) : container{c} {}

    sort_insert_iterator & operator++(){return *this;}
    sort_insert_iterator operator++(int){return *this;}
    sort_insert_iterator & operator=(typename Container::value_type const & v)
    {
        container.insert(lower_bound(begin(container), end(container), v), v);
        return *this;
    }
    sort_insert_iterator & operator*() { return *this; }
private:
    Container & container;
};

template <class Container>
sort_insert_iterator<Container> sort_inserter(Container & c)
{
    return c;
}

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
    copy(begin(v1), end(v1), ostream_iterator<int>{cout, " "});  
   vector<int> v2(data_start, data_end);

   cout << "\nAnother vector, v2, before inserting:\n";
   // Print content of v2!
    copy(begin(v2), end(v2), ostream_iterator<int>{cout, " "});  

   copy(insert, insert_end, sort_inserter(v2));

   cout << "\nAfter inserting 9, 2, 5, 7, 1 into vector v2:\n";
   // Print content of v2!
    copy(begin(v2), end(v2), ostream_iterator<int>{cout, " "});
    cout << endl;

   return 0;
}
