#pragma once
#include <exception>

class CarException : public std::exception
{
};

struct AlreadyTurnedOn : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Car engine already turned ON";
	}
};

struct AlreadyTurnedOff : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Car engine already turned OFF";
	}
};

struct CanBeTurnedOffWhen : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Car can be turned OFF when speed and gear equals zero";
	}
};

struct CantSetGearWhenTurnedOff : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Can't set gear when engine is turned OFF (except neutral gear)";
	}
};

struct GearIsNotSupported : public CarException
{
	virtual const char* what() const throw() override
	{
		return "This gear is not supported";
	}
};

struct CantSetRearGearWhenSpeedNonZero : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Can't set rear gear when speed is not zero";
	}
};

struct GearIsNotSupportCurrentSpeed : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Selected gear is not support current speed";
	}
};

struct CantSetSpeedWhenTurnedOff : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Can't set speed when engine is turned OFF";
	}
};

struct NegativeValueEntered : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Speed must be a positive number";
	}
};

struct CurrentGearIsNotSupportThisSpeed : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Current gear is not support this speed";
	}
};

struct CantIncreaseSpeedWhenNeutralGear : public CarException
{
	virtual const char* what() const throw() override
	{
		return "Can't increase speed when neutral gear";
	}
};