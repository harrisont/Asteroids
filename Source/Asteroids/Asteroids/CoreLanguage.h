#pragma once

template <typename T, size_t N>
size_t ArrayLength(T(&/*arr*/)[N])
{
    return std::extent<T[N]>::value;
}