
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/currency.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/contract.hpp>


namespace eosio {
    static const account_name _self = N(reporter);
    static const eosio::symbol_name _SYM = S(4, DBTC);

    // @abi table income i64
    struct income {
        uint64_t id;
        account_name username;
        eosio::asset quoteamount;
        std::string txn;
        uint64_t baseamount;
        uint64_t buyrate;
        uint64_t status=0;

        uint64_t primary_key()const { return id; }

        EOSLIB_SERIALIZE( income, (id)(username)(quoteamount)(txn)(baseamount)(buyrate)(status))

    };
    typedef eosio::multi_index<N(income), income> income_index;

    // @abi table outcome i64
    struct outcome {
        uint64_t id;
        account_name username;
        std::string addr;
        std::string txn;
        eosio::asset baseamount;
        uint64_t sellrate;
        uint64_t quoteamount;
        uint64_t status;

        uint64_t primary_key()const { return id; }


        EOSLIB_SERIALIZE( outcome, (id)(username)(addr)(txn)(baseamount)(sellrate)(quoteamount)(status))
    };
    typedef eosio::multi_index<N(outcome), outcome> outcome_index;


    // @abi table addrs
    struct addrs{
        account_name username;
        std::string btc;
        uint64_t primary_key()const { return username; }
        
        EOSLIB_SERIALIZE( addrs, (username)(btc))
    };
    typedef eosio::multi_index <N(addrs), addrs> addrs_index;
    
    // @abi table rates
    struct rates{
        uint64_t id;
        uint64_t buyrate;
        uint64_t sellrate;

        uint64_t primary_key()const { return id; }
        
        EOSLIB_SERIALIZE( rates, (id)(buyrate)(sellrate))
    };
    typedef eosio::multi_index <N(rates), rates> rates_index;
    





    /* ACTIONS */



    // @abi action
    struct setaddr{
        account_name username;
        std::string btc;

        EOSLIB_SERIALIZE( setaddr, (username)(btc))
    };

    
    // @abi action 
    struct setinc{
        account_name username;
        std::string txn;
        uint64_t baseamount;
        eosio::asset quoteamount;
        EOSLIB_SERIALIZE( setinc, (username)(txn)(baseamount)(quoteamount))

    };

    // @abi action
    struct setout{
        uint64_t id;
        std::string txn;
        EOSLIB_SERIALIZE( setout, (id)(txn))

    };


    // @abi action
    struct setrate{
        uint64_t buyrate;
        uint64_t sellrate;

        EOSLIB_SERIALIZE( setrate, (buyrate)(sellrate))

    };

   
};






