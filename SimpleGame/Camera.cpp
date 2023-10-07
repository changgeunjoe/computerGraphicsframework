#include "Camera.h"




void CCamera::Render(GLuint& m_Shader)
{


    glUseProgram(m_Shader);
    glUniformMatrix4fv(glGetUniformLocation(m_Shader, "u_ViewMatrix"), 1, GL_FALSE, glm::value_ptr(GetViewMatrix()));
    glm::mat4 projection = glm::perspective(glm::radians(Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(m_Shader, "u_ProjMatrix"), 1, GL_FALSE, glm::value_ptr(projection));

}
