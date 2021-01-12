#include <vector>
#include <algorithm>

void ssort(std::vector<int> & values)
{
    for ( size_t idx {}; idx < values.size(); ++idx )
    {
        size_t smallest_at_index {idx};
        for ( size_t cur {idx+1}; cur < values.size(); ++cur )
        {
            if ( values[smallest_at_index] > values[cur] )
            {
                smallest_at_index = cur;
            }
        }
        std::swap(values[idx], values[smallest_at_index]);
    }
}
