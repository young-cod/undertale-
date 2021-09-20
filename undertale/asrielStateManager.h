#pragma once

class enemyManager;

class asrielStateManager
{
private:
public:
	virtual asrielStateManager*  inputHandle(enemyManager* asriel) = 0;
	virtual void update(enemyManager* asriel) = 0;
	virtual void enter(enemyManager* asriel) = 0;
	virtual void exit(enemyManager* asriel) = 0;
};

