#include "stdafx.h"
#include "Car.h"

CCar::CCar()
	: m_gear(0), m_speed(0), m_isTurnedOn(false)
	, m_speedRangesMap({
		{-1, {0, 20}},
		{0, {0, 150}},
		{1, {0, 30}},
		{2, {20, 50}},
		{3, {30, 60}},
		{4, {40, 90}},
		{5, {50, 150}}
	})
{

}

bool CCar::TurnOnEngine()
{
	m_isTurnedOn = true;
	return m_isTurnedOn;
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
	return m_speed;
}