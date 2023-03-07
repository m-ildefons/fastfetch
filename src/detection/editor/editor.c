#include "editor.h"
#include "common/thread.h"
#include "common/processing.h"

#include <stdlib.h>


void getVisual(FFEditorResult* result)
{
  const char* env_visual = getenv("VISUAL");

  if (env_visual != NULL)
  {
    FFstrbuf visual;
    ffStrbufInit(&visual);

    if (!ffProcessAppendStdOut(&visual,
                               (char* const[]) {
                                  (char*) env_visual,
                                  "--version"
                               })
        && visual.length > 0)
    {
      ffStrbufSubstrBeforeFirstC(&visual, '\n');
      ffStrbufInitCopy(&result->visualName, &visual);
      return;
    }
  }

  ffStrbufInit(&result->visualName);
}


void getEditor(FFEditorResult* result)
{
  const char* env_editor = getenv("EDITOR");

  if (env_editor != NULL)
  {
    FFstrbuf editor;
    ffStrbufInit(&editor);

    if (!ffProcessAppendStdOut(&editor,
                               (char* const[]) {
                                  (char*) env_editor,
                                  "--version"
                               })
        && editor.length > 0)
    {
      ffStrbufSubstrBeforeFirstC(&editor, '\n');
      ffStrbufInitCopy(&result->editorName, &editor);
      return;
    }
  }
  ffStrbufInit(&result->editorName);
}

const FFEditorResult* ffDetectEditor(const FFinstance* instance)
{
  FF_UNUSED(instance);

  static FFThreadMutex mutex = FF_THREAD_MUTEX_INITIALIZER;
  static FFEditorResult result;

  ffThreadMutexLock(&mutex);
  getVisual(&result);
  getEditor(&result);
  ffThreadMutexUnlock(&mutex);
  return &result;
}
