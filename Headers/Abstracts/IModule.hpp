#pragma once

// #include "IMediator.hpp"

namespace Core
{
    class IMediator;

    struct ModInfo
    {
        //! @brief the header of every lib
        enum Type
        {
            UNKONWN,
            GAME,
            GRAPHIC,
        };
        //! @brief The type of the LIB
        Type type;
        //! @brief The name of the LIB
        std::string name;
    };

    class IMod
    {
    public:
        //! @brief destructor
        virtual ~IMod() = default;
        //! @brief Initialize this library
        //! @return True if the initialization was successful. False otherwise.
        virtual bool init(IMediator *) = 0;
        //! @brief should we close it or not
        virtual bool toClose() = 0;
        //! @brief tell library to shutdown and free it's content
        // virtual bool close() = 0;
        //! @brief get the info of the lib
        // virtual Core::ModInfo::Type getModInfo() = 0;
    };
};

//! @brief Get the library's ModuleHeader
//! @info Used to verify the integrity of the lib.
extern "C" Core::ModInfo GetHeader();

//! @brief Get the library's Module
//! @info Used to get the library's module.
extern "C" Core::IMod *GetModule(Core::IMediator *mediator);
