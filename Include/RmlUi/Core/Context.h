#ifndef RMLUI_CORE_CONTEXT_H
#define RMLUI_CORE_CONTEXT_H

// #include "Header.h"
// #include "Input.h"
#include "ScriptInterface.h"
// #include "ScrollTypes.h"
// #include "Traits.h"
#include "Types.h"
#include "ID.h"

namespace Rml {

// class Stream;
// class ContextInstancer;
class ElementDocument;
// class EventListener;
// class DataModel;
// class DataModelConstructor;
// class DataTypeRegister;
// class ScrollController;
class RenderManager;
class TextInputHandler;
// enum class EventId : uint16_t;

/**
    A context for storing, rendering and processing RML documents. Multiple contexts can exist simultaneously.

    @author Peter Curry
 */

class RMLUICORE_API Context : public ScriptInterface {
public:
	/// Constructs a new, uninitialised context. This should not be called directly, use CreateContext() instead.
	/// @param[in] name The name of the context.
	/// @param[in] render_manager The render manager used for this context.
	/// @param[in] text_input_handler The text input handler used for this context.
	Context(const String& name, RenderManager* render_manager);
	/// Destroys a context.
	virtual ~Context();

	/// Updates all elements in the context's documents.
	/// This must be called before Context::Render, but after any elements have been changed, added or removed.
	bool Update();
	/// Renders all visible elements in the context's documents.
	bool Render();


	ElementDocument* LoadDocument(const String& document_path);
	/// Load a document into the context.
	/// @param[in] document_stream The opened stream, ready to read.
	/// @return The loaded document, or nullptr if no document was loaded.

	//处理鼠标移动事件
	bool ProcessMouseMove(int x, int y);

	Element* GetElementAtPoint(Vector2f point, const Element* ignore_element = nullptr, Element* element = nullptr) const;

private:
// Input state; stored from the most recent input events we receive from the application.
	Vector2i mouse_position;
	bool mouse_active;

	Element* hover;

	void UpdateHoverChain(Vector2i old_mouse_position);

	using ElementSet = SmallOrderedSet<Element*>;

	ElementSet hover_chain;

	static void SendEvents(const ElementSet& old_items, const ElementSet& new_items, EventId id);
};

} // namespace Rml
#endif
