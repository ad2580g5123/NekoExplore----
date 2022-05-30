#pragma once

class Effect
{
public:
	Effect();

	virtual ~Effect();

	virtual void Draw();

	virtual void Update(const Math::Matrix& _posmat);

private:

protected:

};