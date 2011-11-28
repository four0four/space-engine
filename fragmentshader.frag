#version 120

uniform sampler2D texture; // the texture with the scene you want to blur

void main(void)
{
    gl_FragColor = texture2D(texture,gl_TexCoord[0].ts);
}
