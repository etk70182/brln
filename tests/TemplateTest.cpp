/*
 * TemplateTest.cpp
 *
 *  Created on: Sep 13, 2019
 *      Author: André Schlinke
 */

#include "Template/Template.h"
#include "CppUTest/TestHarness.h"

TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
   LONGS_EQUAL(1, Mytemplate());
   //CHECK(false);
}


