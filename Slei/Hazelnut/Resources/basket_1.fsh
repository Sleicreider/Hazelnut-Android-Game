
varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;
//varying vec2 v_texCoord2;

uniform sampler2D tex1;


void main()
{
    //vec3 pixel = texture2D(CC_Texture0, v_texCoord).rgb * v_fragmentColor.rgb;
    
    //float s1 = texture2D(CC_Texture1, v_texCoord2).a * v_fragmentColor.a;
    
    
    //v_orColor.rbg += vec3(((sin((v_texCoord.y)+v_texCoord.x *3. + CC_Time.g*3.)) + v_orColor)/2.);
    //v_orColor.rgb *= 1.55;

    vec2 tex_coord = v_texCoord;
    
    tex_coord.x += cos(tex_coord.y*10. + CC_Time.g) / 100.;

    gl_FragColor = texture2D(CC_Texture0, tex_coord);//vec4(pixel,s1);
}				
