// file      : bpkg/database.hxx -*- C++ -*-
// license   : MIT; see accompanying LICENSE file

#ifndef BPKG_DATABASE_HXX
#define BPKG_DATABASE_HXX

#include <type_traits> // remove_reference

#include <odb/query.hxx>
#include <odb/result.hxx>
#include <odb/session.hxx>

#include <odb/sqlite/database.hxx>

#include <bpkg/types.hxx>
#include <bpkg/utility.hxx>

#include <bpkg/diagnostics.hxx>

namespace bpkg
{
  using odb::query;
  using odb::result;
  using odb::session;

  using odb::sqlite::database;

  // Transaction wrapper that allow the creation of dummy transactions (start
  // is false) that in reality use an existing transaction.
  //
  struct transaction
  {
    using database_type = bpkg::database;

    explicit
    transaction (database_type& db, bool start = true)
        : db_ (db), start_ (start), t_ () // Finalized.
    {
      if (start)
        t_.reset (db.begin ());
    }

    void
    commit ()
    {
      if (start_)
        t_.commit ();
    }

    void
    rollback ()
    {
      if (start_)
        t_.rollback ();
    }

    database_type&
    database ()
    {
      return db_;
    }

    static bool
    has_current ()
    {
      return odb::sqlite::transaction::has_current ();
    }

    static odb::sqlite::transaction&
    current ()
    {
      return odb::sqlite::transaction::current ();
    }

  private:
    database_type& db_;
    bool start_;
    odb::sqlite::transaction t_;
  };

  database
  open (const dir_path& configuration, tracer&, bool create = false);

  struct tracer_guard
  {
    tracer_guard (database& db, tracer& t)
        : db_ (db), t_ (db.tracer ()) {db.tracer (t);}
    ~tracer_guard () {db_.tracer (*t_);}

  private:
    database& db_;
    odb::tracer* t_;
  };

  // Range-based for-loop iteration over query result that returns
  // object pointers. For example:
  //
  // for (shared_ptr<object> o: pointer_result (db.query<object> (...)))
  //
  template <typename R>
  class pointer_result_range
  {
    R r_;

  public:
    pointer_result_range (R&& r): r_ (forward<R> (r)) {}

    using base_iterator = typename std::remove_reference<R>::type::iterator;

    struct iterator: base_iterator
    {
      iterator () = default;

      explicit
      iterator (base_iterator i): base_iterator (move (i)) {}

      typename base_iterator::pointer_type
      operator* () {return this->load ();}
    };

    iterator begin () {return iterator (r_.begin ());}
    iterator end () {return iterator (r_.end ());}
  };

  template <typename R>
  inline pointer_result_range<R>
  pointer_result (R&& r)
  {
    return pointer_result_range<R> (forward<R> (r));
  }
}

#endif // BPKG_DATABASE_HXX
