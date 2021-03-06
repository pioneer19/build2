// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

#ifndef BDEP_STATUS_OPTIONS_HXX
#define BDEP_STATUS_OPTIONS_HXX

// Begin prologue.
//
//
// End prologue.

#include <bdep/project-options.hxx>

namespace bdep
{
  class cmd_status_options: public ::bdep::project_options
  {
    public:
    cmd_status_options ();

    // Return true if anything has been parsed.
    //
    bool
    parse (int& argc,
           char** argv,
           bool erase = false,
           ::bdep::cli::unknown_mode option = ::bdep::cli::unknown_mode::fail,
           ::bdep::cli::unknown_mode argument = ::bdep::cli::unknown_mode::stop);

    bool
    parse (int start,
           int& argc,
           char** argv,
           bool erase = false,
           ::bdep::cli::unknown_mode option = ::bdep::cli::unknown_mode::fail,
           ::bdep::cli::unknown_mode argument = ::bdep::cli::unknown_mode::stop);

    bool
    parse (int& argc,
           char** argv,
           int& end,
           bool erase = false,
           ::bdep::cli::unknown_mode option = ::bdep::cli::unknown_mode::fail,
           ::bdep::cli::unknown_mode argument = ::bdep::cli::unknown_mode::stop);

    bool
    parse (int start,
           int& argc,
           char** argv,
           int& end,
           bool erase = false,
           ::bdep::cli::unknown_mode option = ::bdep::cli::unknown_mode::fail,
           ::bdep::cli::unknown_mode argument = ::bdep::cli::unknown_mode::stop);

    bool
    parse (::bdep::cli::scanner&,
           ::bdep::cli::unknown_mode option = ::bdep::cli::unknown_mode::fail,
           ::bdep::cli::unknown_mode argument = ::bdep::cli::unknown_mode::stop);

    // Merge options from the specified instance appending/overriding
    // them as if they appeared after options in this instance.
    //
    void
    merge (const cmd_status_options&);

    // Option accessors and modifiers.
    //
    const bool&
    immediate () const;

    bool&
    immediate ();

    void
    immediate (const bool&);

    const bool&
    recursive () const;

    bool&
    recursive ();

    void
    recursive (const bool&);

    const bool&
    old_available () const;

    bool&
    old_available ();

    void
    old_available (const bool&);

    const bool&
    fetch () const;

    bool&
    fetch ();

    void
    fetch (const bool&);

    const bool&
    fetch_full () const;

    bool&
    fetch_full ();

    void
    fetch_full (const bool&);

    // Print usage information.
    //
    static ::bdep::cli::usage_para
    print_usage (::std::ostream&,
                 ::bdep::cli::usage_para = ::bdep::cli::usage_para::none);

    // Option description.
    //
    static const ::bdep::cli::options&
    description ();

    // Implementation details.
    //
    protected:
    friend struct _cli_cmd_status_options_desc_type;

    static void
    fill (::bdep::cli::options&);

    bool
    _parse (const char*, ::bdep::cli::scanner&);

    private:
    bool
    _parse (::bdep::cli::scanner&,
            ::bdep::cli::unknown_mode option,
            ::bdep::cli::unknown_mode argument);

    public:
    bool immediate_;
    bool recursive_;
    bool old_available_;
    bool fetch_;
    bool fetch_full_;
  };
}

// Print page usage information.
//
namespace bdep
{
  ::bdep::cli::usage_para
  print_bdep_status_usage (::std::ostream&,
                           ::bdep::cli::usage_para = ::bdep::cli::usage_para::none);
}

#include <bdep/status-options.ixx>

// Begin epilogue.
//
//
// End epilogue.

#endif // BDEP_STATUS_OPTIONS_HXX
