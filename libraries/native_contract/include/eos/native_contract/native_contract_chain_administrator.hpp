/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eos/chain/chain_administration_interface.hpp>

namespace eosio { namespace native_contract {
using chain::ProducerRound;

class native_contract_chain_administrator : public chain::chain_administration_interface {
   ProducerRound get_next_round(chainbase::database& db);
   chain::BlockchainConfiguration get_blockchain_configuration(const chainbase::database& db,
                                                               const ProducerRound& round);
};

inline std::unique_ptr<chain::chain_administration_interface> make_administrator() {
   return std::unique_ptr<chain::chain_administration_interface>(new native_contract_chain_administrator());
}

} } // namespace eosio::native_contract
