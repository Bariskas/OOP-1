#include "stdafx.h"
#include "CarRemote.h"
#include "Car.h"

using namespace std;
using namespace std::placeholders;

const CRemoteControl::DirectionMap CRemoteControl::m_directionMap({
	{ MovementDirection::BACKWARD, "Backward" },
	{ MovementDirection::HOLDING, "Holding" },
	{ MovementDirection::FORWARD, "Forward" }
});

CRemoteControl::CRemoteControl(CCar& car, istream& input, ostream& output)
	: m_car(car), m_input(input), m_output(output)
	, m_actionMap({
		{ "Info", bind(&CRemoteControl::Info, this, _1) },
		{ "EngineOn", bind(&CRemoteControl::EngineOn, this, _1) },
		{ "EngineOff", bind(&CRemoteControl::EngineOff, this, _1) },
		{ "SetGear", bind(&CRemoteControl::SetGear, this, _1) },
		{ "SetSpeed", bind(&CRemoteControl::SetSpeed, this, _1) }
})
{
	
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		try
		{
			it->second(strm);
		}
		catch (const exception& e)
		{
			m_output << e.what() << endl;
		}
		return true;
	}
	return false;
}

void CRemoteControl::Info(std::istream & /*args*/)
{
	string info;

	if (m_car.IsTurnedOn())
	{
		info.append("Car engine is ON. Direction is ");
		info.append(GetStrDirection(m_car.GetDirection()));
		info.append(". Gear: ");
		info.append(to_string(m_car.GetGear()));
		info.append(", Speed: ");
		info.append(to_string(m_car.GetSpeed()));
	}
	else
	{
		info.append("Car engine is OFF");
	}

	m_output << info << endl;
}

void CRemoteControl::EngineOn(istream& /*args*/)
{
	m_car.TurnOnEngine();
	m_output << "Car engine is turned ON" << endl;
}

void CRemoteControl::EngineOff(istream& /*args*/)
{
	m_car.TurnOffEngine();
	m_output << "Car engine is turned OFF" << endl;
}

void CRemoteControl::SetGear(istream& args)
{
	int gear;
	args >> gear;
	m_car.SetGear(gear);
	m_output << "Car have gear: " + to_string(m_car.GetGear()) << endl;
}

void CRemoteControl::SetSpeed(istream& args)
{
	int speed;
	args >> speed;
	m_car.SetSpeed(speed);
	m_output << "Car have speed: " + to_string(m_car.GetSpeed()) << endl;
}

std::string CRemoteControl::GetStrDirection(MovementDirection direction)
{
	auto it = m_directionMap.find(direction);
	return it->second;
}
