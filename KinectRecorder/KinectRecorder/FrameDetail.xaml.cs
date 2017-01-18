using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace KinectRecorder
{
  /// <summary>
  /// Interaction logic for FrameDetail.xaml
  /// </summary>
  public partial class FrameDetail : Window
  {
    int frameIndex;

    public FrameDetail(int frameIndex)
    {
      InitializeComponent();
      SetIndex(frameIndex);
    }

   private void SetIndex(int frameIndex) { 
      this.frameIndex = frameIndex;
      btnPreviousFrame.IsEnabled = false;
      btnNextFrame.IsEnabled = false;

      // set Previous Frame content
      if(frameIndex > 0)
      {
        previousHeadX.SetBinding(TextBox.TextProperty, new Binding("HeadX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousHeadY.SetBinding(TextBox.TextProperty, new Binding("HeadY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousHeadZ.SetBinding(TextBox.TextProperty, new Binding("HeadZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousNeckX.SetBinding(TextBox.TextProperty, new Binding("NeckX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousNeckY.SetBinding(TextBox.TextProperty, new Binding("NeckY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousNeckZ.SetBinding(TextBox.TextProperty, new Binding("NeckZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousSpineShoulderX.SetBinding(TextBox.TextProperty, new Binding("SpineShoulderX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousSpineShoulderY.SetBinding(TextBox.TextProperty, new Binding("SpineShoulderY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousSpineShoulderZ.SetBinding(TextBox.TextProperty, new Binding("SpineShoulderZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousSpineMidX.SetBinding(TextBox.TextProperty, new Binding("SpineMidX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousSpineMidY.SetBinding(TextBox.TextProperty, new Binding("SpineMidY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousSpineMidZ.SetBinding(TextBox.TextProperty, new Binding("SpineMidZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousSpineBaseX.SetBinding(TextBox.TextProperty, new Binding("SpineBaseX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousSpineBaseY.SetBinding(TextBox.TextProperty, new Binding("SpineBaseY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousSpineBaseZ.SetBinding(TextBox.TextProperty, new Binding("SpineBaseZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousLeftShoulderX.SetBinding(TextBox.TextProperty, new Binding("LeftShoulderX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftShoulderY.SetBinding(TextBox.TextProperty, new Binding("LeftShoulderY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftShoulderZ.SetBinding(TextBox.TextProperty, new Binding("LeftShoulderZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousLeftElbowX.SetBinding(TextBox.TextProperty, new Binding("LeftElbowX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftElbowY.SetBinding(TextBox.TextProperty, new Binding("LeftElbowY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftElbowZ.SetBinding(TextBox.TextProperty, new Binding("LeftElbowZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousLeftWristX.SetBinding(TextBox.TextProperty, new Binding("LeftWristX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftWristY.SetBinding(TextBox.TextProperty, new Binding("LeftWristY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftWristZ.SetBinding(TextBox.TextProperty, new Binding("LeftWristZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousLeftHandX.SetBinding(TextBox.TextProperty, new Binding("LeftHandX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftHandY.SetBinding(TextBox.TextProperty, new Binding("LeftHandY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftHandZ.SetBinding(TextBox.TextProperty, new Binding("LeftHandZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousRightShoulderX.SetBinding(TextBox.TextProperty, new Binding("RightShoulderX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightShoulderY.SetBinding(TextBox.TextProperty, new Binding("RightShoulderY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightShoulderZ.SetBinding(TextBox.TextProperty, new Binding("RightShoulderZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousRightElbowX.SetBinding(TextBox.TextProperty, new Binding("RightElbowX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightElbowY.SetBinding(TextBox.TextProperty, new Binding("RightElbowY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightElbowZ.SetBinding(TextBox.TextProperty, new Binding("RightElbowZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousRightWristX.SetBinding(TextBox.TextProperty, new Binding("RightWristX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightWristY.SetBinding(TextBox.TextProperty, new Binding("RightWristY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightWristZ.SetBinding(TextBox.TextProperty, new Binding("RightWristZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousRightHandX.SetBinding(TextBox.TextProperty, new Binding("RightHandX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightHandY.SetBinding(TextBox.TextProperty, new Binding("RightHandY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightHandZ.SetBinding(TextBox.TextProperty, new Binding("RightHandZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousLeftHipX.SetBinding(TextBox.TextProperty, new Binding("LeftHipX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftHipY.SetBinding(TextBox.TextProperty, new Binding("LeftHipY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftHipZ.SetBinding(TextBox.TextProperty, new Binding("LeftHipZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousLeftKneeX.SetBinding(TextBox.TextProperty, new Binding("LeftKneeX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftKneeY.SetBinding(TextBox.TextProperty, new Binding("LeftKneeY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftKneeZ.SetBinding(TextBox.TextProperty, new Binding("LeftKneeZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousLeftAnkleX.SetBinding(TextBox.TextProperty, new Binding("LeftAnkleX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftAnkleY.SetBinding(TextBox.TextProperty, new Binding("LeftAnkleY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftAnkleZ.SetBinding(TextBox.TextProperty, new Binding("LeftAnkleZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousLeftFootX.SetBinding(TextBox.TextProperty, new Binding("LeftFootX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftFootY.SetBinding(TextBox.TextProperty, new Binding("LeftFootY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousLeftFootZ.SetBinding(TextBox.TextProperty, new Binding("LeftFootZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousRightHipX.SetBinding(TextBox.TextProperty, new Binding("RightHipX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightHipY.SetBinding(TextBox.TextProperty, new Binding("RightHipY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightHipZ.SetBinding(TextBox.TextProperty, new Binding("RightHipZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousRightKneeX.SetBinding(TextBox.TextProperty, new Binding("RightKneeX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightKneeY.SetBinding(TextBox.TextProperty, new Binding("RightKneeY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightKneeZ.SetBinding(TextBox.TextProperty, new Binding("RightKneeZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousRightAnkleX.SetBinding(TextBox.TextProperty, new Binding("RightAnkleX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightAnkleY.SetBinding(TextBox.TextProperty, new Binding("RightAnkleY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightAnkleZ.SetBinding(TextBox.TextProperty, new Binding("RightAnkleZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        previousRightFootX.SetBinding(TextBox.TextProperty, new Binding("RightFootX") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightFootY.SetBinding(TextBox.TextProperty, new Binding("RightFootY") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });
        previousRightFootZ.SetBinding(TextBox.TextProperty, new Binding("RightFootZ") { Source = FrameRecorder.frames[frameIndex - 1], StringFormat="0.####" });

        btnPreviousFrame.IsEnabled = true;
      }

      // set current frame
      currentHeadX.SetBinding(TextBox.TextProperty, new Binding("HeadX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentHeadY.SetBinding(TextBox.TextProperty, new Binding("HeadY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentHeadZ.SetBinding(TextBox.TextProperty, new Binding("HeadZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentNeckX.SetBinding(TextBox.TextProperty, new Binding("NeckX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentNeckY.SetBinding(TextBox.TextProperty, new Binding("NeckY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentNeckZ.SetBinding(TextBox.TextProperty, new Binding("NeckZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentSpineShoulderX.SetBinding(TextBox.TextProperty, new Binding("SpineShoulderX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentSpineShoulderY.SetBinding(TextBox.TextProperty, new Binding("SpineShoulderY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentSpineShoulderZ.SetBinding(TextBox.TextProperty, new Binding("SpineShoulderZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentSpineMidX.SetBinding(TextBox.TextProperty, new Binding("SpineMidX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentSpineMidY.SetBinding(TextBox.TextProperty, new Binding("SpineMidY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentSpineMidZ.SetBinding(TextBox.TextProperty, new Binding("SpineMidZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentSpineBaseX.SetBinding(TextBox.TextProperty, new Binding("SpineBaseX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentSpineBaseY.SetBinding(TextBox.TextProperty, new Binding("SpineBaseY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentSpineBaseZ.SetBinding(TextBox.TextProperty, new Binding("SpineBaseZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentLeftShoulderX.SetBinding(TextBox.TextProperty, new Binding("LeftShoulderX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftShoulderY.SetBinding(TextBox.TextProperty, new Binding("LeftShoulderY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftShoulderZ.SetBinding(TextBox.TextProperty, new Binding("LeftShoulderZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentLeftElbowX.SetBinding(TextBox.TextProperty, new Binding("LeftElbowX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftElbowY.SetBinding(TextBox.TextProperty, new Binding("LeftElbowY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftElbowZ.SetBinding(TextBox.TextProperty, new Binding("LeftElbowZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentLeftWristX.SetBinding(TextBox.TextProperty, new Binding("LeftWristX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftWristY.SetBinding(TextBox.TextProperty, new Binding("LeftWristY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftWristZ.SetBinding(TextBox.TextProperty, new Binding("LeftWristZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentLeftHandX.SetBinding(TextBox.TextProperty, new Binding("LeftHandX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftHandY.SetBinding(TextBox.TextProperty, new Binding("LeftHandY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftHandZ.SetBinding(TextBox.TextProperty, new Binding("LeftHandZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentRightShoulderX.SetBinding(TextBox.TextProperty, new Binding("RightShoulderX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightShoulderY.SetBinding(TextBox.TextProperty, new Binding("RightShoulderY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightShoulderZ.SetBinding(TextBox.TextProperty, new Binding("RightShoulderZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentRightElbowX.SetBinding(TextBox.TextProperty, new Binding("RightElbowX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightElbowY.SetBinding(TextBox.TextProperty, new Binding("RightElbowY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightElbowZ.SetBinding(TextBox.TextProperty, new Binding("RightElbowZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentRightWristX.SetBinding(TextBox.TextProperty, new Binding("RightWristX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightWristY.SetBinding(TextBox.TextProperty, new Binding("RightWristY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightWristZ.SetBinding(TextBox.TextProperty, new Binding("RightWristZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentRightHandX.SetBinding(TextBox.TextProperty, new Binding("RightHandX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightHandY.SetBinding(TextBox.TextProperty, new Binding("RightHandY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightHandZ.SetBinding(TextBox.TextProperty, new Binding("RightHandZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentLeftHipX.SetBinding(TextBox.TextProperty, new Binding("LeftHipX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftHipY.SetBinding(TextBox.TextProperty, new Binding("LeftHipY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftHipZ.SetBinding(TextBox.TextProperty, new Binding("LeftHipZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentLeftKneeX.SetBinding(TextBox.TextProperty, new Binding("LeftKneeX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftKneeY.SetBinding(TextBox.TextProperty, new Binding("LeftKneeY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftKneeZ.SetBinding(TextBox.TextProperty, new Binding("LeftKneeZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentLeftAnkleX.SetBinding(TextBox.TextProperty, new Binding("LeftAnkleX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftAnkleY.SetBinding(TextBox.TextProperty, new Binding("LeftAnkleY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftAnkleZ.SetBinding(TextBox.TextProperty, new Binding("LeftAnkleZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentLeftFootX.SetBinding(TextBox.TextProperty, new Binding("LeftFootX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftFootY.SetBinding(TextBox.TextProperty, new Binding("LeftFootY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentLeftFootZ.SetBinding(TextBox.TextProperty, new Binding("LeftFootZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentRightHipX.SetBinding(TextBox.TextProperty, new Binding("RightHipX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightHipY.SetBinding(TextBox.TextProperty, new Binding("RightHipY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightHipZ.SetBinding(TextBox.TextProperty, new Binding("RightHipZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentRightKneeX.SetBinding(TextBox.TextProperty, new Binding("RightKneeX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightKneeY.SetBinding(TextBox.TextProperty, new Binding("RightKneeY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightKneeZ.SetBinding(TextBox.TextProperty, new Binding("RightKneeZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentRightAnkleX.SetBinding(TextBox.TextProperty, new Binding("RightAnkleX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightAnkleY.SetBinding(TextBox.TextProperty, new Binding("RightAnkleY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightAnkleZ.SetBinding(TextBox.TextProperty, new Binding("RightAnkleZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      currentRightFootX.SetBinding(TextBox.TextProperty, new Binding("RightFootX") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightFootY.SetBinding(TextBox.TextProperty, new Binding("RightFootY") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });
      currentRightFootZ.SetBinding(TextBox.TextProperty, new Binding("RightFootZ") { Source = FrameRecorder.frames[frameIndex], StringFormat = "0.####" });

      CurrentLabel.Content = "Frame " + (frameIndex+1) + " of " + FrameRecorder.frames.Count;

      if (frameIndex + 1 < FrameRecorder.frames.Count)
      {
        nextHeadX.SetBinding(TextBox.TextProperty, new Binding("HeadX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextHeadY.SetBinding(TextBox.TextProperty, new Binding("HeadY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextHeadZ.SetBinding(TextBox.TextProperty, new Binding("HeadZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextNeckX.SetBinding(TextBox.TextProperty, new Binding("NeckX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextNeckY.SetBinding(TextBox.TextProperty, new Binding("NeckY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextNeckZ.SetBinding(TextBox.TextProperty, new Binding("NeckZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextSpineShoulderX.SetBinding(TextBox.TextProperty, new Binding("SpineShoulderX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextSpineShoulderY.SetBinding(TextBox.TextProperty, new Binding("SpineShoulderY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextSpineShoulderZ.SetBinding(TextBox.TextProperty, new Binding("SpineShoulderZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextSpineMidX.SetBinding(TextBox.TextProperty, new Binding("SpineMidX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextSpineMidY.SetBinding(TextBox.TextProperty, new Binding("SpineMidY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextSpineMidZ.SetBinding(TextBox.TextProperty, new Binding("SpineMidZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextSpineBaseX.SetBinding(TextBox.TextProperty, new Binding("SpineBaseX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextSpineBaseY.SetBinding(TextBox.TextProperty, new Binding("SpineBaseY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextSpineBaseZ.SetBinding(TextBox.TextProperty, new Binding("SpineBaseZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextLeftShoulderX.SetBinding(TextBox.TextProperty, new Binding("LeftShoulderX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftShoulderY.SetBinding(TextBox.TextProperty, new Binding("LeftShoulderY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftShoulderZ.SetBinding(TextBox.TextProperty, new Binding("LeftShoulderZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextLeftElbowX.SetBinding(TextBox.TextProperty, new Binding("LeftElbowX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftElbowY.SetBinding(TextBox.TextProperty, new Binding("LeftElbowY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftElbowZ.SetBinding(TextBox.TextProperty, new Binding("LeftElbowZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextLeftWristX.SetBinding(TextBox.TextProperty, new Binding("LeftWristX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftWristY.SetBinding(TextBox.TextProperty, new Binding("LeftWristY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftWristZ.SetBinding(TextBox.TextProperty, new Binding("LeftWristZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextLeftHandX.SetBinding(TextBox.TextProperty, new Binding("LeftHandX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftHandY.SetBinding(TextBox.TextProperty, new Binding("LeftHandY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftHandZ.SetBinding(TextBox.TextProperty, new Binding("LeftHandZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextRightShoulderX.SetBinding(TextBox.TextProperty, new Binding("RightShoulderX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightShoulderY.SetBinding(TextBox.TextProperty, new Binding("RightShoulderY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightShoulderZ.SetBinding(TextBox.TextProperty, new Binding("RightShoulderZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextRightElbowX.SetBinding(TextBox.TextProperty, new Binding("RightElbowX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightElbowY.SetBinding(TextBox.TextProperty, new Binding("RightElbowY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightElbowZ.SetBinding(TextBox.TextProperty, new Binding("RightElbowZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextRightWristX.SetBinding(TextBox.TextProperty, new Binding("RightWristX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightWristY.SetBinding(TextBox.TextProperty, new Binding("RightWristY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightWristZ.SetBinding(TextBox.TextProperty, new Binding("RightWristZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextRightHandX.SetBinding(TextBox.TextProperty, new Binding("RightHandX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightHandY.SetBinding(TextBox.TextProperty, new Binding("RightHandY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightHandZ.SetBinding(TextBox.TextProperty, new Binding("RightHandZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextLeftHipX.SetBinding(TextBox.TextProperty, new Binding("LeftHipX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftHipY.SetBinding(TextBox.TextProperty, new Binding("LeftHipY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftHipZ.SetBinding(TextBox.TextProperty, new Binding("LeftHipZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextLeftKneeX.SetBinding(TextBox.TextProperty, new Binding("LeftKneeX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftKneeY.SetBinding(TextBox.TextProperty, new Binding("LeftKneeY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftKneeZ.SetBinding(TextBox.TextProperty, new Binding("LeftKneeZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextLeftAnkleX.SetBinding(TextBox.TextProperty, new Binding("LeftAnkleX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftAnkleY.SetBinding(TextBox.TextProperty, new Binding("LeftAnkleY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftAnkleZ.SetBinding(TextBox.TextProperty, new Binding("LeftAnkleZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextLeftFootX.SetBinding(TextBox.TextProperty, new Binding("LeftFootX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftFootY.SetBinding(TextBox.TextProperty, new Binding("LeftFootY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextLeftFootZ.SetBinding(TextBox.TextProperty, new Binding("LeftFootZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextRightHipX.SetBinding(TextBox.TextProperty, new Binding("RightHipX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightHipY.SetBinding(TextBox.TextProperty, new Binding("RightHipY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightHipZ.SetBinding(TextBox.TextProperty, new Binding("RightHipZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextRightKneeX.SetBinding(TextBox.TextProperty, new Binding("RightKneeX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightKneeY.SetBinding(TextBox.TextProperty, new Binding("RightKneeY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightKneeZ.SetBinding(TextBox.TextProperty, new Binding("RightKneeZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextRightAnkleX.SetBinding(TextBox.TextProperty, new Binding("RightAnkleX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightAnkleY.SetBinding(TextBox.TextProperty, new Binding("RightAnkleY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightAnkleZ.SetBinding(TextBox.TextProperty, new Binding("RightAnkleZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        nextRightFootX.SetBinding(TextBox.TextProperty, new Binding("RightFootX") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightFootY.SetBinding(TextBox.TextProperty, new Binding("RightFootY") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });
        nextRightFootZ.SetBinding(TextBox.TextProperty, new Binding("RightFootZ") { Source = FrameRecorder.frames[frameIndex + 1], StringFormat = "0.####" });

        btnNextFrame.IsEnabled = true;
      }

    }

    private void OnNextFrameClick(object sender, RoutedEventArgs e)
    {
      FrameRecorder.body.SetRotations(FrameRecorder.frames[frameIndex + 1], true);
    }

    private void OnCurrentFrameClick(object sender, RoutedEventArgs e)
    {
      FrameRecorder.body.SetRotations(FrameRecorder.frames[frameIndex], true);
    }

    private void onPreviousFrameClick(object sender, RoutedEventArgs e)
    {
      FrameRecorder.body.SetRotations(FrameRecorder.frames[frameIndex - 1], true);
    }

    private void onMakePreviousCurrentClick(object sender, RoutedEventArgs e)
    {
      if(frameIndex > 0)
      {
        SetIndex(frameIndex - 1);
      }
    }

    private void onMakeNextCurrentClick(object sender, RoutedEventArgs e)
    {
      if(frameIndex + 1 < FrameRecorder.frames.Count)
      {
        SetIndex(frameIndex + 1);
      }
    }
  }
}
