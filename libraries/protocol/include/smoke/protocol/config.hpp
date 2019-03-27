/*
 * Copyright (c) 2016 Surfit, Inc., and contributors.
 */
#pragma once

#define SURF_BLOCKCHAIN_VERSION              ( version(0, 0, 6) )
#define SURF_BLOCKCHAIN_HARDFORK_VERSION     ( hardfork_version( SURF_BLOCKCHAIN_VERSION ) )

#ifdef IS_TEST_NET
#define SURF_INIT_PRIVATE_KEY                (fc::ecc::private_key::regenerate(fc::sha256::hash(std::string("init_key"))))
#define SURF_INIT_PUBLIC_KEY_STR             (std::string( surf::protocol::public_key_type(SURF_INIT_PRIVATE_KEY.get_public_key()) ))
#define SURF_CHAIN_ID                        (fc::sha256::hash("testnet"))

#define VESTS_SYMBOL  (uint64_t(6) | (uint64_t('V') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< VESTS with 6 digits of precision
#define SURF_SYMBOL  (uint64_t(3) | (uint64_t('T') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< TESTS with 3 digits of precision

#define SURF_SYMBOL_STR                      "TESTS"
#define SURF_ADDRESS_PREFIX                  "TST"
#define SURF_GENESIS_TIME_EPOCH              1515765200
#define SURF_GENESIS_TIME                    (fc::time_point_sec(SURF_GENESIS_TIME_EPOCH))
#define SURF_CASHOUT_WINDOW_SECONDS          (60*60) /// 1 hr
#define SURF_UPVOTE_LOCKOUT                  (fc::minutes(5))

#define SURF_MIN_ACCOUNT_CREATION_FEE          0

#define SURF_OWNER_AUTH_RECOVERY_PERIOD                  fc::seconds(60)
#define SURF_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::seconds(12)
#define SURF_OWNER_UPDATE_LIMIT                          fc::seconds(0)
#define SURF_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 1
#else // IS LIVE SURF NETWORK

#define SURF_INIT_PUBLIC_KEY_STR             "SMK619jJm3VKrHRLbKaAkFXSCUBFwwv9d4yuTYM9KT6cjJV6zno1G"
#define SURF_CHAIN_ID                        (fc::sha256::hash("surfpubnet")) // 1ce08345e61cd3bf91673a47fc507e7ed01550dab841fd9cdb0ab66ef576aaf0
#define VESTS_SYMBOL  (uint64_t(6) | (uint64_t('V') << 8) | (uint64_t('E') << 16) | (uint64_t('S') << 24) | (uint64_t('T') << 32) | (uint64_t('S') << 40)) ///< VESTS with 6 digits of precision
#define SURF_SYMBOL  (uint64_t(3) | (uint64_t('S') << 8) | (uint64_t('M') << 16) | (uint64_t('O') << 24) | (uint64_t('K') << 32) | (uint64_t('E') << 40)) ///< SURF with 3 digits of precision
#define SURF_SYMBOL_STR                      "SURF"
#define SURF_ADDRESS_PREFIX                  "SMK"

#define SURF_GENESIS_TIME_EPOCH              1537690632  // 2018-09-23T08:17:12Z ( at testnet2 snapshot )
#define SURF_GENESIS_TIME                    (fc::time_point_sec(SURF_GENESIS_TIME_EPOCH))
#define SURF_CASHOUT_WINDOW_SECONDS          (60*60*24*7)  /// 7 days
#define SURF_UPVOTE_LOCKOUT                  (fc::hours(12))

#define SURF_MIN_ACCOUNT_CREATION_FEE         4200 // 4.2 SURF

#define SURF_OWNER_AUTH_RECOVERY_PERIOD                  fc::days(30)
#define SURF_ACCOUNT_RECOVERY_REQUEST_EXPIRATION_PERIOD  fc::days(1)
#define SURF_OWNER_UPDATE_LIMIT                          fc::minutes(60)
#define SURF_OWNER_AUTH_HISTORY_TRACKING_START_BLOCK_NUM 1 // 3186477

#endif

#define SURF_BLOCK_INTERVAL                  3
#define SURF_BLOCKS_PER_YEAR                 (365*24*60*60/SURF_BLOCK_INTERVAL)
#define SURF_BLOCKS_PER_DAY                  (24*60*60/SURF_BLOCK_INTERVAL)
#define SURF_START_MINER_VOTING_BLOCK        (1 * 30) // (SURF_BLOCKS_PER_DAY * 30)

#define SURF_MAX_WITNESSES                   21

#define SURF_INIT_MINER_NAME                 "initminer"

#define SURF_MAX_VOTED_WITNESSES             20
#define SURF_MAX_MINER_WITNESSES             0
#define SURF_MAX_RUNNER_WITNESSES            1

#define SURF_HARDFORK_REQUIRED_WITNESSES     17 // 17 of the 21 dpos witnesses (20 elected and 1 virtual time) required for hardfork. This guarantees 75% participation on all subsequent rounds.
#define SURF_MAX_TIME_UNTIL_EXPIRATION       (60*60) // seconds,  aka: 1 hour
#define SURF_MAX_MEMO_SIZE                   2048
#define SURF_MAX_PROXY_RECURSION_DEPTH       4
#define SURF_VESTING_WITHDRAW_INTERVALS      13
#define SURF_VESTING_WITHDRAW_INTERVAL_SECONDS (60*60*24*7) /// 1 week per interval

#define SURF_MAX_WITHDRAW_ROUTES             10
#define SURF_VOTE_REGENERATION_SECONDS       (5*60*60*24) // 5 day
#define SURF_MAX_VOTE_CHANGES                5
#define SURF_REVERSE_AUCTION_WINDOW_SECONDS  (60*30) /// 30 minutes
#define SURF_MIN_VOTE_INTERVAL_SEC           3
#define SURF_VOTE_DUST_THRESHOLD             (10000) // new user has 4.2 SURF POWER when creating account

#define SURF_MIN_ROOT_COMMENT_INTERVAL       (fc::seconds(60*5)) // 5 minutes
#define SURF_MIN_REPLY_INTERVAL              (fc::seconds(20)) // 20 seconds

#define SURF_MAX_ACCOUNT_WITNESS_VOTES       30

#define SURF_100_PERCENT                     10000
#define SURF_1_PERCENT                       (SURF_100_PERCENT/100)
#define SURF_1_TENTH_PERCENT                 (SURF_100_PERCENT/1000)

#define SURF_INFLATION_RATE_START_PERCENT    (978) // 9.5%
#define SURF_INFLATION_RATE_STOP_PERCENT     (487) // 4.87%
#define SURF_INFLATION_NARROWING_PERIOD      (250000) // Narrow 0.01% every 250k blocks
#define SURF_CONTENT_REWARD_PERCENT          (75*SURF_1_PERCENT) //75% of inflation, 7.125% inflation
#define SURF_VESTING_FUND_PERCENT            (15*SURF_1_PERCENT) //15% of inflation, 1.425% inflation

#define SURF_CONTENT_CURATE_REWARD_PERCENT   (50*SURF_1_PERCENT) // % of SURF_CONTENT_REWARD_PERCENT only

#define SURF_BANDWIDTH_AVERAGE_WINDOW_SECONDS (60*60*24*7) ///< 1 week
#define SURF_BANDWIDTH_PRECISION             (uint64_t(1000000)) ///< 1 million
#define SURF_MAX_COMMENT_DEPTH               0xffff // 64k
#define SURF_SOFT_MAX_COMMENT_DEPTH          0xff // 255

#define SURF_MAX_RESERVE_RATIO               (20000)

#define SURF_CREATE_ACCOUNT_WITH_SURF_MODIFIER 30
#define SURF_CREATE_ACCOUNT_DELEGATION_RATIO    5
#define SURF_CREATE_ACCOUNT_DELEGATION_TIME     fc::days(30)

#define SURF_EQUIHASH_N                      140
#define SURF_EQUIHASH_K                      6

#define SURF_ACTIVE_CHALLENGE_FEE            asset( 2000, SURF_SYMBOL )
#define SURF_OWNER_CHALLENGE_FEE             asset( 30000, SURF_SYMBOL )

#define SURF_POST_REWARD_FUND_NAME           ("post")
#define SURF_RECENT_RSHARES_DECAY_RATE       (fc::days(15))
#define SURF_CONTENT_CONSTANT                (uint128_t(uint64_t(2000000000000ll)))

#define SURF_MIN_PAYOUT_SURF                20
#define SURF_MIN_ACCOUNT_NAME_LENGTH          3
#define SURF_MAX_ACCOUNT_NAME_LENGTH         16

#define SURF_MIN_PERMLINK_LENGTH             0
#define SURF_MAX_PERMLINK_LENGTH             256
#define SURF_MAX_WITNESS_URL_LENGTH          2048

#define SURF_INIT_SUPPLY                     int64_t(42000000000ll) // 42m SURF
#define SURF_MAX_SHARE_SUPPLY                int64_t(1000000000000000ll)
#define SURF_MAX_SIG_CHECK_DEPTH             2

#define SURF_SECONDS_PER_YEAR                (uint64_t(60*60*24*365ll))

#define SURF_MAX_TRANSACTION_SIZE            (1024*64)
#define SURF_MIN_BLOCK_SIZE_LIMIT            (SURF_MAX_TRANSACTION_SIZE)
#define SURF_MAX_BLOCK_SIZE                  (SURF_MAX_TRANSACTION_SIZE*SURF_BLOCK_INTERVAL*2000)
#define SURF_SOFT_MAX_BLOCK_SIZE             (2*1024*1024)
#define SURF_MIN_BLOCK_SIZE                  115
#define SURF_BLOCKS_PER_HOUR                 (60*60/SURF_BLOCK_INTERVAL)
#define SURF_MIN_UNDO_HISTORY                10
#define SURF_MAX_UNDO_HISTORY                10000

#define SURF_MIN_TRANSACTION_EXPIRATION_LIMIT (SURF_BLOCK_INTERVAL * 5) // 5 transactions per block

#define SURF_IRREVERSIBLE_THRESHOLD          (75 * SURF_1_PERCENT)
#define VIRTUAL_SCHEDULE_LAP_LENGTH           ( fc::uint128::max_value() )

/**
 *  Reserved Account IDs with special meaning
 */
///@{
/// Represents the current witnesses
#define SURF_MINER_ACCOUNT                   "miners"
/// Represents the canonical account with NO authority (nobody can access funds in null account)
#define SURF_NULL_ACCOUNT                    "null"
/// Represents the canonical account with WILDCARD authority (anybody can access funds in temp account)
#define SURF_TEMP_ACCOUNT                    "temp"
/// Represents the canonical account for specifying you will vote for directly (as opposed to a proxy)
#define SURF_PROXY_TO_SELF_ACCOUNT           ""
/// Represents the canonical root post parent account
#define SURF_ROOT_POST_PARENT                (account_name_type())
///@}

#define SURF_SURF_ACCOUNT                   "surf"
