/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <string>

#include <utils/stringUtils.h>
#include <gtest/gtest.h>




TEST(stringUtilsTest, split)
{

	Utils::StringUtils su;
	std::string none("");
	std::string string1("string");
	std::string two("two words");

	std::vector<std::string> elements = su.split(none, ' ');
	EXPECT_EQ(0u, elements.size());

	elements = su.split(string1, ' ');
	EXPECT_EQ(1u, elements.size());
	EXPECT_EQ(std::string("string"), elements[0]);
	
	elements = su.split(two, ' ');
	EXPECT_EQ(2u, elements.size());
	EXPECT_EQ(std::string("two"), elements[0]);
	EXPECT_EQ(std::string("words"), elements[1]);
}









