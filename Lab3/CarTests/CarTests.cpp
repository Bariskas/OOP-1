#include "stdafx.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>
#include "../Car/Car.h"
#include "../Car/CarExceptions.h"

using namespace std;

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Car, CarFixture)

	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(has_zero_speed_and_gear_by_default)
	{
		BOOST_CHECK(car.GetSpeed() == 0);
		BOOST_CHECK(car.GetGear() == 0);
	}

	BOOST_AUTO_TEST_CASE(has_holding_direction_by_default)
	{
		BOOST_CHECK(car.GetDirection() == MovementDirection::HOLDING);
	}

	BOOST_AUTO_TEST_CASE(can_be_turned_on)
	{
		car.TurnOnEngine();
		BOOST_CHECK(car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(cant_turned_off)
	{
		BOOST_CHECK_THROW(car.TurnOffEngine(), AlreadyTurnedOff);
		BOOST_CHECK(!car.IsTurnedOn());
	}

	BOOST_AUTO_TEST_CASE(cant_change_speed_and_gear_when_turned_off)
	{
		BOOST_CHECK_THROW(car.SetGear(1), CantSetGearWhenTurnedOff);
		BOOST_CHECK(car.GetGear() == 0);
		BOOST_CHECK_THROW(car.SetSpeed(10), CantSetSpeedWhenTurnedOff);
		BOOST_CHECK(car.GetSpeed() == 0);
	}

	struct WhenTurnedOn : CarFixture
	{
		WhenTurnedOn()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_turned_on, WhenTurnedOn)
		
		BOOST_AUTO_TEST_CASE(cant_turned_on)
		{
			BOOST_CHECK_THROW(car.TurnOnEngine(), AlreadyTurnedOn);
			BOOST_CHECK(car.IsTurnedOn());
		}

		BOOST_AUTO_TEST_CASE(can_turned_off)
		{
			BOOST_CHECK_NO_THROW(car.TurnOffEngine());
			BOOST_CHECK(!car.IsTurnedOn());
		}

		BOOST_AUTO_TEST_CASE(has_zero_speed_and_gear_by_default)
		{
			BOOST_CHECK(car.GetSpeed() == 0);
			BOOST_CHECK(car.GetGear() == 0);
		}

		BOOST_AUTO_TEST_CASE(has_holding_direction_by_default)
		{
			BOOST_CHECK(car.GetDirection() == MovementDirection::HOLDING);
		}

		BOOST_AUTO_TEST_CASE(can_set_gear_from_neutral_to_rear_transmission)
		{
			BOOST_CHECK_NO_THROW(car.SetGear(-1));
			BOOST_CHECK(car.GetGear() == -1);
		}

		BOOST_AUTO_TEST_CASE(can_set_from_neutral_to_first_gear)
		{
			BOOST_CHECK_NO_THROW(car.SetGear(1));
			BOOST_CHECK(car.GetGear() == 1);
		}

		BOOST_AUTO_TEST_CASE(cant_set_from_neutral_to_more_than_first_gear)
		{
			BOOST_CHECK_THROW(car.SetGear(2), GearIsNotSupportCurrentSpeed);
			BOOST_CHECK(car.GetGear() == 0);

			BOOST_CHECK_THROW(car.SetGear(3), GearIsNotSupportCurrentSpeed);
			BOOST_CHECK(car.GetGear() == 0);

			BOOST_CHECK_THROW(car.SetGear(4), GearIsNotSupportCurrentSpeed);
			BOOST_CHECK(car.GetGear() == 0);

			BOOST_CHECK_THROW(car.SetGear(5), GearIsNotSupportCurrentSpeed);
			BOOST_CHECK(car.GetGear() == 0);
		}

		struct WhenMovingForward : WhenTurnedOn
		{
			WhenMovingForward()
			{
				car.SetGear(1);
				car.SetSpeed(10);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_moving_forward, WhenMovingForward)

			BOOST_AUTO_TEST_CASE(can_turned_off)
			{
				BOOST_CHECK_THROW(car.TurnOffEngine(), CanBeTurnedOffWhen);
				BOOST_CHECK(car.IsTurnedOn());
			}
			
			BOOST_AUTO_TEST_CASE(can_set_gear_to_neutral)
			{
				car.SetGear(0);
				BOOST_CHECK(car.GetGear() == 0);
				BOOST_CHECK(car.GetSpeed() == 10);
			}

			BOOST_AUTO_TEST_CASE(cant_set_to_rear_gear)
			{
				BOOST_CHECK_THROW(car.SetGear(-1), CantSetRearGearWhenSpeedNonZero);
			}

			BOOST_AUTO_TEST_CASE(gear_can_be_switched_at_appropriate_speed)
			{
				BOOST_CHECK_THROW(car.SetGear(2), GearIsNotSupportCurrentSpeed);
				car.SetSpeed(20);
				BOOST_CHECK_NO_THROW(car.SetGear(2));
				BOOST_CHECK(car.GetGear() == 2);

				BOOST_CHECK_THROW(car.SetGear(3 ), GearIsNotSupportCurrentSpeed);
				car.SetSpeed(50);
				BOOST_CHECK_NO_THROW(car.SetGear(3));
				BOOST_CHECK(car.GetGear() == 3);

				BOOST_CHECK_NO_THROW(car.SetGear(4));
				BOOST_CHECK(car.GetGear() == 4);

				BOOST_CHECK_NO_THROW(car.SetGear(5));
				BOOST_CHECK(car.GetGear() == 5);

				BOOST_CHECK_NO_THROW(car.SetGear(0));
				BOOST_CHECK(car.GetGear() == 0);
				BOOST_CHECK_NO_THROW(car.SetGear(4));
				BOOST_CHECK(car.GetGear() == 4);
				BOOST_CHECK_NO_THROW(car.SetGear(2));
				BOOST_CHECK(car.GetGear() == 2);
			}

			BOOST_AUTO_TEST_CASE(cant_set_to_unsupported_speed)
			{
				BOOST_CHECK_THROW(car.SetSpeed(50), CurrentGearIsNotSupportThisSpeed);
			}

			struct WhenMovingForwardAtNeutral : WhenMovingForward
			{
				WhenMovingForwardAtNeutral()
				{
					car.SetGear(0);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(at_neutral_gear, WhenMovingForwardAtNeutral)

				BOOST_AUTO_TEST_CASE(can_decrease_speed)
				{
					BOOST_CHECK_NO_THROW(car.SetSpeed(5));
					BOOST_CHECK(car.GetSpeed() == 5);
				}
				
				BOOST_AUTO_TEST_CASE(cant_increase_speed)
				{
					BOOST_CHECK_THROW(car.SetSpeed(20), CantIncreaseSpeedWhenNeutralGear);
					BOOST_CHECK(car.GetSpeed() == 10);
				}

				BOOST_AUTO_TEST_CASE(cant_set_to_rear_gear)
				{
					BOOST_CHECK_THROW(car.SetGear(-1), CantSetRearGearWhenSpeedNonZero);
				}

			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

		struct WhenMovingBackward : WhenTurnedOn
		{
			WhenMovingBackward()
			{
				car.SetGear(-1);
				car.SetSpeed(10);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_moving_backward, WhenMovingBackward)

			BOOST_AUTO_TEST_CASE(can_turned_off)
			{
				BOOST_CHECK_THROW(car.TurnOffEngine(), CanBeTurnedOffWhen);
				BOOST_CHECK(car.IsTurnedOn());
			}

			BOOST_AUTO_TEST_CASE(can_set_gear_to_neutral)
			{
				car.SetGear(0);
				BOOST_CHECK(car.GetGear() == 0);
				BOOST_CHECK(car.GetSpeed() == 10);
			}

			BOOST_AUTO_TEST_CASE(cant_set_gear_to_first_gear)
			{
				BOOST_CHECK_THROW(car.SetGear(1), GearIsNotSupportCurrentSpeed);
				BOOST_CHECK(car.GetGear() == -1);
			}

			BOOST_AUTO_TEST_CASE(can_set_speed)
			{
				BOOST_CHECK_NO_THROW(car.SetSpeed(20));
			}

			struct WhenMovingBackwardAtNeutral : WhenMovingBackward
			{
				WhenMovingBackwardAtNeutral()
				{
					car.SetGear(0);
				}
			};

			BOOST_FIXTURE_TEST_SUITE(at_neutral, WhenMovingBackwardAtNeutral)

				BOOST_AUTO_TEST_CASE(can_decrease_speed)
				{
					BOOST_CHECK_NO_THROW(car.SetSpeed(5));
					BOOST_CHECK(car.GetSpeed() == 5);
				}

				BOOST_AUTO_TEST_CASE(cant_increase_speed)
				{
					BOOST_CHECK_THROW(car.SetSpeed(20), CantIncreaseSpeedWhenNeutralGear);
					BOOST_CHECK(car.GetSpeed() == 10);
				}

				BOOST_AUTO_TEST_CASE(cant_set_to_rear_gear)
				{
					BOOST_CHECK_THROW(car.SetGear(-1), CantSetRearGearWhenSpeedNonZero);
				}

			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

/*
Данный класс управляет форматированием журнала запуска тестов
Для того, чтобы увидеть результат, приложение должно быть запущено с ключём --log_level=test_suite (см. Post-build event в настройках проекта)
*/
class SpecLogFormatter :
	public boost::unit_test::output::compiler_log_formatter
{
	virtual void test_unit_start(std::ostream &os, boost::unit_test::test_unit const& tu) override
	{
		// перед запуском test unit-а выводим имя test unit-а, заменяя символ подчеркивания на пробел
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		// увеличиваем отступ для вывода имен последующих test unit-ов в виде дерева
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
	// Заменили имя log formatter на пользовательский
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	// Имя корневого набора тестов - All tests
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}


int main(int argc, char* argv[])
{
	// Запускаем тесты, передавая параметры командной строки и кастомную функцию инициализации тестов
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}