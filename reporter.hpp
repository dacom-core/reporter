
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
        std::string baseasset;
        uint64_t baseamount;
        uint64_t buyrate;
        uint64_t status=0;

        uint64_t primary_key()const { return id; }

        EOSLIB_SERIALIZE( income, (id)(username)(amount)(trx)(baseamount)(status))

    };
    typedef eosio::multi_index<N(income), income> income_index;

    // @abi table outcome i64
    struct outcome {
        uint64_t id;
        account_name username;
        std::string addr;
        std::string txn;
        eosio::asset amount;
        uint64_t sellrate;
        uint64_t quoteamount;
        std::string quoteasset;
        uint64_t status;

        uint64_t primary_key()const { return id; }


        EOSLIB_SERIALIZE( outcome, (id)(username)(addr)(txn)(amount)(sellrate)(quoteamount)(status))
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
        std::string addr;

        EOSLIB_SERIALIZE( setaddr, (username)(addr))
    };

    
    // @abi action 
    struct setinc{
        account_name username;
        std::string trx;
        uint64_t baseamount;
        std::string baseasset;

        EOSLIB_SERIALIZE( setinc, (username)(trx)(baseamount))

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






