#include "scenes_skybox.h"



namespace vnaon_scenes {

	ScenesSkyBox::ScenesSkyBox() : ScenesEntity() {
		ready_to_draw = false;
		ReleaseResource();
	}
	ScenesSkyBox::~ScenesSkyBox() {
	}

	void ScenesSkyBox::Init(vnaon_gl::GLManager *parg_gl) {
		ready_to_draw = true;
		ready_to_draw |= InitProgram(parg_gl);
		ready_to_draw |= InitTexture(parg_gl);
		ready_to_draw |= InitBuffer(parg_gl);
	}

	void ScenesSkyBox::ReleaseResource() {
		p_vertex_array = nullptr;
		GLTexture_p = nullptr;
		p_skybox_shaderprogram = nullptr;
	}

	ScenesEntity_p ScenesSkyBox::Create() {
		return std::make_shared<ScenesSkyBox>();
	}

	void ScenesSkyBox::MainDraw(vnaon_gl::GLManager *parg_gl, const vnaon_common::Camera &carg_camera) {
		parg_gl->UseProgram(p_skybox_shaderprogram);
		parg_gl->BindSkybox(GLTexture_p);
		parg_gl->BindVertexArray(p_vertex_array);
		glm::mat4 translate = carg_camera.GetRTCMatrix(glm::vec3(0.0));
		glm::mat4 scale = glm::scale(glm::mat4(1.0), glm::vec3(glm::length(carg_camera.GetPosition()) * 10.0f));
		glm::mat4 mvp_matrix = carg_camera.GetViewProjectiveMatrix() * translate;
		p_skybox_shaderprogram->GetUnifrom("u_ProjViewModel")->SetValue(glm::value_ptr(mvp_matrix));
		parg_gl->DrawArrays(GL_TRIANGLES, 0, 36);
		parg_gl->UnbindVertexArray();
	}

	bool ScenesSkyBox::ReadyToDraw(vnaon_gl::GLManager *parg_gl) {
		return ready_to_draw;
	}

	bool ScenesSkyBox::InitProgram(vnaon_gl::GLManager *parg_gl) {
		p_skybox_shaderprogram = parg_gl->CreateProgram("sky_shader");
		p_skybox_shaderprogram->AttachVertexShaderFromFile(R"(glsl\skybox.vs)");
		p_skybox_shaderprogram->AttachFragmentShaderFromFile(R"(glsl\skybox.fs)");
		return parg_gl->CompileProgram(p_skybox_shaderprogram);
	}

	bool ScenesSkyBox::InitTexture(vnaon_gl::GLManager *parg_gl) {

		GLTexture_p = parg_gl->CreateSkyBoxFromFile(
			std::vector<std::string>{
				R"(image\right.jpg)",
				R"(image\left.jpg)",
				R"(image\top.jpg)",
				R"(image\bottom.jpg)",
				R"(image\back.jpg)",
				R"(image\front.jpg)"
			}
		);
		return GLTexture_p != nullptr;
	}

	bool ScenesSkyBox::InitBuffer(vnaon_gl::GLManager *parg_gl) {

		float skybox_vertex_binary[] = {
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		auto vert_buf = parg_gl->CreateVertexBuffer(GL_STATIC_DRAW, skybox_vertex_binary, 108 * sizeof(float));
		
		p_vertex_array = parg_gl->CreateVertexArray();
		parg_gl->SetVertexArray(p_vertex_array, vnaon_gl::GLManager::VertexAttributes{
			{vert_buf, 0, 3, GL_FLOAT, GL_FALSE, 0, 0}
			}
		);

		return p_vertex_array != nullptr;
	}

}