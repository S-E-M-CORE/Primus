#ifndef CRUD_DATABASECOMPONENT_HPP
#define CRUD_DATABASECOMPONENT_HPP

#include "oatpp/core/macro/component.hpp"

#include "DatabaseClient.hpp"
#include "filesystemHelper.hpp"

namespace primus
{
    namespace component
    {
        //  ____        _        _                     ____                                             _   
        // |  _ \  __ _| |_ __ _| |__   __ _ ___  ___ / ___|___  _ __ ___  _ __   ___  _ __   ___ _ __ | |_ 
        // | | | |/ _` | __/ _` | '_ \ / _` / __|/ _ \ |   / _ \| '_ ` _ \| '_ \ / _ \| '_ \ / _ \ '_ \| __|
        // | |_| | (_| | || (_| | |_) | (_| \__ \  __/ |__| (_) | | | | | | |_) | (_) | | | |  __/ | | | |_ 
        // |____/ \__,_|\__\__,_|_.__/ \__,_|___/\___|\____\___/|_| |_| |_| .__/ \___/|_| |_|\___|_| |_|\__|
        //                                                                |_|                               
        /**
         * @brief Database component responsible for creating database connections and clients.
         */
        class DatabaseComponent {
        public:
            // Create database connection provider component
            OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider)([] {

                /* Create database-specific ConnectionProvider */
                auto connectionProvider = std::make_shared<oatpp::sqlite::ConnectionProvider>(DATABASE_FILE);

                /* Create database-specific ConnectionPool */
                return oatpp::sqlite::ConnectionPool::createShared(connectionProvider,
                    10 /* max-connections */,
                    std::chrono::seconds(5) /* connection TTL */);

                }());

            // Create database client
            OATPP_CREATE_COMPONENT(std::shared_ptr<DatabaseClient>, database)([] {

                /* Get database ConnectionProvider component */
                OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, connectionProvider);

                /* Create database-specific Executor */
                auto executor = std::make_shared<oatpp::sqlite::Executor>(connectionProvider);

                /* Create MyClient database client */
                return std::make_shared<DatabaseClient>(executor);

                }());

        };

    } //namespace component
} // namespace primus

#endif //CRUD_DATABASECOMPONENT_HPP
