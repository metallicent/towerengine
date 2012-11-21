//-----------------------------------------------------------------------
// This file has been generated by stringres by Metallic Entertainment
// for further information go to http://www.metallic-entertainment.com
//-----------------------------------------------------------------------

#include "tresources.h"

const char *face_shader_vert = 
"#version 130\n"
"\n"
"uniform mat4 gl_TextureMatrix[gl_MaxTextureCoords];\n"
"uniform mat4 gl_ModelViewProjectionMatrix;\n"
"uniform mat4 gl_ModelViewMatrix;\n"
"uniform mat4 gl_ModelViewMatrixInverse;\n"
"\n"
"in vec2 TexCoord_a;\n"
"in vec3 Vertex_a;\n"
"in vec3 Normal_a;\n"
"in vec3 FaceNormal_a;\n"
"\n"
"in vec4 TexBorder_a;\n"
"in unsigned int DiscardBorder_a;\n"
"\n"
"in float BumpFactor_a;\n"
"\n"
"uniform mat4 Transformation;\n"
"\n"
"uniform vec3 LightPos;\n"
"\n"
"uniform sampler2D HeightTex;\n"
"uniform vec3 HeightFactor;\n"
"\n"
"out vec2 UVCoord;\n"
"out vec4 ShadowCoord;\n"
"out vec3 LightDir;\n"
"out vec3 CamPos;\n"
"out vec3 CamDir;\n"
"out vec3 Normal;\n"
"out vec3 FaceNormal;\n"
"out vec3 TangX;\n"
"out vec3 TangY;\n"
"out vec3 Pos;\n"
"\n"
"out vec4 TexBorder;\n"
"out float DiscardBorder;\n"
"\n"
"out float BumpFactor;\n"
"\n"
"void main(void)\n"
"{\n"
"	vec3 normal = normalize(Normal_a * mat3(Transformation));\n"
"	vec3 tangx;// = normalize(TangX_a * mat3(Transformation));\n"
"	vec3 tangy;// = normalize(TangY_a * mat3(Transformation));\n"
"\n"
"	if(dot(Normal_a, vec3(0.0, 1.0, 0.0)) > 0.5)\n"
"	{\n"
"		tangx = normalize(cross(Normal_a, vec3(0.0, 0.0, 1.0)));\n"
"		tangy = normalize(-cross(Normal_a, tangx));\n"
"	}\n"
"	else\n"
"	{\n"
"		tangx = normalize(cross(Normal_a, vec3(0.0, 1.0, 0.0)));\n"
"		tangy = normalize(-cross(Normal_a, tangx));\n"
"	}\n"
"		\n"
"	Normal = normal;\n"
"	TangX = tangx;\n"
"	TangY = tangy;\n"
"	\n"
"	vec3 shift = vec3(0.0, 0.0, 0.0);\n"
"	if(dot(HeightFactor, vec3(1.0, 1.0, 1.0)) > 0.001)\n"
"	{\n"
"		vec3 displacement = texture2D(HeightTex, TexCoord_a).rgb;\n"
"		displacement -= vec3(0.5, 0.5, 0.5);\n"
"		shift = tangx * displacement.x;\n"
"		shift += tangy * displacement.y;\n"
"		shift += normal * displacement.z;\n"
"		shift *= HeightFactor;\n"
"	}\n"
"	vec4 pos = vec4(Vertex_a.xyz + shift, 1.0) * Transformation;\n"
"	Pos = pos.xyz;\n"
"	UVCoord = TexCoord_a.xy;\n"
"	ShadowCoord = gl_TextureMatrix[5] * pos;\n"
"	gl_Position = gl_ModelViewProjectionMatrix * pos;\n"
"	vec3 camera_dir = (gl_ModelViewMatrix * pos).xyz;\n"
"	vec3 light_dir = LightPos - pos.xyz;\n"
"	mat3 normal_mat = mat3(tangx, tangy, normal);\n"
"	CamPos = normal_mat * camera_dir;\n"
"	vec4 camera_OS = gl_ModelViewMatrixInverse * vec4(0.0, 0.0, 0.0, 1.0);\n"
"	CamDir = normalize(camera_OS.xyz * pos.w - pos.xyz * camera_OS.w);\n"
"	LightDir.x = dot(tangx, light_dir);\n"
"	LightDir.y = dot(tangy, light_dir);\n"
"	LightDir.z = dot(normal, light_dir);	\n"
"	FaceNormal = FaceNormal_a;\n"
"	DiscardBorder = float(DiscardBorder_a);\n"
"}";

const char *face_shader_frag = 
"#version 130\n"
"\n"
"in vec2 UVCoord;\n"
"in vec4 ShadowCoord;\n"
"in vec3 LightDir;\n"
"in vec3 CamPos;\n"
"in vec3 CamDir;\n"
"in vec3 Pos;\n"
"in vec3 Normal;\n"
"in vec3 FaceNormal;\n"
"in vec3 TangX;\n"
"in vec3 TangY;\n"
"\n"
"out vec4 gl_FragColor;\n"
"\n"
"uniform bool ShaderMode;\n"
"\n"
"uniform bool TwoSide;\n"
"\n"
"uniform vec3 LightColor;\n"
"uniform sampler2DShadow ShadowMap;\n"
"\n"
"uniform vec3 DiffuseColor;\n"
"uniform vec4 DiffuseColor2;\n"
"uniform vec3 SpecularColor;\n"
"uniform vec3 AmbientColor;\n"
"uniform float SpecularSize;\n"
"\n"
"uniform sampler2D DiffuseTex;\n"
"uniform sampler2D AEBTex;\n"
"uniform sampler2D NormalTex;\n"
"uniform sampler2D SpecularTex;\n"
"\n"
"in vec4 TexBorder;\n"
"in float DiscardBorder;\n"
"\n"
"uniform vec3 Clip;\n"
"uniform float ClipDist;\n"
"\n"
"in float BumpFactor;\n"
"\n"
"uniform vec3 FogColor;\n"
"uniform float FogDepth;\n"
"uniform float FogDist;\n"
"\n"
"vec3 normal;\n"
"vec3 light_dir;\n"
"vec3 cam_dir;\n"
"vec3 cam_dir_n;\n"
"\n"
"uniform vec2 ShadowPixel;\n"
"\n"
"float CalculateSpecularLight(in vec3 light_dir)\n"
"{\n"
"	return max(dot(normalize(reflect(-light_dir, normal)), cam_dir_n), 0.0);\n"
"}\n"
"	\n"
"vec2 CalculateTexCoord(out vec2 _dx, out vec2 _dy, in sampler2D height_map, in int channel, in vec2 flat_coord, in float max_depth, in vec3 cam_dir) // Parallax Occlusion\n"
"{\n"
"	vec2 dx = dFdx(flat_coord);\n"
"	vec2 dy = dFdy(flat_coord);\n"
"	_dx = dx;\n"
"	_dy = dy;\n"
"	\n"
"	if(max_depth <= 0.0)\n"
"		return flat_coord;\n"
"	if(texture2D(height_map, flat_coord)[channel] == 1.0)\n"
"		return flat_coord;\n"
"	\n"
"	float max_offset = length(cam_dir.xy) / cam_dir.z;\n"
"	max_offset *= max_depth;\n"
"	\n"
"	vec2 offset_v = normalize(cam_dir.xy);\n"
"	offset_v *= max_offset;\n"
"	\n"
"	int num_samples = int(mix(64.0, 8.0, dot(vec3(0.0, 0.0, 1.0), cam_dir_n)));\n"
"	float step_size = 1.0 / float(num_samples);\n"
"	\n"
"	vec2 offset_step = offset_v * step_size;\n"
"	vec2 current_offset = vec2(0.0, 0.0);\n"
"	vec2 last_offset = vec2(0.0, 0.0);\n"
"	vec2 final_offset = vec2(0.0, 0.0);\n"
"	\n"
"	vec4 current_sample_v = vec4(0.0, 0.0, 0.0, 0.0);\n"
"	vec4 last_sample = vec4(0.0, 0.0, 0.0, 0.0);\n"
"	\n"
"	float step_height = 1.0;\n"
"	int current_sample = 0;\n"
"	\n"
"	while(current_sample < num_samples)\n"
"	{\n"
"		current_sample_v = textureGrad(height_map, flat_coord + current_offset, dx, dy);\n"
"		if(current_sample_v[channel] > step_height)\n"
"		{\n"
"			break;\n"
"		}\n"
"		else\n"
"		{\n"
"			current_sample++;\n"
"			step_height -= step_size;\n"
"			last_offset = current_offset;\n"
"			current_offset += offset_step;\n"
"			last_sample = current_sample_v;\n"
"		}\n"
"	}\n"
"	float ua = (last_sample[channel] - (step_height + step_size))\n"
"			/ (step_size + current_sample_v[channel] - last_sample[channel]);\n"
"	final_offset = last_offset + ua * offset_step;\n"
"	return flat_coord + final_offset;\n"
"}\n"
"\n"
"vec4 ShadowCoordO(vec2 offset)\n"
"{\n"
"	return ShadowCoord + vec4(offset.x * ShadowPixel.x * ShadowCoord.w,\n"
"			offset.y * ShadowPixel.y * ShadowCoord.w, -0.0005, 0.0);\n"
"}\n"
"\n"
"vec4 ShadowCoordW(vec2 offset)\n"
"{\n"
"	return ShadowCoordO(offset) / ShadowCoord.w;\n"
"}\n"
"\n"
"float ShadowLookup(vec2 offset)\n"
"{\n"
"	return textureProj(ShadowMap, ShadowCoordO(offset));\n"
"}\n"
"\n"
"void main(void)\n"
"{	\n"
"	if(!gl_FrontFacing && !TwoSide)\n"
"		discard;\n"
"	\n"
"	if(Clip != vec3(0.0, 0.0, 0.0))\n"
"	{\n"
"		vec3 clip = Clip * ClipDist;\n"
"		clip = Pos - clip;\n"
"		if(dot(clip, Clip) >= 0.0)\n"
"			discard;\n"
"	}\n"
"	\n"
"	if(!ShaderMode)\n"
"	{\n"
"		gl_FragColor = vec4(1.0);\n"
"		return;\n"
"	}\n"
"	\n"
"	int i;\n"
"	light_dir = normalize(LightDir);\n"
"	mat3 normal_mat = mat3(TangX, TangY, FaceNormal);\n"
"	cam_dir = CamDir * normal_mat;\n"
"	cam_dir_n = normalize(cam_dir);\n"
"	vec3 aeb = texture2D(AEBTex, UVCoord).rgb;\n"
"	float alpha = aeb.r;\n"
"	if(alpha == 0.0)\n"
"	{\n"
"		gl_FragColor = vec4(0.0);\n"
"		return;\n"
"	}\n"
"	float exponent_factor = aeb.g;\n"
"	float height = aeb.b;\n"
"	vec2 dx, dy;\n"
"	vec2 tex_coord = CalculateTexCoord(dx, dy, AEBTex, 2, UVCoord, BumpFactor, vec3(-cam_dir.xy, cam_dir.z));\n"
"	//if(DiscardBorder > 0.5 && (tex_coord.x < TexBorder.x || tex_coord.y < TexBorder.y || tex_coord.x > TexBorder.z || tex_coord.y > TexBorder.w))\n"
"	//	discard;\n"
"	vec3 color = DiffuseColor * textureGrad(DiffuseTex, tex_coord, dx, dy).rgb;\n"
"	vec3 frag_color = AmbientColor * color;\n"
"	normal = normalize(normalize(texture2D(NormalTex, tex_coord).rgb - 0.5) + (Normal - FaceNormal));\n"
"	normal.x = -normal.x;\n"
"	\n"
"	float shadow = 1.0;\n"
"	float sr = 1.5;\n"
"	int shadow_enabled = 1;\n"
"	if(ShadowCoordW(vec2(sr, 0.0)).x > 1.0 || ShadowCoordW(vec2(0.0, sr)).y > 1.0 ||\n"
"			ShadowCoordW(vec2(sr, 0.0)).x < 0.0 || ShadowCoordW(vec2(0.0, sr)).y < 0.0)\n"
"		shadow_enabled = 0;\n"
"	if(ShadowCoord.z / ShadowCoord.w > 1.0)\n"
"		shadow_enabled = 0;\n"
"	\n"
"	if(shadow_enabled == 1)\n"
"	{\n"
"		float x,y;\n"
"		shadow = 0.0;\n"
"		for (y=-sr; y<=sr; y+=(sr*2.0 + 1.0)/4.0)\n"
"			for (x = -sr ; x <=sr ; x+=(sr*2.0 + 1.0)/4.0)\n"
"				shadow += ShadowLookup(vec2(x,y));\n"
"		shadow /= 16.0;\n"
"	}\n"
"	\n"
"	frag_color += max(0.0, dot(light_dir, normal)) * color * LightColor * shadow;\n"
"	\n"
"	vec3 specular_color = SpecularColor * texture2D(SpecularTex, tex_coord).rgb * LightColor;\n"
"	float specular_intensity = CalculateSpecularLight(light_dir);\n"
"	frag_color += max(vec3(0.0, 0.0, 0.0), specular_color * pow(specular_intensity, SpecularSize) * shadow);\n"
"	\n"
"	if(FogDepth > 0.0)\n"
"	{\n"
"		float fog = clamp((abs(CamPos.z) - FogDist) * FogDepth, 0.0, 1.0);\n"
"		frag_color = mix(frag_color, FogColor, fog);\n"
"	}\n"
"	\n"
"	frag_color *= DiffuseColor2.rgb;\n"
"	alpha *= DiffuseColor2.a;\n"
"		\n"
"	gl_FragColor = vec4(frag_color, alpha);\n"
"}";

