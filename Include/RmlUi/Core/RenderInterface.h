#ifndef RMLUI_CORE_RENDERINTERFACE_H
#define RMLUI_CORE_RENDERINTERFACE_H

#include "Header.h"
#include "Traits.h"
#include "Types.h"

namespace Rml {

class RMLUICORE_API RenderInterface : public NonCopyMoveable {
public:
	RenderInterface();
	virtual ~RenderInterface();
};

}

#endif