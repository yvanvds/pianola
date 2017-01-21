using Microsoft.Kinect;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Threading;

namespace KinectRecorder
{
  class FrameRecorder
  {
    public static ObservableCollection<TimedFrame> frames;
    private static long recordStartTime;
    private static long playStartTime;
    private static int playIndex;
    public static bool Looping = false;
    private static DispatcherTimer timer;
    private static RecordingPage recordingPage;
    private static Editor editor = null;

    TimedFrame CurrentFrame = new TimedFrame();

    public static Body body = new Body();

    public enum Status
    {
      IDLE,
      WAITING,
      RECORDING,
      PLAYING,
    }

    private static Status currentStatus;

    public static void init(RecordingPage page)
    {
      recordingPage = page;
      body.setDebug(recordingPage.debugWindow);
      frames = new ObservableCollection<TimedFrame>();
      timer = new DispatcherTimer();
      timer.Tick += new EventHandler(OnTimedEvent);
      timer.Interval = new TimeSpan(0, 0, 0, 0, 50);
      currentStatus = Status.IDLE;
    }

    public static void LinkEditor(Editor e)
    {
      editor = e;
    }

    public static void StartRecording()
    {
      StopPlaying();
      frames.Clear();
      currentStatus = Status.WAITING;
    }

    public static void FoundBody()
    {
      recordStartTime = DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
      currentStatus = Status.RECORDING;
    }

    public static void StopRecording()
    {
      currentStatus = Status.IDLE;
    }

    public static Status GetStatus()
    {
      return currentStatus;
    }

    public static void StartPlaying(bool reset = true)
    {
      StopRecording();

      playStartTime = DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond;
      playIndex = 0;

      currentStatus = Status.PLAYING;
      timer.Start();
    }

    public static void StopPlaying()
    {
      if (timer != null && timer.IsEnabled)
      {
        timer.Stop();
      }
      currentStatus = Status.IDLE;
    }

    

    public static void Add(TimedFrame frame)
    {
      frame.Time = (DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond) - recordStartTime;
      frames.Add(new TimedFrame(frame));
    }

    private static void OnTimedEvent(Object source, EventArgs e)
    {
      long elapsed = (DateTime.Now.Ticks / TimeSpan.TicksPerMillisecond) - playStartTime;
      int oldIndex = playIndex;

      while (playIndex < frames.Count && frames[playIndex].Time < elapsed)
      {
        playIndex++; // overshoots by one!
      }

      bool restart = false;

      // check for end of sequence
      if(playIndex == frames.Count)
      {
        if(Looping)
        {
          restart = true;
        } else
        {
          StopPlaying();
          recordingPage.PlayButton.Content = "Play";
          recordingPage.PlayButton.Background = new SolidColorBrush(Color.FromRgb(60, 60, 60));
          recordingPage.RecordButton.IsEnabled = true;
        }
      }

      // go one frame back
      playIndex--;
      if (playIndex < 0) playIndex = 0;
      if(oldIndex != playIndex)
      {
        if(frames[playIndex].Joints.Count > 0)
        {
          body.SetRotations(frames[playIndex], true);
          if (editor != null) editor.SetSelected(playIndex);
        }
      }

      if (restart) StartPlaying();
    }

    public static void saveToFile(Stream stream)
    {
      using (BinaryWriter writer = new BinaryWriter(stream))
      {

        // write number of frames
        writer.Write(Convert.ToInt32(frames.Count));

        // write all frames
        for (int i = 0; i < frames.Count; i++)
        {
          frames[i].save(writer);
        }
      }
    }

    public static void loadFromFile(Stream stream)
    {
      using (BinaryReader reader = new BinaryReader(stream))
      {
        // read number of frames
        int count = reader.ReadInt32();

        // read all frames
        for(int i = 0; i < count; i++)
        {
          frames.Add(new TimedFrame(reader));
        }
      }
    }

    public static bool hasRecording()
    {
      return frames.Count() > 0;
    }

    public static void clear()
    {
      frames.Clear();
    }

    public static void RemoveOffset()
    {
      if(frames.Count > 0)
      {
        long offset = 0;
        if (frames[0].Time > 0)
        {
          offset = frames[0].Time;
        }
        if(offset > 0)
        {
          for(int i = 0; i < frames.Count; i++)
          {
            frames[i].Time -= offset;
          }
        }
      }
    }
  }
}
