#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <cstring>
#include <array>
#include <memory>
#include <utility>
#include <unistd.h>

/**
 * @brief A class for reading files
 *
 */
class FileReader
{
public:
    //! @brief Takes a file path and reads the file into #sstream
    FileReader(std::string const &filepath);
    /**
     * @defgroup Deleted
     * @brief DELETED: Copy constructor and copy assignment operator
     *
     *
     *
     * @note: use std::move() to move the object
     * @{
     */
    FileReader &operator=(FileReader const &) = delete;
    FileReader(FileReader const &) = delete;
    /** @} */
    //! @brief Move constructor and move assignment operator
    FileReader(FileReader &&) = default;
    ~FileReader() = default;
    /**
     * @brief Gets the the #line varriable
     *
     * @param getNewLine if true, it will call #nextLine() first else it will return the current line
     *
     * @return a pair containing the return status and the line
     */
    std::pair<bool, std::string &> getline(bool getNewLine = false);
    /**
     * @brief Gets the next line from the file
     *
     * @return true if there is a next line, false if there is not
     *
     * @note: if there is no next line, #line will be set to an empty string
     */
    bool nextLine();
    //! @brief Resets the #sstream to the beginning of the file without closing  or rereading the file
    void reset();
    /**
     * @brief Opens a new file
     *
     * opens a new file, nulls #sstream and sets it to the beginning of the file
     *
     * @param filepath the path to the file
     * @return true if the file was opened, false if it was not
     * @note: if the file was not opened, #sstream will be retained
     */
    bool open(std::string const &filepath);
    //! @brief Error class for when a file cannot be opened
    //! @note: this is a nested class and inherits from std::exception
    static std::vector<std::string> listFiles(const char *path)
    {
        std::vector<std::string> files;
        DIR *dir;
        struct dirent *entry;
        if ((dir = opendir(path)) != nullptr)
        {
            while ((entry = readdir(dir)) != nullptr)
            {
                // Check if the file name ends with ".so"
                if (std::strcmp(entry->d_name + std::strlen(entry->d_name) - 3, ".so") == 0)
                {
                    files.push_back(entry->d_name);
                }
            }
            closedir(dir);
        }
        else
        {
            std::perror("opendir");
        }
        return files;
    }
    static std::string getFontFilePath(const std::string &fontName)
    {
        std::string command = "fc-match -f '%{file}' " + fontName;
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        if (!pipe)
        {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result += buffer.data();
        }
        if (!result.empty() && result.back() == '\n')
        {
            result.pop_back();
        }
        return result;
    }
    class FileNotFoundException : public std::exception
    {
    public:
        FileNotFoundException(std::string const &filepath) : msg(filepath + ": Cannot open file.") {}
        ~FileNotFoundException() = default;
        char const *what() const noexcept override { return msg.c_str(); }

    private:
        std::string msg;
    };

private:
    std::string data;          //< used to store the file data initially
    std::stringstream sstream; //< used to access the file data
    std::string line;          //< used to store the current line
};
