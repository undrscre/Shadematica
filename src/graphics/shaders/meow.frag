#version 330 core
out vec4 FragColor;

uniform float iGlobalTime;
uniform vec3 iResolution;
uniform vec4 iMouse;

void main()
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy;

    float time = iGlobalTime;
    vec2 mouse = iMouse.xy / iResolution.xy;

    vec3 color = vec3(uv.x + sin(time) * 0.5, uv.y + cos(time) * 0.5, mouse.y);
    FragColor = vec4(color, 1.0);
}
