#pragma once

namespace Meccanoid {

  public ref class Speak sealed {
  public:
    Speak();

    void start(Platform::String ^ text);

  private:
    Windows::Media::SpeechSynthesis::SpeechSynthesizer ^ synthesizer;
    Windows::Media::Playback::MediaPlayer ^ player;
  };
}



