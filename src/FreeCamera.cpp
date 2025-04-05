#include <FreeCamera.hpp>
#include <glm/gtx/euler_angles.hpp>

void CFreeCamera::Walk(const float dt)
{
	translation += (look * dt);
}

void CFreeCamera::Strafe(const float dt)
{
	translation += (right * dt);
}

void CFreeCamera::Lift(const float dt)
{
	translation += (up * dt);
}

void CFreeCamera::Update() 
{
	glm::mat4 rot = glm::yawPitchRoll(glm::radians(this->yaw),
		glm::radians(this->pitch), glm::radians(this->roll));
	
	this->position += translation;
	translation = glm::vec3(0);
	
	look = glm::vec3(rot * glm::vec4(0, 0, 1, 0));
	up = glm::vec3(rot * glm::vec4(0, 1, 0, 0));
	right = glm::cross(look, up);
	
	glm::vec3 tgt = position + look;
	
	V = glm::lookAt(position, tgt, up);
	this->CalcFrustumPlanes();

}

//void CFreeCamera::Update()
//{
//    // Ograniczenie pitch do [-89, 89] stopni, aby unikn¹æ przewrotu kamery
//    if (pitch > 89.0f) pitch = 89.0f;
//    if (pitch < -89.0f) pitch = -89.0f;
//
//    // Tworzenie macierzy rotacji na podstawie yaw, pitch, roll
//    glm::mat4 rot = glm::yawPitchRoll(glm::radians(yaw),
//        glm::radians(pitch),
//        glm::radians(roll));
//
//    // Aktualizacja pozycji na podstawie translacji
//    position += translation;
//    translation = glm::vec3(0);
//
//    // Przekszta³cenie wektorów kierunkowych
//    look = glm::normalize(glm::vec3(rot * glm::vec4(0, 0, 1, 0)));
//    up = glm::normalize(glm::vec3(rot * glm::vec4(0, 1, 0, 0)));
//
//    // Zapewnienie ortogonalnoœci `right`
//    right = glm::normalize(glm::cross(look, up));
//
//    // Wyznaczanie celu kamery
//    glm::vec3 tgt = position + look;
//
//    // Aktualizacja macierzy widoku
//    V = glm::lookAt(position, tgt, up);
//}
