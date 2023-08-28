#include <OpenGLShaders.h>
#include <iostream>





GLboolean OpenGLShader::Link() {
    if (GL_TRUE == is_linked) {
        return GL_TRUE;
    }
    if (pgm_handle <= 0) {
        return GL_FALSE;
    }

    glLinkProgram(pgm_handle); // link the various compiled shaders

    // verify the link status
    GLint lnk_status;
    glGetProgramiv(pgm_handle, GL_LINK_STATUS, &lnk_status);
    if (GL_FALSE == lnk_status) {
        log_string = "Failed to link shader program\n";
        GLint log_len;
        glGetProgramiv(pgm_handle, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 0) {
            GLchar* log_str = new GLchar[log_len];
            GLsizei written_log_len;
            glGetProgramInfoLog(pgm_handle, log_len, &written_log_len, log_str);
            log_string += log_str;
            delete[] log_str;
        }
        return GL_FALSE;
    }
    return is_linked = GL_TRUE;
}

GLuint OpenGLShader::GetHandle() const {
    return pgm_handle;
}


GLboolean
OpenGLShader::CompileLinkValidate(std::vector<std::pair<GLenum, std::string>> vec) {
    for (auto& elem : vec) {
        if (GL_FALSE == CompileShaderFromFile(elem.first, elem.second.c_str())) {
            return GL_FALSE;
        }
    }
    if (GL_FALSE == Link()) {
        return GL_FALSE;
    }
    if (GL_FALSE == Validate()) {
        return GL_FALSE;
    }
    PrintActiveAttribs();
    PrintActiveUniforms();

    return GL_TRUE;
}
GLboolean
OpenGLShader::CompileShaderFromFile(GLenum shader_type, const std::string& file_name) {
    if (GL_FALSE == FileExists(file_name)) {
        log_string = "File not found";
        return GL_FALSE;
    }
    if (pgm_handle <= 0) {
        pgm_handle = glCreateProgram();
        if (0 == pgm_handle) {
            log_string = "Cannot create program handle";
            return GL_FALSE;
        }
    }

    std::ifstream shader_file(file_name, std::ifstream::in);
    if (!shader_file) {
        log_string = "Error opening file " + file_name;
        return GL_FALSE;
    }
    std::stringstream buffer;
    buffer << shader_file.rdbuf();
    shader_file.close();
    return CompileShaderFromString(shader_type, buffer.str());
}

void OpenGLShader::Use() {
    if (pgm_handle > 0 && is_linked == GL_TRUE) {
        glUseProgram(pgm_handle);
    }
}

void OpenGLShader::UnUse() {
    glUseProgram(0);
}


void OpenGLShader::SetUniform(GLchar const* name, GLboolean val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform1i(loc, val);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void OpenGLShader::SetUniform(GLchar const* name, GLint val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform1i(loc, val);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void OpenGLShader::SetUniform(GLchar const* name, GLfloat val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform1f(loc, val);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void OpenGLShader::SetUniform(GLchar const* name, GLfloat x, GLfloat y) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform2f(loc, x, y);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void OpenGLShader::SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform3f(loc, x, y, z);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void
OpenGLShader::SetUniform(GLchar const* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform4f(loc, x, y, z, w);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void OpenGLShader::SetUniform(GLchar const* name, glm::vec2 const& val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform2f(loc, val.x, val.y);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void OpenGLShader::SetUniform(GLchar const* name, glm::vec3 const& val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform3f(loc, val.x, val.y, val.z);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void OpenGLShader::SetUniform(GLchar const* name, glm::vec4 const& val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniform4f(loc, val.x, val.y, val.z, val.w);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void OpenGLShader::SetUniform(GLchar const* name, glm::mat3 const& val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniformMatrix3fv(loc, 1, GL_FALSE, &val[0][0]);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}

void OpenGLShader::SetUniform(GLchar const* name, glm::mat4 const& val) {
    GLint loc = glGetUniformLocation(pgm_handle, name);
    if (loc >= 0) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &val[0][0]);
    }
    else {
        std::cout << "Uniform variable " << name << " doesn't exist" << std::endl;
    }
}