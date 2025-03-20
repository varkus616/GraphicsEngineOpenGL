#include <AbstractCamera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

void CAbstractCamera::SetupProjection(float fovy, float aspectRatio, float near, float far) {

    this->fov = fovy;
    this->aspect_ratio = aspectRatio;
    this->Znear = near;
    this->Zfar = far;
    P = glm::perspective(glm::radians(fovy), aspectRatio, near, far);
}

//void CAbstractCamera::Rotate(float yaw, float pitch, float roll) {
//    this->yaw += yaw;
//    this->pitch += pitch;
//    this->roll += roll;
//    glm::mat4 rot = glm::yawPitchRoll(glm::radians(this->yaw),
//        glm::radians(this->pitch), glm::radians(this->roll));
//    look = glm::vec3(rot * glm::vec4(look.x, look.y, look.z, 0));
//    up = glm::vec3(rot * glm::vec4(0, 1, 0, 0));
//    V = glm::lookAt(position, position + look, up);
//}

void CAbstractCamera::Rotate(float yaw, float pitch, float roll) {
    this->yaw += yaw;
    this->pitch += pitch;
    this->roll += roll;

    // Ograniczenie pitch do zakresu [-89, 89] stopni
    if (this->pitch > 89.0f) this->pitch = 89.0f;
    if (this->pitch < -89.0f) this->pitch = -89.0f;

    // Tworzenie macierzy rotacji na podstawie yaw, pitch, roll
    glm::mat4 rot = glm::yawPitchRoll(glm::radians(this->yaw),
        glm::radians(this->pitch),
        glm::radians(this->roll));

    // U¿ycie domyœlnego wektora odniesienia (0,0,1) dla `look`
    look = glm::normalize(glm::vec3(rot * glm::vec4(0, 0, 1, 0)));

    // `up` musi zostaæ obliczone po `look`, by zapewniæ ortogonalnoœæ
    up = glm::normalize(glm::vec3(rot * glm::vec4(0, 1, 0, 0)));

    // Upewnienie siê, ¿e `right` jest ortogonalny do `look` i `up`
    right = glm::normalize(glm::cross(look, up));

    // Aktualizacja macierzy widoku
    V = glm::lookAt(position, position + look, up);
}


void CAbstractCamera::ResetRotation()
{
    this->yaw = 0;
    this->pitch = 0;
    this->roll = 0;
    this->Rotate(0, 0, 0);
}

void CAbstractCamera::SetPosition(const glm::vec3& v) {
    position = v;
    V = glm::lookAt(position, position + look, up);
}

void CAbstractCamera::CalcFrustumPlanes() {
    glm::mat4 comboMatrix = P * V;
    planes[0] = CPlane(glm::vec3(comboMatrix[0][3] + comboMatrix[0][0],
        comboMatrix[1][3] + comboMatrix[1][0],
        comboMatrix[2][3] + comboMatrix[2][0]), comboMatrix[3][3] + comboMatrix[3][0]); // Left

    planes[1] = CPlane(glm::vec3(comboMatrix[0][3] - comboMatrix[0][0],
        comboMatrix[1][3] - comboMatrix[1][0],
        comboMatrix[2][3] - comboMatrix[2][0]), comboMatrix[3][3] - comboMatrix[3][0]); // Right

    planes[2] = CPlane(glm::vec3(comboMatrix[0][3] + comboMatrix[0][1],
        comboMatrix[1][3] + comboMatrix[1][1],
        comboMatrix[2][3] + comboMatrix[2][1]), comboMatrix[3][3] + comboMatrix[3][1]); // Bottom

    planes[3] = CPlane(glm::vec3(comboMatrix[0][3] - comboMatrix[0][1],
        comboMatrix[1][3] - comboMatrix[1][1],
        comboMatrix[2][3] - comboMatrix[2][1]), comboMatrix[3][3] - comboMatrix[3][1]); // Top

    planes[4] = CPlane(glm::vec3(comboMatrix[0][3] + comboMatrix[0][2],
        comboMatrix[1][3] + comboMatrix[1][2],
        comboMatrix[2][3] + comboMatrix[2][2]), comboMatrix[3][3] + comboMatrix[3][2]); // Near

    planes[5] = CPlane(glm::vec3(comboMatrix[0][3] - comboMatrix[0][2],
        comboMatrix[1][3] - comboMatrix[1][2],
        comboMatrix[2][3] - comboMatrix[2][2]), comboMatrix[3][3] - comboMatrix[3][2]); // Far

}

bool CAbstractCamera::IsPointInFrustum(const glm::vec3& point) const {
    for (const auto& plane : planes) {
        if (!plane.IsPointInFront(point)) {
            return false;
        }
    }
    return true;
}

bool CAbstractCamera::IsSphereInFrustum(const glm::vec3& center, const float radius) const{
    for (const auto& plane : planes) {
        if (plane.Distance(center) < -radius) {
            return false;
        }
    }
    return true;
}

bool CAbstractCamera::IsBoxInFrustum(const glm::vec3& min, const glm::vec3& max) const {
    glm::vec3 corners[8] = {
        glm::vec3(min.x, min.y, min.z),  // 000
        glm::vec3(max.x, min.y, min.z),  // 100
        glm::vec3(min.x, max.y, min.z),  // 010
        glm::vec3(max.x, max.y, min.z),  // 110
        glm::vec3(min.x, min.y, max.z),  // 001
        glm::vec3(max.x, min.y, max.z),  // 101
        glm::vec3(min.x, max.y, max.z),  // 011
        glm::vec3(max.x, max.y, max.z)   // 111
    };
    
    for (int i = 0; i < 6; ++i) {
        int outCount = 0;
    
        for (int j = 0; j < 8; ++j) {
            if (!planes[i].IsPointInFront(corners[j])) {
                outCount++;
            }
        }
    
        // Jeœli wszystkie 8 naro¿ników znajduje siê poza jedn¹ p³aszczyzn¹, box jest ca³kowicie poza frustum
        if (outCount == 8) {
            return false;
        }
    }
    
    // Jeœli przetrwaliœmy wszystkie p³aszczyzny, box jest przynajmniej czêœciowo we frustum
    return true;
}
