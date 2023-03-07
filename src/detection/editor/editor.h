#pragma once

#ifndef FF_INCLUDED_detection_editor
#define FF_INCLUDED_detection_editor


#include "fastfetch.h"


typedef struct FFEditorResult
{
  FFstrbuf visualName;
  FFstrbuf editorName;
} FFEditorResult;

const FFEditorResult* ffDetectEditor(const FFinstance* instance);

#endif  // FF_INCLUDED_detection_editor
