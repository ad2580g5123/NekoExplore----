#include "Headers.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Draw()
{
}

void Object::Update()
{
}

const KdModel& Object::GetModel() const
{
	return m_Model;
}

const Math::Matrix& Object::GetMat() const
{
	return m_Mat;
}
