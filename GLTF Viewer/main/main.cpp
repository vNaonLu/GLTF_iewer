#include "..\Viewer\ViewContext.h"

int main() {

	using namespace vNaonScenes;
	CRenderContext *pContext = new CRenderContext("TEST", 800, 600);


	pContext->render();

	return 0;

}