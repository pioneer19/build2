// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

#ifndef BPKG_PKG_BUILD_OPTIONS_HXX
#define BPKG_PKG_BUILD_OPTIONS_HXX

// Begin prologue.
//
//
// End prologue.

#include <bpkg/configuration-options.hxx>

namespace bpkg
{
  class pkg_build_pkg_options
  {
    public:
    pkg_build_pkg_options ();

    // Return true if anything has been parsed.
    //
    bool
    parse (int& argc,
           char** argv,
           bool erase = false,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    bool
    parse (int start,
           int& argc,
           char** argv,
           bool erase = false,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    bool
    parse (int& argc,
           char** argv,
           int& end,
           bool erase = false,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    bool
    parse (int start,
           int& argc,
           char** argv,
           int& end,
           bool erase = false,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    bool
    parse (::bpkg::cli::scanner&,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    // Merge options from the specified instance appending/overriding
    // them as if they appeared after options in this instance.
    //
    void
    merge (const pkg_build_pkg_options&);

    // Option accessors and modifiers.
    //
    const bool&
    upgrade () const;

    bool&
    upgrade ();

    void
    upgrade (const bool&);

    const bool&
    patch () const;

    bool&
    patch ();

    void
    patch (const bool&);

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
    upgrade_immediate () const;

    bool&
    upgrade_immediate ();

    void
    upgrade_immediate (const bool&);

    const bool&
    patch_immediate () const;

    bool&
    patch_immediate ();

    void
    patch_immediate (const bool&);

    const bool&
    upgrade_recursive () const;

    bool&
    upgrade_recursive ();

    void
    upgrade_recursive (const bool&);

    const bool&
    patch_recursive () const;

    bool&
    patch_recursive ();

    void
    patch_recursive (const bool&);

    const bool&
    dependency () const;

    bool&
    dependency ();

    void
    dependency (const bool&);

    const bool&
    keep_out () const;

    bool&
    keep_out ();

    void
    keep_out (const bool&);

    // Print usage information.
    //
    static ::bpkg::cli::usage_para
    print_usage (::std::ostream&,
                 ::bpkg::cli::usage_para = ::bpkg::cli::usage_para::none);

    // Implementation details.
    //
    protected:
    bool
    _parse (const char*, ::bpkg::cli::scanner&);

    private:
    bool
    _parse (::bpkg::cli::scanner&,
            ::bpkg::cli::unknown_mode option,
            ::bpkg::cli::unknown_mode argument);

    public:
    bool upgrade_;
    bool patch_;
    bool immediate_;
    bool recursive_;
    bool upgrade_immediate_;
    bool patch_immediate_;
    bool upgrade_recursive_;
    bool patch_recursive_;
    bool dependency_;
    bool keep_out_;
  };

  class pkg_build_options: public ::bpkg::configuration_options,
    public ::bpkg::pkg_build_pkg_options
  {
    public:
    pkg_build_options ();

    // Return true if anything has been parsed.
    //
    bool
    parse (int& argc,
           char** argv,
           bool erase = false,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    bool
    parse (int start,
           int& argc,
           char** argv,
           bool erase = false,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    bool
    parse (int& argc,
           char** argv,
           int& end,
           bool erase = false,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    bool
    parse (int start,
           int& argc,
           char** argv,
           int& end,
           bool erase = false,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    bool
    parse (::bpkg::cli::scanner&,
           ::bpkg::cli::unknown_mode option = ::bpkg::cli::unknown_mode::fail,
           ::bpkg::cli::unknown_mode argument = ::bpkg::cli::unknown_mode::stop);

    // Merge options from the specified instance appending/overriding
    // them as if they appeared after options in this instance.
    //
    void
    merge (const pkg_build_options&);

    // Option accessors and modifiers.
    //
    const bool&
    yes () const;

    bool&
    yes ();

    void
    yes (const bool&);

    const string&
    for_ () const;

    string&
    for_ ();

    void
    for_ (const string&);

    bool
    for__specified () const;

    void
    for__specified (bool);

    const bool&
    keep_unused () const;

    bool&
    keep_unused ();

    void
    keep_unused (const bool&);

    const bool&
    update_dependent () const;

    bool&
    update_dependent ();

    void
    update_dependent (const bool&);

    const bool&
    leave_dependent () const;

    bool&
    leave_dependent ();

    void
    leave_dependent (const bool&);

    const bool&
    configure_only () const;

    bool&
    configure_only ();

    void
    configure_only (const bool&);

    const bool&
    print_only () const;

    bool&
    print_only ();

    void
    print_only (const bool&);

    const string&
    plan () const;

    string&
    plan ();

    void
    plan (const string&);

    bool
    plan_specified () const;

    void
    plan_specified (bool);

    const bool&
    no_fetch () const;

    bool&
    no_fetch ();

    void
    no_fetch (const bool&);

    const bool&
    fetch_shallow () const;

    bool&
    fetch_shallow ();

    void
    fetch_shallow (const bool&);

    // Print usage information.
    //
    static ::bpkg::cli::usage_para
    print_usage (::std::ostream&,
                 ::bpkg::cli::usage_para = ::bpkg::cli::usage_para::none);

    // Implementation details.
    //
    protected:
    bool
    _parse (const char*, ::bpkg::cli::scanner&);

    private:
    bool
    _parse (::bpkg::cli::scanner&,
            ::bpkg::cli::unknown_mode option,
            ::bpkg::cli::unknown_mode argument);

    public:
    bool yes_;
    string for__;
    bool for__specified_;
    bool keep_unused_;
    bool update_dependent_;
    bool leave_dependent_;
    bool configure_only_;
    bool print_only_;
    string plan_;
    bool plan_specified_;
    bool no_fetch_;
    bool fetch_shallow_;
  };
}

// Print page usage information.
//
namespace bpkg
{
  ::bpkg::cli::usage_para
  print_bpkg_pkg_build_usage (::std::ostream&,
                              ::bpkg::cli::usage_para = ::bpkg::cli::usage_para::none);
}

#include <bpkg/pkg-build-options.ixx>

// Begin epilogue.
//
//
// End epilogue.

#endif // BPKG_PKG_BUILD_OPTIONS_HXX
