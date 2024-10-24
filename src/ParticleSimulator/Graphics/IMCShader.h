#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include <IMCPrerequisites.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <glad/glad.h>

class IMCShader
{
public:
	IMCShader(const char* vFileLoc, const char* fFileLoc);
	~IMCShader();

	void Use();
	void Unuse();

	void SetMat4(const std::string& name, const glm::mat4& v) const;
	void SetVec4(const std::string& name, const glm::vec4& v) const;
	void SetVec3(const std::string& name, const glm::vec3& v) const;
	void SetVec2(const std::string& name, const glm::vec2& v) const;
	void SetFloat(const std::string& name, float v) const;
	void SetInt(const std::string& name, int v) const;
private:
	unsigned int ID;
	bool isUsed = false;

	void CheckCompileError(unsigned int shaderId, const char* typeShader);
};
