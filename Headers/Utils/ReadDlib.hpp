#pragma once
#include <dlfcn.h>
#include <iostream>
#include <string>
#include <exception>
#include <map>

/**
 * @brief A class for reading symbols from shared libraries
 *
 */
class DlibReader
{
public:
    DlibReader() = default;
    /**
     * @brief opens a shared library
     *
     * sets #handle to the handle of the library
     * thorws LibNotFoundException if the library cannot be opened
     *
     * @param libPath the path to the library
     * @param mode the mode to open the library in (default: RTLD_LAZY)
     */
    DlibReader(std::string const &libPath, size_t mode = RTLD_LAZY);
    /**
     * @brief closes the library
     *
     *  and #handle if it is open
     */
    ~DlibReader();
    /**
     * @brief Gets a symbol from the library
     *  converts the symbol to the type T
     * @param symbolName the name of the symbol
     * @return the symbol
     * @note: throws SymbolNotFoundException if the symbol cannot be found
     * @note: T must be a function pointer
     */
    template <typename T>
    /**
     * @brief Function brief description
     *
     * Function detailed description.
     *
     * @param Parameter name Parameter description
     * @return Return description
     */

    T getSymbol(std::string const &symbolName)
    {
        T symbol = (T)dlsym(handle, symbolName.c_str());
        if (!symbol)
        {
            throw SymbolNotFoundException(symbolName);
            return nullptr;
        }
        return symbol;
    }
    //! Exception thrown when a library cannot be opened
    class LibNotFoundException : public std::exception
    {
    public:
        LibNotFoundException(std::string const &libPath) : msg(libPath + ": Cannot open library.") {}
        ~LibNotFoundException() = default;
        char const *what() const noexcept override { return msg.c_str(); }

    private:
        std::string msg;
    };
    //! Exception thrown when a symbol cannot be found
    class SymbolNotFoundException : public std::exception
    {
    public:
        SymbolNotFoundException(std::string const &symbolName) : msg(symbolName + ": Cannot load symbol.") {}
        ~SymbolNotFoundException() = default;
        char const *what() const noexcept override { return msg.c_str(); }

    private:
        std::string msg;
    };
    //! gets the path to the library
    std::string const &getLibPath() const { return libPath; }
    /**
     * @brief opens a new shared library closing the old one
     *
     * if the library cannot be opened, the old library is not closed
     *
     * @param libPath the path to the library
     * @param mode the mode to open the library in (default: RTLD_LAZY)
     * @return true if the library was opened
     */
    void Open(std::string const &libPath, size_t mode = RTLD_LAZY);

private:
    void *handle{nullptr};    //!< The handle of the library
    std::string libPath = ""; //!< The path/name to the library
};

class LibLoader
{
public:
    LibLoader(std::string const &libPath, size_t mode = RTLD_LAZY) : lib(new DlibReader(libPath, mode)), isCreated(true) {}
    LibLoader(DlibReader &lib) { this->lib = &lib; }
    LibLoader() = default;
    //! @brief deltes the DlibReader if it was created in the constructor
    ~LibLoader()
    {
        if (isCreated)
            delete lib;
    }
    /**
     * @defgroup call function
     * @brief calls the symbol with the given name.
     *
     *
     * @param symbolName the name of the symbol
     *
     * @param Args the arguments to pass to the symbol
     * @return the return value of the symbol
     * @note: throws SymbolNotFoundException if the symbol cannot be loaded
     * @note: do not put void as the return type just ignore the template parameter
     * @{
     */
    template <typename T, typename... Args>
    T call(std::string const &symbolName, Args &&...args)
    {
        // if the symbol is not the map load it
        if (symbols.find(symbolName) == symbols.end())
            symbols[symbolName] = lib->getSymbol<void *>(symbolName);
        // cast the symbol to the type T
        T ret_val = reinterpret_cast<T (*)(Args...)>(symbols[symbolName])(std::forward<Args>(args)...);
        return ret_val;
    }
    template <typename... Args>
    void call(std::string const &symbolName, Args &&...args)
    {
        // if the symbol is not the map load it
        if (symbols.find(symbolName) == symbols.end())
            symbols[symbolName] = lib->getSymbol<void *>(symbolName);

        // cast the symbol to the type void
        reinterpret_cast<void (*)(Args...)>(symbols[symbolName])(std::forward<Args>(args)...);
    }
    /**@}*/
    /**
     * @defgroup reset function
     * @brief resets the library
     *
     * @param libPath the path to the library
     * @param mode the mode to open the library in (default: RTLD_LAZY)
     * @{
     */
    void reset(std::string const &libPath, size_t mode = RTLD_LAZY) //!< inits a new library
    {
        symbols.clear();
        if (isCreated)
            delete lib;
        isCreated = true;
        lib = new DlibReader(libPath, mode);
    }
    void reset() //!< resets the library and nulls the pointer
    {
        symbols.clear();
        if (isCreated)
            delete lib;
        isCreated = false;
        lib = nullptr;
    }
    /**@}*/
protected:
    DlibReader *lib{nullptr};              //!< the library reader
    std::map<std::string, void *> symbols; //!< map of fuction pointers key -> symbol name, value -> symbol

private:
    bool isCreated = false; //!< if the lib is created by the class or not
};