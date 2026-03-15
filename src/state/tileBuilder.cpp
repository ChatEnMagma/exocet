#include "state/tileBuilder.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

TileBuilder& TileBuilder::addLine(std::vector<std::size_t> line) {
    if(lines.size() > static_cast<size_t>(h)) throw runtime_error("You cant add a new line");
    if(line.size() != static_cast<size_t>(w)) throw runtime_error("You should have " + w + string(" of index tiles in this new line"));

    for_each(line.begin(), line.end(), [this](auto i) {
        if(i > handler.getGame().getStateManager().getTileManager().size()) throw runtime_error("The " + std::to_string(i) + string("th uknow tine")); 
    });

    lines.emplace_back(line);

    return *this;
}