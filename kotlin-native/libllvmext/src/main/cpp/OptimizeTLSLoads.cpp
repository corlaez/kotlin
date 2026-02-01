// Copyright 2010-2026 JetBrains s.r.o. and Kotlin Programming Language contributors.
// Use of this source code is governed by the Apache 2.0 license that can be found in the license/LICENSE.txt file.

#include "OptimizeTLSLoads.hpp"

#include "llvm/IR/Analysis.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/PassManager.h"

using namespace llvm;

bool kotlin::OptimizeTLSLoadsPass::removeMultipleThreadDataLoads(Function &F) {
  if (F.isDeclaration())
    return false;
  if (!F.getName().starts_with("kfun:"))
    return false;
  return true;
}

PreservedAnalyses kotlin::OptimizeTLSLoadsPass::run(Function &F, FunctionAnalysisManager &) {
  if (!removeMultipleThreadDataLoads(F))
    return PreservedAnalyses::all();
  return PreservedAnalyses::none();
}
