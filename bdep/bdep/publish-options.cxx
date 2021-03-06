// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

// Begin prologue.
//
#include <bdep/types-parsers.hxx>
//
// End prologue.

#include <bdep/publish-options.hxx>

#include <map>
#include <set>
#include <string>
#include <vector>
#include <ostream>
#include <sstream>

namespace bdep
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

namespace bdep
{
  // cmd_publish_options
  //

  cmd_publish_options::
  cmd_publish_options ()
  : yes_ (),
    control_ (),
    control_specified_ (false),
    repository_ ("https://cppget.org"),
    repository_specified_ (false),
    section_ (),
    section_specified_ (false),
    author_name_ (),
    author_name_specified_ (false),
    author_email_ (),
    author_email_specified_ (false),
    force_ (),
    force_specified_ (false),
    simulate_ (),
    simulate_specified_ (false),
    forward_ ()
  {
  }

  bool cmd_publish_options::
  parse (int& argc,
         char** argv,
         bool erase,
         ::bdep::cli::unknown_mode opt,
         ::bdep::cli::unknown_mode arg)
  {
    ::bdep::cli::argv_scanner s (argc, argv, erase);
    bool r = _parse (s, opt, arg);
    return r;
  }

  bool cmd_publish_options::
  parse (int start,
         int& argc,
         char** argv,
         bool erase,
         ::bdep::cli::unknown_mode opt,
         ::bdep::cli::unknown_mode arg)
  {
    ::bdep::cli::argv_scanner s (start, argc, argv, erase);
    bool r = _parse (s, opt, arg);
    return r;
  }

  bool cmd_publish_options::
  parse (int& argc,
         char** argv,
         int& end,
         bool erase,
         ::bdep::cli::unknown_mode opt,
         ::bdep::cli::unknown_mode arg)
  {
    ::bdep::cli::argv_scanner s (argc, argv, erase);
    bool r = _parse (s, opt, arg);
    end = s.end ();
    return r;
  }

  bool cmd_publish_options::
  parse (int start,
         int& argc,
         char** argv,
         int& end,
         bool erase,
         ::bdep::cli::unknown_mode opt,
         ::bdep::cli::unknown_mode arg)
  {
    ::bdep::cli::argv_scanner s (start, argc, argv, erase);
    bool r = _parse (s, opt, arg);
    end = s.end ();
    return r;
  }

  bool cmd_publish_options::
  parse (::bdep::cli::scanner& s,
         ::bdep::cli::unknown_mode opt,
         ::bdep::cli::unknown_mode arg)
  {
    bool r = _parse (s, opt, arg);
    return r;
  }

  void cmd_publish_options::
  merge (const cmd_publish_options& a)
  {
    CLI_POTENTIALLY_UNUSED (a);

    // project_options base
    //
    ::bdep::project_options::merge (a);

    if (a.yes_)
    {
      ::bdep::cli::parser< bool>::merge (
        this->yes_, a.yes_);
    }

    if (a.control_specified_)
    {
      ::bdep::cli::parser< string>::merge (
        this->control_, a.control_);
      this->control_specified_ = true;
    }

    if (a.repository_specified_)
    {
      ::bdep::cli::parser< url>::merge (
        this->repository_, a.repository_);
      this->repository_specified_ = true;
    }

    if (a.section_specified_)
    {
      ::bdep::cli::parser< string>::merge (
        this->section_, a.section_);
      this->section_specified_ = true;
    }

    if (a.author_name_specified_)
    {
      ::bdep::cli::parser< string>::merge (
        this->author_name_, a.author_name_);
      this->author_name_specified_ = true;
    }

    if (a.author_email_specified_)
    {
      ::bdep::cli::parser< string>::merge (
        this->author_email_, a.author_email_);
      this->author_email_specified_ = true;
    }

    if (a.force_specified_)
    {
      ::bdep::cli::parser< std::set<string>>::merge (
        this->force_, a.force_);
      this->force_specified_ = true;
    }

    if (a.simulate_specified_)
    {
      ::bdep::cli::parser< string>::merge (
        this->simulate_, a.simulate_);
      this->simulate_specified_ = true;
    }

    if (a.forward_)
    {
      ::bdep::cli::parser< bool>::merge (
        this->forward_, a.forward_);
    }
  }

  ::bdep::cli::usage_para cmd_publish_options::
  print_usage (::std::ostream& os, ::bdep::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p != ::bdep::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mPUBLISH OPTIONS\033[0m" << ::std::endl;

    os << std::endl
       << "\033[1m--yes\033[0m|\033[1m-y\033[0m                Don't prompt for confirmation before publishing." << ::std::endl;

    os << std::endl
       << "\033[1m--control\033[0m \033[4murl\033[0m           Control repository URL for the packages being" << ::std::endl
       << "                        published." << ::std::endl;

    os << std::endl
       << "\033[1m--repository\033[0m \033[4murl\033[0m        Repository to publish the packages to." << ::std::endl;

    os << std::endl
       << "\033[1m--section\033[0m \033[4mname\033[0m          Repository section to publish the packages under." << ::std::endl;

    os << std::endl
       << "\033[1m--author-name\033[0m \033[4mname\033[0m      Publisher's name. If unspecified, it will be obtained" << ::std::endl
       << "                        from the environment and/or version control system. See" << ::std::endl
       << "                        the ENVIRONMENT section for details." << ::std::endl;

    os << std::endl
       << "\033[1m--author-email\033[0m \033[4memail\033[0m    Publisher's email address. If unspecified, it will be" << ::std::endl
       << "                        obtained from the environment and/or version control" << ::std::endl
       << "                        system. See the ENVIRONMENT section for details." << ::std::endl;

    os << std::endl
       << "\033[1m--force\033[0m \033[4mcheck\033[0m           Force publishing, disabling the specified check. Repeat" << ::std::endl
       << "                        this option to disable multiple checks." << ::std::endl;

    os << std::endl
       << "\033[1m--simulate\033[0m \033[4moutcome\033[0m      Simulate the specified outcome of the submission" << ::std::endl
       << "                        process without actually performing any externally" << ::std::endl
       << "                        visible actions (such as publishing the package). The" << ::std::endl
       << "                        commonly used outcome value is \033[1msuccess\033[0m. For other" << ::std::endl
       << "                        recognized outcomes refer to the submission service" << ::std::endl
       << "                        documentation." << ::std::endl;

    os << std::endl
       << "\033[1m--forward\033[0m               Use the forwarded configuration for each package" << ::std::endl
       << "                        instead of the default configuration." << ::std::endl;

    p = ::bdep::cli::usage_para::option;

    // project_options base
    //
    p = ::bdep::project_options::print_usage (os, p);

    return p;
  }

  struct _cli_cmd_publish_options_desc_type: ::bdep::cli::options
  {
    _cli_cmd_publish_options_desc_type ()
    {
      ::bdep::cmd_publish_options::fill (*this);
    }
  };

  void cmd_publish_options::
  fill (::bdep::cli::options& os)
  {
    // project_options base
    //
    ::bdep::project_options::fill (os);

    // --yes
    //
    {
      ::bdep::cli::option_names a;
      a.push_back ("-y");
      std::string dv;
      ::bdep::cli::option o ("--yes", a, true, dv);
      os.push_back (o);
    }

    // --control
    //
    {
      ::bdep::cli::option_names a;
      std::string dv;
      ::bdep::cli::option o ("--control", a, false, dv);
      os.push_back (o);
    }

    // --repository
    //
    {
      ::bdep::cli::option_names a;
      std::string dv ("https://cppget.org");
      ::bdep::cli::option o ("--repository", a, false, dv);
      os.push_back (o);
    }

    // --section
    //
    {
      ::bdep::cli::option_names a;
      std::string dv;
      ::bdep::cli::option o ("--section", a, false, dv);
      os.push_back (o);
    }

    // --author-name
    //
    {
      ::bdep::cli::option_names a;
      std::string dv;
      ::bdep::cli::option o ("--author-name", a, false, dv);
      os.push_back (o);
    }

    // --author-email
    //
    {
      ::bdep::cli::option_names a;
      std::string dv;
      ::bdep::cli::option o ("--author-email", a, false, dv);
      os.push_back (o);
    }

    // --force
    //
    {
      ::bdep::cli::option_names a;
      std::string dv;
      ::bdep::cli::option o ("--force", a, false, dv);
      os.push_back (o);
    }

    // --simulate
    //
    {
      ::bdep::cli::option_names a;
      std::string dv;
      ::bdep::cli::option o ("--simulate", a, false, dv);
      os.push_back (o);
    }

    // --forward
    //
    {
      ::bdep::cli::option_names a;
      std::string dv;
      ::bdep::cli::option o ("--forward", a, true, dv);
      os.push_back (o);
    }
  }

  const ::bdep::cli::options& cmd_publish_options::
  description ()
  {
    static _cli_cmd_publish_options_desc_type _cli_cmd_publish_options_desc_;
    return _cli_cmd_publish_options_desc_;
  }

  typedef
  std::map<std::string, void (*) (cmd_publish_options&, ::bdep::cli::scanner&)>
  _cli_cmd_publish_options_map;

  static _cli_cmd_publish_options_map _cli_cmd_publish_options_map_;

  struct _cli_cmd_publish_options_map_init
  {
    _cli_cmd_publish_options_map_init ()
    {
      _cli_cmd_publish_options_map_["--yes"] =
      &::bdep::cli::thunk< cmd_publish_options, bool, &cmd_publish_options::yes_ >;
      _cli_cmd_publish_options_map_["-y"] =
      &::bdep::cli::thunk< cmd_publish_options, bool, &cmd_publish_options::yes_ >;
      _cli_cmd_publish_options_map_["--control"] =
      &::bdep::cli::thunk< cmd_publish_options, string, &cmd_publish_options::control_,
        &cmd_publish_options::control_specified_ >;
      _cli_cmd_publish_options_map_["--repository"] =
      &::bdep::cli::thunk< cmd_publish_options, url, &cmd_publish_options::repository_,
        &cmd_publish_options::repository_specified_ >;
      _cli_cmd_publish_options_map_["--section"] =
      &::bdep::cli::thunk< cmd_publish_options, string, &cmd_publish_options::section_,
        &cmd_publish_options::section_specified_ >;
      _cli_cmd_publish_options_map_["--author-name"] =
      &::bdep::cli::thunk< cmd_publish_options, string, &cmd_publish_options::author_name_,
        &cmd_publish_options::author_name_specified_ >;
      _cli_cmd_publish_options_map_["--author-email"] =
      &::bdep::cli::thunk< cmd_publish_options, string, &cmd_publish_options::author_email_,
        &cmd_publish_options::author_email_specified_ >;
      _cli_cmd_publish_options_map_["--force"] =
      &::bdep::cli::thunk< cmd_publish_options, std::set<string>, &cmd_publish_options::force_,
        &cmd_publish_options::force_specified_ >;
      _cli_cmd_publish_options_map_["--simulate"] =
      &::bdep::cli::thunk< cmd_publish_options, string, &cmd_publish_options::simulate_,
        &cmd_publish_options::simulate_specified_ >;
      _cli_cmd_publish_options_map_["--forward"] =
      &::bdep::cli::thunk< cmd_publish_options, bool, &cmd_publish_options::forward_ >;
    }
  };

  static _cli_cmd_publish_options_map_init _cli_cmd_publish_options_map_init_;

  bool cmd_publish_options::
  _parse (const char* o, ::bdep::cli::scanner& s)
  {
    _cli_cmd_publish_options_map::const_iterator i (_cli_cmd_publish_options_map_.find (o));

    if (i != _cli_cmd_publish_options_map_.end ())
    {
      (*(i->second)) (*this, s);
      return true;
    }

    // project_options base
    //
    if (::bdep::project_options::_parse (o, s))
      return true;

    return false;
  }

  bool cmd_publish_options::
  _parse (::bdep::cli::scanner& s,
          ::bdep::cli::unknown_mode opt_mode,
          ::bdep::cli::unknown_mode arg_mode)
  {
    // Can't skip combined flags (--no-combined-flags).
    //
    assert (opt_mode != ::bdep::cli::unknown_mode::skip);

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

            ::bdep::cli::argv_scanner ns (0, ac, av);

            if (_parse (co.c_str (), ns))
            {
              // Parsed the option but not its value?
              //
              if (ns.end () != 2)
                throw ::bdep::cli::invalid_value (co, v);

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

                ::bdep::cli::argv_scanner ns (0, ac, av);

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
            case ::bdep::cli::unknown_mode::skip:
            {
              s.skip ();
              r = true;
              continue;
            }
            case ::bdep::cli::unknown_mode::stop:
            {
              break;
            }
            case ::bdep::cli::unknown_mode::fail:
            {
              throw ::bdep::cli::unknown_option (o);
            }
          }

          break;
        }
      }

      switch (arg_mode)
      {
        case ::bdep::cli::unknown_mode::skip:
        {
          s.skip ();
          r = true;
          continue;
        }
        case ::bdep::cli::unknown_mode::stop:
        {
          break;
        }
        case ::bdep::cli::unknown_mode::fail:
        {
          throw ::bdep::cli::unknown_argument (o);
        }
      }

      break;
    }

    return r;
  }
}

namespace bdep
{
  ::bdep::cli::usage_para
  print_bdep_publish_usage (::std::ostream& os, ::bdep::cli::usage_para p)
  {
    CLI_POTENTIALLY_UNUSED (os);

    if (p != ::bdep::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mSYNOPSIS\033[0m" << ::std::endl
       << ::std::endl
       << "\033[1mbdep publish\033[0m [\033[4moptions\033[0m] [\033[4mcfg-spec\033[0m] [\033[4mpkg-spec\033[0m]\033[0m" << ::std::endl
       << ::std::endl
       << "\033[4mpkg-spec\033[0m = (\033[1m--directory\033[0m|\033[1m-d\033[0m \033[4mpkg-dir\033[0m)... | \033[4mprj-spec\033[0m" << ::std::endl
       << "\033[4mprj-spec\033[0m = \033[1m--directory\033[0m|\033[1m-d\033[0m \033[4mprj-dir\033[0m" << ::std::endl
       << "\033[4mcfg-spec\033[0m = \033[1m@\033[0m\033[4mcfg-name\033[0m | \033[1m--config\033[0m|\033[1m-c\033[0m \033[4mcfg-dir\033[0m | \033[1m--forward\033[0m\033[0m" << ::std::endl
       << ::std::endl
       << "\033[1mDESCRIPTION\033[0m" << ::std::endl
       << ::std::endl
       << "The \033[1mpublish\033[0m command publishes the project packages to an archive-based" << ::std::endl
       << "repository." << ::std::endl
       << ::std::endl
       << "If no project or package directory is specified, then the current working" << ::std::endl
       << "directory is assumed. If no configuration is specified, then the default" << ::std::endl
       << "configuration is used to prepare the package distributions. If the specified" << ::std::endl
       << "directory is a project directory, then all the packages in the project are" << ::std::endl
       << "published. See \033[1mbdep-projects-configs(1)\033[0m for details on specifying projects and" << ::std::endl
       << "configurations." << ::std::endl
       << ::std::endl
       << "For each specified package the \033[1mpublish\033[0m command prepares a package archive and" << ::std::endl
       << "sends it as part of the package submission request to an archive-based" << ::std::endl
       << "repository. If the repository is not explicitly specified with the" << ::std::endl
       << "\033[1m--repository\033[0m option, packages are published to \033[1mcppget.org\033[0m by default." << ::std::endl
       << ::std::endl
       << "Along with the package archive, the submission request specifies the repository" << ::std::endl
       << "section to publish the package under, the control repository URL to use for" << ::std::endl
       << "authorization, and the publisher's name and email address for the record. While" << ::std::endl
       << "the exact usage and interpretation of this information depends on the specific" << ::std::endl
       << "repository, the following semantics apply when submitting to \033[1mcppget.org\033[0m." << ::std::endl
       << ::std::endl
       << "The section specifies the desired repository section to publish the project" << ::std::endl
       << "under. If not explicitly specified with the \033[1m--section\033[0m option, one of the \033[1malpha\033[0m," << ::std::endl
       << "\033[1mbeta\033[0m, or \033[1mstable\033[0m values are automatically derived from the package version." << ::std::endl
       << ::std::endl
       << "The control repository URL is a publicly accessible, read-only URL to a version" << ::std::endl
       << "control repository (normally the same as the project's) that is used to" << ::std::endl
       << "authenticate the publisher as someone authorized to publish under this package" << ::std::endl
       << "name (currently only \033[1mgit(1)\033[0m is supported)." << ::std::endl
       << ::std::endl
       << "Prior to sending the submission request, the \033[1mpublish\033[0m command adds the package" << ::std::endl
       << "archive checksum to the \033[1mbuild2-control\033[0m branch of the project's version control" << ::std::endl
       << "repository. Upon receiving the submission request, the archive repository" << ::std::endl
       << "either (1) associates the control repository with the package name if this is" << ::std::endl
       << "the first time this package name is published or (2) compares the submitted" << ::std::endl
       << "control repository to the previously associated and, if matching, queries the" << ::std::endl
       << "\033[1mbuild2-control\033[0m branch to verify that the submitter is authorized to publish" << ::std::endl
       << "this archive under this package name." << ::std::endl
       << ::std::endl
       << "Unless the control repository URL is specified with the \033[1m--control\033[0m option, it" << ::std::endl
       << "will be automatically derived from the version control's \"remote\" URL. In case" << ::std::endl
       << "of \033[1mgit(1)\033[0m, it will be based on the \033[1mremote.origin.url\033[0m configuration value unless" << ::std::endl
       << "overridden with \033[1mremote.origin.build2ControlUrl\033[0m or \033[1mremote.origin.build2Url\033[0m. The" << ::std::endl
       << "special \033[1mnone\033[0m value to the \033[1m--control\033[0m option can be used to disable this" << ::std::endl
       << "functionality." << ::std::endl
       << ::std::endl
       << "See Package Submission (brep#submit) for details on the submission request" << ::std::endl
       << "handling by archive repositories." << ::std::endl;

    p = ::bdep::cmd_publish_options::print_usage (os, ::bdep::cli::usage_para::text);

    if (p != ::bdep::cli::usage_para::none)
      os << ::std::endl;

    os << "\033[1mDEFAULT OPTIONS FILES\033[0m" << ::std::endl
       << ::std::endl
       << "See \033[1mbdep-default-options-files(1)\033[0m for an overview of the default options files." << ::std::endl
       << "For the \033[1mpublish\033[0m command the search start directory is the project directory." << ::std::endl
       << "The following options files are searched for in each directory and, if found," << ::std::endl
       << "loaded in the order listed:" << ::std::endl
       << ::std::endl
       << "bdep.options" << ::std::endl
       << "bdep-publish.options" << ::std::endl
       << ::std::endl
       << "The following \033[1mpublish\033[0m command options cannot be specified in the default" << ::std::endl
       << "options files:" << ::std::endl
       << ::std::endl
       << "--directory|-d" << ::std::endl
       << ::std::endl
       << "\033[1mENVIRONMENT\033[0m" << ::std::endl
       << ::std::endl
       << "The \033[1mBDEP_AUTHOR_NAME\033[0m and \033[1mBDEP_AUTHOR_EMAIL\033[0m environment variables can be used to" << ::std::endl
       << "specify the publisher's name and email address, respectively. If not set, the" << ::std::endl
       << "\033[1mpublish\033[0m command will first try to obtain the name and email from the version" << ::std::endl
       << "control system (if used) and then from the \033[1mUSER\033[0m and \033[1mEMAIL\033[0m environment" << ::std::endl
       << "variables, respectively. See also the \033[1m--author-name\033[0m and \033[1m--author-email\033[0m options." << ::std::endl;

    p = ::bdep::cli::usage_para::text;

    return p;
  }
}

// Begin epilogue.
//
//
// End epilogue.

