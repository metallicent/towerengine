#version 330

#define MAX_LAYERS 8

#define GAUSSIAN_BLUR

uniform sampler2DArray tex_uni;

uniform vec2 blur_dir_uni;
uniform float blur_factors_uni[MAX_LAYERS];
uniform int tex_layers_count_uni;

in vec2 uv_coord_var;

out vec4 tex_out[MAX_LAYERS];

void main()
{
	vec2 color;
	float layer;
	vec2 blur_dir;
	
	for(int s=0; s<tex_layers_count_uni; s++)
	{
		layer = float(s);
		color = vec2(0.0, 0.0);
		blur_dir = blur_dir_uni * blur_factors_uni[s];
		
		#ifdef GAUSSIAN_BLUR	
		
		color += texture(tex_uni, vec3(uv_coord_var - blur_dir * 2.0, layer)).rg * 0.06;
		color += texture(tex_uni, vec3(uv_coord_var - blur_dir, layer)).rg * 0.24;
		color += texture(tex_uni, vec3(uv_coord_var, layer)).rg * 0.4;
		color += texture(tex_uni, vec3(uv_coord_var + blur_dir, layer)).rg * 0.24;
		color += texture(tex_uni, vec3(uv_coord_var + blur_dir * 2.0, layer)).rg * 0.06;
		
		#else
		
		color += texture(tex_uni, vec3(uv_coord_var - blur_dir * 2.0, layer)).rg * 0.2;
		color += texture(tex_uni, vec3(uv_coord_var - blur_dir, layer)).rg * 0.2;
		color += texture(tex_uni, vec3(uv_coord_var, layer)).rg * 0.2;
		color += texture(tex_uni, vec3(uv_coord_var + blur_dir, layer)).rg * 0.2;
		color += texture(tex_uni, vec3(uv_coord_var + blur_dir * 2.0, layer)).rg * 0.2;
		
		#endif
		
		
		/*switch(s)
		{
			case 0:
				color = vec2(1.0, 0.0);
				break;
			case 1:
				color = vec2(0.0, 1.0);
				break;
			case 2:
				color = vec2(1.0, 1.0);
				break;
			case 3:
				color = vec2(0.0, 0.0);
				break;
		}*/
				
		tex_out[s] = vec4(color, 0.0, 1.0);
	}
}