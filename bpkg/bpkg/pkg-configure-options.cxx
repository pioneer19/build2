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

#include <bpkg/pkg-configure-options.hxx>

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
  // pkg_configure_options
  //

  pkg_configure_options::
  pkg_configure_options ()
  {
  }

  bool pkg_configure_options::
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

  bool pkg_configure_options::
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

  bool pkg_configure_options::
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

  bool pkg_configure_options::
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

  bool pkg_configure_options::
  parse (::bpkg::cli::scanner& s,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    bool r = _parse (s, opt, arg);
    return r;
  }

  void pkg_configure_options::
  merge (const pkg_configure_options& a)
  {
    CLI_POTENTIALLY_UNUSED (a);

    // configuration_options base
    //
    ::bpkg::configuration_options::merge (a);
  }

  ::bpkg::cli::usage_para pkg_configure_options::
  print_usage (::std::ostream& os, ::bpkg::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mPKG-CONFIGURE OPTIONS\033[0m" << ::std::endl;

    p = ::bpkg::cli::usage_para::text;

    // configuration_options base
    //
    p = ::bpkg::configuration_options::print_usage (os, p);

    return p;
  }

  typedef
  std::map<std::string, void (*) (pkg_configure_options&, ::bpkg::cli::scanner&)>
  _cli_pkg_configure_options_map;

  static _cli_pkg_configure_options_map _cli_pkg_configure_options_map_;

  struct _cli_pkg_configure_options_map_init
  {
    _cli_pkg_configure_options_map_init ()
    {
    }
  };

  static _cli_pkg_configure_options_map_init _cli_pkg_configure_options_map_init_;

  bool pkg_configure_options::
  _parse (const char* o, ::bpkg::cli::scanner& s)
  {
    _cli_pkg_configure_options_map::const_iterator i (_cli_pkg_configure_options_map_.find (o));

    if (i != _cli_pkg_configure_options_map_.end ())
    {
      (*(i->second)) (*this, s);
      return true;
    }

    // configuration_options base
    //
    if (::bpkg::configuration_options::_parse (o, s))
      return true;

    return false;
  }

  bool pkg_configure_options::
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
  print_bpkg_pkg_configure_usage (::std::ostream& os, ::bpkg::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mSYNOPSIS\033[0m" << ::std::endl
       << ::std::endl
       << "\033[1mbpkg pkg-configure\033[0m [\033[4moptions\033[0m] [\033[4mcfg-var\033[0m...] \033[4mpkg\033[0m\033[0m" << ::std::endl
       << ::std::endl
       << "\033[1mDESCRIPTION\033[0m" << ::std::endl
       << ::std::endl
       << "The \033[1mpkg-configure\033[0m command configures either the previously unpacked" << ::std::endl
       << "(\033[1mbpkg-pkg-unpack(1)\033[0m, \033[1mbpkg-pkg-checkout(1)\033[0m) source code package or a package" << ::std::endl
       << "that is present in the system." << ::std::endl
       << ::std::endl
       << "A source code package inherits the common \033[1mbuild2\033[0m configuration values that were" << ::std::endl
       << "specified when creating the configuration (\033[1mbpkg-cfg-create(1)\033[0m). Additional" << ::std::endl
       << "package-specific configuration variables can be passed to \033[1mpkg-configure\033[0m" << ::std::endl
       << "(\033[4mcfg-var\033[0m)." << ::std::endl
       << ::std::endl
       << "A system package is specified using the \033[1msys:\033[0m\033[4mpkg\033[0m[/\033[4mver\033[0m]\033[0m syntax. If the package" << ::std::endl
       << "version (\033[4mver\033[0m) is not specified, then it is considered to be unknown but" << ::std::endl
       << "satisfying any dependency constraint. Such a version is displayed as \033[1m*\033[0m." << ::std::endl;

    p = ::bpkg::pkg_configure_options::print_usage (os, ::bpkg::cli::usage_para::text);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mDEFAULT OPTIONS FILES\033[0m" << ::std::endl
       << ::std::endl
       << "See \033[1mbpkg-default-options-files(1)\033[0m for an overview of the default options files." << ::std::endl
       << "For the \033[1mpkg-configure\033[0m command the search start directory is the configuration" << ::std::endl
       << "directory. The following options files are searched for in each directory and," << ::std::endl
       << "if found, loaded in the order listed:" << ::std::endl
       << ::std::endl
       << "bpkg.options" << ::std::endl
       << "bpkg-pkg-configure.options" << ::std::endl
       << ::std::endl
       << "The following \033[1mpkg-configure\033[0m command options cannot be specified in the default" << ::std::endl
       << "options files:" << ::std::endl
       << ::std::endl
       << "--directory|-d" << ::std::endl;

    p = ::bpkg::cli::usage_para::text;

    return p;
  }
}

// Begin epilogue.
//
//
// End epilogue.

