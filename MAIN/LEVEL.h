#pragma once
#include <vector>
class LEVEL
{
public:
	LEVEL(class MAIN* main);
	virtual ~LEVEL();
	virtual int create() = 0;
	virtual void proc() = 0;
	virtual void destroy() = 0;
	class MAIN* main() { return Main; }
private:
	class MAIN* Main = nullptr;
};

