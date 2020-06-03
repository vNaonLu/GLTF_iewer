#include "ViewEngine.h"

#include "_DEBUG_OBJECT.hpp"

namespace vnaon_scenes {

	CViewEngine::CViewEngine() {
		_last_engine_time = clock::now();
		_fps = 0.0;
		_p_glcontroller = nullptr;
		test_program = nullptr;

		_init();
	}

	CViewEngine::~CViewEngine() {
		if ( _p_glcontroller != nullptr ) delete _p_glcontroller;
	}

	void CViewEngine::draw() {

		if ( _p_glcontroller == nullptr ) return;
		_clac_fps();

		_p_glcontroller->set_clean_color(vnaon_gl::GLcolor("#000000"));
		_p_glcontroller->clear();

		if ( test_program == nullptr ) {
			test_program = _p_glcontroller->create_shader_program("Test_Shader");
			test_program->attach_vertex_shader_from_file(R"(glsl\sample.vs)");
			test_program->attach_fragment_shader_from_file(R"(glsl\sample.fs)");
			_p_glcontroller->compile_program(test_program);
		}

	}

	void CViewEngine::adjust_viewport(const int &w, const int &h) {
		_p_glcontroller->adjust_viewport(w, h);
	}

	void CViewEngine::_init() {
		_p_glcontroller = new vnaon_gl::GLcontroller();
	}

	void CViewEngine::_clac_fps() {
		using namespace std;
		using namespace std::chrono;
		clock::time_point nowTimePoint = clock::now();
		double timeLag = duration<double, milli>(nowTimePoint - _last_engine_time).count();
		_last_engine_time = nowTimePoint;

		_fps = 1000.0 / timeLag;

		//DEBUGConsole::log({ _fps });
	}

}