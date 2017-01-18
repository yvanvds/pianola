using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Forms;
using LightBuzz.Vitruvius;
using Microsoft.Kinect;
using System.Net;
using Rug.Osc;
using System.IO;

namespace KinectRecorder
{
  /// <summary>
  /// Interaction logic for RecordingPage.xaml
  /// </summary>
  public partial class RecordingPage : Page
  {
    SaveFileDialog saveFileDialog = new SaveFileDialog();
    OpenFileDialog openFileDialog = new OpenFileDialog();
    readonly string FOLDER_PATH = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "recordings");

    KinectSensor _sensor = null;
    MultiSourceFrameReader _reader = null;
    PlayersController _playersController;
    TimedFrame currentFrame = new TimedFrame();

    public SolidColorBrush boneBrush;

    public DebugWindow debugWindow = new DebugWindow();

    public RecordingPage()
    {
      InitializeComponent();

      _sensor = KinectSensor.GetDefault();

      if(_sensor != null)
      {
        _sensor.Open();
        _reader = _sensor.OpenMultiSourceFrameReader(FrameSourceTypes.Color | FrameSourceTypes.Depth | FrameSourceTypes.Infrared | FrameSourceTypes.Body);
        _reader.MultiSourceFrameArrived += Reader_MultiSourceFrameArrived;

        _playersController = new PlayersController();
        _playersController.BodyEntered += UserReporter_BodyEntered;
        _playersController.BodyLeft += UserReporter_BodyLeft;
        _playersController.Start();

        saveFileDialog.InitialDirectory = FOLDER_PATH;
        saveFileDialog.Filter = "kinect data files |*.kdf";
        saveFileDialog.RestoreDirectory = true;
        saveFileDialog.OverwritePrompt = true;

        openFileDialog.InitialDirectory = FOLDER_PATH;
        openFileDialog.Filter = "kinect data files |*.kdf";
        openFileDialog.RestoreDirectory = true;
      }

      boneBrush = new SolidColorBrush(Color.FromRgb(0, 255, 0));

      FrameRecorder.init(this);

      debugWindow.Show();
    }

    private void Page_Unloaded(object sender, RoutedEventArgs e)
    {
      if(_playersController != null)
      {
        _playersController.Stop();
      }

      if (_reader != null)
      {
        _reader.Dispose();
      }

      if (_sensor != null)
      {
        _sensor.Close();
      }
    }

    void Reader_MultiSourceFrameArrived(object sender, MultiSourceFrameArrivedEventArgs e)
    {
      if (FrameRecorder.GetStatus() == FrameRecorder.Status.PLAYING) return;

      if (FrameRecorder.GetStatus() == FrameRecorder.Status.RECORDING || FrameRecorder.GetStatus() == FrameRecorder.Status.WAITING)
      {
        var reference = e.FrameReference.AcquireFrame();

        // color
        using (var frame = reference.ColorFrameReference.AcquireFrame())
        {
          if (frame != null)
          {
            if (viewer.Visualization == Visualization.Color)
            {
              viewer.Image = frame.ToBitmap();
            }
          }
        }

        // body
        using (var frame = reference.BodyFrameReference.AcquireFrame())
        {
          if (frame != null)
          {
            var bodies = frame.Bodies();
            _playersController.Update(bodies);
            Microsoft.Kinect.Body body = bodies.Closest();

            if (body != null)
            {
              if(FrameRecorder.GetStatus() == FrameRecorder.Status.WAITING)
              {
                RecordButton.Content = "Recording...";
                RecordButton.Background = new SolidColorBrush(Color.FromRgb(252, 47, 32));
                FrameRecorder.FoundBody();
              }

              viewer.DrawBody(body, 15, boneBrush, 5, boneBrush);
              currentFrame.set(body);
              FrameRecorder.Add(currentFrame);
              FrameRecorder.body.SetRotations(currentFrame, true);

              

            }
          }
        }
      }

      else 
      {
        var reference = e.FrameReference.AcquireFrame();

        // Color
        using (var frame = reference.ColorFrameReference.AcquireFrame())
        {
          if (frame != null)
          {
            if(viewer.Visualization == Visualization.Color)
            {
              viewer.Image = frame.ToBitmap();
            }
          }
        }

        // body
        using (var frame = reference.BodyFrameReference.AcquireFrame())
        {
          if (frame != null)
          {
            var bodies = frame.Bodies();
            _playersController.Update(bodies);

            var body = bodies.Closest();
            if (body != null)
            {
              viewer.DrawBody(body, 15, boneBrush, 5, boneBrush);
              currentFrame.set(body);
              FrameRecorder.body.SetRotations(currentFrame, true);

              Vec2 spineShoulderXY = currentFrame.getXY(JointType.SpineShoulder);
              Vec2 spineShoulderXZ = currentFrame.getXZ(JointType.SpineShoulder);
              Vec2 elbowXY = currentFrame.getXY(JointType.ElbowLeft);
              Vec2 shoulderXY = currentFrame.getXY(JointType.ShoulderLeft);
              Vec2 elbowXZ = currentFrame.getXZ(JointType.ElbowLeft);
              Vec2 shoulderXZ = currentFrame.getXZ(JointType.ShoulderLeft);

              elbowXY.x = elbowXY.x - spineShoulderXY.x;
              elbowXY.y = elbowXY.y - spineShoulderXY.y;
              shoulderXY.x -= spineShoulderXY.x;
              shoulderXY.y -= spineShoulderXY.y;

              elbowXZ.x = elbowXZ.x - spineShoulderXZ.x;
              elbowXZ.y = elbowXZ.y - spineShoulderXZ.y;
              shoulderXZ.x -= spineShoulderXZ.x;
              shoulderXZ.y -= spineShoulderXZ.y;

              DebugText1.Text = Vec2.GetAngle(shoulderXY, elbowXY).ToDegrees().ToString();
              DebugText2.Text = Vec2.GetAngle(shoulderXZ, elbowXZ).ToDegrees().ToString();
            }
            else viewer.Clear();
          }
          else viewer.Clear();
        }
      }
    }

    private void Record_Click(object sender, RoutedEventArgs e)
    {
      if(FrameRecorder.GetStatus() == FrameRecorder.Status.IDLE)
      {
        FrameRecorder.StartRecording();
        RecordButton.Content = "Waiting...";
        RecordButton.Background = new SolidColorBrush(Color.FromRgb(244, 152, 66));
        PlayButton.IsEnabled = false;
        viewer.Clear();
      } else
      {
        FrameRecorder.StopRecording();
        RecordButton.Content = "Record";
        RecordButton.Background = new SolidColorBrush(Color.FromRgb(60, 60, 60));
        PlayButton.IsEnabled = true;
        viewer.Clear();
      }
    }

    private void Edit_Click(object sender, RoutedEventArgs e)
    {
      if(!FrameRecorder.hasRecording())
      {
        System.Windows.Forms.MessageBox.Show("No data available.");
        return;
      }
      Editor editor = new Editor();
      editor.SetParent(this);
      editor.Show();
    }

    private void Clear_Click(object sender, RoutedEventArgs e)
    {
      DialogResult result = System.Windows.Forms.MessageBox.Show("Are You Sure?", "This will remove the current recording.", MessageBoxButtons.YesNo);
      if(result == DialogResult.Yes) FrameRecorder.clear();
    }

    void UserReporter_BodyEntered(object sender, PlayersControllerEventArgs e) { }

    void UserReporter_BodyLeft(object sender, PlayersControllerEventArgs e)
    {
      viewer.Clear();
      angle1.Clear();
      angle2.Clear();
      angle3.Clear();
    }

    private void Playback_Click(object sender, RoutedEventArgs e)
    {
      if(FrameRecorder.GetStatus() == FrameRecorder.Status.IDLE)
      {
        FrameRecorder.StartPlaying();
        PlayButton.Content = "Playing...";
        PlayButton.Background = new SolidColorBrush(Color.FromRgb(83, 219, 99));
        RecordButton.IsEnabled = false;
        viewer.Clear();
      } else
      {
        FrameRecorder.StopPlaying();
        PlayButton.Content = "Play";
        PlayButton.Background = new SolidColorBrush(Color.FromRgb(60,60,60));
        RecordButton.IsEnabled = true;
      }
      

    }

    private void Save_Click(object sender, RoutedEventArgs e)
    {
      if (FrameRecorder.GetStatus() != FrameRecorder.Status.IDLE) return;

      Stream stream = null;

      if(saveFileDialog.ShowDialog() == DialogResult.OK)
      {
        try
        {
          if((stream = saveFileDialog.OpenFile()) != null)
          {
            FrameRecorder.saveToFile(stream);
          }
        }
        catch (Exception ex)
        {
          System.Windows.Forms.MessageBox.Show("Error: Could not write to file. Original Error: " + ex.Message);
        }
      }


    }

    private void Load_Click(object sender, RoutedEventArgs e)
    {
      if (FrameRecorder.GetStatus() != FrameRecorder.Status.IDLE) return;

      if (FrameRecorder.hasRecording())
      {
        DialogResult result = System.Windows.Forms.MessageBox.Show("Are You Sure?", "This will remove the current recording.", MessageBoxButtons.YesNo);
        if (result == DialogResult.No) return;
      }

      Stream stream = null;

      if(openFileDialog.ShowDialog() == DialogResult.OK)
      {
        try
        {
          if ((stream = openFileDialog.OpenFile()) != null)
          {
            FrameRecorder.loadFromFile(stream);
          }
        }
        catch (Exception ex)
        {
          System.Windows.Forms.MessageBox.Show("Error: Could not read from file. Original Error: " + ex.Message);
        }
      }
    }

  }
}
