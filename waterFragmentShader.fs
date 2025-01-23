#version 330 core

out vec4 FragColor;

in vec2 TexCoord; // Interpolated texture coordinates from the vertex shader

uniform sampler2D waterTexture; // The water texture sampler
uniform float time; // Time for wave animation

void main() {
    // Basic wave effect by modifying texture coordinates
    float wave = sin(15.0 * TexCoord.x + time) * 0.2; // Add wave distortion
    vec2 distortedTexCoord = TexCoord + vec2(wave, 0.0); // Offset the texture coordinates

    // Sample the water texture with distorted coordinates
    vec4 waterColor = texture(waterTexture, distortedTexCoord);

    FragColor = waterColor; // Set the output color
}
