#pragma once
#include <vector>
class GAME_BASE
{
public:
	GAME_BASE(class MAIN* main);
	virtual ~GAME_BASE();
	virtual int create() = 0;
	virtual void proc() = 0;
	virtual void destroy() = 0;
	class MAIN* main() { return Main; }
private:
	class MAIN* Main = nullptr;
};

