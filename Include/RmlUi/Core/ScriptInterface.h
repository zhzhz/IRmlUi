#ifndef RMLUI_CORE_SCRIPTINTERFACE_H
#define RMLUI_CORE_SCRIPTINTERFACE_H

#include "Traits.h"
#include "Types.h"

namespace Rml {

class RMLUICORE_API ScriptInterface : public Releasable {
public:
	RMLUI_RTTI_Define(ScriptInterface)

	virtual ~ScriptInterface() {}

	virtual ScriptObject GetScriptObject() const { return nullptr; }
};

} // namespace Rml
#endif
