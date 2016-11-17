#pragma once

enum struct MovementDirection{ STAYING, FORWARD, BACKWARD };

class CCar
{
public:
	CCar();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear();
	bool SetSpeed();
	bool GetIsTurnedOn();
	int GetGear();
	int GetSpeed();
	MovementDirection GetDirection();
private:
	bool IsSpeedCompatibleWithGear(int gearNumber);
	bool IsDirectionCompatibleWithGear(int gearNumber);
	bool IsGearSupported(int gearNumber);
	std::map<int, std::pair<int, int>> m_speedRangesMap;
	bool m_isTurnedOn;
	int m_gear;
	int m_speed;
};