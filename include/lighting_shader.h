
#ifndef _LIGHTING_SHADER_H
#define _LIGHTING_SHADER_H


class tLightingShader : public tShader
{
	protected:
		void InitLightingShader(const char *frag_src, const char *shader_name);

	public:
		static const int vertex_attribute = 0;
};


#endif
