
#include "../Std/Array.h"
using namespace CustomStd;

TEST_CASE("Array - Constructor - Empty", "[Array]")
{
	Array<int, 4> arr;
	REQUIRE(arr.Size() == 4);
}