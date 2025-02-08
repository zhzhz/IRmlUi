#ifndef RMLUI_CONFIG_CONFIG_H
#define RMLUI_CONFIG_CONFIG_H

#include <array>
#include <functional>
#include <list>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Rml {
// Containers types.
template <typename T>
using Vector = std::vector<T>;

// Strings.
using String = std::string;
using StringList = Vector<String>;


}
#endif