// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

#ifndef BDEP_COMMON_OPTIONS_HXX
#define BDEP_COMMON_OPTIONS_HXX

// Begin prologue.
//
//
// End prologue.

#include <list>
#include <deque>
#include <map>
#include <vector>
#include <iosfwd>
#include <string>
#include <cstddef>
#include <exception>

#ifndef CLI_POTENTIALLY_UNUSED
#  if defined(_MSC_VER) || defined(__xlC__)
#    define CLI_POTENTIALLY_UNUSED(x) (void*)&x
#  else
#    define CLI_POTENTIALLY_UNUSED(x) (void)x
#  endif
#endif

namespace bdep
{
  namespace cli
  {
    class usage_para
    {
      public:
      enum value
      {
        none,
        text,
        option
      };

      usage_para (value);

      operator value () const 
      {
        return v_;
      }

      private:
      value v_;
    };

    class unknown_mode
    {
      public:
      enum value
      {
        skip,
        stop,
        fail
      };

      unknown_mode (value);

      operator value () const 
      {
        return v_;
      }

      private:
      value v_;
    };

    // Exceptions.
    //

    class exception: public std::exception
    {
      public:
      virtual void
      print (::std::ostream&) const = 0;
    };

    ::std::ostream&
    operator<< (::std::ostream&, const exception&);

    class unknown_option: public exception
    {
      public:
      virtual
      ~unknown_option () throw ();

      unknown_option (const std::string& option);

      const std::string&
      option () const;

      virtual void
      print (::std::ostream&) const;

      virtual const char*
      what () const throw ();

      private:
      std::string option_;
    };

    class unknown_argument: public exception
    {
      public:
      virtual
      ~unknown_argument () throw ();

      unknown_argument (const std::string& argument);

      const std::string&
      argument () const;

      virtual void
      print (::std::ostream&) const;

      virtual const char*
      what () const throw ();

      private:
      std::string argument_;
    };

    class missing_value: public exception
    {
      public:
      virtual
      ~missing_value () throw ();

      missing_value (const std::string& option);

      const std::string&
      option () const;

      virtual void
      print (::std::ostream&) const;

      virtual const char*
      what () const throw ();

      private:
      std::string option_;
    };

    class invalid_value: public exception
    {
      public:
      virtual
      ~invalid_value () throw ();

      invalid_value (const std::string& option,
                     const std::string& value,
                     const std::string& message = std::string ());

      const std::string&
      option () const;

      const std::string&
      value () const;

      const std::string&
      message () const;

      virtual void
      print (::std::ostream&) const;

      virtual const char*
      what () const throw ();

      private:
      std::string option_;
      std::string value_;
      std::string message_;
    };

    class eos_reached: public exception
    {
      public:
      virtual void
      print (::std::ostream&) const;

      virtual const char*
      what () const throw ();
    };

    class file_io_failure: public exception
    {
      public:
      virtual
      ~file_io_failure () throw ();

      file_io_failure (const std::string& file);

      const std::string&
      file () const;

      virtual void
      print (::std::ostream&) const;

      virtual const char*
      what () const throw ();

      private:
      std::string file_;
    };

    class unmatched_quote: public exception
    {
      public:
      virtual
      ~unmatched_quote () throw ();

      unmatched_quote (const std::string& argument);

      const std::string&
      argument () const;

      virtual void
      print (::std::ostream&) const;

      virtual const char*
      what () const throw ();

      private:
      std::string argument_;
    };

    class unexpected_group: public exception
    {
      public:
      virtual
      ~unexpected_group () throw ();

      unexpected_group (const std::string& argument,
                        const std::string& group);

      const std::string&
      argument () const;

      const std::string&
      group () const;

      virtual void
      print (std::ostream&) const;

      virtual const char*
      what () const throw ();

      private:
      std::string argument_;
      std::string group_;
    };

    class group_separator: public exception
    {
      public:
      virtual
      ~group_separator () throw ();

      // Note: either (but not both) can be empty.
      //
      group_separator (const std::string& encountered,
                       const std::string& expected);

      const std::string&
      encountered () const;

      const std::string&
      expected () const;

      virtual void
      print (std::ostream&) const;

      virtual const char*
      what () const throw ();

      private:
      std::string encountered_;
      std::string expected_;
    };

    // Command line argument scanner interface.
    //
    // The values returned by next() are guaranteed to be valid
    // for the two previous arguments up until a call to a third
    // peek() or next().
    //
    class scanner
    {
      public:
      virtual
      ~scanner ();

      virtual bool
      more () = 0;

      virtual const char*
      peek () = 0;

      virtual const char*
      next () = 0;

      virtual void
      skip () = 0;
    };

    class argv_scanner: public scanner
    {
      public:
      argv_scanner (int& argc, char** argv, bool erase = false);
      argv_scanner (int start, int& argc, char** argv, bool erase = false);

      int
      end () const;

      virtual bool
      more ();

      virtual const char*
      peek ();

      virtual const char*
      next ();

      virtual void
      skip ();

      private:
      int i_;
      int& argc_;
      char** argv_;
      bool erase_;
    };

    class vector_scanner: public scanner
    {
      public:
      vector_scanner (const std::vector<std::string>&, std::size_t start = 0);

      std::size_t
      end () const;

      void
      reset (std::size_t start = 0);

      virtual bool
      more ();

      virtual const char*
      peek ();

      virtual const char*
      next ();

      virtual void
      skip ();

      private:
      const std::vector<std::string>& v_;
      std::size_t i_;
    };

    class argv_file_scanner: public argv_scanner
    {
      public:
      argv_file_scanner (int& argc,
                         char** argv,
                         const std::string& option,
                         bool erase = false);

      argv_file_scanner (int start,
                         int& argc,
                         char** argv,
                         const std::string& option,
                         bool erase = false);

      argv_file_scanner (const std::string& file,
                         const std::string& option);

      struct option_info
      {
        // If search_func is not NULL, it is called, with the arg
        // value as the second argument, to locate the options file.
        // If it returns an empty string, then the file is ignored.
        //
        const char* option;
        std::string (*search_func) (const char*, void* arg);
        void* arg;
      };

      argv_file_scanner (int& argc,
                          char** argv,
                          const option_info* options,
                          std::size_t options_count,
                          bool erase = false);

      argv_file_scanner (int start,
                         int& argc,
                         char** argv,
                         const option_info* options,
                         std::size_t options_count,
                         bool erase = false);

      argv_file_scanner (const std::string& file,
                         const option_info* options = 0,
                         std::size_t options_count = 0);

      virtual bool
      more ();

      virtual const char*
      peek ();

      virtual const char*
      next ();

      virtual void
      skip ();

      // Return the file path if the peeked at argument came from a file and
      // the empty string otherwise. The reference is guaranteed to be valid
      // till the end of the scanner lifetime.
      //
      const std::string&
      peek_file ();

      // Return the 1-based line number if the peeked at argument came from
      // a file and zero otherwise.
      //
      std::size_t
      peek_line ();

      private:
      const option_info*
      find (const char*) const;

      void
      load (const std::string& file);

      typedef argv_scanner base;

      const std::string option_;
      option_info option_info_;
      const option_info* options_;
      std::size_t options_count_;

      struct arg
      {
        std::string value;
        const std::string* file;
        std::size_t line;
      };

      std::deque<arg> args_;
      std::list<std::string> files_;

      // Circular buffer of two arguments.
      //
      std::string hold_[2];
      std::size_t i_;

      bool skip_;

      static int zero_argc_;
      static std::string empty_string_;
    };

    class group_scanner: public scanner
    {
      public:
      group_scanner (scanner&);

      virtual bool
      more ();

      virtual const char*
      peek ();

      virtual const char*
      next ();

      virtual void
      skip ();

      // The group is only available after the call to next()
      // (and skip() -- in case one needs to make sure the group
      // was empty, or some such) and is only valid (and must be
      // handled) until the next call to any of the scanner
      // functions (including more()).
      //
      scanner&
      group ();

      // Escape an argument that is a group separator. Return the
      // passed string if no escaping is required.
      //
      static const char*
      escape (const char*);

      private:
      enum state
      {
        peeked,  // Argument peeked at with peek().
        scanned, // Argument scanned with next().
        skipped, // Argument skipped with skip()/initial.
      };

      enum separator
      {
        none,
        open,      // {
        close,     // }
        open_plus, // +{
        close_plus // }+
      };

      static separator
      sense (const char*);

      // If the state is scanned or skipped, then scan the
      // leading groups and save the next (unescaped) argument in
      // arg_. If the state is peeked, then scan the trailing
      // groups. In both cases set the new state.
      //
      void
      scan_group (state);

      scanner& scan_;
      state state_;

      // Circular buffer of two arguments.
      //
      std::string arg_[2];
      std::size_t i_;

      std::vector<std::string> group_;
      vector_scanner group_scan_;
    };

    typedef std::vector<std::string> option_names;

    class option
    {
      public:

      const std::string&
      name () const;

      const option_names&
      aliases () const;

      bool
      flag () const;

      const std::string&
      default_value () const;

      public:option ();
      option (const std::string& name,
              const option_names& aliases,
              bool flag,
              const std::string& default_value);

      private:
      std::string name_;
      option_names aliases_;
      bool flag_;
      std::string default_value_;
    };

    class options: public std::vector<option>
    {
      public:
      typedef std::vector<option> container_type;

      container_type::const_iterator
      find (const std::string& name) const;

      void
      push_back (const option&);
      private:
      typedef std::map<std::string, container_type::size_type> map_type;
      map_type map_;
    };

    template <typename X>
    struct parser;
  }
}

#include <bdep/types.hxx>

#include <bdep/options-types.hxx>

namespace bdep
{
  class common_options
  {
    public:
    // Merge options from the specified instance appending/overriding
    // them as if they appeared after options in this instance.
    //
    void
    merge (const common_options&);

    // Option accessors and modifiers.
    //
    const bool&
    v () const;

    bool&
    v ();

    void
    v (const bool&);

    const bool&
    V () const;

    bool&
    V ();

    void
    V (const bool&);

    const bool&
    quiet () const;

    bool&
    quiet ();

    void
    quiet (const bool&);

    const uint16_t&
    verbose () const;

    uint16_t&
    verbose ();

    void
    verbose (const uint16_t&);

    bool
    verbose_specified () const;

    void
    verbose_specified (bool);

    const size_t&
    jobs () const;

    size_t&
    jobs ();

    void
    jobs (const size_t&);

    bool
    jobs_specified () const;

    void
    jobs_specified (bool);

    const bool&
    no_progress () const;

    bool&
    no_progress ();

    void
    no_progress (const bool&);

    const path&
    bpkg () const;

    path&
    bpkg ();

    void
    bpkg (const path&);

    bool
    bpkg_specified () const;

    void
    bpkg_specified (bool);

    const strings&
    bpkg_option () const;

    strings&
    bpkg_option ();

    void
    bpkg_option (const strings&);

    bool
    bpkg_option_specified () const;

    void
    bpkg_option_specified (bool);

    const path&
    build () const;

    path&
    build ();

    void
    build (const path&);

    bool
    build_specified () const;

    void
    build_specified (bool);

    const strings&
    build_option () const;

    strings&
    build_option ();

    void
    build_option (const strings&);

    bool
    build_option_specified () const;

    void
    build_option_specified (bool);

    const path&
    curl () const;

    path&
    curl ();

    void
    curl (const path&);

    bool
    curl_specified () const;

    void
    curl_specified (bool);

    const strings&
    curl_option () const;

    strings&
    curl_option ();

    void
    curl_option (const strings&);

    bool
    curl_option_specified () const;

    void
    curl_option_specified (bool);

    const string&
    pager () const;

    string&
    pager ();

    void
    pager (const string&);

    bool
    pager_specified () const;

    void
    pager_specified (bool);

    const strings&
    pager_option () const;

    strings&
    pager_option ();

    void
    pager_option (const strings&);

    bool
    pager_option_specified () const;

    void
    pager_option_specified (bool);

    const string&
    options_file () const;

    string&
    options_file ();

    void
    options_file (const string&);

    bool
    options_file_specified () const;

    void
    options_file_specified (bool);

    const dir_path&
    default_options () const;

    dir_path&
    default_options ();

    void
    default_options (const dir_path&);

    bool
    default_options_specified () const;

    void
    default_options_specified (bool);

    const bool&
    no_default_options () const;

    bool&
    no_default_options ();

    void
    no_default_options (const bool&);

    // Print usage information.
    //
    static ::bdep::cli::usage_para
    print_usage (::std::ostream&,
                 ::bdep::cli::usage_para = ::bdep::cli::usage_para::none);

    static ::bdep::cli::usage_para
    print_long_usage (::std::ostream&,
                      ::bdep::cli::usage_para = ::bdep::cli::usage_para::none);

    // Option description.
    //
    static const ::bdep::cli::options&
    description ();

    // Implementation details.
    //
    protected:
    common_options ();

    friend struct _cli_common_options_desc_type;

    static void
    fill (::bdep::cli::options&);

    bool
    _parse (const char*, ::bdep::cli::scanner&);

    public:
    bool v_;
    bool V_;
    bool quiet_;
    uint16_t verbose_;
    bool verbose_specified_;
    size_t jobs_;
    bool jobs_specified_;
    bool no_progress_;
    path bpkg_;
    bool bpkg_specified_;
    strings bpkg_option_;
    bool bpkg_option_specified_;
    path build_;
    bool build_specified_;
    strings build_option_;
    bool build_option_specified_;
    path curl_;
    bool curl_specified_;
    strings curl_option_;
    bool curl_option_specified_;
    string pager_;
    bool pager_specified_;
    strings pager_option_;
    bool pager_option_specified_;
    string options_file_;
    bool options_file_specified_;
    dir_path default_options_;
    bool default_options_specified_;
    bool no_default_options_;
  };
}

// Print page usage information.
//
namespace bdep
{
  ::bdep::cli::usage_para
  print_bdep_common_options_usage (::std::ostream&,
                                   ::bdep::cli::usage_para = ::bdep::cli::usage_para::none);

  ::bdep::cli::usage_para
  print_bdep_common_options_long_usage (::std::ostream&,
                                        ::bdep::cli::usage_para = ::bdep::cli::usage_para::none);
}

#include <bdep/common-options.ixx>

// Begin epilogue.
//
//
// End epilogue.

#endif // BDEP_COMMON_OPTIONS_HXX
