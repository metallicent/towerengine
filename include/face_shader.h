
#ifndef _FACE_SHADER_H
#define _FACE_SHADER_H

class CFaceShader : public CShader
{
	private:
		GLint shader_mode_uniform;

		GLint transformation_uniform;

		GLint two_side_uniform;

		GLint diffuse_color_uniform;
		GLint diffuse_color2_uniform;
		GLint specular_color_uniform;
		GLint ambient_uniform;

		GLint light_pos_uniform;
		GLint light_color_uniform;
		GLint light_ambient_color_uniform;

		GLint specular_size_uniform; // TODO: in exponent umbenennen

		GLint shadow_map_uniform;
		GLint shadow_enabled_uniform;
		GLint shadow_pixel_uniform;

		GLint diffuse_tex_enabled_uniform;
		GLint normal_tex_enabled_uniform;
		GLint height_tex_enabled_uniform;
		GLint specular_tex_enabled_uniform;

		GLint diffuse_tex_uniform;
		GLint normal_tex_uniform;
		GLint height_tex_uniform;
		GLint specular_tex_uniform;

		GLint tex_border_uniform;
		GLint discard_border_uniform;

		GLint height_factor_uniform;
		GLint bump_factor_uniform;

		GLint fog_color_uniform;
		GLint fog_depth_uniform;
		GLint fog_dist_uniform;

		GLint clip_uniform;
		GLint clip_dist_uniform;

	public:
		static const GLint vertex_attribute = 0;
		static const GLint normal_attribute = 1;
		static const GLint tang_attribute = 2;
		static const GLint bitang_attribute = 3;
		static const GLint uvcoord_attribute = 4;
		void Init(void);

		void SetMode(int e); // disables or enables calculation of the color to speed up e.g. shadow mapping
		void SetClip(CVector c, float d);
		void SetDiffuseColor(CVector color);
		void SetDiffuseColor2(CVector color, float alpha);
		void SetSpecularColor(CVector color);
		void SetAmbient(float ambient);
		void SetLight(CVector pos, CVector color);
		void SetLightAmbientColor(CVector color);
		void SetSpecular(float size);
		void SetDiffuseTexture(bool enabled, GLuint tex = 0);
		void SetSpecularTexture(bool enabled, GLuint tex = 0);
		void SetNormalTexture(bool enabled, GLuint tex = 0);
		void SetHeightTexture(bool enabled, GLuint tex = 0);
		void SetBorder(int e, CVector2 a, CVector2 b);
		void SetTexCoord(CVector2 coord);
		void SetVectors(CVector normal, CVector tangx, CVector tangy, CVector fnormal = Vec(0.0, 0.0, 0.0));
		void SetHeightFactor(CVector factor);
		void SetBumpFactor(float f);
		void SetFog(CVector color, float depth, float dist);
		void SetTwoSide(int v);
		void SetShadow(int enabled, GLuint tex, CVector2 pixel);
		void SetTransformation(float m[16]);
		void ResetUniforms(void);
};

extern int shader_enabled;

#endif
