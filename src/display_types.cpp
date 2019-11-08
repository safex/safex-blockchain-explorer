//
// Created by igor on 17.8.18..
//

#include "display_types.h"
#include "../../safexcore/src/cryptonote_basic/cryptonote_basic.h"

namespace safexeg
{

  public_key const &get_public_key(displayable_output const &d_out)
  {
    struct visitor : public boost::static_visitor<public_key const &>
    {
      public_key const &operator()(const txout_to_key &txin) const
      {
        return txin.key;
      }

      public_key const &operator()(const txout_token_to_key &txin) const
      {
        return txin.key;
      }

      public_key const &operator()(const txout_to_script &txout) const
      {
        return txout.keys[0];
      }
    };
    return boost::apply_visitor(visitor{}, d_out);
  }

  key_image const &get_key_image(displayable_input const &d_in)
  {
    struct visitor : public boost::static_visitor<key_image const &>
    {
      key_image const &operator()(const txin_to_key &txin) const
      {
        return txin.k_image;
      }

      key_image const &operator()(const txin_token_to_key &txin) const
      {
        return txin.k_image;
      }

      key_image const &operator()(const txin_token_migration &txin) const
      {
        return txin.k_image;
      }

      key_image const &operator()(const txin_to_script &txin) const
      {
        return txin.k_image;
      }
    };
    return boost::apply_visitor(visitor{}, d_in);
  }

  uint64_t get_cash_amount(displayable_input const &d_in)
  {
    struct visitor : public boost::static_visitor<uint64_t>
    {
      uint64_t operator()(const txin_to_key &txin) const
      {
        return txin.amount;
      }

      uint64_t operator()(const txin_token_to_key &txin) const
      {
        return 0;
      }

      uint64_t operator()(const txin_token_migration &txin) const
      {
        return 0;
      }

      uint64_t operator()(const txin_to_script &txin) const
      {
        return txin.amount;
      }
    };
    return boost::apply_visitor(visitor{}, d_in);
  }

  uint64_t get_token_amount(displayable_input const &d_in)
  {
    struct visitor : public boost::static_visitor<uint64_t>
    {
      uint64_t operator()(const txin_to_key &txin) const
      {
        return 0;
      }

      uint64_t operator()(const txin_token_to_key &txin) const
      {
        return txin.token_amount;
      }

      uint64_t operator()(const txin_token_migration &txin) const
      {
        return txin.token_amount;
      }

      uint64_t operator()(const txin_to_script &txin) const
      {
        return txin.token_amount;
      }
    };
    return boost::apply_visitor(visitor{}, d_in);
  }

  std::vector <uint64_t> const &get_key_offsets(displayable_input const &d_in)
  {
    static std::vector <uint64_t> empty{};
    struct visitor
            : public boost::static_visitor<std::vector < uint64_t> const &> {
      std::vector <uint64_t> const &operator()(const txin_to_key &txin) const
      {
        return txin.key_offsets;
      }

      std::vector <uint64_t> const &
      operator()(const txin_token_to_key &txin) const
      {
        return txin.key_offsets;
      }

      std::vector <uint64_t> const &
      operator()(const txin_token_migration &txin) const
      {
        return empty;
      }

      std::vector <uint64_t> const &
      operator()(const txin_to_script &txin) const
      {
        return txin.key_offsets;
      }
    };
    return boost::apply_visitor(visitor{}, d_in);
  }

  tx_out_type get_out_type(displayable_input const &d_in)
  {
    struct visitor : public boost::static_visitor<tx_out_type>
    {
      tx_out_type operator()(const txin_to_key &txin) const
      {
        return tx_out_type::out_cash;
      }

      tx_out_type operator()(const txin_token_to_key &txin) const
      {
        return tx_out_type::out_token;
      }

      tx_out_type operator()(const txin_token_migration &txin) const
      {
        return tx_out_type::out_token;
      }

      tx_out_type operator()(const cryptonote::txin_to_script &txin) const
      {
        //TODO: GRKI Token collect missing
        switch (txin.command_type) {
          case safex::command_t::donate_network_fee:
            return tx_out_type::out_cash;
          case safex::command_t::token_stake:
            return tx_out_type::out_token;
          case safex::command_t::token_unstake:
            return tx_out_type::out_staked_token;
          case safex::command_t::distribute_network_fee:
            return tx_out_type::out_network_fee;
          case safex::command_t::create_account:
              return tx_out_type::out_safex_account;
          case safex::command_t::edit_account:
              return tx_out_type::out_safex_account_update;
          case safex::command_t::nop:
          default:
            return tx_out_type::out_invalid;
        }
      }
    };
    return boost::apply_visitor(visitor{}, d_in);
  }

  tx_out_type get_out_type(displayable_output const &d_in)
  {
    struct visitor : public boost::static_visitor<tx_out_type>
    {
      tx_out_type operator()(const txout_to_key &txout) const
      {
        return tx_out_type::out_cash;
      }

      tx_out_type operator()(const txout_token_to_key &txout) const
      {
        return tx_out_type::out_token;
      }

      tx_out_type operator()(const txout_to_script &txout) const
      {
        return static_cast<tx_out_type>(txout.output_type);
      }
    };
    return boost::apply_visitor(visitor{}, d_in);
  }

  boost::optional<crypto::hash const &> get_bitcoin_hash(displayable_input const &d_in)
  {
    struct visitor : public boost::static_visitor<boost::optional<crypto::hash const & >> {
            boost::optional < crypto::hash const &> operator()(const txin_to_key &txin) const
            {
              return {};
            }

            boost::optional<crypto::hash const &> operator()(const txin_token_to_key &txin) const
            {
              return {};
            }

            boost::optional<crypto::hash const &> operator()(const txin_token_migration &txin) const
            {
              return txin.bitcoin_burn_transaction;
            }

            boost::optional < crypto::hash const &> operator()(const txin_to_script &txin) const
            {
              return {};
            }

    };
    return boost::apply_visitor(visitor{}, d_in);
  }

  std::string const &get_type_string(displayable_input const &d_in)
  {
    static std::string cash{"cash"};
    static std::string token{"token"};
    static std::string migration{"migration"};
    static std::string staked_token{"staked token"};
    static std::string collected_network_fee{"collected network fee"};
    static std::string create_account{"create account"};
    static std::string edit_account{"edit account"};
    static std::string invalid_type{"invalid type"};

    struct visitor : public boost::static_visitor<std::string const &>
    {
      std::string const &operator()(const txin_to_key &) const
      {
        return cash;
      }

      std::string const &operator()(const txin_token_to_key &) const
      {
        return token;
      }

      std::string const &operator()(const txin_token_migration &) const
      {
        return migration;
      }

      std::string const &operator()(const txin_to_script &txin) const
      {

        switch (txin.command_type) {
          case safex::command_t::donate_network_fee:
            return cash;
          case safex::command_t::token_stake:
            return token;
          case safex::command_t::token_unstake:
          case safex::command_t::token_collect:
            return staked_token;
          case safex::command_t::distribute_network_fee:
            return collected_network_fee;
          case safex::command_t::create_account:
              return create_account;
          case safex::command_t::edit_account:
              return edit_account;
          case safex::command_t::nop:
          default:
            return invalid_type;
        }
      }
    };
    return boost::apply_visitor(visitor{}, d_in);
  }

  std::string const &get_type_string(const cryptonote::tx_out_type output_type)
  {
    static const std::string cash{"cash"};
    static const std::string token{"token"};
    static const std::string migration{"migration"};
    static const std::string staked_token{"staked token"};
    static const std::string collected_network_fee{"collected network fee"};
    static const std::string create_account{"create account"};
    static const std::string edit_account{"edit account"};
    static const std::string invalid_type{"invalid type"};
    static const std::string advanced_outout{"advanced output"};


    switch (output_type)
    {
      case cryptonote::tx_out_type::out_cash:
        return cash;
      case cryptonote::tx_out_type::out_token:
        return token;
      case cryptonote::tx_out_type::out_staked_token:
        return staked_token;
      case cryptonote::tx_out_type::out_network_fee:
        return collected_network_fee;
      case cryptonote::tx_out_type::out_advanced:
        return collected_network_fee;
      case cryptonote::tx_out_type::out_safex_account:
        return create_account;
      case cryptonote::tx_out_type::out_safex_account_update:
        return edit_account;
      case cryptonote::tx_out_type::out_invalid:
      default:
        return invalid_type;
    }
  }

}