#include "Map.h"

Map::Map(int TexID, int NumofRowMap, int NumofColMap, int NumofRowTileSet, int NumofColTileSet, int TotalTile)
{
	Tex = CTextures::GetInstance()->Get(TexID);
	this->NumofRowMap = NumofRowMap;
	this->NumofColMap = NumofColMap;
	this->NumofRowTileSet = NumofRowTileSet;
	this->NumofColTileSet = NumofColTileSet;
	this->TotalTile = TotalTile;
}

Map::~Map()
{
}

void Map::SetMapData(int** mapData)
{
	TileMapData = mapData;
}

void Map::GetSpriteTile()
{
	for (int tile = 0; tile < TotalTile; tile++)
	{
		{
			int left = tile % NumofColTileSet * TILE_WIDTH;
			int top = tile / NumofColTileSet * TILE_HEIGHT;
			int right = left + TILE_WIDTH;
			int bottom = top + TILE_HEIGHT;
			LPSPRITE SpriteTile = new CSprite(tile, left, top, right, bottom, Tex);
			Tiles.push_back(SpriteTile);
		}
	}
}

