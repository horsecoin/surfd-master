#pragma once

#include <surf/chain/util/asset.hpp>
#include <surf/chain/surf_objects.hpp>

#include <surf/protocol/asset.hpp>
#include <surf/protocol/config.hpp>
#include <surf/protocol/types.hpp>

#include <fc/reflect/reflect.hpp>

#include <fc/uint128.hpp>

namespace surf { namespace chain { namespace util {

using surf::protocol::asset;
using surf::protocol::price;
using surf::protocol::share_type;

using fc::uint128_t;

struct comment_reward_context
{
   share_type rshares;
   uint16_t   reward_weight = 0;
   asset      max_sbd; // sbd is disabled, value in SURF_SYMBOL
   uint128_t  total_reward_shares2;
   asset      total_reward_fund_surf;
   price      current_surf_price;
   curve_id   reward_curve = quadratic;
   uint128_t  content_constant = SURF_CONTENT_CONSTANT;
};

uint64_t get_rshare_reward( const comment_reward_context& ctx );

inline uint128_t get_content_constant_s()
{
   return SURF_CONTENT_CONSTANT; // looking good for posters
}

uint128_t evaluate_reward_curve( const uint128_t& rshares, const curve_id& curve = quadratic, const uint128_t& content_constant = SURF_CONTENT_CONSTANT );

} } } // surf::chain::util

FC_REFLECT( surf::chain::util::comment_reward_context,
   (rshares)
   (reward_weight)
   (max_sbd)
   (total_reward_shares2)
   (total_reward_fund_surf)
   (current_surf_price)
   (reward_curve)
   (content_constant)
   )
