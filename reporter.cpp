#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/print.hpp>
#include "reporter.hpp"
using namespace eosio;

struct impl {


//Устанавливаем адрес при регистрации нового аккаунта (актор - регистратор)
    void setaddr_action(const setaddr &op){
        require_auth(_self);
        
        account_index accounts(_self, _self);
        auto acc = accounts.find(op.username);
        if (acc == accounts.end()) {
            accounts.emplace(_self, [&](auto &a){
                a.username = op.username;
                a.addr = op.addr;
            });
        } else {
            accounts.modify(acc, _self,[&](auto &a){
                a.addr = op.addr;
            });
        }
           
    }

//В момент поступлений, добавляем инкам 
    void setinc_action(const setinc &op){
        require_auth(_self);
        
        income_index incomes(_self, _self);
        account_index accounts (_self, _self);

        auto acc = accounts.find(op.username);

        incomes.emplace(_self, [&](auto &a){
            a.id = incomes.available_primary_key();
            a.username = op.username;
            a.trx = op.trx;
        });   
    }

//После фактического вывода, изменяем статус
    void setout_action(const setout &op){
        require_auth(_self);
        
        outcome_index outcomes(_self, _self);
        auto out = outcomes.find(op.id);

        outcomes.modify(out, _self, [&](auto &a){
            a.status = 1;
        });   
    }


//В момент трансфера на аккаунт контракта, добавляем в базу новый вывод и ожидаем подтверждения от шлюза о
// завершении. 
    void withdraw ( account_name username, std::string addr, eosio::asset amount){
        require_auth(username);

        eosio_assert( amount.is_valid(), "Rejected. Invalid quantity" );
        eosio_assert( amount.symbol == _SYM, "Rejected. Invalid symbol for this contract.");
        
        outcome_index outcomes (_self, _self);
     
        outcomes.emplace(_self, [&](auto &a){
            a.id = outcomes.available_primary_key();
            a.username = username;
            a.addr = addr;
            a.amount = amount;
            a.status = 0;
        });  

    };





    void apply( uint64_t /*receiver*/, uint64_t code, uint64_t action ) {

      if (code == _self) {
         
         if (action == N(setaddr)){
            setaddr_action(eosio::unpack_action_data<setaddr>());
         }
         if (action == N(setinc)){
            setinc_action(eosio::unpack_action_data<setinc>());
         }
         if (action == N(setout)){
            setout_action(eosio::unpack_action_data<setout>());
         }
     };

     if (action == N(transfer))
     {
        if (code == N(eosio.token)){
            
            auto op = eosio::unpack_action_data<eosio::currency::transfer>();

            if (op.from != _self){
                eosio_assert(op.memo != "", "Rejected. Require address in memo field");
                auto addr = op.memo.c_str();
                withdraw(op.from, addr, op.quantity);
            }
        } else {
            eosio_assert(false, "Rejected");
        }
     } 
   }


   

};

extern "C" {
   
   /// The apply method implements the dispatch of events to this contract
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) {
      impl().apply(receiver, code, action);
   }

}; 