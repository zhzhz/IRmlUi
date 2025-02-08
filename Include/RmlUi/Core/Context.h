#ifndef RMLUI_CORE_CONTEXT_H
#define RMLUI_CORE_CONTEXT_H

// #include "Header.h"
// #include "Input.h"
#include "ScriptInterface.h"
// #include "ScrollTypes.h"
// #include "Traits.h"
#include "Types.h"

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
};

} // namespace Rml
#endif
