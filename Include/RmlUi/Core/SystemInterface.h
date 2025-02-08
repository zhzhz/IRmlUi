#ifndef RMLUI_CORE_SYSTEMINTERFACE_H
#define RMLUI_CORE_SYSTEMINTERFACE_H

#include "Header.h"
#include "Traits.h"
#include "Types.h"

namespace Rml {

class RMLUICORE_API SystemInterface : public NonCopyMoveable {
public:
	SystemInterface();
	virtual ~SystemInterface();
};

} // namespace Rml
#endif
