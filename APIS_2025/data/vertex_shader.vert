#version 330
uniform mat4 mMat;
in vec4 vPos;
void main() {
    gl_Position = mMat * vPos;
}