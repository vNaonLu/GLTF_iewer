#ifndef STBI_INCLUDE_STB_IMAGE_H
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "..\Viewer\main_context.h"

int main() {

	using namespace vnaon_scenes;
	render_context *pContext = new render_context("TEST", 800, 600);


	pContext->render();

	return 0;

}