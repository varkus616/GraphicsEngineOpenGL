#version 420

out vec4 vFragColor;

smooth in vec4 color;
uniform vec4 objectColor;
void main()
{
	vFragColor = color ;//+ objectColor;
}