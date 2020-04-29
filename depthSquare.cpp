#include "depthSquare.h"

DepthSquare::DepthSquare(const int& x, const int& y, const int& length)
{
	m_x = x;
	m_y = y;
	m_length = length;
	m_depth = 0;
	m_color = 0;
}

const double DepthSquare::m_minDist = 0.1;
const double DepthSquare::m_maxDist = 1.5;

void DepthSquare::draw()
{
	auto mapped_distance = ofMap(m_depth, m_minDist, m_maxDist, 0, 255, true);
	ofSetColor(mapped_distance);
	ofDrawRectangle(m_x, m_y, m_length, m_length);
}

int DepthSquare::getLength() const
{
	return m_length;
}

int DepthSquare::getX() const
{
	return m_x;
}

int DepthSquare::getY() const
{
	return m_y;
}

void DepthSquare::setDepth(const float& depth)
{
	m_depth = depth;
}
