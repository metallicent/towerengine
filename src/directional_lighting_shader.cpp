
#include "towerengine.h"
#include "resources.h"
#include "shader_source.h"


const GLint tDirectionalLightingShader::max_directional_light_splits;

tDirectionalLightingShader::tDirectionalLightingShader(tGBuffer *gbuffer)
{
	InitScreenShader(resources_get("directional_lighting_shader.frag"), "Directional Lighting Shader");

	depth_tex_uniform = GetUniformLocation("position_tex_uni");
	base_color_tex_uniform = GetUniformLocation("base_color_tex_uni");
	normal_tex_uniform = GetUniformLocation("normal_tex_uni");
	metallic_roughness_tex_uniform = GetUniformLocation("metallic_roughness_tex_uni");

	cam_pos_uniform = GetUniformLocation("cam_pos_uni");

	directional_light_dir_uniform = GetUniformLocation("directional_light_dir_uni");
	directional_light_color_uniform = GetUniformLocation("directional_light_color_uni");
	directional_light_shadow_enabled_uniform = GetUniformLocation("directional_light_shadow_enabled_uni");
	directional_light_shadow_clip_uniform = GetUniformLocation("directional_light_shadow_clip_uni");
	directional_light_shadow_tex_matrix_uniform = GetUniformLocation("directional_light_shadow_tex_matrix_uni");
	directional_light_shadow_splits_count_uniform = GetUniformLocation("directional_light_shadow_splits_count_uni");
	directional_light_shadow_splits_z_uniform = GetUniformLocation("directional_light_shadow_splits_z_uni");
	directional_light_shadow_map_uniform = GetUniformLocation("directional_light_shadow_map_uni");


	GLuint position_restore_data_block_index = glGetUniformBlockIndex(program, "PositionRestoreDataBlock");
	glUniformBlockBinding(program, position_restore_data_block_index, position_restore_data_binding_point);

	Bind();
	glUniform1i(depth_tex_uniform, gbuffer->GetTextureUnit(tGBuffer::DEPTH_TEX));
	glUniform1i(base_color_tex_uniform, gbuffer->GetTextureUnit(tGBuffer::BASE_COLOR_TEX));
	glUniform1i(normal_tex_uniform, gbuffer->GetTextureUnit(tGBuffer::NORMAL_TEX));
	glUniform1i(metallic_roughness_tex_uniform, gbuffer->GetTextureUnit(tGBuffer::METAL_ROUGH_REFLECT_TEX));

	directional_light_shadow_tex_unit = gbuffer->GetLastTextureUnit() + 1;
	glUniform1i(directional_light_shadow_map_uniform, directional_light_shadow_tex_unit);
}

void tDirectionalLightingShader::SetDirectionalLight(tVector dir, tVector color, int shadow_enabled, GLuint shadow_map, tVector2 shadow_clip, float *shadow_tex_matrix, int shadow_splits_count, float *shadow_splits_z)
{
	glUniform3f(directional_light_dir_uniform, dir.x, dir.y, dir.z);
	glUniform3f(directional_light_color_uniform, color.x, color.y, color.z);
	glUniform1i(directional_light_shadow_enabled_uniform, shadow_enabled);
	glUniform2f(directional_light_shadow_clip_uniform, shadow_clip.x, shadow_clip.y);
	glUniformMatrix4fv(directional_light_shadow_tex_matrix_uniform, shadow_splits_count, GL_TRUE, shadow_tex_matrix);
	glUniform1i(directional_light_shadow_splits_count_uniform, shadow_splits_count);
	glUniform1fv(directional_light_shadow_splits_z_uniform, shadow_splits_count+1, shadow_splits_z);

	glActiveTexture(GL_TEXTURE0 + directional_light_shadow_tex_unit);
	glBindTexture(GL_TEXTURE_2D_ARRAY, shadow_map);
}

void tDirectionalLightingShader::SetCameraPosition(tVector pos)
{
	glUniform3f(cam_pos_uniform, pos.x, pos.y, pos.z);
}

