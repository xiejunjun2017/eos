/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <eoslib/eos.hpp>
#include <eoslib/db.hpp>

namespace proxy {
   
   //@abi proxy action
   struct PACKED( SetOwner ) {
      AccountName owner;	
   };

   //@abi proxy table
   struct PACKED( Config ) {
      Config( AccountName o = AccountName() ):owner(o){}
      const uint64_t     key = N(config);
      AccountName        owner;
   };

   using Configs = Table<N(proxy),N(proxy),N(configs),Config,uint64_t>;

} /// namespace proxy