#include "stdafx.h"
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
		// Предварительно очищаем содержимое выходного потока
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