#include "stdafx.h"
#include "../Vector/VectorProcess.h"
#include <boost/test/output/compiler_log_formatter.hpp>
#include <boost/algorithm/string/replace.hpp>


using namespace std;

BOOST_AUTO_TEST_SUITE(An_apple)
	BOOST_AUTO_TEST_CASE(is_round)
	{
		// TODO: check that apple is round
		BOOST_CHECK(true);
	}
	BOOST_AUTO_TEST_SUITE(when_bitten)
		BOOST_AUTO_TEST_CASE(produces_its_juice)
		{
			BOOST_CHECK(true);

		}
		BOOST_AUTO_TEST_CASE(becomes_lighter)
		{
			BOOST_CHECK(true);

		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()


//BOOST_AUTO_TEST_SUITE(VectorTests34a)

// Пустой вектор остается пустым
BOOST_AUTO_TEST_CASE(makes_empty_vector_from_empty_vector)
{
	vector<double> emptyVector;
	ProcessVector(emptyVector);
	BOOST_CHECK(emptyVector.empty());
}

// Вектор с минимальным значением - 0.0
BOOST_AUTO_TEST_CASE(vector_with_min_value_equal_zero_does_not_change)
{
	vector<double> testVector = {3, 0, 1, 2};
	vector<double> vectorCopy(testVector);
	ProcessVector(testVector);
	BOOST_CHECK(testVector == vectorCopy);
}

// Вектор с одним значением

// Вектор с несколькими значениями

// Невалидные символы в начале строки

// Невалидные символы посреди строки

//BOOST_AUTO_TEST_SUITE_END()



/*
Данный класс управляет формаитрованием журнала запуска тестов
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
