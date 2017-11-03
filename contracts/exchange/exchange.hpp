/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <currency/currency.hpp>

namespace exchange {

   using currency::CurrencyTokens;
   using EosTokens = eos::Tokens;

   //@abi action cancelbuy cancelsell
   struct OrderID {
      AccountName name    = 0;
      uint64_t    number  = 0;
   };

   typedef eos::price<EosTokens,CurrencyTokens>     Price;

   //@abi table
   struct PACKED( Bid ) {
      OrderID            buyer;
      Price              price;
      EosTokens          quantity;
      Time               expiration;

      void print() {
         eos::print( "{ quantity: ", quantity, ", price: ", price, " }" );
      }
   };
   static_assert( sizeof(Bid) == 32+12, "unexpected padding" );
   
   //@abi table
   struct PACKED( Ask ) {
      OrderID          seller;
      Price            price;
      CurrencyTokens   quantity;
      Time             expiration;

      void print() {
         eos::print( "{ quantity: ", quantity, ", price: ", price, " }" );
      }
   };
   static_assert( sizeof(Ask) == 32+12, "unexpected padding" );

   //@abi table i64
   struct PACKED( Account ) {
      Account( AccountName o = AccountName() ):owner(o){}

      AccountName        owner;
      EosTokens          eos_balance;
      CurrencyTokens     currency_balance;
      uint32_t           open_orders = 0;

      bool isEmpty()const { return ! ( bool(eos_balance) | bool(currency_balance) | open_orders); }
   };

   using Accounts = Table<N(exchange),N(exchange),N(account),Account,uint64_t>;

   TABLE2(Bids,exchange,exchange,bids,Bid,BidsById,OrderID,BidsByPrice,Price); 
   TABLE2(Asks,exchange,exchange,asks,Ask,AsksById,OrderID,AsksByPrice,Price); 


   //@abi action buy
   struct BuyOrder : public Bid  { uint8_t fill_or_kill = false; };
   
   //@abi action sell
   struct SellOrder : public Ask { uint8_t fill_or_kill = false; };

   inline Account getAccount( AccountName owner ) {
      Account account(owner);
      Accounts::get( account );
      return account;
   }
}

