
varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;
varying vec2 v_texCoord2;

uniform sampler2D tex1;


void main()
{
    vec3 pixel = texture2D(CC_Texture0, v_texCoord).rgb * v_fragmentColor.rgb;
    
    float s1 = texture2D(CC_Texture1, v_texCoord2).a * v_fragmentColor.a;

	gl_FragColor = vec4(pixel,s1);
}				
