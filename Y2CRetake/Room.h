#pragma once
struct Room
{
	Room()
	{
		m_Start[0] = 0;
		m_Start[1] = 0;
		m_End[0] = 0;
		m_End[1] = 0;
	}
	Room(int a_StartX, int a_StartY, int a_EndX, int a_EndY)
	{
		m_Start[0] = a_StartX;
		m_Start[1] = a_StartY;
		m_End[0] = a_EndX;
		m_End[1] = a_EndY;
	}
	~Room() = default;
	Room(Room&& a_Rhs) noexcept
	{
		m_Start[0] = a_Rhs.m_Start[0];
		m_Start[1] = a_Rhs.m_Start[1];

		m_End[0] = a_Rhs.m_End[0];
		m_End[1] = a_Rhs.m_End[1];
	}

	Room(const Room& a_Rhs)
	{
		m_Start[0] = a_Rhs.m_Start[0];
		m_Start[1] = a_Rhs.m_Start[1];

		m_End[0] = a_Rhs.m_End[0];
		m_End[1] = a_Rhs.m_End[1];
	}

	Room& operator=(const Room& a_Rhs)
	{
		m_Start[0] = a_Rhs.m_Start[0];
		m_Start[1] = a_Rhs.m_Start[1];

		m_End[0] = a_Rhs.m_End[0];
		m_End[1] = a_Rhs.m_End[1];
		return *this;
	}

	Room& operator=(Room&& a_Rhs) noexcept
	{
		m_Start[0] = a_Rhs.m_Start[0];
		m_Start[1] = a_Rhs.m_Start[1];

		m_End[0] = a_Rhs.m_End[0];
		m_End[1] = a_Rhs.m_End[1];
		return *this;
	}

	int m_Start[2]{};
	int m_End[2]{};
};