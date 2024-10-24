#include <Graphics/IMCShader.h>

IMCShader::IMCShader(const char* vFileLoc, const char* fFileLoc)
{
	std::string vShaderSourceStr;
	std::string fShaderSourceStr;

	std::ifstream vFile(vFileLoc);
	std::ifstream fFile(fFileLoc);
	if (vFile.is_open() && fFile.is_open())
	{
		std::stringstream vSstr;
		std::stringstream fSstr;
		vSstr << vFile.rdbuf();
		fSstr << fFile.rdbuf();

		vShaderSourceStr = vSstr.str();
		fShaderSourceStr = fSstr.str();
	}
	else
	{
		IMC_WARNING("IMCShader | Failed to open " << vFileLoc << " or " << fFileLoc << " file." << std::endl);
	}

	unsigned int vertex = 0, fragment = 0;
	const char* vShaderSource = vShaderSourceStr.c_str();
	const char* fShaderSource = fShaderSourceStr.c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderSource, nullptr);
	glCompileShader(vertex);
	CheckCompileError(vertex, "Vertex");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderSource, nullptr);
	glCompileShader(fragment);
	CheckCompileError(fragment, "Fragment");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	Unuse();
}

IMCShader::~IMCShader()
{
	glDeleteProgram(ID);
}

void IMCShader::Use()
{
	if (!isUsed)
	{
		glUseProgram(ID);
		isUsed = true;
	}
}

void IMCShader::Unuse()
{
	if (isUsed)
	{
		glUseProgram(0);
		isUsed = false;
	}
}

void IMCShader::CheckCompileError(unsigned int shaderId, const char* typeShader)
{
	int success;
	char infoLog[1024];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
		IMC_WARNING("IMCShader Warning | Error compiling " << typeShader << " shader: " << infoLog << std::endl);
	}
}

void IMCShader::SetMat4(const std::string& name, const glm::mat4& v) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(v));
}

void IMCShader::SetVec4(const std::string& name, const glm::vec4& v) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
}

void IMCShader::SetVec3(const std::string& name, const glm::vec3& v) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
}

void IMCShader::SetVec2(const std::string& name, const glm::vec2& v) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(v));
}

void IMCShader::SetFloat(const std::string& name, float v) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), v);
}

void IMCShader::SetInt(const std::string& name, int v) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), v);
}

