#pragma once
#include "ofMain.h"

class DepthSquare
{

public:
	DepthSquare(const int& x, const int& y, const int& length);
	void draw();
	int getLength() const;
	int getX() const;
	int getY() const;
	void setDepth(const float& depth);

private:
	int m_color;
	float m_depth;
	int m_x; // Upper Left
	int m_y; // Upper Left
	int m_length;

	static const double m_minDist;
	static const double m_maxDist;
};
