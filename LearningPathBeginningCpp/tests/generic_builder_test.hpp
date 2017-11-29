/*
 * generic_builder_test.hpp
 *
 *  Created on: Jul 30, 2015
 *      Author: dubchak
 */

#ifndef GENERIC_BUILDER_TEST_HPP_
#define GENERIC_BUILDER_TEST_HPP_

#include "gtest/gtest.h"

#include "generic_builder.hpp"
#include "messaging.hpp"


TEST(BuilderTest, createBuilderDecoratorWithDefaultAdapter) {

	GenericBuilder<MessageBuilder> builder;
	Message m = builder.build();

	std::string actual = m.message();
	EXPECT_STREQ("", actual.c_str());
}

TEST(BuilderTest, createBuilderDecorator) {

	GenericBuilder<MessageBuilder, MessageBuilderAdapter> builder;
	Message m = builder.build();

	std::string actual = m.message();
	EXPECT_STREQ("A message adapter to customize the message body", actual.c_str());
}

TEST(BuilderTest, testSpecializedNullAdapter) {

	GenericBuilder<MessageBuilder, NullAdapter> builder;
	Message m = builder.build();

	std::string actual = m.message();
	EXPECT_STREQ("", actual.c_str());
}

TEST(BuilderTest, createBuilderDecoratorWithDefaultAdapterAndCustomMessage) {

	Message m = GenericBuilder<MessageBuilder>()
					.body("this is my custom message")
					.header("SECRET", "hello123")
					.header("TIME", "08:37:23 AM")
					.build();

	ASSERT_TRUE(m.contains_header("SECRET"));
	EXPECT_STREQ("hello123", m.get("SECRET").c_str());

	std::string actual = m.message();
	EXPECT_STREQ("this is my custom message", actual.c_str());
}

#endif /* GENERIC_BUILDER_TEST_HPP_ */
