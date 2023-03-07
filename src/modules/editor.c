#include "fastfetch.h"
#include "common/printing.h"
#include "detection/editor/editor.h"

#define FF_EDITOR_MODULE_NAME "Editor"
#define FF_EDITOR_NUM_FORMAT_ARGS 2

void ffPrintEditor(FFinstance* instance)
{
  const FFEditorResult* editor = ffDetectEditor(instance);

  if (editor->visualName.length == 0 && editor->editorName.length == 0)
  {
    ffPrintError(instance, FF_EDITOR_MODULE_NAME, 0, &instance->config.editor,
        "neither $VISUAL nor $EDITOR is set.");
    return;
  }

  if (instance->config.editor.outputFormat.length == 0)
  {
    ffPrintLogoAndKey(instance, FF_EDITOR_MODULE_NAME, 0, &instance->config.editor.key);

    FFstrbuf output;
    ffStrbufInit(&output);

    if (editor->visualName.length > 0)
      ffStrbufAppend(&output, &editor->visualName);
    else
      ffStrbufAppend(&output, &editor->editorName);

    ffStrbufPutTo(&output, stdout);
    ffStrbufDestroy(&output);
  }
  else
  {
    ffPrintFormat(instance,
                  FF_EDITOR_MODULE_NAME,
                  0,
                  &instance->config.editor,
                  FF_EDITOR_NUM_FORMAT_ARGS,
                  (FFformatarg[]) {
                    {FF_FORMAT_ARG_TYPE_STRBUF, &editor->visualName},
                    {FF_FORMAT_ARG_TYPE_STRBUF, &editor->editorName}
                  });
  }
}
