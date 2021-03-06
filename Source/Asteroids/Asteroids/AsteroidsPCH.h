// Ignore SFML warnings.
#pragma warning(push, 0)
// Setting the warning level to 1 doesn't disable C4350 for some reason, so explicitly disable it.
#pragma warning(disable : 4350)
#include <SFML/Graphics.hpp>
#pragma warning(pop)

#include <assert.h>
#include <chrono>
#include <functional>
#include <iostream>
#include <sstream>