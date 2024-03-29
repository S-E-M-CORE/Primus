#ifndef STATICCONTROLLERTEST_HPP
#define STATICCONTROLLERTEST_HPP

#include "oatpp-test/UnitTest.hpp"

class StaticControllerTest : public oatpp::test::UnitTest
{
public:
	StaticControllerTest() : UnitTest("TEST[StaticControllerTest]"){}
	void onRun() override;
};

#endif // STATICCONTROLLERTEST_HPP
