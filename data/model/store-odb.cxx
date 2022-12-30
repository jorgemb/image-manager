// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "store-odb.hxx"

#include <cassert>
#include <cstring>  // std::memcpy


#include <odb/pgsql/traits.hxx>
#include <odb/pgsql/database.hxx>
#include <odb/pgsql/transaction.hxx>
#include <odb/pgsql/connection.hxx>
#include <odb/pgsql/statement.hxx>
#include <odb/pgsql/statement-cache.hxx>
#include <odb/pgsql/simple-object-statements.hxx>
#include <odb/pgsql/container-statements.hxx>
#include <odb/pgsql/exceptions.hxx>
#include <odb/pgsql/simple-object-result.hxx>

namespace odb
{
  // Album
  //

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  persist_statement_name[] = "persist_imgr_model_Album";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  find_statement_name[] = "find_imgr_model_Album";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  update_statement_name[] = "update_imgr_model_Album";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  erase_statement_name[] = "erase_imgr_model_Album";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  query_statement_name[] = "query_imgr_model_Album";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  erase_query_statement_name[] = "erase_query_imgr_model_Album";

  const unsigned int access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  persist_statement_types[] =
  {
    pgsql::text_oid
  };

  const unsigned int access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  find_statement_types[] =
  {
    pgsql::int8_oid
  };

  const unsigned int access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  update_statement_types[] =
  {
    pgsql::text_oid,
    pgsql::int8_oid
  };

  struct access::object_traits_impl< ::imgr::model::Album, id_pgsql >::extra_statement_cache_type
  {
    extra_statement_cache_type (
      pgsql::connection&,
      image_type&,
      id_image_type&,
      pgsql::binding&,
      pgsql::binding&,
      pgsql::native_binding&,
      const unsigned int*)
    {
    }
  };

  access::object_traits_impl< ::imgr::model::Album, id_pgsql >::id_type
  access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  id (const id_image_type& i)
  {
    pgsql::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      pgsql::value_traits<
          ::imgr::model::Album::id_type,
          pgsql::id_bigint >::set_value (
        id,
        i.id_value,
        i.id_null);
    }

    return id;
  }

  access::object_traits_impl< ::imgr::model::Album, id_pgsql >::id_type
  access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  id (const image_type& i)
  {
    pgsql::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      pgsql::value_traits<
          ::imgr::model::Album::id_type,
          pgsql::id_bigint >::set_value (
        id,
        i.m_id_value,
        i.m_id_null);
    }

    return id;
  }

  bool access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  grow (image_type& i,
        bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // m_id
    //
    t[0UL] = 0;

    // m_absolute_path
    //
    if (t[1UL])
    {
      i.m_absolute_path_value.capacity (i.m_absolute_path_size);
      grew = true;
    }

    return grew;
  }

  void access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  bind (pgsql::bind* b,
        image_type& i,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    std::size_t n (0);

    // m_id
    //
    if (sk != statement_insert && sk != statement_update)
    {
      b[n].type = pgsql::bind::bigint;
      b[n].buffer = &i.m_id_value;
      b[n].is_null = &i.m_id_null;
      n++;
    }

    // m_absolute_path
    //
    b[n].type = pgsql::bind::text;
    b[n].buffer = i.m_absolute_path_value.data ();
    b[n].capacity = i.m_absolute_path_value.capacity ();
    b[n].size = &i.m_absolute_path_size;
    b[n].is_null = &i.m_absolute_path_null;
    n++;
  }

  void access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  bind (pgsql::bind* b, id_image_type& i)
  {
    std::size_t n (0);
    b[n].type = pgsql::bind::bigint;
    b[n].buffer = &i.id_value;
    b[n].is_null = &i.id_null;
  }

  bool access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  init (image_type& i,
        const object_type& o,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    bool grew (false);

    // m_absolute_path
    //
    {
      ::std::string const& v =
        o.m_absolute_path;

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.m_absolute_path_value.capacity ());
      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_image (
        i.m_absolute_path_value,
        size,
        is_null,
        v);
      i.m_absolute_path_null = is_null;
      i.m_absolute_path_size = size;
      grew = grew || (cap != i.m_absolute_path_value.capacity ());
    }

    return grew;
  }

  void access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  init (object_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // m_id
    //
    {
      ::imgr::model::Album::id_type& v =
        o.m_id;

      pgsql::value_traits<
          ::imgr::model::Album::id_type,
          pgsql::id_bigint >::set_value (
        v,
        i.m_id_value,
        i.m_id_null);
    }

    // m_absolute_path
    //
    {
      ::std::string& v =
        o.m_absolute_path;

      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_value (
        v,
        i.m_absolute_path_value,
        i.m_absolute_path_size,
        i.m_absolute_path_null);
    }
  }

  void access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  init (id_image_type& i, const id_type& id)
  {
    {
      bool is_null (false);
      pgsql::value_traits<
          ::imgr::model::Album::id_type,
          pgsql::id_bigint >::set_image (
        i.id_value, is_null, id);
      i.id_null = is_null;
    }
  }

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::persist_statement[] =
  "INSERT INTO \"Album\" "
  "(\"id\", "
  "\"absolute_path\") "
  "VALUES "
  "(DEFAULT, $1) "
  "RETURNING \"id\"";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::find_statement[] =
  "SELECT "
  "\"Album\".\"id\", "
  "\"Album\".\"absolute_path\" "
  "FROM \"Album\" "
  "WHERE \"Album\".\"id\"=$1";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::update_statement[] =
  "UPDATE \"Album\" "
  "SET "
  "\"absolute_path\"=$1 "
  "WHERE \"id\"=$2";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::erase_statement[] =
  "DELETE FROM \"Album\" "
  "WHERE \"id\"=$1";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::query_statement[] =
  "SELECT "
  "\"Album\".\"id\", "
  "\"Album\".\"absolute_path\" "
  "FROM \"Album\"";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::erase_query_statement[] =
  "DELETE FROM \"Album\"";

  const char access::object_traits_impl< ::imgr::model::Album, id_pgsql >::table_name[] =
  "\"Album\"";

  void access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  persist (database& db, object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    callback (db,
              static_cast<const object_type&> (obj),
              callback_event::pre_persist);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    if (im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    {
      id_image_type& i (sts.id_image ());
      binding& b (sts.id_image_binding ());
      if (i.version != sts.id_image_version () || b.version == 0)
      {
        bind (b.bind, i);
        sts.id_image_version (i.version);
        b.version++;
      }
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    obj.m_id = id (sts.id_image ());

    callback (db,
              static_cast<const object_type&> (obj),
              callback_event::post_persist);
  }

  void access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  update (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace pgsql;
    using pgsql::update_statement;

    callback (db, obj, callback_event::pre_update);

    pgsql::transaction& tr (pgsql::transaction::current ());
    pgsql::connection& conn (tr.connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    const id_type& id (
      obj.m_id);
    id_image_type& idi (sts.id_image ());
    init (idi, id);

    image_type& im (sts.image ());
    if (init (im, obj, statement_update))
      im.version++;

    bool u (false);
    binding& imb (sts.update_image_binding ());
    if (im.version != sts.update_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_update);
      sts.update_image_version (im.version);
      imb.version++;
      u = true;
    }

    binding& idb (sts.id_image_binding ());
    if (idi.version != sts.update_id_image_version () ||
        idb.version == 0)
    {
      if (idi.version != sts.id_image_version () ||
          idb.version == 0)
      {
        bind (idb.bind, idi);
        sts.id_image_version (idi.version);
        idb.version++;
      }

      sts.update_id_image_version (idi.version);

      if (!u)
        imb.version++;
    }

    update_statement& st (sts.update_statement ());
    if (st.execute () == 0)
      throw object_not_persistent ();

    callback (db, obj, callback_event::post_update);
    pointer_cache_traits::update (db, obj);
  }

  void access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  erase (database& db, const id_type& id)
  {
    using namespace pgsql;

    ODB_POTENTIALLY_UNUSED (db);

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    if (sts.erase_statement ().execute () != 1)
      throw object_not_persistent ();

    pointer_cache_traits::erase (db, id);
  }

  access::object_traits_impl< ::imgr::model::Album, id_pgsql >::pointer_type
  access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  find (database& db, const id_type& id)
  {
    using namespace pgsql;

    {
      pointer_type p (pointer_cache_traits::find (db, id));

      if (!pointer_traits::null_ptr (p))
        return p;
    }

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (l.locked ())
    {
      if (!find_ (sts, &id))
        return pointer_type ();
    }

    pointer_type p (
      access::object_factory<object_type, pointer_type>::create ());
    pointer_traits::guard pg (p);

    pointer_cache_traits::insert_guard ig (
      pointer_cache_traits::insert (db, id, p));

    object_type& obj (pointer_traits::get_ref (p));

    if (l.locked ())
    {
      select_statement& st (sts.find_statement ());
      ODB_POTENTIALLY_UNUSED (st);

      callback (db, obj, callback_event::pre_load);
      init (obj, sts.image (), &db);
      load_ (sts, obj, false);
      sts.load_delayed (0);
      l.unlock ();
      callback (db, obj, callback_event::post_load);
      pointer_cache_traits::load (ig.position ());
    }
    else
      sts.delay_load (id, obj, ig.position ());

    ig.release ();
    pg.release ();
    return p;
  }

  bool access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  find (database& db, const id_type& id, object_type& obj)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    reference_cache_traits::position_type pos (
      reference_cache_traits::insert (db, id, obj));
    reference_cache_traits::insert_guard ig (pos);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, false);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    reference_cache_traits::load (pos);
    ig.release ();
    return true;
  }

  bool access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  reload (database& db, object_type& obj)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    const id_type& id  (
      obj.m_id);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, true);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    return true;
  }

  bool access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  find_ (statements_type& sts,
         const id_type* id)
  {
    using namespace pgsql;

    id_image_type& i (sts.id_image ());
    init (i, *id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    select_statement& st (sts.find_statement ());

    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      if (grow (im, sts.select_image_truncated ()))
        im.version++;

      if (im.version != sts.select_image_version ())
      {
        bind (imb.bind, im, statement_select);
        sts.select_image_version (im.version);
        imb.version++;
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  result< access::object_traits_impl< ::imgr::model::Album, id_pgsql >::object_type >
  access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  query (database&, const query_base_type& q)
  {
    using namespace pgsql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    std::string text (query_statement);
    if (!q.empty ())
    {
      text += " ";
      text += q.clause ();
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        sts.connection (),
        query_statement_name,
        text,
        false,
        true,
        q.parameter_types (),
        q.parameter_count (),
        q.parameters_binding (),
        imb));

    st->execute ();
    st->deallocate ();

    shared_ptr< odb::object_result_impl<object_type> > r (
      new (shared) pgsql::object_result_impl<object_type> (
        q, st, sts, 0));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::imgr::model::Album, id_pgsql >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    std::string text (erase_query_statement);
    if (!q.empty ())
    {
      text += ' ';
      text += q.clause ();
    }

    q.init_parameters ();
    delete_statement st (
      conn,
      erase_query_statement_name,
      text,
      q.parameter_types (),
      q.parameter_count (),
      q.parameters_binding ());

    return st.execute ();
  }

  // Photo
  //

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  persist_statement_name[] = "persist_imgr_model_Photo";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  find_statement_name[] = "find_imgr_model_Photo";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  update_statement_name[] = "update_imgr_model_Photo";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  erase_statement_name[] = "erase_imgr_model_Photo";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  query_statement_name[] = "query_imgr_model_Photo";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  erase_query_statement_name[] = "erase_query_imgr_model_Photo";

  const unsigned int access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  persist_statement_types[] =
  {
    pgsql::text_oid,
    pgsql::int4_oid,
    pgsql::int4_oid,
    pgsql::bytea_oid,
    pgsql::int8_oid
  };

  const unsigned int access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  find_statement_types[] =
  {
    pgsql::int8_oid
  };

  const unsigned int access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  update_statement_types[] =
  {
    pgsql::text_oid,
    pgsql::int4_oid,
    pgsql::int4_oid,
    pgsql::bytea_oid,
    pgsql::int8_oid,
    pgsql::int8_oid
  };

  const char alias_traits<  ::imgr::model::Album,
    id_pgsql,
    access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::album_tag>::
  table_name[] = "\"album\"";

  struct access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::extra_statement_cache_type
  {
    extra_statement_cache_type (
      pgsql::connection&,
      image_type&,
      id_image_type&,
      pgsql::binding&,
      pgsql::binding&,
      pgsql::native_binding&,
      const unsigned int*)
    {
    }
  };

  access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::id_type
  access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  id (const id_image_type& i)
  {
    pgsql::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      pgsql::value_traits<
          ::imgr::model::Photo::id_type,
          pgsql::id_bigint >::set_value (
        id,
        i.id_value,
        i.id_null);
    }

    return id;
  }

  access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::id_type
  access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  id (const image_type& i)
  {
    pgsql::database* db (0);
    ODB_POTENTIALLY_UNUSED (db);

    id_type id;
    {
      pgsql::value_traits<
          ::imgr::model::Photo::id_type,
          pgsql::id_bigint >::set_value (
        id,
        i.m_id_value,
        i.m_id_null);
    }

    return id;
  }

  bool access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  grow (image_type& i,
        bool* t)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (t);

    bool grew (false);

    // m_id
    //
    t[0UL] = 0;

    // m_filename
    //
    if (t[1UL])
    {
      i.m_filename_value.capacity (i.m_filename_size);
      grew = true;
    }

    // m_width
    //
    t[2UL] = 0;

    // m_height
    //
    t[3UL] = 0;

    // m_thumbnail
    //
    if (t[4UL])
    {
      i.m_thumbnail_value.capacity (i.m_thumbnail_size);
      grew = true;
    }

    // m_album
    //
    t[5UL] = 0;

    return grew;
  }

  void access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  bind (pgsql::bind* b,
        image_type& i,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    std::size_t n (0);

    // m_id
    //
    if (sk != statement_insert && sk != statement_update)
    {
      b[n].type = pgsql::bind::bigint;
      b[n].buffer = &i.m_id_value;
      b[n].is_null = &i.m_id_null;
      n++;
    }

    // m_filename
    //
    b[n].type = pgsql::bind::text;
    b[n].buffer = i.m_filename_value.data ();
    b[n].capacity = i.m_filename_value.capacity ();
    b[n].size = &i.m_filename_size;
    b[n].is_null = &i.m_filename_null;
    n++;

    // m_width
    //
    b[n].type = pgsql::bind::integer;
    b[n].buffer = &i.m_width_value;
    b[n].is_null = &i.m_width_null;
    n++;

    // m_height
    //
    b[n].type = pgsql::bind::integer;
    b[n].buffer = &i.m_height_value;
    b[n].is_null = &i.m_height_null;
    n++;

    // m_thumbnail
    //
    b[n].type = pgsql::bind::bytea;
    b[n].buffer = i.m_thumbnail_value.data ();
    b[n].capacity = i.m_thumbnail_value.capacity ();
    b[n].size = &i.m_thumbnail_size;
    b[n].is_null = &i.m_thumbnail_null;
    n++;

    // m_album
    //
    b[n].type = pgsql::bind::bigint;
    b[n].buffer = &i.m_album_value;
    b[n].is_null = &i.m_album_null;
    n++;
  }

  void access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  bind (pgsql::bind* b, id_image_type& i)
  {
    std::size_t n (0);
    b[n].type = pgsql::bind::bigint;
    b[n].buffer = &i.id_value;
    b[n].is_null = &i.id_null;
  }

  bool access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  init (image_type& i,
        const object_type& o,
        pgsql::statement_kind sk)
  {
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (sk);

    using namespace pgsql;

    bool grew (false);

    // m_filename
    //
    {
      ::std::string const& v =
        o.m_filename;

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.m_filename_value.capacity ());
      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_image (
        i.m_filename_value,
        size,
        is_null,
        v);
      i.m_filename_null = is_null;
      i.m_filename_size = size;
      grew = grew || (cap != i.m_filename_value.capacity ());
    }

    // m_width
    //
    {
      unsigned int const& v =
        o.m_width;

      bool is_null (false);
      pgsql::value_traits<
          unsigned int,
          pgsql::id_integer >::set_image (
        i.m_width_value, is_null, v);
      i.m_width_null = is_null;
    }

    // m_height
    //
    {
      unsigned int const& v =
        o.m_height;

      bool is_null (false);
      pgsql::value_traits<
          unsigned int,
          pgsql::id_integer >::set_image (
        i.m_height_value, is_null, v);
      i.m_height_null = is_null;
    }

    // m_thumbnail
    //
    {
      ::std::vector< unsigned char > const& v =
        o.m_thumbnail;

      bool is_null (false);
      std::size_t size (0);
      std::size_t cap (i.m_thumbnail_value.capacity ());
      pgsql::value_traits<
          ::std::vector< unsigned char >,
          pgsql::id_bytea >::set_image (
        i.m_thumbnail_value,
        size,
        is_null,
        v);
      i.m_thumbnail_null = is_null;
      i.m_thumbnail_size = size;
      grew = grew || (cap != i.m_thumbnail_value.capacity ());
    }

    // m_album
    //
    {
      ::std::shared_ptr< ::imgr::model::Album > const& v =
        o.m_album;

      typedef object_traits< ::imgr::model::Album > obj_traits;
      typedef odb::pointer_traits< ::std::shared_ptr< ::imgr::model::Album > > ptr_traits;

      bool is_null (ptr_traits::null_ptr (v));
      if (!is_null)
      {
        const obj_traits::id_type& id (
          obj_traits::id (ptr_traits::get_ref (v)));

        pgsql::value_traits<
            obj_traits::id_type,
            pgsql::id_bigint >::set_image (
          i.m_album_value, is_null, id);
        i.m_album_null = is_null;
      }
      else
        throw null_pointer ();
    }

    return grew;
  }

  void access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  init (object_type& o,
        const image_type& i,
        database* db)
  {
    ODB_POTENTIALLY_UNUSED (o);
    ODB_POTENTIALLY_UNUSED (i);
    ODB_POTENTIALLY_UNUSED (db);

    // m_id
    //
    {
      ::imgr::model::Photo::id_type& v =
        o.m_id;

      pgsql::value_traits<
          ::imgr::model::Photo::id_type,
          pgsql::id_bigint >::set_value (
        v,
        i.m_id_value,
        i.m_id_null);
    }

    // m_filename
    //
    {
      ::std::string& v =
        o.m_filename;

      pgsql::value_traits<
          ::std::string,
          pgsql::id_string >::set_value (
        v,
        i.m_filename_value,
        i.m_filename_size,
        i.m_filename_null);
    }

    // m_width
    //
    {
      unsigned int& v =
        o.m_width;

      pgsql::value_traits<
          unsigned int,
          pgsql::id_integer >::set_value (
        v,
        i.m_width_value,
        i.m_width_null);
    }

    // m_height
    //
    {
      unsigned int& v =
        o.m_height;

      pgsql::value_traits<
          unsigned int,
          pgsql::id_integer >::set_value (
        v,
        i.m_height_value,
        i.m_height_null);
    }

    // m_thumbnail
    //
    {
      ::std::vector< unsigned char >& v =
        o.m_thumbnail;

      pgsql::value_traits<
          ::std::vector< unsigned char >,
          pgsql::id_bytea >::set_value (
        v,
        i.m_thumbnail_value,
        i.m_thumbnail_size,
        i.m_thumbnail_null);
    }

    // m_album
    //
    {
      ::std::shared_ptr< ::imgr::model::Album >& v =
        o.m_album;

      typedef object_traits< ::imgr::model::Album > obj_traits;
      typedef odb::pointer_traits< ::std::shared_ptr< ::imgr::model::Album > > ptr_traits;

      if (i.m_album_null)
        v = ptr_traits::pointer_type ();
      else
      {
        obj_traits::id_type id;
        pgsql::value_traits<
            obj_traits::id_type,
            pgsql::id_bigint >::set_value (
          id,
          i.m_album_value,
          i.m_album_null);

        // If a compiler error points to the line below, then
        // it most likely means that a pointer used in a member
        // cannot be initialized from an object pointer.
        //
        v = ptr_traits::pointer_type (
          static_cast<pgsql::database*> (db)->load<
            obj_traits::object_type > (id));
      }
    }
  }

  void access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  init (id_image_type& i, const id_type& id)
  {
    {
      bool is_null (false);
      pgsql::value_traits<
          ::imgr::model::Photo::id_type,
          pgsql::id_bigint >::set_image (
        i.id_value, is_null, id);
      i.id_null = is_null;
    }
  }

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::persist_statement[] =
  "INSERT INTO \"Photo\" "
  "(\"id\", "
  "\"filename\", "
  "\"width\", "
  "\"height\", "
  "\"thumbnail\", "
  "\"album\") "
  "VALUES "
  "(DEFAULT, $1, $2, $3, $4, $5) "
  "RETURNING \"id\"";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::find_statement[] =
  "SELECT "
  "\"Photo\".\"id\", "
  "\"Photo\".\"filename\", "
  "\"Photo\".\"width\", "
  "\"Photo\".\"height\", "
  "\"Photo\".\"thumbnail\", "
  "\"Photo\".\"album\" "
  "FROM \"Photo\" "
  "WHERE \"Photo\".\"id\"=$1";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::update_statement[] =
  "UPDATE \"Photo\" "
  "SET "
  "\"filename\"=$1, "
  "\"width\"=$2, "
  "\"height\"=$3, "
  "\"thumbnail\"=$4, "
  "\"album\"=$5 "
  "WHERE \"id\"=$6";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::erase_statement[] =
  "DELETE FROM \"Photo\" "
  "WHERE \"id\"=$1";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::query_statement[] =
  "SELECT\n"
  "\"Photo\".\"id\",\n"
  "\"Photo\".\"filename\",\n"
  "\"Photo\".\"width\",\n"
  "\"Photo\".\"height\",\n"
  "\"Photo\".\"thumbnail\",\n"
  "\"Photo\".\"album\"\n"
  "FROM \"Photo\"\n"
  "LEFT JOIN \"Album\" AS \"album\" ON \"album\".\"id\"=\"Photo\".\"album\"";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::erase_query_statement[] =
  "DELETE FROM \"Photo\"";

  const char access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::table_name[] =
  "\"Photo\"";

  void access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  persist (database& db, object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    callback (db,
              static_cast<const object_type&> (obj),
              callback_event::pre_persist);

    image_type& im (sts.image ());
    binding& imb (sts.insert_image_binding ());

    if (init (im, obj, statement_insert))
      im.version++;

    if (im.version != sts.insert_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_insert);
      sts.insert_image_version (im.version);
      imb.version++;
    }

    {
      id_image_type& i (sts.id_image ());
      binding& b (sts.id_image_binding ());
      if (i.version != sts.id_image_version () || b.version == 0)
      {
        bind (b.bind, i);
        sts.id_image_version (i.version);
        b.version++;
      }
    }

    insert_statement& st (sts.persist_statement ());
    if (!st.execute ())
      throw object_already_persistent ();

    obj.m_id = id (sts.id_image ());

    callback (db,
              static_cast<const object_type&> (obj),
              callback_event::post_persist);
  }

  void access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  update (database& db, const object_type& obj)
  {
    ODB_POTENTIALLY_UNUSED (db);

    using namespace pgsql;
    using pgsql::update_statement;

    callback (db, obj, callback_event::pre_update);

    pgsql::transaction& tr (pgsql::transaction::current ());
    pgsql::connection& conn (tr.connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    const id_type& id (
      obj.m_id);
    id_image_type& idi (sts.id_image ());
    init (idi, id);

    image_type& im (sts.image ());
    if (init (im, obj, statement_update))
      im.version++;

    bool u (false);
    binding& imb (sts.update_image_binding ());
    if (im.version != sts.update_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_update);
      sts.update_image_version (im.version);
      imb.version++;
      u = true;
    }

    binding& idb (sts.id_image_binding ());
    if (idi.version != sts.update_id_image_version () ||
        idb.version == 0)
    {
      if (idi.version != sts.id_image_version () ||
          idb.version == 0)
      {
        bind (idb.bind, idi);
        sts.id_image_version (idi.version);
        idb.version++;
      }

      sts.update_id_image_version (idi.version);

      if (!u)
        imb.version++;
    }

    update_statement& st (sts.update_statement ());
    if (st.execute () == 0)
      throw object_not_persistent ();

    callback (db, obj, callback_event::post_update);
    pointer_cache_traits::update (db, obj);
  }

  void access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  erase (database& db, const id_type& id)
  {
    using namespace pgsql;

    ODB_POTENTIALLY_UNUSED (db);

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    id_image_type& i (sts.id_image ());
    init (i, id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    if (sts.erase_statement ().execute () != 1)
      throw object_not_persistent ();

    pointer_cache_traits::erase (db, id);
  }

  access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::pointer_type
  access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  find (database& db, const id_type& id)
  {
    using namespace pgsql;

    {
      pointer_type p (pointer_cache_traits::find (db, id));

      if (!pointer_traits::null_ptr (p))
        return p;
    }

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (l.locked ())
    {
      if (!find_ (sts, &id))
        return pointer_type ();
    }

    pointer_type p (
      access::object_factory<object_type, pointer_type>::create ());
    pointer_traits::guard pg (p);

    pointer_cache_traits::insert_guard ig (
      pointer_cache_traits::insert (db, id, p));

    object_type& obj (pointer_traits::get_ref (p));

    if (l.locked ())
    {
      select_statement& st (sts.find_statement ());
      ODB_POTENTIALLY_UNUSED (st);

      callback (db, obj, callback_event::pre_load);
      init (obj, sts.image (), &db);
      load_ (sts, obj, false);
      sts.load_delayed (0);
      l.unlock ();
      callback (db, obj, callback_event::post_load);
      pointer_cache_traits::load (ig.position ());
    }
    else
      sts.delay_load (id, obj, ig.position ());

    ig.release ();
    pg.release ();
    return p;
  }

  bool access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  find (database& db, const id_type& id, object_type& obj)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    reference_cache_traits::position_type pos (
      reference_cache_traits::insert (db, id, obj));
    reference_cache_traits::insert_guard ig (pos);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, false);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    reference_cache_traits::load (pos);
    ig.release ();
    return true;
  }

  bool access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  reload (database& db, object_type& obj)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());
    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    statements_type::auto_lock l (sts);

    const id_type& id  (
      obj.m_id);

    if (!find_ (sts, &id))
      return false;

    select_statement& st (sts.find_statement ());
    ODB_POTENTIALLY_UNUSED (st);

    callback (db, obj, callback_event::pre_load);
    init (obj, sts.image (), &db);
    load_ (sts, obj, true);
    sts.load_delayed (0);
    l.unlock ();
    callback (db, obj, callback_event::post_load);
    return true;
  }

  bool access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  find_ (statements_type& sts,
         const id_type* id)
  {
    using namespace pgsql;

    id_image_type& i (sts.id_image ());
    init (i, *id);

    binding& idb (sts.id_image_binding ());
    if (i.version != sts.id_image_version () || idb.version == 0)
    {
      bind (idb.bind, i);
      sts.id_image_version (i.version);
      idb.version++;
    }

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    select_statement& st (sts.find_statement ());

    st.execute ();
    auto_result ar (st);
    select_statement::result r (st.fetch ());

    if (r == select_statement::truncated)
    {
      if (grow (im, sts.select_image_truncated ()))
        im.version++;

      if (im.version != sts.select_image_version ())
      {
        bind (imb.bind, im, statement_select);
        sts.select_image_version (im.version);
        imb.version++;
        st.refetch ();
      }
    }

    return r != select_statement::no_data;
  }

  result< access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::object_type >
  access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  query (database&, const query_base_type& q)
  {
    using namespace pgsql;
    using odb::details::shared;
    using odb::details::shared_ptr;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    statements_type& sts (
      conn.statement_cache ().find_object<object_type> ());

    image_type& im (sts.image ());
    binding& imb (sts.select_image_binding ());

    if (im.version != sts.select_image_version () ||
        imb.version == 0)
    {
      bind (imb.bind, im, statement_select);
      sts.select_image_version (im.version);
      imb.version++;
    }

    std::string text (query_statement);
    if (!q.empty ())
    {
      text += "\n";
      text += q.clause ();
    }

    q.init_parameters ();
    shared_ptr<select_statement> st (
      new (shared) select_statement (
        sts.connection (),
        query_statement_name,
        text,
        true,
        true,
        q.parameter_types (),
        q.parameter_count (),
        q.parameters_binding (),
        imb));

    st->execute ();
    st->deallocate ();

    shared_ptr< odb::object_result_impl<object_type> > r (
      new (shared) pgsql::object_result_impl<object_type> (
        q, st, sts, 0));

    return result<object_type> (r);
  }

  unsigned long long access::object_traits_impl< ::imgr::model::Photo, id_pgsql >::
  erase_query (database&, const query_base_type& q)
  {
    using namespace pgsql;

    pgsql::connection& conn (
      pgsql::transaction::current ().connection ());

    std::string text (erase_query_statement);
    if (!q.empty ())
    {
      text += ' ';
      text += q.clause ();
    }

    q.init_parameters ();
    delete_statement st (
      conn,
      erase_query_statement_name,
      text,
      q.parameter_types (),
      q.parameter_count (),
      q.parameters_binding ());

    return st.execute ();
  }
}

#include <odb/post.hxx>