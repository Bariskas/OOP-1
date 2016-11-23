#pragma once

enum struct MovementDirection{ HOLDING, FORWARD, BACKWARD };

class CCar
{
public:
	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gearNumber);
	void SetSpeed(int speed);
	bool IsTurnedOn()const;
	int GetGear()const;
	int GetSpeed()const;
	MovementDirection GetDirection()const;

private:
	bool IsSpeedCompatibleWithGear(int gearNumber, int speed)const;
	bool IsGearSupported(int gearNumber)const;
	static const std::map<int, std::pair<int, int>> m_speedRangesMap;
	bool m_isTurnedOn = false;
	int m_gear = 0;
	int m_speed = 0;
};