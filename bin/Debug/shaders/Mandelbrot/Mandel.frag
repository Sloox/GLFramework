uniform vec4 fpar[4];
uniform int iter;

void main(void)
{
	vec2 c=vec2(-0.75,0)+gl_TexCoord[0].xy*vec2(1.333,1.00);
	vec2 z=vec2(0.0);
	float h=0.0;
	float m;
	for(int i=0;i<512;i++)
	{
		z=vec2(z.x*z.x-z.y*z.y,2.0*z.x*z.y)+c;
		m=dot(z,z);
		if(m>4.0) break;
		h+=1.0;
	}
	h=h+1.0-log2(.5*log(m));
	gl_FragColor=vec4(h/100.0);
}