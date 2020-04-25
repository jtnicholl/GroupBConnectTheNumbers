#include "fileio/PuzzleLoader.h"

#include <fstream>
#include <sstream>

#include "../model/Tile.h"

namespace fileio {

std::vector<TileBoard*> PuzzleLoader::loadPuzzlesFromFile(const std::string& filename)
{
	std::ifstream infile;
	std::vector<TileBoard*> output;
	infile.open(filename, std::ios::in);
	while (infile)
	{
		std::string line;
		std::getline(infile, line);
		if (!line.empty())
		{
			output.push_back(loadPuzzleFromLine(line));
		}
	}
	infile.close();
	return output;
}

TileBoard* PuzzleLoader::loadPuzzleFromLine(const std::string& line)
{
	std::vector<TileEntry> entries = parseLine(line);
    TileBoard* output = new TileBoard();
    for (int i = 0; i < TileBoard::BOARD_AREA; i++)
    {
		if (!entries.empty() && entries.front().position == i)
		{
			Tile* tile = entries.front().tile;
			output->setTile(i, tile);
			entries.erase(entries.begin());
		}
		else
		{
			output->setTile(i, new Tile());
		}
    }
    return output;
}

std::vector<TileEntry> PuzzleLoader::parseLine(const std::string& line)
{
	std::stringstream stream;
	std::vector<TileEntry> output;
	for (int i = 0; line[i] != '\n' && line[i] != '\0'; i++)
	{
		if (line[i] == ',')
		{
			output.push_back(parseEntry(stream.str()));
			stream.str("");
		}
		else
		{
			stream << line[i];
		}
	}
	output.push_back(parseEntry(stream.str()));
	return output;
}

TileEntry PuzzleLoader::parseEntry(const std::string& entry)
{
	bool readingValue = false;
	TileEntry output;
	output.position = 0;
	int value = 0;
	bool immutable;
	for (int i = 0; entry[i] != '\0'; i++)
	{
		if (readingValue)
		{
			value *= 10;
			value += entry[i] - '0';
		}
		else if (entry[i] == ':')
		{
			immutable = true;
			readingValue = true;
		}
		else if (entry[i] == ';')
		{
			immutable = false;
			readingValue = true;
		}
		else
		{
			output.position *= 10;
			output.position += entry[i] - '0';
		}
	}
	output.tile = new Tile(value, immutable);
	return output;
}

} // namespace fileio
