/*
  Copyright 2012-2019 David Robillard <http://drobilla.net>

  Permission to use, copy, modify, and/or distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THIS SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/**
   @file types.h Shared internal type definitions.
*/

#ifndef PUGL_DETAIL_TYPES_H
#define PUGL_DETAIL_TYPES_H

#include "pugl/pugl.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Unused parameter macro to suppresses warnings and make it impossible to use
#if defined(__cplusplus) || defined(_MSC_VER)
#   define PUGL_UNUSED(name)
#elif defined(__GNUC__)
#   define PUGL_UNUSED(name) name##_unused __attribute__((__unused__))
#else
#   define PUGL_UNUSED(name)
#endif

/** Platform-specific world internals. */
typedef struct PuglWorldInternalsImpl PuglWorldInternals;

/** Platform-specific view internals. */
typedef struct PuglInternalsImpl PuglInternals;

/** View hints. */
typedef int PuglHints[PUGL_NUM_WINDOW_HINTS];

/** Blob of arbitrary data. */
typedef struct {
	void*  data; //!< Dynamically allocated data
	size_t len;  //!< Length of data in bytes
} PuglBlob;

/** Cross-platform view definition. */
struct PuglViewImpl {
	PuglWorld*         world;
	const PuglBackend* backend;
	PuglInternals*     impl;
	PuglHandle         handle;
	PuglEventFunc      eventFunc;
	char*              title;
	PuglBlob           clipboard;
	PuglNativeWindow   parent;
	uintptr_t          transientParent;
	PuglHints          hints;
	PuglRect           frame;
	int                reqX;
	int                reqY;
	int                reqWidth;
	int                reqHeight;
	int                minWidth;
	int                minHeight;
	int                maxWidth;
	int                maxHeight;
	int                minAspectX;
	int                minAspectY;
	int                maxAspectX;
	int                maxAspectY;
	bool               visible;
};

/** Cross-platform world definition. */
struct PuglWorldImpl {
	PuglWorldInternals* impl;
	char*               className;
	double              startTime;
	PuglProcessFunc     processFunc;
	void*               processUserData;
	size_t              numViews;
	PuglView**          views;
	PuglBlob            clipboard;
};

/** Opaque surface used by graphics backend. */
typedef void PuglSurface;

/** Graphics backend interface. */
struct PuglBackendImpl {
	/** Get visual information from display and setup view as necessary. */
	PuglStatus (*configure)(PuglView*);

	/** Create surface and drawing context. */
	PuglStatus (*create)(PuglView*);

	/** Destroy surface and drawing context. */
	PuglStatus (*destroy)(PuglView*);

	/** Enter drawing context, for drawing if expose is non-null. */
	PuglStatus (*enter)(PuglView*, const PuglEventExpose*);

	/** Leave drawing context, after drawing if expose is non-null. */
	PuglStatus (*leave)(PuglView*, const PuglEventExpose*);

	/** Resize drawing context to the given width and height. */
	PuglStatus (*resize)(PuglView*, int, int);

	/** Return the puglGetContext() handle for the application, if any. */
	void* (*getContext)(PuglView*);
};

#endif // PUGL_DETAIL_TYPES_H
