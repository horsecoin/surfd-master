#pragma once

#include <surf/account_statistics/account_statistics_plugin.hpp>

#include <fc/api.hpp>

namespace surf{ namespace app {
   struct api_context;
} }

namespace surf { namespace account_statistics {

namespace detail
{
   class account_statistics_api_impl;
}

class account_statistics_api
{
   public:
      account_statistics_api( const surf::app::api_context& ctx );

      void on_api_startup();

   private:
      std::shared_ptr< detail::account_statistics_api_impl > _my;
};

} } // surf::account_statistics

FC_API( surf::account_statistics::account_statistics_api, )