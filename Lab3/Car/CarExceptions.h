#pragma once
#include <exception>

struct AlreadyTurnedOn : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Car engine already turned ON";
	}
};

struct AlreadyTurnedOff : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Car engine already turned OFF";
	}
};

struct CanBeTurnedOffWhen : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Car can be turned OFF when speed and gear equals zero";
	}
};

struct AlreadyHaveThisGear : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Car already have this gear";
	}
};

struct CantSetGearWhenTurnedOff : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Can't set gear when engine is turned OFF (except neutral gear)";
	}
};

struct GearIsNotSupported : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "This gear is not supported";
	}
};

struct CantSetRearGearWhenSpeedNonZero : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Can't set rear gear when speed is not zero";
	}
};

struct GearIsNotSupportCurrentSpeed : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Selected gear is not support current speed";
	}
};

struct CantSetSpeedWhenTurnedOff : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Can't set speed when engine is turned OFF";
	}
};

struct NegativeValueEntered : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Speed must be a positive value";
	}
};

struct AlreadyHaveThisSpeed : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Car already have this speed";
	}
};

struct CurrentGearIsNotSupportThisSpeed : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Current gear is not support this speed";
	}
};

struct CantIncreaseSpeedWhenNeutralGear : public std::exception
{
	virtual const char* what() const throw() override
	{
		return "Can't increase speed when neutral gear";
	}
};