#ifndef RMLUI_CORE_CORE_H
#define RMLUI_CORE_CORE_H


#include "Header.h"
#include "Types.h"

namespace Rml {
class Context;
class RenderInterface;
class SystemInterface;

/**
    RmlUi library core API.

    @author Peter Curry
 */

/// Initialises RmlUi.
RMLUICORE_API bool Initialise();
/// Shutdown RmlUi.
RMLUICORE_API void Shutdown();



/// Sets the interface through which all system requests are made. This is not required to be called, but if it is it
/// must be called before Initialise().
/// @param[in] system_interface A non-owning pointer to the application-specified logging interface.
/// @lifetime The interface must be kept alive until after the call to Rml::Shutdown.
RMLUICORE_API void SetSystemInterface(SystemInterface* system_interface);
/// Returns RmlUi's system interface.


/// Sets the interface through which all rendering requests are made. This is not required to be called, but if it is,
/// it must be called before Initialise(). If no render interface is specified, then all contexts must specify a render
/// interface when created.
/// @param[in] render_interface A non-owning pointer to the render interface implementation.
/// @lifetime The interface must be kept alive until after the call to Rml::Shutdown.
RMLUICORE_API void SetRenderInterface(RenderInterface* render_interface);


/// Creates a new element context.
/// @param[in] name The new name of the context. This must be unique.
/// @param[in] dimensions The initial dimensions of the new context.
/// @param[in] render_interface The custom render interface to use, or nullptr to use the default.
/// @param[in] text_input_handler The custom text input handler to use, or nullptr to use the default.
/// @lifetime If specified, the render interface and the text input handler must be kept alive until after the call to
///           Rml::Shutdown. Alternatively, the render interface can be destroyed after all contexts it belongs to have been
///           destroyed and a subsequent call has been made to Rml::ReleaseRenderManagers.
/// @return A non-owning pointer to the new context, or nullptr if the context could not be created.
RMLUICORE_API Context* CreateContext(const String& name, Vector2i dimensions, RenderInterface* render_interface = nullptr);


} // namespace Rml

#endif
