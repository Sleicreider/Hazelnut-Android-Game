#ifdef GL_ES
precision lowp float;
#endif

varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;
varying vec2 v_texCoord2;

uniform sampler2D u_texture1;
uniform float u_opacity;


void main()
{
    vec3 tex = texture2D(CC_Texture0, v_texCoord).rgb ;
    float alpha = texture2D(u_texture1, v_texCoord).r * u_opacity;
    
    gl_FragColor = vec4(tex,alpha);
}
