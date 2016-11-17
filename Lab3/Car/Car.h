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
	bool GetIsTurnedOn()const;
	int GetGear()const;
	int GetSpeed()const;
	MovementDirection GetDirection()const;
private:
	bool IsSpeedCompatibleWithGear(int gearNumber)const;
	bool IsDirectionCompatibleWithGear(int gearNumber)const;
	bool IsGearSupported(int gearNumber)const;
	std::map<int, std::pair<int, int>> m_speedRangesMap;
	bool m_isTurnedOn;
	int m_gear;
	int m_speed;
};