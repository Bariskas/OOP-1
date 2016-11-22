#include "stdafx.h"
#include "Car.h"
#include "CarExceptions.h"

using namespace std;

const map<int, pair<int, int>> CCar::m_speedRangesMap{
	{ -1, { -20, 0 } },
	{ 0, { -20, 150 } },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } }
};

void CCar::TurnOnEngine()
{
	if (m_isTurnedOn)
	{
		throw AlreadyTurnedOn();
	}
	else
	{
		m_isTurnedOn = true;
	}
}

void CCar::TurnOffEngine()
{
	if (!m_isTurnedOn)
	{
		throw AlreadyTurnedOff();
	}
	else if (m_speed == 0 && m_gear == 0)
	{
		m_isTurnedOn = false;
	}
	else
	{
		throw CanBeTurnedOffWhen();
	}
}

void CCar::SetGear(int gearNumber)
{
	if (m_gear == gearNumber)
	{
		throw AlreadyHaveThisGear();
	}
	else if (!m_isTurnedOn)
	{
		throw CantSetGearWhenTurnedOff();
	}
	else if (!IsGearSupported(gearNumber))
	{
		throw GearIsNotSupported();
	}
	else if (gearNumber == -1 && m_speed != 0)
	{
		throw CantSetRearGearWhenSpeedNonZero();
	}
	else if (!IsSpeedCompatibleWithGear(gearNumber, m_speed))
	{
		throw GearIsNotSupportCurrentSpeed();
	}
	else
	{
		m_gear = gearNumber;
	}
}

void CCar::SetSpeed(int speed)
{
	if (!m_isTurnedOn)
	{
		throw CantSetSpeedWhenTurnedOff();
	}
	else if (speed < 0)
	{
		throw NegativeValueEntered();
	}

	if (m_gear == -1 || GetDirection() == MovementDirection::BACKWARD)
	{
		speed = -speed;
	}

	if (m_speed == speed)
	{
		throw AlreadyHaveThisSpeed();
	}
	else if (m_gear == 0 && abs(m_speed) < abs(speed))
	{
		throw CantIncreaseSpeedWhenNeutralGear();
	}
	else if (!IsSpeedCompatibleWithGear(m_gear, speed))
	{
		throw CurrentGearIsNotSupportThisSpeed();
	}
	else
	{
		m_speed = speed;
	}
}

bool CCar::GetIsTurnedOn()const
{
	return m_isTurnedOn;
}

int CCar::GetGear()const
{
	return m_gear;
}

int CCar::GetSpeed()const
{
	return abs(m_speed);
}

MovementDirection CCar::GetDirection()const
{
	MovementDirection direction;
	if (m_speed > 0)
	{
		direction = MovementDirection::FORWARD;
	}
	else if (m_speed < 0)
	{
		direction = MovementDirection::BACKWARD;
	}
	else
	{
		direction = MovementDirection::HOLDING;
	}
	return direction;
}

bool CCar::IsSpeedCompatibleWithGear(int gearNumber, int speed)const
{
	auto gearSpeedRange = m_speedRangesMap.find(gearNumber);
	if (gearSpeedRange != m_speedRangesMap.end())
	{
		pair<int, int> speedRange = gearSpeedRange->second;
		return (speed >= speedRange.first && speed <= speedRange.second);
	}
	else
	{
		throw GearIsNotSupported();
	}
}

bool CCar::IsGearSupported(int gearNumber)const
{
	return m_speedRangesMap.find(gearNumber) != m_speedRangesMap.end();
}