#include "scenes_engine.h"
#include "gl_program.h"
#include "gl_entity.h"
#include "scenes_skybox.h"



#include "debug_tools.hpp"



namespace vnaon_scenes {

	ScenesEngine::ScenesEngine() {
		_p_glcontroller = nullptr;
		_near = 0.1;
		_far = 10.0;

		_first_render = true;
		entities.clear();

		Init();
	}

	ScenesEngine::~ScenesEngine() {
		if ( _p_glcontroller != nullptr ) delete _p_glcontroller;
	}

	void ScenesEngine::Draw(glm::ivec2 arg_viewport, glm::vec3 arg_frustum_pos) {
		SetCamera(arg_viewport, arg_frustum_pos, _near, _far);

		if ( _p_glcontroller == nullptr ) return;

		if ( _first_render ) {
			_first_render = false;
			InitRender();
		}

		_p_glcontroller->AdjustViewport(arg_viewport.x, arg_viewport.y);
		_p_glcontroller->SetClearColor(vnaon_gl::GLColor("#505050"));
		_p_glcontroller->Clear();

		for ( auto entity : entities ) {
			entity->DrawScenes(_p_glcontroller, _camera);
		}

	}

	void ScenesEngine::Init() {
		_p_glcontroller = new vnaon_gl::GLManager();

		entities.push_back(ScenesSkyBox::Create());
	}

	void ScenesEngine::SetCamera(glm::ivec2 arg_viewport, glm::vec3 arg_pos, double arg_near, double arg_far){
		if ( arg_viewport.y > 0 ) {
			_camera.SetPosition(arg_pos);
			_camera.SetPerspective(45.0, (double) arg_viewport.x / (double) arg_viewport.y, arg_near, arg_far);
		}
	}

	void ScenesEngine::InitRender() {
		for ( auto entity : entities )
			entity->Init(_p_glcontroller);
	}

}