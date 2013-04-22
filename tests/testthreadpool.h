#ifndef TESTTHREADPOOL_H
#define TESTTHREADPOOL_H

#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

class TestThreadPool : public CppUnit::TestFixture
{
CPPUNIT_TEST_SUITE(TestThreadPool);
//CPPUNIT_TEST(testAddition);
//CPPUNIT_TEST(testMultiply);
CPPUNIT_TEST_SUITE_END();


public:
    TestThreadPool();

    void setUp(void);

    void tearDown(void);

};

#endif // TESTTHREADPOOL_H
