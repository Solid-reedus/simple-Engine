#include "monkey.h"
#include "camera.h"
#include "model.h"

Monkey::Monkey(Camera& p_cameraRef, Shader* p_shader) : BaseRenderable(p_cameraRef)
{
	m_shader = p_shader;
	m_model = new Model("assets/monkey/monkey.obj");
}

void Monkey::Render()
{
	for (Instance& ins : m_intances)
	{
		m_shader->use();
		m_shader->setMat4("projection", m_cameraRef.GetProjectionMatrix());
		m_shader->setMat4("view", m_cameraRef.GetViewMatrix());
		m_shader->setVec3("viewPos", m_cameraRef.position);

		m_shader->setMat4("model", ins.trans);
		m_model->Draw(m_shader, m_cameraRef);
	}
}
