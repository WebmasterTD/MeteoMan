#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__
#include <array>
#include <numeric>

template<typename T, size_t S>
class ring_buffer
{
public:
    ring_buffer():
     buffer{}
    {}
    void add_value(T value)
    {
        if (count < S)
        {
            count += 1.0;
        }
        buffer[index] = value;
        index = (index + 1) % S;
    }

    T average()
    {
        T sum = std::accumulate(buffer.begin(), buffer.end(), 0.0);
        return sum / count;
    }

private:
    std::array<T, S> buffer;
    size_t count = 0;
    size_t index = 0;
};

#endif