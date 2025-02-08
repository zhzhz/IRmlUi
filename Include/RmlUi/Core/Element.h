#ifndef RMLUI_CORE_ELEMENT_H
#define RMLUI_CORE_ELEMENT_H

#include "Types.h"
#include "ScriptInterface.h"
#include "ObserverPtr.h"

namespace Rml {

class RMLUICORE_API Element : public ScriptInterface {
public:
	RMLUI_RTTI_DefineWithParent(Element, ScriptInterface)

	/// Constructs a new RmlUi element. This should not be called directly; use the Factory instead.
	/// @param[in] tag The tag the element was declared as in RML.
	Element(const String& tag);
	virtual ~Element();
};

}
#endif