#include <chrono>
class Timer
{
public:
    using milliseconds = std::chrono::milliseconds::rep;

    Timer(): last_reset{std::chrono::steady_clock::now()} {}
    milliseconds reset()
    {
        auto new_time { std::chrono::steady_clock::now() };
        auto diff { new_time - last_reset };
        last_reset = new_time;
        return std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    }
private:
    std::chrono::steady_clock::time_point last_reset;
};
