#pragma once
#include <surf/protocol/block_header.hpp>
#include <surf/protocol/transaction.hpp>

namespace surf { namespace protocol {

   struct signed_block : public signed_block_header
   {
      checksum_type calculate_merkle_root()const;
      vector<signed_transaction> transactions;
   };

} } // surf::protocol

FC_REFLECT_DERIVED( surf::protocol::signed_block, (surf::protocol::signed_block_header), (transactions) )
