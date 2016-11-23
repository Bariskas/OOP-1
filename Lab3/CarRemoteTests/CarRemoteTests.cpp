#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "../Car/Car.h"
#include "../Car/CarRemote.h"

using boost::optional;
using boost::none;

struct RemoteFixture
{
	CCar car;

	std::stringstream input;
	std::stringstream output;

	CRemoteControl remoteControl;
	RemoteFixture()
		: remoteControl(car, input, output)
	{
		car.TurnOnEngine();
	}

	void VerifyCommandHandling(const std::string& command, const std::string& expectedOutput)
	{
		// �������������� ������� ���������� ��������� ������
		output = std::stringstream();
		input = std::stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(remoteControl.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_control, RemoteFixture)

	BOOST_AUTO_TEST_CASE(can_handle_EngineOn_command)
	{
		car.TurnOffEngine();
		VerifyCommandHandling("EngineOn", "Car engine is turned ON\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_EngineOff_command)
	{
		VerifyCommandHandling("EngineOff", "Car engine is turned OFF\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_SetGear_command)
	{
		VerifyCommandHandling("SetGear 1", "Car have gear: 1\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_SetSpeed_command)
	{
		car.SetGear(1);
		VerifyCommandHandling("SetSpeed 20", "Car have speed: 20\n");
	}

	BOOST_AUTO_TEST_CASE(can_handle_Info_command)
	{
		VerifyCommandHandling("Info", "Car engine is ON. Direction is Holding. Gear: 0, Speed: 0\n");
	}

BOOST_AUTO_TEST_SUITE_END()

/*
������ ����� ��������� ��������������� ������� ������� ������
��� ����, ����� ������� ���������, ���������� ������ ���� �������� � ������ --log_level=test_suite (��. Post-build event � ���������� �������)
*/
class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream &os, boost::unit_test::test_unit const& tu) override
	{
		// ����� �������� test unit-� ������� ��� test unit-�, ������� ������ ������������� �� ������
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		// ����������� ������ ��� ������ ���� ����������� test unit-�� � ���� ������
		m_indent += 2;
	}

	virtual void test_unit_finish(std::ostream &/*os*/, boost::unit_test::test_unit const& /*tu*/, unsigned long /*elapsed*/) override
	{
		// �� ��������� test unit-� ��������� ������
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	// �������� ��� log formatter �� ����������������
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	// ��� ��������� ������ ������ - All tests
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	// ��������� �����, ��������� ��������� ��������� ������ � ��������� ������� ������������� ������
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
