#include "../include/Camera.hpp"
#include <cstdio>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>

void agl::Camera::setPerspectiveProjection(float fov, float aspectRatio, float near, float far)
{
	projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);

	return;
}

void agl::Camera::setOrthographicProjection(float left, float right, float bottom, float top, float near, float far)
{
	projection = glm::ortho(left, right, bottom, top, near, far);

	return;
}

void agl::Camera::setView(Vec3f pos, Vec3f target, Vec3f head)
{
	view = glm::lookAt(glm::vec3(pos.x, pos.y, pos.z), glm::vec3(target.x, target.y, target.z), glm::vec3(head.x, head.y, head.z));
}

glm::mat4 agl::Camera::getMVP()
{
	return projection * view * model;
}