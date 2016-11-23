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
		// ѕредварительно очищаем содержимое выходного потока
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
ƒанный класс управл€ет форматированием журнала запуска тестов
ƒл€ того, чтобы увидеть результат, приложение должно быть запущено с ключЄм --log_level=test_suite (см. Post-build event в настройках проекта)
*/
class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream &os, boost::unit_test::test_unit const& tu) override
	{
		// перед запуском test unit-а выводим им€ test unit-а, замен€€ символ подчеркивани€ на пробел
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		// увеличиваем отступ дл€ вывода имен последующих test unit-ов в виде дерева
		m_indent += 2;
	}

	virtual void test_unit_finish(std::ostream &/*os*/, boost::unit_test::test_unit const& /*tu*/, unsigned long /*elapsed*/) override
	{
		// по окончании test unit-а уменьшаем отступ
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/[])
{
	// «аменили им€ log formatter на пользовательский
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	// »м€ корневого набора тестов - All tests
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	// «апускаем тесты, передава€ параметры командной строки и кастомную функцию инициализации тестов
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
