/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_RUNTIME_GC_SPACE_BUMP_POINTER_SPACE_INL_H_
#define ART_RUNTIME_GC_SPACE_BUMP_POINTER_SPACE_INL_H_

#include <museum/8.1.0/art/runtime/gc/space/bump_pointer_space.h>

#include <museum/8.1.0/art/runtime/base/bit_utils.h>

namespace facebook { namespace museum { namespace MUSEUM_VERSION { namespace art {
namespace gc {
namespace space {

inline mirror::Object* BumpPointerSpace::Alloc(Thread*, size_t num_bytes, size_t* bytes_allocated,
                                               size_t* usable_size,
                                               size_t* bytes_tl_bulk_allocated) {
  num_bytes = RoundUp(num_bytes, kAlignment);
  mirror::Object* ret = AllocNonvirtual(num_bytes);
  if (LIKELY(ret != nullptr)) {
    *bytes_allocated = num_bytes;
    if (usable_size != nullptr) {
      *usable_size = num_bytes;
    }
    *bytes_tl_bulk_allocated = num_bytes;
  }
  return ret;
}

inline mirror::Object* BumpPointerSpace::AllocThreadUnsafe(Thread* self, size_t num_bytes,
                                                           size_t* bytes_allocated,
                                                           size_t* usable_size,
                                                           size_t* bytes_tl_bulk_allocated) {
  Locks::mutator_lock_->AssertExclusiveHeld(self);
  num_bytes = RoundUp(num_bytes, kAlignment);
  uint8_t* end = end_.LoadRelaxed();
  if (end + num_bytes > growth_end_) {
    return nullptr;
  }
  mirror::Object* obj = reinterpret_cast<mirror::Object*>(end);
  end_.StoreRelaxed(end + num_bytes);
  *bytes_allocated = num_bytes;
  // Use the CAS free versions as an optimization.
  objects_allocated_.StoreRelaxed(objects_allocated_.LoadRelaxed() + 1);
  bytes_allocated_.StoreRelaxed(bytes_allocated_.LoadRelaxed() + num_bytes);
  if (UNLIKELY(usable_size != nullptr)) {
    *usable_size = num_bytes;
  }
  *bytes_tl_bulk_allocated = num_bytes;
  return obj;
}

inline mirror::Object* BumpPointerSpace::AllocNonvirtualWithoutAccounting(size_t num_bytes) {
  DCHECK_ALIGNED(num_bytes, kAlignment);
  uint8_t* old_end;
  uint8_t* new_end;
  do {
    old_end = end_.LoadRelaxed();
    new_end = old_end + num_bytes;
    // If there is no more room in the region, we are out of memory.
    if (UNLIKELY(new_end > growth_end_)) {
      return nullptr;
    }
  } while (!end_.CompareExchangeWeakSequentiallyConsistent(old_end, new_end));
  return reinterpret_cast<mirror::Object*>(old_end);
}

inline mirror::Object* BumpPointerSpace::AllocNonvirtual(size_t num_bytes) {
  mirror::Object* ret = AllocNonvirtualWithoutAccounting(num_bytes);
  if (ret != nullptr) {
    objects_allocated_.FetchAndAddSequentiallyConsistent(1);
    bytes_allocated_.FetchAndAddSequentiallyConsistent(num_bytes);
  }
  return ret;
}

}  // namespace space
}  // namespace gc
} } } } // namespace facebook::museum::MUSEUM_VERSION::art

#endif  // ART_RUNTIME_GC_SPACE_BUMP_POINTER_SPACE_INL_H_
