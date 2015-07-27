
varying vec4 v_fragmentColor;	
varying vec2 v_texCoord;	
		
void main()			
{
	
	vec3 bgCol = vec3(1.0);
	vec3 col1 = vec3(1.0,1.0,0.0);
	
	vec3 pixel = bgCol;
	


	gl_FragColor = vec4(pixel,1.0);
}				
