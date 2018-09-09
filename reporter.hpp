
#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/currency.hpp>
#include <eosiolib/multi_index.hpp>
#include <eosiolib/contract.hpp>


namespace eosio {
    static const account_name _self = N(reporter);
    static const eosio::symbol_name _SYM = S(4, FLO);

    // @abi table income i64
    struct income {
        uint64_t id;
        account_name username;
        std::string amount;
        std::string trx;
        uint64_t status=0;

        uint64_t primary_key()const { return id; }

        EOSLIB_SERIALIZE( income, (id)(username)(amount)(trx)(status))

    };
    typedef eosio::multi_index<N(income), income> income_index;

    // @abi table outcome i64
    struct outcome {
        uint64_t id;
        account_name username;
        std::string addr;
        eosio::asset amount;
        uint64_t status;

        uint64_t primary_key()const { return id; }


        EOSLIB_SERIALIZE( outcome, (id)(username)(addr)(amount)(status))
    };
    typedef eosio::multi_index<N(outcome), outcome> outcome_index;


    // @abi table account
    struct account{
        account_name username;
        std::string addr;
        uint64_t primary_key()const { return username; }
        
        EOSLIB_SERIALIZE( account, (username)(addr))
    };
    typedef eosio::multi_index <N(account), account> account_index;
    




    /* ACTIONS */



    // @abi action
    struct setaddr{
        account_name username;
        std::string addr;

        EOSLIB_SERIALIZE( setaddr, (username)(addr))
    };

    
    // @abi action 
    struct setinc{
        account_name username;
        std::string trx;
        std::string amount;

        EOSLIB_SERIALIZE( setinc, (username)(trx)(amount))

    };

    // @abi action
    struct setout{
        uint64_t id;

        EOSLIB_SERIALIZE( setout, (id))

    };
   
};






