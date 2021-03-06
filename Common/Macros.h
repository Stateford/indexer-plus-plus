// This file is the part of the Indexer++ project.
// Copyright (C) 2016 Anna Krykora <krykoraanna@gmail.com>. All rights reserved.
// Use of this source code is governed by a MIT-style license that can be found in the LICENSE file.

#pragma once

#include "CompilerSymb.h"

namespace indexer_common {

#define NO_COPY(classname)                \
        classname(const classname&) = delete; \
        classname& operator=(const classname&) = delete;


#ifdef SINGLE_THREAD

#define NEW_MUTEX
#define DELETE_MUTEX

#define LOCK
#define UNLOCK

#define PLOCK
#define PUNLOCK

#define LOCK_GUARD
#define PLOCK_GUARD

#define UNIQUE_LOCK
#define UNIQUE_UNLOCK

#define NOTIFY_ONE SearchWorker();

#else

#define NEW_MUTEX mtx_ = new std::mutex();
#define DELETE_MUTEX delete mtx_;

#define LOCK mtx_.lock();
#define UNLOCK mtx_.unlock();

#define PLOCK mtx_->lock();
#define PUNLOCK mtx_->unlock();

#define LOCK_GUARD std::lock_guard<std::mutex> locker(mtx_);
#define PLOCK_GUARD std::lock_guard<std::mutex> locker(*mtx_);

#define UNIQUE_LOCK std::unique_lock<std::mutex> locker(mtx_);
#define UNIQUE_UNLOCK locker.unlock();

#define NOTIFY_ONE conditional_var_.notify_one();

#endif // SINGLE_THREAD


#ifdef LIB_EXPORT
#define EXPORT __declspec( dllexport )
#define STL_EXTERN 
#else
#define EXPORT __declspec( dllimport )
#define STL_EXTERN extern
#endif
} // namespace indexer_common