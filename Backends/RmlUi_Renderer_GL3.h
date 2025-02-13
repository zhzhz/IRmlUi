#ifndef RMLUI_BACKENDS_RENDERER_GL3_H
#define RMLUI_BACKENDS_RENDERER_GL3_H

#include "../Include/RmlUi/Core/RenderInterface.h"
#include "../Include/RmlUi/Core/Types.h"
#include <bitset>


class RenderInterface_GL3 : public Rml::RenderInterface {
public:
	RenderInterface_GL3();
	~RenderInterface_GL3();
};


#endif