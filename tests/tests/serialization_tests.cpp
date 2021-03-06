/*
 * Copyright (c) 2015 Cryptonomex, Inc., and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifdef IS_TEST_NET
#include <boost/test/unit_test.hpp>

#include <surf/chain/surf_objects.hpp>
#include <surf/chain/database.hpp>

#include <fc/crypto/digest.hpp>
#include <fc/crypto/elliptic.hpp>
#include <fc/reflect/variant.hpp>

#include "../common/database_fixture.hpp"

#include <cmath>

using namespace surf;
using namespace surf::chain;
using namespace surf::protocol;

BOOST_FIXTURE_TEST_SUITE( serialization_tests, clean_database_fixture )

   /*
BOOST_AUTO_TEST_CASE( account_name_type_test )
{

   auto test = []( const string& data ) {
      fixed_string<> a(data);
      std::string    b(data);

      auto ap = fc::raw::pack( empty );
      auto bp = fc::raw::pack( emptystr );
      FC_ASSERT( ap.size() == bp.size() );
      FC_ASSERT( std::equal( ap.begin(), ap.end(), bp.begin() ) );

      auto sfa = fc::raw::unpack<std::string>( ap );
      auto afs = fc::raw::unpack<fixed_string<>>( bp );
   }
   test( std::string() );
   test( "helloworld" );
   test( "1234567890123456" );

   auto packed_long_string = fc::raw::pack( std::string( "12345678901234567890" ) );
   auto unpacked = fc::raw::unpack<fixed_string<>>( packed_long_string );
   idump( (unpacked) );
}
*/

BOOST_AUTO_TEST_CASE( serialization_raw_test )
{
   try {
      ACTORS( (alice)(bob) )
      transfer_operation op;
      op.from = "alice";
      op.to = "bob";
      op.amount = asset(100,SURF_SYMBOL);

      trx.operations.push_back( op );
      auto packed = fc::raw::pack( trx );
      signed_transaction unpacked = fc::raw::unpack<signed_transaction>(packed);
      unpacked.validate();
      BOOST_CHECK( trx.digest() == unpacked.digest() );
   } catch (fc::exception& e) {
      edump((e.to_detail_string()));
      throw;
   }
}
BOOST_AUTO_TEST_CASE( serialization_json_test )
{
   try {
      ACTORS( (alice)(bob) )
      transfer_operation op;
      op.from = "alice";
      op.to = "bob";
      op.amount = asset(100,SURF_SYMBOL);

      fc::variant test(op.amount);
      auto tmp = test.as<asset>();
      BOOST_REQUIRE( tmp == op.amount );

      trx.operations.push_back( op );
      fc::variant packed(trx);
      signed_transaction unpacked = packed.as<signed_transaction>();
      unpacked.validate();
      BOOST_CHECK( trx.digest() == unpacked.digest() );
   } catch (fc::exception& e) {
      edump((e.to_detail_string()));
      throw;
   }
}

BOOST_AUTO_TEST_CASE( asset_test )
{
   try
   {
      BOOST_CHECK_EQUAL( asset().decimals(), 3 );
      BOOST_CHECK_EQUAL( asset().symbol_name(), "TESTS" );
      BOOST_CHECK_EQUAL( asset().to_string(), "0.000 TESTS" );

      BOOST_TEST_MESSAGE( "Asset Test" );
      asset surf = asset::from_string( "123.456 TESTS" );
      asset tmp = asset::from_string( "0.456 TESTS" );
      BOOST_CHECK_EQUAL( tmp.amount.value, 456 );
      tmp = asset::from_string( "0.056 TESTS" );
      BOOST_CHECK_EQUAL( tmp.amount.value, 56 );

      BOOST_CHECK( std::abs( surf.to_real() - 123.456 ) < 0.0005 );
      BOOST_CHECK_EQUAL( surf.amount.value, 123456 );
      BOOST_CHECK_EQUAL( surf.decimals(), 3 );
      BOOST_CHECK_EQUAL( surf.symbol_name(), "TESTS" );
      BOOST_CHECK_EQUAL( surf.to_string(), "123.456 TESTS" );
      BOOST_CHECK_EQUAL( surf.symbol, SURF_SYMBOL);
      BOOST_CHECK_EQUAL( asset(50, SURF_SYMBOL).to_string(), "0.050 TESTS" );
      BOOST_CHECK_EQUAL( asset(50000, SURF_SYMBOL).to_string(), "50.000 TESTS" );

      BOOST_CHECK_THROW( surf.set_decimals(100), fc::exception );
      char* surf_sy = (char*) &surf.symbol;
      surf_sy[0] = 100;
      BOOST_CHECK_THROW( surf.decimals(), fc::exception );
      surf_sy[6] = 'A';
      surf_sy[7] = 'A';

      auto check_sym = []( const asset& a ) -> std::string
      {
         auto symbol = a.symbol_name();
         wlog( "symbol_name is ${s}", ("s", symbol) );
         return symbol;
      };

      BOOST_CHECK_THROW( check_sym(surf), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "1.00000000000000000000 TESTS" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "1.000TESTS" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "1. 333 TESTS" ), fc::exception ); // Fails because symbol is '333 TESTS', which is too long
      BOOST_CHECK_THROW( asset::from_string( "1 .333 TESTS" ), fc::exception );
      asset unusual = asset::from_string( "1. 333 X" ); // Passes because symbol '333 X' is short enough
      FC_ASSERT( unusual.decimals() == 0 );
      FC_ASSERT( unusual.symbol_name() == "333 X" );
      BOOST_CHECK_THROW( asset::from_string( "1 .333 X" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "1 .333" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "1 1.1" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "11111111111111111111111111111111111111111111111 TESTS" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "1.1.1 TESTS" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "1.abc TESTS" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( " TESTS" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "TESTS" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "1.333" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "1.333 " ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "" ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( " " ), fc::exception );
      BOOST_CHECK_THROW( asset::from_string( "  " ), fc::exception );

      BOOST_CHECK_EQUAL( asset::from_string( "100 TESTS" ).amount.value, 100 );
   }
   FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE( json_tests )
{
   try {
   auto var = fc::json::variants_from_string( "10.6 " );
   var = fc::json::variants_from_string( "10.5" );
   } catch ( const fc::exception& e )
   {
      edump((e.to_detail_string()));
      throw;
   }
}

BOOST_AUTO_TEST_CASE( extended_private_key_type_test )
{
   try
   {
     fc::ecc::extended_private_key key = fc::ecc::extended_private_key( fc::ecc::private_key::generate(),
                                                                       fc::sha256(),
                                                                       0, 0, 0 );
      extended_private_key_type type = extended_private_key_type( key );
      std::string packed = std::string( type );
      extended_private_key_type unpacked = extended_private_key_type( packed );
      BOOST_CHECK( type == unpacked );
   } catch ( const fc::exception& e )
   {
      edump((e.to_detail_string()));
      throw;
   }
}

BOOST_AUTO_TEST_CASE( extended_public_key_type_test )
{
   try
   {
      fc::ecc::extended_public_key key = fc::ecc::extended_public_key( fc::ecc::private_key::generate().get_public_key(),
                                                                       fc::sha256(),
                                                                       0, 0, 0 );
      extended_public_key_type type = extended_public_key_type( key );
      std::string packed = std::string( type );
      extended_public_key_type unpacked = extended_public_key_type( packed );
      BOOST_CHECK( type == unpacked );
   } catch ( const fc::exception& e )
   {
      edump((e.to_detail_string()));
      throw;
   }
}

BOOST_AUTO_TEST_CASE( version_test )
{
   try
   {
      BOOST_REQUIRE_EQUAL( string( version( 1, 2, 3) ), "1.2.3" );

      fc::variant ver_str( "3.0.0" );
      version ver;
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == version( 3, 0 , 0 ) );

      ver_str = fc::variant( "0.0.0" );
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == version() );

      ver_str = fc::variant( "1.0.1" );
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == version( 1, 0, 1 ) );

      ver_str = fc::variant( "1_0_1" );
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == version( 1, 0, 1 ) );

      ver_str = fc::variant( "12.34.56" );
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == version( 12, 34, 56 ) );

      ver_str = fc::variant( "256.0.0" );
      SURF_REQUIRE_THROW( fc::from_variant( ver_str, ver ), fc::exception );

      ver_str = fc::variant( "0.256.0" );
      SURF_REQUIRE_THROW( fc::from_variant( ver_str, ver ), fc::exception );

      ver_str = fc::variant( "0.0.65536" );
      SURF_REQUIRE_THROW( fc::from_variant( ver_str, ver ), fc::exception );

      ver_str = fc::variant( "1.0" );
      SURF_REQUIRE_THROW( fc::from_variant( ver_str, ver ), fc::exception );

      ver_str = fc::variant( "1.0.0.1" );
      SURF_REQUIRE_THROW( fc::from_variant( ver_str, ver ), fc::exception );
   }
   FC_LOG_AND_RETHROW();
}

BOOST_AUTO_TEST_CASE( hardfork_version_test )
{
   try
   {
      BOOST_REQUIRE_EQUAL( string( hardfork_version( 1, 2 ) ), "1.2.0" );

      fc::variant ver_str( "3.0.0" );
      hardfork_version ver;
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == hardfork_version( 3, 0 ) );

      ver_str = fc::variant( "0.0.0" );
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == hardfork_version() );

      ver_str = fc::variant( "1.0.0" );
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == hardfork_version( 1, 0 ) );

      ver_str = fc::variant( "1_0_0" );
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == hardfork_version( 1, 0 ) );

      ver_str = fc::variant( "12.34.00" );
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == hardfork_version( 12, 34 ) );

      ver_str = fc::variant( "256.0.0" );
      SURF_REQUIRE_THROW( fc::from_variant( ver_str, ver ), fc::exception );

      ver_str = fc::variant( "0.256.0" );
      SURF_REQUIRE_THROW( fc::from_variant( ver_str, ver ), fc::exception );

      ver_str = fc::variant( "0.0.1" );
      fc::from_variant( ver_str, ver );
      BOOST_REQUIRE( ver == hardfork_version( 0, 0 ) );

      ver_str = fc::variant( "1.0" );
      SURF_REQUIRE_THROW( fc::from_variant( ver_str, ver ), fc::exception );

      ver_str = fc::variant( "1.0.0.1" );
      SURF_REQUIRE_THROW( fc::from_variant( ver_str, ver ), fc::exception );
   }
   FC_LOG_AND_RETHROW();
}

BOOST_AUTO_TEST_CASE( min_block_size )
{
   signed_block b;
   while( b.witness.length() < SURF_MIN_ACCOUNT_NAME_LENGTH )
      b.witness += 'a';
   size_t min_size = fc::raw::pack_size( b );
   BOOST_CHECK( min_size == SURF_MIN_BLOCK_SIZE );
}

BOOST_AUTO_TEST_CASE(unpack_clear_test) {
   try {
      std::stringstream ss1;
      std::stringstream ss2;

      signed_block b1;

      for (int i = 0; i < 10; i++) {
         signed_transaction tx;

         vote_operation op;
         op.voter = "alice";
         op.author = "bob";
         op.permlink = "permlink1";
         op.weight = SURF_100_PERCENT;
         tx.operations.push_back(op);

         vote_operation op2;
         op2.voter = "charlie";
         op2.author = "sam";
         op2.permlink = "permlink2";
         op2.weight = SURF_100_PERCENT;
         tx.operations.push_back(op2);

         tx.ref_block_num = 1000;
         tx.ref_block_prefix = 1000000000;
         tx.expiration = fc::time_point_sec(1514764800 + i);

         b1.transactions.push_back(tx);
      }

      signed_block b2;

      for (int i = 0; i < 20; i++) {
         signed_transaction tx;
         vote_operation op;
         op.voter = "dave";
         op.author = "greg";
         op.permlink = "foobar";
         op.weight = SURF_100_PERCENT/2;
         tx.ref_block_num = 4000;
         tx.ref_block_prefix = 4000000000;
         tx.expiration = fc::time_point_sec(1714764800 + i);
         tx.operations.push_back(op);

         b2.transactions.push_back(tx);
      }

      fc::raw::pack(ss2, b2);
      fc::raw::pack(ss1, b1);

      signed_block unpacked_block;
      fc::raw::unpack(ss2, unpacked_block);

      // This operation should completely overwrite signed block 'b2'
      fc::raw::unpack(ss1, unpacked_block);

      BOOST_REQUIRE(b1.transactions.size() == unpacked_block.transactions.size());
      for (size_t i = 0; i < unpacked_block.transactions.size(); i++) {
         signed_transaction tx = unpacked_block.transactions[i];
         BOOST_REQUIRE(unpacked_block.transactions[i].operations.size() == b1.transactions[i].operations.size());

         vote_operation op = tx.operations[0].get<vote_operation>();
         BOOST_REQUIRE(op.voter == "alice");
         BOOST_REQUIRE(op.author == "bob");
         BOOST_REQUIRE(op.permlink == "permlink1");
         BOOST_REQUIRE(op.weight == SURF_100_PERCENT);

         vote_operation op2 = tx.operations[1].get<vote_operation>();
         BOOST_REQUIRE(op2.voter == "charlie");
         BOOST_REQUIRE(op2.author == "sam");
         BOOST_REQUIRE(op2.permlink == "permlink2");
         BOOST_REQUIRE(op2.weight == SURF_100_PERCENT);

         BOOST_REQUIRE(tx.ref_block_num == 1000);
         BOOST_REQUIRE(tx.ref_block_prefix == 1000000000);
         BOOST_REQUIRE(tx.expiration == fc::time_point_sec(1514764800 + i));
     }
   } FC_LOG_AND_RETHROW();
}

BOOST_AUTO_TEST_CASE(unpack_recursion_test) {
   try {
       std::stringstream ss;
       int recursion_level = 100000;
       uint64_t allocation_per_level = 500000;
       for (int i = 0; i < recursion_level; i++) {
          fc::raw::pack(ss, unsigned_int(allocation_per_level));
          fc::raw::pack(ss, static_cast<uint8_t>(variant::array_type));
       }
       std::vector<fc::variant> v;
       SURF_REQUIRE_THROW(fc::raw::unpack(ss, v), fc::assert_exception);
   } FC_LOG_AND_RETHROW();
}



BOOST_AUTO_TEST_SUITE_END()
#endif
