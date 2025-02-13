#ifndef RMLUI_CORE_TYPES_H
#define RMLUI_CORE_TYPES_H

#include "../Config/Config.h"
#include "Traits.h"
#include <cstdlib>
#include <memory>
#include <stddef.h>
#include <stdint.h>
#include "Vector2.h"

namespace Rml {

// Commonly used basic types
using byte = unsigned char;
using ScriptObject = void*;

enum class Character : char32_t { Null, Replacement = 0xfffd }; // Unicode code point
enum class BoxArea { Margin, Border, Padding, Content, Auto };

class Element;

// Color and linear algebra

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;



} // namespace std

#endif
