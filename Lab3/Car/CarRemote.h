#pragma once
#include <boost/noncopyable.hpp>

class CCar;
enum struct MovementDirection;

class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	void Info(std::istream & args);
	void EngineOn(std::istream & args);
	void EngineOff(std::istream & args);
	void SetGear(std::istream & args);
	void SetSpeed(std::istream & args);
	std::string GetStrDirection(MovementDirection direction);
private:
	typedef std::map<std::string, std::function<void(std::istream& args)>> ActionMap;
	typedef std::map<MovementDirection, std::string> DirectionMap;

	static const DirectionMap m_directionMap;
	const ActionMap m_actionMap;
	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
};