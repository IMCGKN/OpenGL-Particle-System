#include "IMCVao.h"

IMCVao::IMCVao()
{
	float vertices[] = {
		-0.5f,-0.5f,
		 0.5f,-0.5f,
		 0.5f, 0.5f,
		-0.5f, 0.5f,
	};

	glGenVertexArrays(1, &ID);

	glBindVertexArray(ID);

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * sizeof(float), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, (2 * sizeof(float)), (const void*)0);
	glEnableVertexAttribArray(0);

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

IMCVao::~IMCVao()
{
	glDeleteBuffers(1, &vboID);
	glDeleteBuffers(1, &eboID);
	glDeleteVertexArrays(1, &ID);
}

void IMCVao::Use()
{
	if (!isUsed)
	{
		glBindVertexArray(ID);
		isUsed = true;
	}
}

void IMCVao::Unuse()
{
	if (isUsed)
	{
		glBindVertexArray(0);
		isUsed = false;
	}
}
