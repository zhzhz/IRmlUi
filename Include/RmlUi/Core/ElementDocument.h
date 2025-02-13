#ifndef RMLUI_CORE_ELEMENTDOCUMENT_H
#define RMLUI_CORE_ELEMENTDOCUMENT_H

#include "Element.h"

namespace Rml {

/** ModalFlag controls the modal state of the document. */
enum class ModalFlag {
	None,  // Remove modal state.
	Modal, // Set modal state, other documents cannot receive focus.
	Keep,  // Modal state unchanged.
};
/** FocusFlag controls the focus when showing the document. */
enum class FocusFlag {
	None,     // No focus.
	Document, // Focus the document.
	Keep,     // Focus the element in the document which last had focus.
	Auto,     // Focus the first tab element with the 'autofocus' attribute or else the document.
};

/**
    Represents a document in the dom tree.

    @author Lloyd Weehuizen
 */

class RMLUICORE_API ElementDocument : public Element {
public:
	RMLUI_RTTI_DefineWithParent(ElementDocument, Element)

	ElementDocument(const String& tag);
	virtual ~ElementDocument();

	void Show(ModalFlag modal_flag = ModalFlag::None, FocusFlag focus_flag = FocusFlag::Auto);
};

} // namespace Rml
#endif
