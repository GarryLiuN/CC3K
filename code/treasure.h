/**
 * Project CC3k - Fall 2015
 * @author Nian Liu and Jiancheng Chen
 */
 
#ifndef TREASURE_H
#define TREASURE_H

#include "item.h"

class Dragon;

class Treasure : public Item {
private:	
	const std::string size;
	const int value;
public:
	Treasure(char symbol, std::string type, int value, std::string size);
	virtual ~Treasure() = 0;

	int getValue();
	std::string getSize();
	virtual Dragon* getDragon();
	virtual void deleteDragon();
};

class NormalHoard : public Treasure {
public:
	NormalHoard();
	~NormalHoard();
};

class SmallHoard : public Treasure {
public:
	SmallHoard();
	~SmallHoard();
};

class MerchantHoard : public Treasure{
public:
	MerchantHoard();
	~MerchantHoard();
};

class DragonHoard : public Treasure{
private:
	Dragon* dragon;
public:
	DragonHoard();
	DragonHoard(Dragon* dragon);
	~DragonHoard();
	Dragon* getDragon();
	void deleteDragon();
	void setDragon(Dragon* drag);
};

#endif
