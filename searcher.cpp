#include "searcher.h"
#include "indexes.h"
#include <fstream>
#include <set>

searcher::searcher(std::string inputString) : inputString(inputString), flagStop(false) {}


void searcher::toStop() {
    flagStop = true;
}
