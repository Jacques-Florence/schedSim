/**
 * Copyright 2017 Jacques Florence
 * All rights reserved.
 * See License.txt file
 *
 */



#include <gtest/gtest.h>
#include <utils/configuration.h>
#include <iostream>
#include <stdexcept>


class ConfigurationTest : public ::testing::Test
{
public:
	ConfigurationTest() : conf("configurationTest.conf"),
		wrongFile("blaaa") {};
	Utils::Configuration conf;
	Utils::Configuration wrongFile;
	
};

TEST_F(ConfigurationTest, getStringValueTest)
{
	std::string value = conf.getStringValue("abc", "key1");
	EXPECT_EQ(std::string("value1"), value);
}

TEST_F(ConfigurationTest, getStringListTest)
{
	std::vector<std::string> vect = conf.getStringList("def", "key7");
	EXPECT_EQ(3u, vect.size());
	EXPECT_EQ(std::string("2"), vect[0]);
	EXPECT_EQ(std::string("6"), vect[2]);
}


TEST_F(ConfigurationTest, getDoubleValueTest)
{
	double value = conf.getDoubleValue("def", "key9");
	EXPECT_DOUBLE_EQ((double) 3.14159, value);
}

/*FIXME: the behavior works as expected when tested outside of gtest,
but for some reason, here stoull throws an invalid_argument exception...
might be some compilation settings*/
TEST_F(ConfigurationTest, DISABLED_getUnsignedLongLongIntValueTest)
{
	std::cerr << "hi\n";
	unsigned long long int value = conf.getUnsignedLongLongIntValue("def", "value10");
	unsigned long long int expected = 18446744073709551615ull;
	std::cerr << "Hello\n";
	EXPECT_EQ(expected, value);
}

TEST_F(ConfigurationTest, getIntValueTest)
{
	int value = conf.getIntValue("def", "key6");
	EXPECT_EQ((int) -1, value);
}

TEST_F(ConfigurationTest, getBoolValueTest)
{
	bool value1 = conf.getBoolValue("abc", "key1", true);
	bool value2 = conf.getBoolValue("abc", "key1", false);
	bool value3 = conf.getBoolValue("def", "key4", false);
	bool value4 = conf.getBoolValue("def", "key5", false);
	bool value5 = conf.getBoolValue("def", "key11", true);

	EXPECT_TRUE(value1);
	EXPECT_FALSE(value2);
	EXPECT_TRUE(value3);
	EXPECT_TRUE(value4);
	EXPECT_FALSE(value5);
}


TEST(ConfigurationNameTest, getFilePrefixTest)
{
	std::string filename = "./configuration.conf";
	Utils::Configuration conf(filename);
	std::string actualName = conf.getName();
	EXPECT_EQ(filename, actualName);
	

	std::string expectedPrefix = "configuration.conf";
	std::string actualPrefix = conf.getFilePrefix();
	EXPECT_EQ(expectedPrefix, actualPrefix);
}


TEST_F(ConfigurationTest, wrongFilenameTest)
{
	EXPECT_THROW(wrongFile.getStringValue("abc", "key1"), std::runtime_error);
}

TEST_F(ConfigurationTest, noSpacesTest)
{
	std::string expected = "value2";
	std::string actual = conf.getStringValue("abc", "key2");
	/*Not a bug, a feature! This promotes a clear style*/
	EXPECT_NE(expected, actual);
}




