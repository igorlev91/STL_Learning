#include "xrstl/string_view.h"
#include "xrstl/fixed_string.h"

#include <string>

#if xrstl_cppversion >= 201703L
#include <string_view>
#endif

void RunUnitTestsString()
{
	const char* MyCharString = u8"Hello String汉字";
	const wchar_t* MyWCharString = L"Hello String汉字";

	std::string mystds;
	xrstl::fixed_string32 myfs32;
	xrstl::fixed_string32 myfs32_2("String");
	xrstl::fixed_string32 myfs32_foo("foo");
	xrstl::fixed_string32 myfs32_bar("bar");

	xrstl::fixed_string8 myfs8_foo("foo");
	xrstl::fixed_string8 myfs8_bar("bar");

	xrstl::fixed_wstring32 mywfs32;

	mystds = "Hello String";
	myfs32 = "Hello String";

	const auto mystdsub = mystds.substr(3, 5);
	const auto myfssub = myfs32.substr(3, 5);

	const char* mystdc_str = mystds.c_str();
	const char* myfsc_str = myfs32.c_str();

	const size_t stdfindc = mystds.find('S', 0);
	const size_t fsfindc = myfs32.find('S', 0);

	const size_t stdfind = mystds.find("rin", 2);
	const size_t fsfind = myfs32.find("rin", 2);

	const size_t stdrfindc = mystds.rfind('S', 6);
	const size_t fsrfindc = myfs32.rfind('S', 6);

	const size_t stdfindr = mystds.rfind("ing");
	const size_t fsfindr = myfs32.rfind("ing");

	myfs32 = "Hello String";
	myfs32.replace(4, 3, "foo", 3);
	myfs32 = "Hello String";
	myfs32.replace(4, 6, "foo", 3);
	myfs32 = "Hello String";
	myfs32.replace(4, 1, "foo", 3);

	mywfs32 = L"Hello String";
	mywfs32.replace(4, 3, L"foo", 3);
	mywfs32 = L"Hello String";
	mywfs32.replace(4, 6, L"foo", 3);
	mywfs32 = L"Hello String";
	mywfs32.replace(4, 1, L"foo", 3);

	mystds.replace(0, 2, "Hello");

	const auto fsfindfs = myfs32.find(myfs32_2);

	mystds.push_back('a');
	mystds.pop_back();

	// Operator +
	myfs32 = myfs32_foo + myfs32_bar;
	myfs32 = myfs8_foo + myfs8_bar;
	myfs32 = myfs8_foo + myfs32_bar;

	const char* u1 = u8"a";
	const char* u2 = u8"\u03EA";
	const char* u3 = u8"\u27c1";
	const char* u4 = u8"\U00010CFF";
	
	size_t utf8Offset = 0;
	xrstl::codepoint_t cp = xrstl::decode_utf8((const uint8_t*)u4, strlen((const char*)u4), utf8Offset);
	
	myfs32.append_convert(MyWCharString, xrstl::string_length(MyWCharString));
	
	mywfs32.append_convert(MyCharString, xrstl::string_length(MyCharString));

	// string_view

	xrstl::string_view crStringViewEmpty;

	xrstl::string_view crStringViewConstChar("String View");

	for (char c : crStringViewConstChar)
	{
		printf("%c ", c);
	}

	printf("\n");

	if (crStringViewConstChar.substr(1, 5) == "tring")
	{
		printf("String was equal\n");
	}

	if (crStringViewConstChar.starts_with('S'))
	{
		printf("Starts with letter S\n");
	}

	if (crStringViewConstChar.ends_with('w'))
	{
		printf("Ends with letter w\n");
	}

	if (crStringViewConstChar.ends_with("View"))
	{
		printf("Ends with View\n");
	}

#if xrstl_cppversion >= 201703L
	std::basic_string_view<char> stdStringViewEmpty;

	std::basic_string_view<char> stdStringViewConstChar("String View");
#endif
}