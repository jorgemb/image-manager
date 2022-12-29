// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef MANAGER_ODB_HXX
#define MANAGER_ODB_HXX

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "manager.h"

#include <memory>
#include <cstddef>
#include <utility>

#include <odb/core.hxx>
#include <odb/traits.hxx>
#include <odb/callback.hxx>
#include <odb/wrapper-traits.hxx>
#include <odb/pointer-traits.hxx>
#include <odb/container-traits.hxx>
#include <odb/no-op-cache-traits.hxx>
#include <odb/result.hxx>
#include <odb/simple-object-result.hxx>

#include <odb/details/unused.hxx>
#include <odb/details/shared-ptr.hxx>

namespace odb {
// Album
//
template<>
struct class_traits<::imgr::model::Album> {
    static const class_kind kind = class_object;
};

template<>
class access::object_traits<::imgr::model::Album> {
public:
    typedef ::imgr::model::Album object_type;
    typedef ::imgr::model::Album *pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef long unsigned int id_type;

    static const bool auto_id = true;

    static const bool abstract = false;

    static id_type
    id(const object_type &);

    typedef
    no_op_pointer_cache_traits<pointer_type>
            pointer_cache_traits;

    typedef
    no_op_reference_cache_traits<object_type>
            reference_cache_traits;

    static void
    callback(database &, object_type &, callback_event);

    static void
    callback(database &, const object_type &, callback_event);
};

// Photo
//
template<>
struct class_traits<::imgr::model::Photo> {
    static const class_kind kind = class_object;
};

template<>
class access::object_traits<::imgr::model::Photo> {
public:
    typedef ::imgr::model::Photo object_type;
    typedef ::imgr::model::Photo *pointer_type;
    typedef odb::pointer_traits<pointer_type> pointer_traits;

    static const bool polymorphic = false;

    typedef long unsigned int id_type;

    static const bool auto_id = true;

    static const bool abstract = false;

    static id_type
    id(const object_type &);

    typedef
    no_op_pointer_cache_traits<pointer_type>
            pointer_cache_traits;

    typedef
    no_op_reference_cache_traits<object_type>
            reference_cache_traits;

    static void
    callback(database &, object_type &, callback_event);

    static void
    callback(database &, const object_type &, callback_event);
};
}

#include <odb/details/buffer.hxx>

#include <odb/pgsql/version.hxx>
#include <odb/pgsql/forward.hxx>
#include <odb/pgsql/binding.hxx>
#include <odb/pgsql/pgsql-types.hxx>
#include <odb/pgsql/query.hxx>

namespace odb {
// Album
//
template<typename A>
struct query_columns<::imgr::model::Album, id_pgsql, A> {
    // id
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    long unsigned int,
                    pgsql::id_bigint>::query_type,
            pgsql::id_bigint>
            id_type_;

    static const id_type_ id;

    // absolute_path
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    ::std::string,
                    pgsql::id_string>::query_type,
            pgsql::id_string>
            absolute_path_type_;

    static const absolute_path_type_ absolute_path;
};

template<typename A>
const typename query_columns<::imgr::model::Album, id_pgsql, A>::id_type_
        query_columns<::imgr::model::Album, id_pgsql, A>::
        id(A::table_name, "\"id\"", 0);

template<typename A>
const typename query_columns<::imgr::model::Album, id_pgsql, A>::absolute_path_type_
        query_columns<::imgr::model::Album, id_pgsql, A>::
        absolute_path(A::table_name, "\"absolute_path\"", 0);

template<typename A>
struct pointer_query_columns<::imgr::model::Album, id_pgsql, A> :
        query_columns<::imgr::model::Album, id_pgsql, A> {
};

template<>
class access::object_traits_impl<::imgr::model::Album, id_pgsql> :
        public access::object_traits<::imgr::model::Album> {
public:
    struct id_image_type {
        long long id_value;
        bool id_null;

        std::size_t version;
    };

    struct image_type {
        // m_id
        //
        long long m_id_value;
        bool m_id_null;

        // m_absolute_path
        //
        details::buffer m_absolute_path_value;
        std::size_t m_absolute_path_size;
        bool m_absolute_path_null;

        std::size_t version;
    };

    struct extra_statement_cache_type;

    using object_traits<object_type>::id;

    static id_type
    id(const id_image_type &);

    static id_type
    id(const image_type &);

    static bool
    grow(image_type &,
         bool *);

    static void
    bind(pgsql::bind *,
         image_type &,
         pgsql::statement_kind);

    static void
    bind(pgsql::bind *, id_image_type &);

    static bool
    init(image_type &,
         const object_type &,
         pgsql::statement_kind);

    static void
    init(object_type &,
         const image_type &,
         database *);

    static void
    init(id_image_type &, const id_type &);

    typedef pgsql::object_statements<object_type> statements_type;

    typedef pgsql::query_base query_base_type;

    static const std::size_t column_count = 2UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist(database &, object_type &);

    static pointer_type
    find(database &, const id_type &);

    static bool
    find(database &, const id_type &, object_type &);

    static bool
    reload(database &, object_type &);

    static void
    update(database &, const object_type &);

    static void
    erase(database &, const id_type &);

    static void
    erase(database &, const object_type &);

    static result<object_type>
    query(database &, const query_base_type &);

    static unsigned long long
    erase_query(database &, const query_base_type &);

    static const char persist_statement_name[];
    static const char find_statement_name[];
    static const char update_statement_name[];
    static const char erase_statement_name[];
    static const char query_statement_name[];
    static const char erase_query_statement_name[];

    static const unsigned int persist_statement_types[];
    static const unsigned int find_statement_types[];
    static const unsigned int update_statement_types[];

public:
    static bool
    find_(statements_type &,
          const id_type *);

    static void
    load_(statements_type &,
          object_type &,
          bool reload);
};

template<>
class access::object_traits_impl<::imgr::model::Album, id_common> :
        public access::object_traits_impl<::imgr::model::Album, id_pgsql> {
};

// Photo
//
template<typename A>
struct pointer_query_columns<::imgr::model::Photo, id_pgsql, A> {
    // id
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    long unsigned int,
                    pgsql::id_bigint>::query_type,
            pgsql::id_bigint>
            id_type_;

    static const id_type_ id;

    // filename
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    ::std::string,
                    pgsql::id_string>::query_type,
            pgsql::id_string>
            filename_type_;

    static const filename_type_ filename;

    // width
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    unsigned int,
                    pgsql::id_integer>::query_type,
            pgsql::id_integer>
            width_type_;

    static const width_type_ width;

    // height
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    unsigned int,
                    pgsql::id_integer>::query_type,
            pgsql::id_integer>
            height_type_;

    static const height_type_ height;

    // thumbnail
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    ::std::vector<unsigned char>,
                    pgsql::id_bytea>::query_type,
            pgsql::id_bytea>
            thumbnail_type_;

    static const thumbnail_type_ thumbnail;

    // album
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    long unsigned int,
                    pgsql::id_bigint>::query_type,
            pgsql::id_bigint>
            album_type_;

    static const album_type_ album;
};

template<typename A>
const typename pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::id_type_
        pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::
        id(A::table_name, "\"id\"", 0);

template<typename A>
const typename pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::filename_type_
        pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::
        filename(A::table_name, "\"filename\"", 0);

template<typename A>
const typename pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::width_type_
        pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::
        width(A::table_name, "\"width\"", 0);

template<typename A>
const typename pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::height_type_
        pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::
        height(A::table_name, "\"height\"", 0);

template<typename A>
const typename pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::thumbnail_type_
        pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::
        thumbnail(A::table_name, "\"thumbnail\"", 0);

template<typename A>
const typename pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::album_type_
        pointer_query_columns<::imgr::model::Photo, id_pgsql, A>::
        album(A::table_name, "\"album\"", 0);

template<>
class access::object_traits_impl<::imgr::model::Photo, id_pgsql> :
        public access::object_traits<::imgr::model::Photo> {
public:
    struct id_image_type {
        long long id_value;
        bool id_null;

        std::size_t version;
    };

    struct image_type {
        // m_id
        //
        long long m_id_value;
        bool m_id_null;

        // m_filename
        //
        details::buffer m_filename_value;
        std::size_t m_filename_size;
        bool m_filename_null;

        // m_width
        //
        int m_width_value;
        bool m_width_null;

        // m_height
        //
        int m_height_value;
        bool m_height_null;

        // m_thumbnail
        //
        details::buffer m_thumbnail_value;
        std::size_t m_thumbnail_size;
        bool m_thumbnail_null;

        // m_album
        //
        long long m_album_value;
        bool m_album_null;

        std::size_t version;
    };

    struct extra_statement_cache_type;

    struct album_tag;

    using object_traits<object_type>::id;

    static id_type
    id(const id_image_type &);

    static id_type
    id(const image_type &);

    static bool
    grow(image_type &,
         bool *);

    static void
    bind(pgsql::bind *,
         image_type &,
         pgsql::statement_kind);

    static void
    bind(pgsql::bind *, id_image_type &);

    static bool
    init(image_type &,
         const object_type &,
         pgsql::statement_kind);

    static void
    init(object_type &,
         const image_type &,
         database *);

    static void
    init(id_image_type &, const id_type &);

    typedef pgsql::object_statements<object_type> statements_type;

    typedef pgsql::query_base query_base_type;

    static const std::size_t column_count = 6UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist(database &, object_type &);

    static pointer_type
    find(database &, const id_type &);

    static bool
    find(database &, const id_type &, object_type &);

    static bool
    reload(database &, object_type &);

    static void
    update(database &, const object_type &);

    static void
    erase(database &, const id_type &);

    static void
    erase(database &, const object_type &);

    static result<object_type>
    query(database &, const query_base_type &);

    static unsigned long long
    erase_query(database &, const query_base_type &);

    static const char persist_statement_name[];
    static const char find_statement_name[];
    static const char update_statement_name[];
    static const char erase_statement_name[];
    static const char query_statement_name[];
    static const char erase_query_statement_name[];

    static const unsigned int persist_statement_types[];
    static const unsigned int find_statement_types[];
    static const unsigned int update_statement_types[];

public:
    static bool
    find_(statements_type &,
          const id_type *);

    static void
    load_(statements_type &,
          object_type &,
          bool reload);
};

template<>
class access::object_traits_impl<::imgr::model::Photo, id_common> :
        public access::object_traits_impl<::imgr::model::Photo, id_pgsql> {
};

// Album
//
// Photo
//
template<>
struct alias_traits<
        ::imgr::model::Album,
        id_pgsql,
        access::object_traits_impl<::imgr::model::Photo, id_pgsql>::album_tag> {
    static const char table_name[];
};

template<>
struct query_columns_base<::imgr::model::Photo, id_pgsql> {
    // album
    //
    typedef
    odb::alias_traits<
            ::imgr::model::Album,
            id_pgsql,
            access::object_traits_impl<::imgr::model::Photo, id_pgsql>::album_tag>
            album_alias_;
};

template<typename A>
struct query_columns<::imgr::model::Photo, id_pgsql, A> :
        query_columns_base<::imgr::model::Photo, id_pgsql> {
    // id
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    long unsigned int,
                    pgsql::id_bigint>::query_type,
            pgsql::id_bigint>
            id_type_;

    static const id_type_ id;

    // filename
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    ::std::string,
                    pgsql::id_string>::query_type,
            pgsql::id_string>
            filename_type_;

    static const filename_type_ filename;

    // width
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    unsigned int,
                    pgsql::id_integer>::query_type,
            pgsql::id_integer>
            width_type_;

    static const width_type_ width;

    // height
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    unsigned int,
                    pgsql::id_integer>::query_type,
            pgsql::id_integer>
            height_type_;

    static const height_type_ height;

    // thumbnail
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    ::std::vector<unsigned char>,
                    pgsql::id_bytea>::query_type,
            pgsql::id_bytea>
            thumbnail_type_;

    static const thumbnail_type_ thumbnail;

    // album
    //
    typedef
    pgsql::query_column<
            pgsql::value_traits<
                    long unsigned int,
                    pgsql::id_bigint>::query_type,
            pgsql::id_bigint>
            album_column_type_;

    typedef
    odb::query_pointer<
            odb::pointer_query_columns<
                    ::imgr::model::Album,
                    id_pgsql,
                    album_alias_> >
            album_pointer_type_;

    struct album_type_ : album_pointer_type_, album_column_type_ {
        album_type_(const char *t, const char *c, const char *conv)
                : album_column_type_(t, c, conv) {
        }
    };

    static const album_type_ album;
};

template<typename A>
const typename query_columns<::imgr::model::Photo, id_pgsql, A>::id_type_
        query_columns<::imgr::model::Photo, id_pgsql, A>::
        id(A::table_name, "\"id\"", 0);

template<typename A>
const typename query_columns<::imgr::model::Photo, id_pgsql, A>::filename_type_
        query_columns<::imgr::model::Photo, id_pgsql, A>::
        filename(A::table_name, "\"filename\"", 0);

template<typename A>
const typename query_columns<::imgr::model::Photo, id_pgsql, A>::width_type_
        query_columns<::imgr::model::Photo, id_pgsql, A>::
        width(A::table_name, "\"width\"", 0);

template<typename A>
const typename query_columns<::imgr::model::Photo, id_pgsql, A>::height_type_
        query_columns<::imgr::model::Photo, id_pgsql, A>::
        height(A::table_name, "\"height\"", 0);

template<typename A>
const typename query_columns<::imgr::model::Photo, id_pgsql, A>::thumbnail_type_
        query_columns<::imgr::model::Photo, id_pgsql, A>::
        thumbnail(A::table_name, "\"thumbnail\"", 0);

template<typename A>
const typename query_columns<::imgr::model::Photo, id_pgsql, A>::album_type_
        query_columns<::imgr::model::Photo, id_pgsql, A>::
        album(A::table_name, "\"album\"", 0);
}

#include "manager-odb.ixx"

#include <odb/post.hxx>

#endif // MANAGER_ODB_HXX
