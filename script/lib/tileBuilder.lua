--- @class TileBuilder
TileBuilder = {}

--- @param width integer the width of number tiles
--- @param height integer the height of number tiles
--- @return TileBuilder ...
function TileBuilder:new(width, height)end

--- @param ... integer the id of tiles
--- @return TileBuilder ...
function TileBuilder:addLine(...)end

--- Setup all the tiles into the state
function TileBuilder:settupTiles()end