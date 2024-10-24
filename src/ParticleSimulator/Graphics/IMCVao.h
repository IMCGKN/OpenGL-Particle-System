#pragma once

#include <glad/glad.h>

#include <string>

class IMCVao
{
public:
	IMCVao();
	~IMCVao();

	void Use();
	void Unuse();
private:
	unsigned int ID = 0;
	unsigned int vboID = 0;
	unsigned int eboID = 0;
	bool isUsed = false;
};
