/* Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

#include <map>
#include <memory>
#include <vector>

#include "paddle/fluid/framework/ir/graph.h"
#include "paddle/fluid/framework/ir/node.h"

namespace paddle {
namespace framework {
namespace ir {

// Test if the graph contains circle.
bool HasCircle(const Graph &graph);

size_t GraphNum(const Graph &graph);

// Topology Sort the operations in the graph from inputs to outputs.
// `graph` cannot contain circle.
std::vector<ir::Node *> TopologySortOperations(const Graph &graph);

// Build an adjacency list of operations for the `graph`.
std::map<ir::Node *, std::unordered_set<ir::Node *>> BuildOperationAdjList(
    const Graph &graph);

template <typename T>
std::vector<T *> FilterByNodeWrapper(const Graph &graph) {
  std::vector<T *> ret;
  for (ir::Node *n : graph.Nodes()) {
    if (n->IsWrappedBy<T>()) ret.push_back(&n->Wrapper<T>());
  }
  return ret;
}

}  // namespace ir
}  // namespace framework
}  // namespace paddle
