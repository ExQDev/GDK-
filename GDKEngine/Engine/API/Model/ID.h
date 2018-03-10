#pragma once
#ifndef GDK_ID_H
#define GDK_ID_H

class ID {
public:
	UINT32 id;

	ID()
	{
		generate();
	}

	ID(UINT32 id) 
	{
		this->id = id;
	}

	void generate() 
	{
		id = reinterpret_cast<UINT32>(this);
	}
};
#endif // !GDK_ID_H
