using num_type = unsigned long long;

bool is_prime(num_type val, num_type divisor=2)
{
    if ( divisor*divisor > val )
    {
        return true;
    }
    if ( val % divisor == 0 )
    {
        return false;
    }
    return is_prime(val, ++divisor);
}
