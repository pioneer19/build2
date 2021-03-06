// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

// Begin prologue.
//
#include <bpkg/types-parsers.hxx>
//
// End prologue.

#include <bpkg/bpkg-options.hxx>

#include <map>
#include <set>
#include <string>
#include <vector>
#include <ostream>
#include <sstream>

namespace bpkg
{
  namespace cli
  {
    template <typename X>
    struct parser
    {
      static void
      parse (X& x, bool& xs, scanner& s)
      {
        using namespace std;

        const char* o (s.next ());
        if (s.more ())
        {
          string v (s.next ());
          istringstream is (v);
          if (!(is >> x && is.peek () == istringstream::traits_type::eof ()))
            throw invalid_value (o, v);
        }
        else
          throw missing_value (o);

        xs = true;
      }

      static void
      merge (X& b, const X& a)
      {
        b = a;
      }
    };

    template <>
    struct parser<bool>
    {
      static void
      parse (bool& x, scanner& s)
      {
        s.next ();
        x = true;
      }

      static void
      merge (bool& b, const bool&)
      {
        b = true;
      }
    };

    template <>
    struct parser<std::string>
    {
      static void
      parse (std::string& x, bool& xs, scanner& s)
      {
        const char* o (s.next ());

        if (s.more ())
          x = s.next ();
        else
          throw missing_value (o);

        xs = true;
      }

      static void
      merge (std::string& b, const std::string& a)
      {
        b = a;
      }
    };

    template <typename X>
    struct parser<std::vector<X> >
    {
      static void
      parse (std::vector<X>& c, bool& xs, scanner& s)
      {
        X x;
        bool dummy;
        parser<X>::parse (x, dummy, s);
        c.push_back (x);
        xs = true;
      }

      static void
      merge (std::vector<X>& b, const std::vector<X>& a)
      {
        b.insert (b.end (), a.begin (), a.end ());
      }
    };

    template <typename X>
    struct parser<std::set<X> >
    {
      static void
      parse (std::set<X>& c, bool& xs, scanner& s)
      {
        X x;
        bool dummy;
        parser<X>::parse (x, dummy, s);
        c.insert (x);
        xs = true;
      }

      static void
      merge (std::set<X>& b, const std::set<X>& a)
      {
        b.insert (a.begin (), a.end ());
      }
    };

    template <typename K, typename V>
    struct parser<std::map<K, V> >
    {
      static void
      parse (std::map<K, V>& m, bool& xs, scanner& s)
      {
        const char* o (s.next ());

        if (s.more ())
        {
          std::string ov (s.next ());
          std::string::size_type p = ov.find ('=');

          K k = K ();
          V v = V ();
          std::string kstr (ov, 0, p);
          std::string vstr (ov, (p != std::string::npos ? p + 1 : ov.size ()));

          int ac (2);
          char* av[] =
          {
            const_cast<char*> (o),
            0
          };

          bool dummy;
          if (!kstr.empty ())
          {
            av[1] = const_cast<char*> (kstr.c_str ());
            argv_scanner s (0, ac, av);
            parser<K>::parse (k, dummy, s);
          }

          if (!vstr.empty ())
          {
            av[1] = const_cast<char*> (vstr.c_str ());
            argv_scanner s (0, ac, av);
            parser<V>::parse (v, dummy, s);
          }

          m[k] = v;
        }
        else
          throw missing_value (o);

        xs = true;
      }

      static void
      merge (std::map<K, V>& b, const std::map<K, V>& a)
      {
        for (typename std::map<K, V>::const_iterator i (a.begin ()); 
             i != a.end (); 
             ++i)
          b[i->first] = i->second;
      }
    };

    template <typename X, typename T, T X::*M>
    void
    thunk (X& x, scanner& s)
    {
      parser<T>::parse (x.*M, s);
    }

    template <typename X, typename T, T X::*M, bool X::*S>
    void
    thunk (X& x, scanner& s)
    {
      parser<T>::parse (x.*M, x.*S, s);
    }
  }
}

#include <map>
#include <cstring>

namespace bpkg
{
  // commands
  //

  commands::
  commands ()
  : help_ (),
    cfg_create_ (),
    rep_info_ (),
    rep_add_ (),
    rep_remove_ (),
    rep_list_ (),
    rep_fetch_ (),
    rep_create_ (),
    pkg_status_ (),
    pkg_build_ (),
    pkg_drop_ (),
    pkg_install_ (),
    pkg_uninstall_ (),
    pkg_update_ (),
    pkg_test_ (),
    pkg_clean_ (),
    pkg_verify_ (),
    pkg_fetch_ (),
    pkg_unpack_ (),
    pkg_checkout_ (),
    pkg_configure_ (),
    pkg_disfigure_ (),
    pkg_purge_ ()
  {
  }

  bool commands::
  parse (int& argc,
         char** argv,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (argc, argv, erase);
    bool r = _parse (s, opt, arg);
    return r;
  }

  bool commands::
  parse (int start,
         int& argc,
         char** argv,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (start, argc, argv, erase);
    bool r = _parse (s, opt, arg);
    return r;
  }

  bool commands::
  parse (int& argc,
         char** argv,
         int& end,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (argc, argv, erase);
    bool r = _parse (s, opt, arg);
    end = s.end ();
    return r;
  }

  bool commands::
  parse (int start,
         int& argc,
         char** argv,
         int& end,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (start, argc, argv, erase);
    bool r = _parse (s, opt, arg);
    end = s.end ();
    return r;
  }

  bool commands::
  parse (::bpkg::cli::scanner& s,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    bool r = _parse (s, opt, arg);
    return r;
  }

  void commands::
  merge (const commands& a)
  {
    CLI_POTENTIALLY_UNUSED (a);

    if (a.help_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->help_, a.help_);
    }

    if (a.cfg_create_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->cfg_create_, a.cfg_create_);
    }

    if (a.rep_info_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->rep_info_, a.rep_info_);
    }

    if (a.rep_add_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->rep_add_, a.rep_add_);
    }

    if (a.rep_remove_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->rep_remove_, a.rep_remove_);
    }

    if (a.rep_list_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->rep_list_, a.rep_list_);
    }

    if (a.rep_fetch_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->rep_fetch_, a.rep_fetch_);
    }

    if (a.rep_create_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->rep_create_, a.rep_create_);
    }

    if (a.pkg_status_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_status_, a.pkg_status_);
    }

    if (a.pkg_build_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_build_, a.pkg_build_);
    }

    if (a.pkg_drop_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_drop_, a.pkg_drop_);
    }

    if (a.pkg_install_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_install_, a.pkg_install_);
    }

    if (a.pkg_uninstall_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_uninstall_, a.pkg_uninstall_);
    }

    if (a.pkg_update_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_update_, a.pkg_update_);
    }

    if (a.pkg_test_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_test_, a.pkg_test_);
    }

    if (a.pkg_clean_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_clean_, a.pkg_clean_);
    }

    if (a.pkg_verify_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_verify_, a.pkg_verify_);
    }

    if (a.pkg_fetch_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_fetch_, a.pkg_fetch_);
    }

    if (a.pkg_unpack_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_unpack_, a.pkg_unpack_);
    }

    if (a.pkg_checkout_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_checkout_, a.pkg_checkout_);
    }

    if (a.pkg_configure_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_configure_, a.pkg_configure_);
    }

    if (a.pkg_disfigure_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_disfigure_, a.pkg_disfigure_);
    }

    if (a.pkg_purge_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->pkg_purge_, a.pkg_purge_);
    }
  }

  ::bpkg::cli::usage_para commands::
  print_usage (::std::ostream& os, ::bpkg::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mCOMMANDS\033[0m" << ::std::endl;

    os << std::endl
       << "\033[1mhelp\033[0m [\033[4mtopic\033[0m]             \033[1mbpkg-help(1)\033[0m -- show help for a command or help topic" << ::std::endl;

    os << "\033[1mcfg-create\033[0m|\033[1mcreate\033[0m        \033[1mbpkg-cfg-create(1)\033[0m -- create configuration" << ::std::endl;

    os << "\033[1mrep-info\033[0m                 \033[1mbpkg-rep-info(1)\033[0m -- print repository information" << ::std::endl;

    os << "\033[1mrep-add\033[0m|\033[1madd\033[0m              \033[1mbpkg-rep-add(1)\033[0m -- add repository to configuration" << ::std::endl;

    os << "\033[1mrep-remove\033[0m|\033[1mremove\033[0m        \033[1mbpkg-rep-remove(1)\033[0m -- remove repository from" << ::std::endl
       << "                         configuration" << ::std::endl;

    os << "\033[1mrep-list\033[0m|\033[1mlist\033[0m            \033[1mbpkg-rep-list(1)\033[0m -- list repositories in configuration" << ::std::endl;

    os << "\033[1mrep-fetch\033[0m|\033[1mfetch\033[0m          \033[1mbpkg-rep-fetch(1)\033[0m -- fetch list of available packages" << ::std::endl;

    os << "\033[1mrep-create\033[0m               \033[1mbpkg-rep-create(1)\033[0m -- create repository" << ::std::endl;

    os << "\033[1mpkg-status\033[0m|\033[1mstatus\033[0m        \033[1mbpkg-pkg-status(1)\033[0m -- print package status" << ::std::endl;

    os << "\033[1mpkg-build\033[0m|\033[1mbuild\033[0m          \033[1mbpkg-pkg-build(1)\033[0m -- build package" << ::std::endl;

    os << "\033[1mpkg-drop\033[0m|\033[1mdrop\033[0m            \033[1mbpkg-pkg-drop(1)\033[0m -- drop package" << ::std::endl;

    os << "\033[1mpkg-install\033[0m|\033[1minstall\033[0m      \033[1mbpkg-pkg-install(1)\033[0m -- install package" << ::std::endl;

    os << "\033[1mpkg-uninstall\033[0m|\033[1muninstall\033[0m  \033[1mbpkg-pkg-uninstall(1)\033[0m -- uninstall package" << ::std::endl;

    os << "\033[1mpkg-update\033[0m|\033[1mupdate\033[0m        \033[1mbpkg-pkg-update(1)\033[0m -- update package" << ::std::endl;

    os << "\033[1mpkg-test\033[0m|\033[1mtest\033[0m            \033[1mbpkg-pkg-test(1)\033[0m -- test package" << ::std::endl;

    os << "\033[1mpkg-clean\033[0m|\033[1mclean\033[0m          \033[1mbpkg-pkg-clean(1)\033[0m -- clean package" << ::std::endl;

    os << "\033[1mpkg-verify\033[0m               \033[1mbpkg-pkg-verify(1)\033[0m -- verify package archive" << ::std::endl;

    os << "\033[1mpkg-fetch\033[0m                \033[1mbpkg-pkg-fetch(1)\033[0m -- fetch package archive" << ::std::endl;

    os << "\033[1mpkg-unpack\033[0m               \033[1mbpkg-pkg-unpack(1)\033[0m -- unpack package archive" << ::std::endl;

    os << "\033[1mpkg-checkout\033[0m             \033[1mbpkg-pkg-checkout(1)\033[0m -- check out package version" << ::std::endl;

    os << "\033[1mpkg-configure\033[0m            \033[1mbpkg-pkg-configure(1)\033[0m -- configure package" << ::std::endl;

    os << "\033[1mpkg-disfigure\033[0m            \033[1mbpkg-pkg-disfigure(1)\033[0m -- disfigure package" << ::std::endl;

    os << "\033[1mpkg-purge\033[0m                \033[1mbpkg-pkg-purge(1)\033[0m -- purge package" << ::std::endl;

    p = ::bpkg::cli::usage_para::option;

    return p;
  }

  typedef
  std::map<std::string, void (*) (commands&, ::bpkg::cli::scanner&)>
  _cli_commands_map;

  static _cli_commands_map _cli_commands_map_;

  struct _cli_commands_map_init
  {
    _cli_commands_map_init ()
    {
      _cli_commands_map_["help"] =
      &::bpkg::cli::thunk< commands, bool, &commands::help_ >;
      _cli_commands_map_["cfg-create"] =
      &::bpkg::cli::thunk< commands, bool, &commands::cfg_create_ >;
      _cli_commands_map_["create"] =
      &::bpkg::cli::thunk< commands, bool, &commands::cfg_create_ >;
      _cli_commands_map_["rep-info"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_info_ >;
      _cli_commands_map_["rep-add"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_add_ >;
      _cli_commands_map_["add"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_add_ >;
      _cli_commands_map_["rep-remove"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_remove_ >;
      _cli_commands_map_["remove"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_remove_ >;
      _cli_commands_map_["rep-list"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_list_ >;
      _cli_commands_map_["list"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_list_ >;
      _cli_commands_map_["rep-fetch"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_fetch_ >;
      _cli_commands_map_["fetch"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_fetch_ >;
      _cli_commands_map_["rep-create"] =
      &::bpkg::cli::thunk< commands, bool, &commands::rep_create_ >;
      _cli_commands_map_["pkg-status"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_status_ >;
      _cli_commands_map_["status"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_status_ >;
      _cli_commands_map_["pkg-build"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_build_ >;
      _cli_commands_map_["build"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_build_ >;
      _cli_commands_map_["pkg-drop"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_drop_ >;
      _cli_commands_map_["drop"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_drop_ >;
      _cli_commands_map_["pkg-install"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_install_ >;
      _cli_commands_map_["install"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_install_ >;
      _cli_commands_map_["pkg-uninstall"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_uninstall_ >;
      _cli_commands_map_["uninstall"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_uninstall_ >;
      _cli_commands_map_["pkg-update"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_update_ >;
      _cli_commands_map_["update"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_update_ >;
      _cli_commands_map_["pkg-test"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_test_ >;
      _cli_commands_map_["test"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_test_ >;
      _cli_commands_map_["pkg-clean"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_clean_ >;
      _cli_commands_map_["clean"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_clean_ >;
      _cli_commands_map_["pkg-verify"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_verify_ >;
      _cli_commands_map_["pkg-fetch"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_fetch_ >;
      _cli_commands_map_["pkg-unpack"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_unpack_ >;
      _cli_commands_map_["pkg-checkout"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_checkout_ >;
      _cli_commands_map_["pkg-configure"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_configure_ >;
      _cli_commands_map_["pkg-disfigure"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_disfigure_ >;
      _cli_commands_map_["pkg-purge"] =
      &::bpkg::cli::thunk< commands, bool, &commands::pkg_purge_ >;
    }
  };

  static _cli_commands_map_init _cli_commands_map_init_;

  bool commands::
  _parse (const char* o, ::bpkg::cli::scanner& s)
  {
    _cli_commands_map::const_iterator i (_cli_commands_map_.find (o));

    if (i != _cli_commands_map_.end ())
    {
      (*(i->second)) (*this, s);
      return true;
    }

    return false;
  }

  bool commands::
  _parse (::bpkg::cli::scanner& s,
          ::bpkg::cli::unknown_mode opt_mode,
          ::bpkg::cli::unknown_mode arg_mode)
  {
    // Can't skip combined flags (--no-combined-flags).
    //
    assert (opt_mode != ::bpkg::cli::unknown_mode::skip);

    bool r = false;
    bool opt = true;

    while (s.more ())
    {
      const char* o = s.peek ();

      if (std::strcmp (o, "--") == 0)
      {
        opt = false;
      }

      if (opt)
      {
        if (_parse (o, s))
        {
          r = true;
          continue;
        }

        if (std::strncmp (o, "-", 1) == 0 && o[1] != '\0')
        {
          // Handle combined option values.
          //
          std::string co;
          if (const char* v = std::strchr (o, '='))
          {
            co.assign (o, 0, v - o);
            ++v;

            int ac (2);
            char* av[] =
            {
              const_cast<char*> (co.c_str ()),
              const_cast<char*> (v)
            };

            ::bpkg::cli::argv_scanner ns (0, ac, av);

            if (_parse (co.c_str (), ns))
            {
              // Parsed the option but not its value?
              //
              if (ns.end () != 2)
                throw ::bpkg::cli::invalid_value (co, v);

              s.next ();
              r = true;
              continue;
            }
            else
            {
              // Set the unknown option and fall through.
              //
              o = co.c_str ();
            }
          }

          // Handle combined flags.
          //
          char cf[3];
          {
            const char* p = o + 1;
            for (; *p != '\0'; ++p)
            {
              if (!((*p >= 'a' && *p <= 'z') ||
                    (*p >= 'A' && *p <= 'Z') ||
                    (*p >= '0' && *p <= '9')))
                break;
            }

            if (*p == '\0')
            {
              for (p = o + 1; *p != '\0'; ++p)
              {
                std::strcpy (cf, "-");
                cf[1] = *p;
                cf[2] = '\0';

                int ac (1);
                char* av[] =
                {
                  cf
                };

                ::bpkg::cli::argv_scanner ns (0, ac, av);

                if (!_parse (cf, ns))
                  break;
              }

              if (*p == '\0')
              {
                // All handled.
                //
                s.next ();
                r = true;
                continue;
              }
              else
              {
                // Set the unknown option and fall through.
                //
                o = cf;
              }
            }
          }

          switch (opt_mode)
          {
            case ::bpkg::cli::unknown_mode::skip:
            {
              s.skip ();
              r = true;
              continue;
            }
            case ::bpkg::cli::unknown_mode::stop:
            {
              break;
            }
            case ::bpkg::cli::unknown_mode::fail:
            {
              throw ::bpkg::cli::unknown_option (o);
            }
          }

          break;
        }
      }

      switch (arg_mode)
      {
        case ::bpkg::cli::unknown_mode::skip:
        {
          s.skip ();
          r = true;
          continue;
        }
        case ::bpkg::cli::unknown_mode::stop:
        {
          break;
        }
        case ::bpkg::cli::unknown_mode::fail:
        {
          throw ::bpkg::cli::unknown_argument (o);
        }
      }

      break;
    }

    return r;
  }

  // topics
  //

  topics::
  topics ()
  : common_options_ (),
    default_options_files_ (),
    repository_types_ (),
    repository_signing_ (),
    argument_grouping_ ()
  {
  }

  bool topics::
  parse (int& argc,
         char** argv,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (argc, argv, erase);
    bool r = _parse (s, opt, arg);
    return r;
  }

  bool topics::
  parse (int start,
         int& argc,
         char** argv,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (start, argc, argv, erase);
    bool r = _parse (s, opt, arg);
    return r;
  }

  bool topics::
  parse (int& argc,
         char** argv,
         int& end,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (argc, argv, erase);
    bool r = _parse (s, opt, arg);
    end = s.end ();
    return r;
  }

  bool topics::
  parse (int start,
         int& argc,
         char** argv,
         int& end,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (start, argc, argv, erase);
    bool r = _parse (s, opt, arg);
    end = s.end ();
    return r;
  }

  bool topics::
  parse (::bpkg::cli::scanner& s,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    bool r = _parse (s, opt, arg);
    return r;
  }

  void topics::
  merge (const topics& a)
  {
    CLI_POTENTIALLY_UNUSED (a);

    if (a.common_options_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->common_options_, a.common_options_);
    }

    if (a.default_options_files_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->default_options_files_, a.default_options_files_);
    }

    if (a.repository_types_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->repository_types_, a.repository_types_);
    }

    if (a.repository_signing_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->repository_signing_, a.repository_signing_);
    }

    if (a.argument_grouping_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->argument_grouping_, a.argument_grouping_);
    }
  }

  ::bpkg::cli::usage_para topics::
  print_usage (::std::ostream& os, ::bpkg::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mHELP TOPICS\033[0m" << ::std::endl;

    os << std::endl
       << "\033[1mcommon-options\033[0m           \033[1mbpkg-common-options(1)\033[0m -- details on common options" << ::std::endl;

    os << "\033[1mdefault-options-files\033[0m    \033[1mbpkg-default-options-files(1)\033[0m -- specifying default" << ::std::endl
       << "                         options" << ::std::endl;

    os << "\033[1mrepository-types\033[0m         \033[1mbpkg-repository-types(1)\033[0m -- repository types," << ::std::endl
       << "                         structure, and URLs" << ::std::endl;

    os << "\033[1mrepository-signing\033[0m       \033[1mbpkg-repository-signing(1)\033[0m -- how to sign repository" << ::std::endl;

    os << "\033[1margument-grouping\033[0m        \033[1mbpkg-argument-grouping(1)\033[0m -- argument grouping" << ::std::endl
       << "                         facility" << ::std::endl;

    p = ::bpkg::cli::usage_para::option;

    return p;
  }

  typedef
  std::map<std::string, void (*) (topics&, ::bpkg::cli::scanner&)>
  _cli_topics_map;

  static _cli_topics_map _cli_topics_map_;

  struct _cli_topics_map_init
  {
    _cli_topics_map_init ()
    {
      _cli_topics_map_["common-options"] =
      &::bpkg::cli::thunk< topics, bool, &topics::common_options_ >;
      _cli_topics_map_["default-options-files"] =
      &::bpkg::cli::thunk< topics, bool, &topics::default_options_files_ >;
      _cli_topics_map_["repository-types"] =
      &::bpkg::cli::thunk< topics, bool, &topics::repository_types_ >;
      _cli_topics_map_["repository-signing"] =
      &::bpkg::cli::thunk< topics, bool, &topics::repository_signing_ >;
      _cli_topics_map_["argument-grouping"] =
      &::bpkg::cli::thunk< topics, bool, &topics::argument_grouping_ >;
    }
  };

  static _cli_topics_map_init _cli_topics_map_init_;

  bool topics::
  _parse (const char* o, ::bpkg::cli::scanner& s)
  {
    _cli_topics_map::const_iterator i (_cli_topics_map_.find (o));

    if (i != _cli_topics_map_.end ())
    {
      (*(i->second)) (*this, s);
      return true;
    }

    return false;
  }

  bool topics::
  _parse (::bpkg::cli::scanner& s,
          ::bpkg::cli::unknown_mode opt_mode,
          ::bpkg::cli::unknown_mode arg_mode)
  {
    // Can't skip combined flags (--no-combined-flags).
    //
    assert (opt_mode != ::bpkg::cli::unknown_mode::skip);

    bool r = false;
    bool opt = true;

    while (s.more ())
    {
      const char* o = s.peek ();

      if (std::strcmp (o, "--") == 0)
      {
        opt = false;
      }

      if (opt)
      {
        if (_parse (o, s))
        {
          r = true;
          continue;
        }

        if (std::strncmp (o, "-", 1) == 0 && o[1] != '\0')
        {
          // Handle combined option values.
          //
          std::string co;
          if (const char* v = std::strchr (o, '='))
          {
            co.assign (o, 0, v - o);
            ++v;

            int ac (2);
            char* av[] =
            {
              const_cast<char*> (co.c_str ()),
              const_cast<char*> (v)
            };

            ::bpkg::cli::argv_scanner ns (0, ac, av);

            if (_parse (co.c_str (), ns))
            {
              // Parsed the option but not its value?
              //
              if (ns.end () != 2)
                throw ::bpkg::cli::invalid_value (co, v);

              s.next ();
              r = true;
              continue;
            }
            else
            {
              // Set the unknown option and fall through.
              //
              o = co.c_str ();
            }
          }

          // Handle combined flags.
          //
          char cf[3];
          {
            const char* p = o + 1;
            for (; *p != '\0'; ++p)
            {
              if (!((*p >= 'a' && *p <= 'z') ||
                    (*p >= 'A' && *p <= 'Z') ||
                    (*p >= '0' && *p <= '9')))
                break;
            }

            if (*p == '\0')
            {
              for (p = o + 1; *p != '\0'; ++p)
              {
                std::strcpy (cf, "-");
                cf[1] = *p;
                cf[2] = '\0';

                int ac (1);
                char* av[] =
                {
                  cf
                };

                ::bpkg::cli::argv_scanner ns (0, ac, av);

                if (!_parse (cf, ns))
                  break;
              }

              if (*p == '\0')
              {
                // All handled.
                //
                s.next ();
                r = true;
                continue;
              }
              else
              {
                // Set the unknown option and fall through.
                //
                o = cf;
              }
            }
          }

          switch (opt_mode)
          {
            case ::bpkg::cli::unknown_mode::skip:
            {
              s.skip ();
              r = true;
              continue;
            }
            case ::bpkg::cli::unknown_mode::stop:
            {
              break;
            }
            case ::bpkg::cli::unknown_mode::fail:
            {
              throw ::bpkg::cli::unknown_option (o);
            }
          }

          break;
        }
      }

      switch (arg_mode)
      {
        case ::bpkg::cli::unknown_mode::skip:
        {
          s.skip ();
          r = true;
          continue;
        }
        case ::bpkg::cli::unknown_mode::stop:
        {
          break;
        }
        case ::bpkg::cli::unknown_mode::fail:
        {
          throw ::bpkg::cli::unknown_argument (o);
        }
      }

      break;
    }

    return r;
  }

  // options
  //

  options::
  options ()
  : help_ (),
    version_ ()
  {
  }

  bool options::
  parse (int& argc,
         char** argv,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (argc, argv, erase);
    bool r = _parse (s, opt, arg);
    return r;
  }

  bool options::
  parse (int start,
         int& argc,
         char** argv,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (start, argc, argv, erase);
    bool r = _parse (s, opt, arg);
    return r;
  }

  bool options::
  parse (int& argc,
         char** argv,
         int& end,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (argc, argv, erase);
    bool r = _parse (s, opt, arg);
    end = s.end ();
    return r;
  }

  bool options::
  parse (int start,
         int& argc,
         char** argv,
         int& end,
         bool erase,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    ::bpkg::cli::argv_scanner s (start, argc, argv, erase);
    bool r = _parse (s, opt, arg);
    end = s.end ();
    return r;
  }

  bool options::
  parse (::bpkg::cli::scanner& s,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    bool r = _parse (s, opt, arg);
    return r;
  }

  void options::
  merge (const options& a)
  {
    CLI_POTENTIALLY_UNUSED (a);

    // common_options base
    //
    ::bpkg::common_options::merge (a);

    if (a.help_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->help_, a.help_);
    }

    if (a.version_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->version_, a.version_);
    }
  }

  ::bpkg::cli::usage_para options::
  print_usage (::std::ostream& os, ::bpkg::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    // common_options base
    //
    p = ::bpkg::common_options::print_usage (os, p);

    return p;
  }

  typedef
  std::map<std::string, void (*) (options&, ::bpkg::cli::scanner&)>
  _cli_options_map;

  static _cli_options_map _cli_options_map_;

  struct _cli_options_map_init
  {
    _cli_options_map_init ()
    {
      _cli_options_map_["--help"] =
      &::bpkg::cli::thunk< options, bool, &options::help_ >;
      _cli_options_map_["--version"] =
      &::bpkg::cli::thunk< options, bool, &options::version_ >;
    }
  };

  static _cli_options_map_init _cli_options_map_init_;

  bool options::
  _parse (const char* o, ::bpkg::cli::scanner& s)
  {
    _cli_options_map::const_iterator i (_cli_options_map_.find (o));

    if (i != _cli_options_map_.end ())
    {
      (*(i->second)) (*this, s);
      return true;
    }

    // common_options base
    //
    if (::bpkg::common_options::_parse (o, s))
      return true;

    return false;
  }

  bool options::
  _parse (::bpkg::cli::scanner& s,
          ::bpkg::cli::unknown_mode opt_mode,
          ::bpkg::cli::unknown_mode arg_mode)
  {
    // Can't skip combined flags (--no-combined-flags).
    //
    assert (opt_mode != ::bpkg::cli::unknown_mode::skip);

    bool r = false;
    bool opt = true;

    while (s.more ())
    {
      const char* o = s.peek ();

      if (std::strcmp (o, "--") == 0)
      {
        opt = false;
      }

      if (opt)
      {
        if (_parse (o, s))
        {
          r = true;
          continue;
        }

        if (std::strncmp (o, "-", 1) == 0 && o[1] != '\0')
        {
          // Handle combined option values.
          //
          std::string co;
          if (const char* v = std::strchr (o, '='))
          {
            co.assign (o, 0, v - o);
            ++v;

            int ac (2);
            char* av[] =
            {
              const_cast<char*> (co.c_str ()),
              const_cast<char*> (v)
            };

            ::bpkg::cli::argv_scanner ns (0, ac, av);

            if (_parse (co.c_str (), ns))
            {
              // Parsed the option but not its value?
              //
              if (ns.end () != 2)
                throw ::bpkg::cli::invalid_value (co, v);

              s.next ();
              r = true;
              continue;
            }
            else
            {
              // Set the unknown option and fall through.
              //
              o = co.c_str ();
            }
          }

          // Handle combined flags.
          //
          char cf[3];
          {
            const char* p = o + 1;
            for (; *p != '\0'; ++p)
            {
              if (!((*p >= 'a' && *p <= 'z') ||
                    (*p >= 'A' && *p <= 'Z') ||
                    (*p >= '0' && *p <= '9')))
                break;
            }

            if (*p == '\0')
            {
              for (p = o + 1; *p != '\0'; ++p)
              {
                std::strcpy (cf, "-");
                cf[1] = *p;
                cf[2] = '\0';

                int ac (1);
                char* av[] =
                {
                  cf
                };

                ::bpkg::cli::argv_scanner ns (0, ac, av);

                if (!_parse (cf, ns))
                  break;
              }

              if (*p == '\0')
              {
                // All handled.
                //
                s.next ();
                r = true;
                continue;
              }
              else
              {
                // Set the unknown option and fall through.
                //
                o = cf;
              }
            }
          }

          switch (opt_mode)
          {
            case ::bpkg::cli::unknown_mode::skip:
            {
              s.skip ();
              r = true;
              continue;
            }
            case ::bpkg::cli::unknown_mode::stop:
            {
              break;
            }
            case ::bpkg::cli::unknown_mode::fail:
            {
              throw ::bpkg::cli::unknown_option (o);
            }
          }

          break;
        }
      }

      switch (arg_mode)
      {
        case ::bpkg::cli::unknown_mode::skip:
        {
          s.skip ();
          r = true;
          continue;
        }
        case ::bpkg::cli::unknown_mode::stop:
        {
          break;
        }
        case ::bpkg::cli::unknown_mode::fail:
        {
          throw ::bpkg::cli::unknown_argument (o);
        }
      }

      break;
    }

    return r;
  }
}

namespace bpkg
{
  ::bpkg::cli::usage_para
  print_bpkg_usage (::std::ostream& os, ::bpkg::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mSYNOPSIS\033[0m" << ::std::endl
       << ::std::endl
       << "\033[1mbpkg --help\033[0m" << ::std::endl
       << "\033[1mbpkg --version\033[0m" << ::std::endl
       << "\033[1mbpkg help\033[0m [\033[4mcommand\033[0m | \033[4mtopic\033[0m]" << ::std::endl
       << "\033[1mbpkg\033[0m [\033[4mcommon-options\033[0m] \033[4mcommand\033[0m [\033[4mcommand-options\033[0m] \033[4mcommand-args\033[0m\033[0m" << ::std::endl
       << ::std::endl
       << "\033[1mDESCRIPTION\033[0m" << ::std::endl
       << ::std::endl
       << "The \033[1mbuild2\033[0m package dependency manager is used to manipulate build" << ::std::endl
       << "configurations, packages, and repositories using a set of commands that are" << ::std::endl
       << "summarized below." << ::std::endl
       << ::std::endl
       << "For a detailed description of any command or help topic, use the \033[1mhelp\033[0m command" << ::std::endl
       << "or see the corresponding man page (the man pages have the \033[1mbpkg-\033[0m prefix, for" << ::std::endl
       << "example \033[1mbpkg-help(1)\033[0m). Note also that \033[4mcommand-options\033[0m and \033[4mcommand-args\033[0m can be" << ::std::endl
       << "specified in any order and \033[4mcommon-options\033[0m can be specified as part of" << ::std::endl
       << "\033[4mcommand-options\033[0m." << ::std::endl;

    p = ::bpkg::commands::print_usage (os, ::bpkg::cli::usage_para::text);

    p = ::bpkg::topics::print_usage (os, p);

    p = ::bpkg::options::print_usage (os, p);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mENVIRONMENT\033[0m" << ::std::endl
       << ::std::endl
       << "Commands executed by \033[1mbpkg\033[0m while the build configuration database is open will" << ::std::endl
       << "have the \033[1mBPKG_OPEN_CONFIG\033[0m environment variable set to the absolute and" << ::std::endl
       << "normalized configuration directory path. This can be used by build system hooks" << ::std::endl
       << "and/or programs that they execute." << ::std::endl;

    os << std::endl
       << "\033[1mEXIT STATUS\033[0m" << ::std::endl
       << ::std::endl
       << "Non-zero exit status is returned in case of an error." << ::std::endl;

    p = ::bpkg::cli::usage_para::text;

    return p;
  }
}

// Begin epilogue.
//
//
// End epilogue.

