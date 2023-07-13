#include "./Utils/FileReader.hpp"

FileReader::FileReader(std::string const &filepath)
    : data{}, sstream{}, line{}
{
    std::ifstream file{filepath};
    if (!file.is_open())
    {
        throw FileNotFoundException{filepath};
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    data = buffer.str();
    sstream.str(data);
}

bool FileReader::nextLine()
{
    if (!std::getline(sstream, line))
    {
        line = "";
        return false;
    }
    return true;
}

bool FileReader::open(std::string const &filepath)
{
    std::ifstream file{filepath};
    if (!file.is_open())
    {
        return false;
    }
    sstream.clear();
    std::stringstream buffer;
    buffer << file.rdbuf();
    data = buffer.str();
    sstream.str(data);
    return true;
}

void FileReader::reset()
{
    sstream.seekg(0);
}

std::pair<bool, std::string &> FileReader::getline(bool getNewLine)
{
    if (getNewLine)
        if (nextLine() == false)
            return std::pair<bool, std::string &>{false, line};
    return std::pair<bool, std::string &>{true, line};
}
