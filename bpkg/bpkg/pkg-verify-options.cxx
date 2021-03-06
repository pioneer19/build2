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

#include <bpkg/pkg-verify-options.hxx>

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
  // pkg_verify_options
  //

  pkg_verify_options::
  pkg_verify_options ()
  : silent_ (),
    deep_ (),
    ignore_unknown_ (),
    manifest_ ()
  {
  }

  bool pkg_verify_options::
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

  bool pkg_verify_options::
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

  bool pkg_verify_options::
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

  bool pkg_verify_options::
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

  bool pkg_verify_options::
  parse (::bpkg::cli::scanner& s,
         ::bpkg::cli::unknown_mode opt,
         ::bpkg::cli::unknown_mode arg)
  {
    bool r = _parse (s, opt, arg);
    return r;
  }

  void pkg_verify_options::
  merge (const pkg_verify_options& a)
  {
    CLI_POTENTIALLY_UNUSED (a);

    // common_options base
    //
    ::bpkg::common_options::merge (a);

    if (a.silent_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->silent_, a.silent_);
    }

    if (a.deep_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->deep_, a.deep_);
    }

    if (a.ignore_unknown_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->ignore_unknown_, a.ignore_unknown_);
    }

    if (a.manifest_)
    {
      ::bpkg::cli::parser< bool>::merge (
        this->manifest_, a.manifest_);
    }
  }

  ::bpkg::cli::usage_para pkg_verify_options::
  print_usage (::std::ostream& os, ::bpkg::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mPKG-VERIFY OPTIONS\033[0m" << ::std::endl;

    os << std::endl
       << "\033[1m--silent\033[0m                 Suppress the error messages about the reason why the" << ::std::endl
       << "                         package is invalid. Just return the error status." << ::std::endl;

    os << std::endl
       << "\033[1m--deep\033[0m                   Verify files referenced by the \033[1m*-file\033[0m manifest values." << ::std::endl;

    os << std::endl
       << "\033[1m--ignore-unknown\033[0m         Ignore unknown manifest entries. By default, \033[1mbpkg\033[0m will" << ::std::endl
       << "                         refuse to declare such a package valid since it cannot" << ::std::endl
       << "                         be sure the unknown entries are valid." << ::std::endl;

    os << std::endl
       << "\033[1m--manifest\033[0m               Instead of printing the successful verification result" << ::std::endl
       << "                         in the human-readable form, dump the package manifest" << ::std::endl
       << "                         to \033[1mstdout\033[0m. If the \033[1m--deep\033[0m option is specified, then in" << ::std::endl
       << "                         the resulting manifest the \033[1m*-file\033[0m values are replaced" << ::std::endl
       << "                         with the contents of the referenced files and the" << ::std::endl
       << "                         package dependency constraints are completed." << ::std::endl;

    p = ::bpkg::cli::usage_para::option;

    // common_options base
    //
    p = ::bpkg::common_options::print_usage (os, p);

    return p;
  }

  typedef
  std::map<std::string, void (*) (pkg_verify_options&, ::bpkg::cli::scanner&)>
  _cli_pkg_verify_options_map;

  static _cli_pkg_verify_options_map _cli_pkg_verify_options_map_;

  struct _cli_pkg_verify_options_map_init
  {
    _cli_pkg_verify_options_map_init ()
    {
      _cli_pkg_verify_options_map_["--silent"] =
      &::bpkg::cli::thunk< pkg_verify_options, bool, &pkg_verify_options::silent_ >;
      _cli_pkg_verify_options_map_["--deep"] =
      &::bpkg::cli::thunk< pkg_verify_options, bool, &pkg_verify_options::deep_ >;
      _cli_pkg_verify_options_map_["--ignore-unknown"] =
      &::bpkg::cli::thunk< pkg_verify_options, bool, &pkg_verify_options::ignore_unknown_ >;
      _cli_pkg_verify_options_map_["--manifest"] =
      &::bpkg::cli::thunk< pkg_verify_options, bool, &pkg_verify_options::manifest_ >;
    }
  };

  static _cli_pkg_verify_options_map_init _cli_pkg_verify_options_map_init_;

  bool pkg_verify_options::
  _parse (const char* o, ::bpkg::cli::scanner& s)
  {
    _cli_pkg_verify_options_map::const_iterator i (_cli_pkg_verify_options_map_.find (o));

    if (i != _cli_pkg_verify_options_map_.end ())
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

  bool pkg_verify_options::
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
  print_bpkg_pkg_verify_usage (::std::ostream& os, ::bpkg::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mSYNOPSIS\033[0m" << ::std::endl
       << ::std::endl
       << "\033[1mbpkg pkg-verify\033[0m [\033[4moptions\033[0m] \033[4mfile\033[0m\033[0m" << ::std::endl
       << ::std::endl
       << "\033[1mDESCRIPTION\033[0m" << ::std::endl
       << ::std::endl
       << "The \033[1mpkg-verify\033[0m command verifies that the specified archive file is a valid" << ::std::endl
       << "\033[1mbpkg\033[0m package. Specifically, it checks that the file's name and the top-level" << ::std::endl
       << "directory inside the archive match the canonical \033[4mname\033[0m\033[1m-\033[0m\033[4mversion\033[0m\033[0m form and that" << ::std::endl
       << "there is a valid manifest file in that top-level directory. Additionally, if" << ::std::endl
       << "the \033[1m--deep\033[0m option is specified, it also checks that the files referenced by the" << ::std::endl
       << "\033[1m*-file\033[0m manifest values are present in the archive and are not empty." << ::std::endl;

    p = ::bpkg::pkg_verify_options::print_usage (os, ::bpkg::cli::usage_para::text);

    if (p != ::bpkg::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mDEFAULT OPTIONS FILES\033[0m" << ::std::endl
       << ::std::endl
       << "See \033[1mbpkg-default-options-files(1)\033[0m for an overview of the default options files." << ::std::endl
       << "For the \033[1mpkg-verify\033[0m command the following options files are searched for in the" << ::std::endl
       << "predefined directories (system, etc) and, if found, loaded in the order listed:" << ::std::endl
       << ::std::endl
       << "bpkg.options" << ::std::endl
       << "bpkg-pkg-verify.options" << ::std::endl;

    p = ::bpkg::cli::usage_para::text;

    return p;
  }
}

// Begin epilogue.
//
//
// End epilogue.

