#include "pch.h"
#include "Speak.h"

using namespace Windows::Media::SpeechSynthesis;
using namespace Windows::Media;
using namespace Platform;
using namespace Concurrency;

Meccanoid::Speak::Speak()
{
  synthesizer = ref new SpeechSynthesizer();
  player = ref new Windows::Media::Playback::MediaPlayer();
}

void Meccanoid::Speak::start(Platform::String ^ text)
{
  create_task(synthesizer->SynthesizeTextToStreamAsync(text), task_continuation_context::use_current())
    .then([this](task<SpeechSynthesisStream^> synthesisStreamTask) {
    try {
      SpeechSynthesisStream ^ synthesisStream = synthesisStreamTask.get();
      
      // play the new stream
      player->AutoPlay = true;
      player->SetStreamSource(synthesisStream);
      player->Play();
    }
    catch (Exception ^ ex) {
      if (ex->HResult == HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND)) {
        // show error message
      }
      else {
        // show another error message
      }
    }
  });
}
