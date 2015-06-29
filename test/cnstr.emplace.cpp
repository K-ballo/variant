// Eggs.Variant
//
// Copyright Agustin K-ballo Berge, Fusion Fenix 2014-2015
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <eggs/variant.hpp>
#include <string>

#include <eggs/variant/detail/config/prefix.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "constexpr.hpp"

using eggs::variants::in_place;

struct Aggregate
{
    int x;
    float y;
};

TEST_CASE("variant<Ts...>::variant(in_place<I>, Args&&...)", "[variant.cnstr]")
{
    eggs::variant<int, std::string> v(in_place<0>, 42);

    CHECK(bool(v) == true);
    CHECK(v.which() == 0u);
    CHECK(v.target_type() == typeid(int));
    REQUIRE(v.target<int>() != nullptr);
    CHECK(*v.target<int>() == 42);

#if EGGS_CXX11_HAS_CONSTEXPR
    SECTION("constexpr")
    {
        constexpr eggs::variant<int, Constexpr> v(in_place<1>, 42);
        constexpr bool vb = bool(v);
        constexpr std::size_t vw = v.which();
        constexpr bool vttb = v.target<Constexpr>()->x == 42;
        constexpr std::type_info const& vtt = v.target_type();

#  if EGGS_CXX14_HAS_CONSTEXPR
        struct test { static constexpr int call()
        {
            eggs::variant<int, Constexpr> v(in_place<1>, 42);
            v.target<Constexpr>()->x = 43;
            return 0;
        }};
        constexpr int c = test::call();
#  endif
    }
#endif

    SECTION("list-initialization")
    {
        eggs::variant<Aggregate, std::string> v(in_place<0>, 42);

        CHECK(bool(v) == true);
        CHECK(v.which() == 0u);
        CHECK(v.target_type() == typeid(Aggregate));
        REQUIRE(v.target<Aggregate>() != nullptr);
        CHECK(v.target<Aggregate>()->x == 42);
        CHECK(v.target<Aggregate>()->y == 0.f);

#if EGGS_CXX11_HAS_CONSTEXPR
        SECTION("constexpr")
        {
            constexpr eggs::variant<int, Aggregate> v(in_place<1>, 42);
            constexpr bool vb = bool(v);
            constexpr std::size_t vw = v.which();
            constexpr bool vttb = v.target<Aggregate>()->x == 42;
            constexpr std::type_info const& vtt = v.target_type();

#  if EGGS_CXX14_HAS_CONSTEXPR
            struct test { static constexpr int call()
            {
                eggs::variant<int, Aggregate> v(in_place<1>, 42);
                v.target<Aggregate>()->x = 43;
                return 0;
            }};
            constexpr int c = test::call();
#  endif
        }
#endif
    }
}

TEST_CASE("variant<T, T>::variant(in_place<I>, Args&&...)", "[variant.cnstr]")
{
    eggs::variant<int, int> v(in_place<0>, 42);

    CHECK(bool(v) == true);
    CHECK(v.which() == 0u);
    CHECK(v.target_type() == typeid(int));
    REQUIRE(v.target() != nullptr);
}

#if EGGS_CXX11_HAS_INITIALIZER_LIST_OVERLOADING
TEST_CASE("variant<Ts...>::variant(in_place<I>, std::initializer_list<U>, Args&&...)", "[variant.cnstr]")
{
    eggs::variant<int, std::string> v(in_place<1>, {'4', '2'});

    CHECK(bool(v) == true);
    CHECK(v.which() == 1u);
    CHECK(v.target_type() == typeid(std::string));
    REQUIRE(v.target<std::string>() != nullptr);
    CHECK(*v.target<std::string>() == "42");

#if EGGS_CXX14_HAS_CONSTEXPR
    SECTION("constexpr")
    {
        constexpr eggs::variant<int, Constexpr> v(in_place<1>, {4, 2});
        constexpr bool vb = bool(v);
        constexpr std::size_t vw = v.which();
        constexpr bool vttb = v.target<Constexpr>()->x == 4;
        constexpr std::type_info const& vtt = v.target_type();

#  if EGGS_CXX14_HAS_CONSTEXPR
        struct test { static constexpr int call()
        {
            eggs::variant<int, Constexpr> v(in_place<1>, {4, 2});
            v.target<Constexpr>()->x = 5;
            return 0;
        }};
        constexpr int c = test::call();
#  endif
    }
#endif
}

TEST_CASE("variant<T, T>::variant(in_place<I>, std::initializer_list<U>, Args&&...)", "[variant.cnstr]")
{
    eggs::variant<std::string, std::string> v(in_place<1>, {'4', '2'});

    CHECK(bool(v) == true);
    CHECK(v.which() == 1u);
    CHECK(v.target_type() == typeid(std::string));
    REQUIRE(v.target() != nullptr);
}
#endif

TEST_CASE("variant<Ts...>::variant(in_place<T>, Args&&...)", "[variant.cnstr]")
{
    eggs::variant<int, std::string> v(in_place<int>, 42);

    CHECK(bool(v) == true);
    CHECK(v.which() == 0u);
    CHECK(v.target_type() == typeid(int));
    REQUIRE(v.target<int>() != nullptr);
    CHECK(*v.target<int>() == 42);

#if EGGS_CXX11_HAS_CONSTEXPR
    SECTION("constexpr")
    {
        constexpr eggs::variant<int, Constexpr> v(in_place<Constexpr>, 42);
        constexpr bool vb = bool(v);
        constexpr std::size_t vw = v.which();
        constexpr bool vttb = v.target<Constexpr>()->x == 42;
        constexpr std::type_info const& vtt = v.target_type();

#  if EGGS_CXX14_HAS_CONSTEXPR
        struct test { static constexpr int call()
        {
            eggs::variant<int, Constexpr> v(in_place<Constexpr>, 42);
            v.target<Constexpr>()->x = 43;
            return 0;
        }};
        constexpr int c = test::call();
#  endif
    }
#endif

    SECTION("list-initialization")
    {
        eggs::variant<Aggregate, std::string> v(in_place<Aggregate>, 42);

        CHECK(bool(v) == true);
        CHECK(v.which() == 0u);
        CHECK(v.target_type() == typeid(Aggregate));
        REQUIRE(v.target<Aggregate>() != nullptr);
        CHECK(v.target<Aggregate>()->x == 42);
        CHECK(v.target<Aggregate>()->y == 0.f);

#if EGGS_CXX11_HAS_CONSTEXPR
        SECTION("constexpr")
        {
            constexpr eggs::variant<int, Aggregate> v(in_place<Aggregate>, 42);
            constexpr bool vb = bool(v);
            constexpr std::size_t vw = v.which();
            constexpr bool vttb = v.target<Aggregate>()->x == 42;
            constexpr std::type_info const& vtt = v.target_type();

#  if EGGS_CXX14_HAS_CONSTEXPR
            struct test { static constexpr int call()
            {
                eggs::variant<int, Aggregate> v(in_place<Aggregate>, 42);
                v.target<Aggregate>()->x = 43;
                return 0;
            }};
            constexpr int c = test::call();
#  endif
        }
#endif
    }
}

#if EGGS_CXX11_HAS_INITIALIZER_LIST_OVERLOADING
TEST_CASE("variant<Ts...>::variant(in_place<T>, std::initializer_list<U>, Args&&...)", "[variant.cnstr]")
{
    eggs::variant<int, std::string> v(in_place<std::string>, {'4', '2'});

    CHECK(bool(v) == true);
    CHECK(v.which() == 1u);
    CHECK(v.target_type() == typeid(std::string));
    REQUIRE(v.target<std::string>() != nullptr);
    CHECK(*v.target<std::string>() == "42");

#if EGGS_CXX14_HAS_CONSTEXPR
    SECTION("constexpr")
    {
        constexpr eggs::variant<int, Constexpr> v(in_place<Constexpr>, {4, 2});
        constexpr bool vb = bool(v);
        constexpr std::size_t vw = v.which();
        constexpr bool vttb = v.target<Constexpr>()->x == 4;
        constexpr std::type_info const& vtt = v.target_type();

#  if EGGS_CXX14_HAS_CONSTEXPR
        struct test { static constexpr int call()
        {
            eggs::variant<int, Constexpr> v(in_place<Constexpr>, {4, 2});
            v.target<Constexpr>()->x = 5;
            return 0;
        }};
        constexpr int c = test::call();
#  endif
    }
#endif
}
#endif
