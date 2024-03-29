#include "../Std/HashMap.h"
#include <string>
#include <iostream>
using namespace CustomStd;
using namespace std;

TEST_CASE("HashMap - Constructor", "[HashMap]")
{
	SECTION("Empty")
	{
		HashMap<string, double> map;
		REQUIRE(map.Size() == 0);
		REQUIRE(map.BucketCount() == HashMap<string, double>::START_BUCKETS);
		REQUIRE(map.Begin() == map.End());
		REQUIRE(map.begin() == map.Begin());
		REQUIRE(map.end() == map.End());
	}
	SECTION("Initializer list constructor - Empty")
	{
		HashMap<string, double> map = {};
		REQUIRE(map.Size() == 0);
		REQUIRE(map.BucketCount() == HashMap<string, double>::START_BUCKETS);
		REQUIRE(map.Begin() == map.End());
	}
	SECTION("Initializer list constructor - Non-empty")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = { P("Hello", 1.23), P("World", 2.46) };
		REQUIRE(map.BucketCount() == HashMap<string, double>::START_BUCKETS);
		REQUIRE(map.Size() == 2);
		REQUIRE(map.Begin() != map.End());
	}
	SECTION("Initializer list constructor - Non-Empty exceed load")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = {
			P("Hello", 1.23),
			P("World", 2.46),
			P("Lorem", 6.89),
			P("Ipsum", 4.87),
			P("Foo", 7.57),
			P("Bar", 8.41),
			P("C++", 1.35),
			P("C#", 2.85),
		};
		REQUIRE(map.BucketCount() > HashMap<string, double>::START_BUCKETS);
		REQUIRE(map.Size() == 8);
		REQUIRE(map.Begin() != map.End());
	}
}

TEST_CASE("HashMap - Copy constructor", "[HashMap]")
{
	SECTION("From empty")
	{
		HashMap<string, double> map;
		HashMap<string, double> map2(map);
		REQUIRE(map.Size() == 0);
		REQUIRE(map.Begin() == map.End());
		REQUIRE(map2.Size() == 0);
	}
	SECTION("From non-empty")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = { P("Hello", 1.23), P("World", 2.46) };
		HashMap<string, double> map2(map);
		REQUIRE(map.Size() == 2);
		REQUIRE(map.Begin() != map.End());
		REQUIRE(map2.Size() == 2);
	}
}

TEST_CASE("HashMap - Assignment", "[HashMap]")
{
	SECTION("From empty to empty")
	{
		HashMap<string, double> map;
		HashMap<string, double> map2;
		REQUIRE(map.Size() == 0);
		REQUIRE(map2.Size() == 0);
		map = map2;
		REQUIRE(map.Size() == 0);
		REQUIRE(map2.Size() == 0);
	}
	SECTION("From non-empty to empty")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = { P("Hello", 1.23), P("World", 2.46) };
		HashMap<string, double> map2;
		REQUIRE(map.Size() == 2);
		REQUIRE(map2.Size() == 0);
		map2 = map;
		REQUIRE(map.Size() == 2);
		REQUIRE(map2.Size() == 2);
	}
	SECTION("From non-empty to non-empty")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = { P("Hello", 1.23), P("World", 2.46) };
		HashMap<string, double> map2 = { P("CPP", 4.87), P("Foo", 1.23), P("Bar", 2.46) };
		REQUIRE(map2.Size() == 3);
		REQUIRE(map.Size() == 2);
		map2 = map;
		REQUIRE(map2.Size() == 2);
		REQUIRE(map2.Size() == 2);
		REQUIRE(map.Size() == 2);
	}
}

TEST_CASE("HashMap - Find", "[HashMap]")
{
	SECTION("Empty")
	{
		HashMap<string, double> map;
		REQUIRE(map.Size() == 0);

		REQUIRE(map.Find("Poo") == map.End());
		REQUIRE(map.Find("Hey") == map.End());
		REQUIRE(map.Find("Thing") == map.End());
		REQUIRE(map.Find("No") == map.End());
	}
	SECTION("Non-empty")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = {
			P("Hello", 1.23),
			P("World", 2.46),
			P("Lorem", 6.89),
			P("Ipsum", 4.87),
			P("Foo", 7.57),
			P("Bar", 8.41),
			P("C++", 1.35),
			P("C#", 2.85),
		};
		REQUIRE(map.Size() == 8);

		REQUIRE(map.Find("Hello") != map.End());
		REQUIRE(map.Find("World") != map.End());
		REQUIRE(map.Find("Lorem") != map.End());
		REQUIRE(map.Find("Ipsum") != map.End());
		REQUIRE(map.Find("Foo") != map.End());
		REQUIRE(map.Find("Bar") != map.End());
		REQUIRE(map.Find("C++") != map.End());
		REQUIRE(map.Find("C#") != map.End());

		REQUIRE(map.Find("Poo") == map.End());
		REQUIRE(map.Find("Hey") == map.End());
		REQUIRE(map.Find("Thing") == map.End());
		REQUIRE(map.Find("No") == map.End());
	}
}

TEST_CASE("HashMap - Insert", "[HashMap]")
{
	SECTION("Empty")
	{
		HashMap<string, double> map;
		REQUIRE(map.Size() == 0);
		map.Insert(KeyValuePair<string, double>("Hello", 1.0));
		REQUIRE(map.Size() == 1);
		REQUIRE(map.Find("Hello") != map.End());
		map.Insert("World", 5.0);
		REQUIRE(map.Size() == 2);
		REQUIRE(map.Find("World") != map.End());
		map.Insert("Hello", 5.0);
		REQUIRE(map.Find("Hello") != map.End());
		REQUIRE(map.Size() == 2);
	}
	SECTION("Non-empty")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = { P("Foo", 1.23), P("Bar", 2.46) };
		REQUIRE(map.Size() == 2);
		map.Insert(KeyValuePair<string, double>("Hello", 1.0));
		REQUIRE(map.Size() == 3);
		REQUIRE(map.Find("Hello") != map.End());
		map.Insert("World", 5.0);
		REQUIRE(map.Size() == 4);
		REQUIRE(map.Find("World") != map.End());
		map.Insert(KeyValuePair<string, double>("Hello", 5.0));
		REQUIRE(map.Size() == 4);
		REQUIRE(map.Find("Hello") != map.End());
	}
}

TEST_CASE("HashMap - Accessors", "[HashMap]")
{
	SECTION("Get")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = {
			P("Hello", 1.23),
			P("World", 2.46),
			P("Lorem", 6.89),
			P("Ipsum", 4.87),
			P("Foo", 7.57),
			P("Bar", 8.41),
			P("C++", 1.35),
			P("C#", 2.85),
		};
		REQUIRE(map.Size() == 8);

		REQUIRE(map["Hello"] == 1.23);
		REQUIRE(map["World"] == 2.46);
		REQUIRE(map["Lorem"] == 6.89);
		REQUIRE(map["Ipsum"] == 4.87);
		REQUIRE(map["Foo"] == 7.57);
		REQUIRE(map["Bar"] == 8.41);
		REQUIRE(map["C++"] == 1.35);
		REQUIRE(map["C#"] == 2.85);
	}
	SECTION("Modify & Insert")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = {
			P("Hello", 1.23),
			P("World", 2.46),
			P("Lorem", 6.89),
			P("Ipsum", 4.87),
		};
		REQUIRE(map.Size() == 4);

		REQUIRE(map.Contains("Hello"));
		REQUIRE(map["Hello"] == 1.23);
		map["Hello"] = 5.0;
		REQUIRE(map["Hello"] == 5.0);

		REQUIRE(!map.Contains("Foo"));
		REQUIRE(map.Find("Foo") == map.End());
		map["Foo"] = 1.0;
		REQUIRE(map.Contains("Foo"));
		REQUIRE(map.Size() == 5);
		REQUIRE(map.Find("Foo") != map.End());
		REQUIRE(map["Foo"] == 1.0);
	}
	SECTION("Erase")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = {
			P("Hello", 1.23),
			P("World", 2.46),
			P("Lorem", 6.89),
			P("Ipsum", 4.87),
		};
		REQUIRE(map.Size() == 4);

		REQUIRE(map.Contains("Hello"));
		HashMap<string, double>::Iterator it = map.Erase("Hello");
		REQUIRE(map.Size() == 3);
		REQUIRE(it != map.End());
		REQUIRE(map.Find("Hello") == map.End());
		REQUIRE(!map.Contains("Hello"));

		it = map.Erase("Foo");
		REQUIRE(map.Size() == 3);
		REQUIRE(it == map.End());
		REQUIRE(map.Find("Foo") == map.End());
		REQUIRE(!map.Contains("Foo"));

		map.Erase("World");
		map.Erase("Ipsum");
		map.Erase("Lorem");
		REQUIRE(map.Size() == 0);
		REQUIRE(map.Begin() == map.End());
	}
}

TEST_CASE("HashMap - Comparison", "[HashMap]")
{
	SECTION("Empty")
	{
		HashMap<string, double> map;
		HashMap<string, double> map2;
		REQUIRE(map == map2);
		REQUIRE(!(map != map2));
	}
	SECTION("One empty")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = {
			P("Hello", 1.23),
			P("World", 2.46),
			P("Lorem", 6.89),
			P("Ipsum", 4.87),
		};
		HashMap<string, double> map2;
		REQUIRE(map != map2);
		REQUIRE(!(map == map2));
	}
	SECTION("Non-empty - Equal")
	{
		using P = KeyValuePair<string, double>;
		HashMap<string, double> map = {
			P("Hello", 1.23),
			P("World", 2.46),
			P("Lorem", 6.89),
			P("Ipsum", 4.87),
		};
		HashMap<string, double> map2 = {
			P("Hello", 1.23),
			P("World", 2.46),
			P("Lorem", 6.89),
			P("Ipsum", 4.87),
		};
		REQUIRE(map == map2);
		REQUIRE(!(map != map2));
	}
}

TEST_CASE("HashMap - Clear", "[HashMap]")
{
	SECTION("Empty")
	{
		HashMap<string, double> map;
		REQUIRE(map.Size() == 0);
		map.Clear();
		REQUIRE(map.Size() == 0);
	}
	SECTION("Non-empty")
	{
		HashMap<string, double> map;
		REQUIRE(map.Size() == 0);
		map.Clear();
		REQUIRE(map.Size() == 0);
	}
}
