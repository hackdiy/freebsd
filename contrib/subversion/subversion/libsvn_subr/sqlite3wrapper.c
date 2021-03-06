/* sqlite3wrapper.c
 *
 * ====================================================================
 *    Licensed to the Apache Software Foundation (ASF) under one
 *    or more contributor license agreements.  See the NOTICE file
 *    distributed with this work for additional information
 *    regarding copyright ownership.  The ASF licenses this file
 *    to you under the Apache License, Version 2.0 (the
 *    "License"); you may not use this file except in compliance
 *    with the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing,
 *    software distributed under the License is distributed on an
 *    "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *    KIND, either express or implied.  See the License for the
 *    specific language governing permissions and limitations
 *    under the License.
 * ====================================================================
 */

#include "svn_private_config.h"

/* Include sqlite3 inline, making all symbols private. */
#ifdef SVN_SQLITE_INLINE
#  define SQLITE_OMIT_DEPRECATED
#  define SQLITE_API static
#  if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 6 || __APPLE_CC__))
#    if !__APPLE_CC__ || __GNUC_MINOR__ >= 6
#      pragma GCC diagnostic push
#    endif
#    pragma GCC diagnostic ignored "-Wunreachable-code"
#    pragma GCC diagnostic ignored "-Wunused-function"
#    pragma GCC diagnostic ignored "-Wcast-qual"
#    pragma GCC diagnostic ignored "-Wunused"
#    pragma GCC diagnostic ignored "-Wshadow"
#    if __APPLE_CC__
#      pragma GCC diagnostic ignored "-Wshorten-64-to-32"
#    endif
#  endif
#  ifdef __APPLE__
#    include <Availability.h>
#    if __MAC_OS_X_VERSION_MIN_REQUIRED < 1060
       /* <libkern/OSAtomic.h> is included on OS X by sqlite3.c, and
          on old systems (Leopard or older), it cannot be compiled
          with -std=c89 because it uses inline. This is a work-around. */
#      define inline __inline__
#      include <libkern/OSAtomic.h>
#      undef inline
#    endif
#  endif
#  define SQLITE_DEFAULT_FILE_PERMISSIONS 0666
#  include <sqlite3.c>
#  if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ >= 6))
#    pragma GCC diagnostic pop
#  endif

/* Expose the sqlite API vtable and the two missing functions */
const sqlite3_api_routines *const svn_sqlite3__api_funcs = &sqlite3Apis;
int (*const svn_sqlite3__api_initialize)(void) = sqlite3_initialize;
int (*const svn_sqlite3__api_config)(int, ...)  = sqlite3_config;
#endif
