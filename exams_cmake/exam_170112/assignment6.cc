int main()
{
    { 
        // This block should work when everything is finished
        // print values [0,9[
        for ( int v : range(10) )
            cout << v << ' ';

        // print values 2.3, 2.6, 2.9
        for ( auto v : range(2.3, 3.0, 0.3) )
            cout << v << ' ';

        // prints 2 1 0 -1 (has a negative step size)
        for ( auto v : range(2, -2, -1) )
            cout << v << ' ';
    
        // will not print anything
        for ( auto v : range(2, -1, 3) )
            cout << v << ' ';
    }

    {
        // This block shows some parts of the Range_Iterator class
        Range_Iterator<int> s{2};
        Range_Iterator<int> e{10};
        while ( s != e )
        {
            cout << *s << ' ';
            ++s;
        } // prints 2 3 4 5 6 7 8 9

        *s = 4; // should not be possible

        Range_Iterator<double> start{2.3, 0.3};
        Range_Iterator<double> stop{3.0};
        while ( start != stop )
        {
            cout << *start++ << ' ';
        } // should print 2.3 2.6 2.9
    }
}
