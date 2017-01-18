using LightBuzz.Vitruvius;
using Microsoft.Kinect;
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
  /// Interaction logic for DebugWindow.xaml
  /// </summary>
  public partial class DebugWindow : Window
  {
    public DebugWindow()
    {
      InitializeComponent();
    }

    public void setFrame(TimedFrame frame)
    {
      line1.Text = "Parent X: " + frame.LeftShoulderX.ToString("0.###") + " Y: " + frame.LeftShoulderY.ToString("0.###") + " Z: " + frame.LeftShoulderZ.ToString("0.###");
      line2.Text = "Node   X: " + frame.LeftElbowX.ToString("0.###") + " Y: " + frame.LeftElbowY.ToString("0.###") + " Z: " + frame.LeftElbowZ.ToString("0.###");

      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.WristLeft, JointType.ElbowLeft, ref x, ref y, ref z);
      line3.Text = "Offset   X: " + x.ToString("0.###") + " Y: " + y.ToString("0.###") + " Z: " + z.ToString("0.###");

      ellipseXY.SetValue(Canvas.LeftProperty, (Double)40 + -x * 100);
      ellipseXY.SetValue(Canvas.TopProperty, (Double)40 + -y * 100);

      ellipseXZ.SetValue(Canvas.LeftProperty, (Double)40 + -x * 100);
      ellipseXZ.SetValue(Canvas.TopProperty, (Double)40 + z * 100);

      double angleXY = 0;
      if (x < 0)
      {
        angleXY = Body.clampRadians(Math.Atan2(x, y) + Constants.PI_2);
      } else
      {
        angleXY = Body.clampRadians(Constants.PI_2 - Math.Atan2(x, y));
      }

      double angleXZ = Body.clampRadians(Constants.PI - Math.Atan2(z, x));

      line4.Text = "XY: " + angleXY.ToDegrees().ToString("0.") + " ZY: "  + " XZ: " + angleXZ.ToDegrees().ToString("0.");
      //line4.Text = "XY: " + angleXY.ToDegrees().ToString("0.") + " XZ: " + angleXZ.ToDegrees().ToString("0.");

      //red dot
      ellipseXYangle.SetValue(Canvas.LeftProperty, (double)10);
      ellipseXYangle.SetValue(Canvas.TopProperty, 40 - angleXY.ToDegrees() / 5);

      // green dot
      //ellipseZYangle.SetValue(Canvas.LeftProperty, (double)70);
      //ellipseZYangle.SetValue(Canvas.TopProperty, 40 - angleZY.ToDegrees() / 5);

      ellipseXZangle.SetValue(Canvas.LeftProperty, (Double)40 + Math.Cos(angleXZ) * 20);
      ellipseXZangle.SetValue(Canvas.TopProperty, (Double)40 + Math.Sin(angleXZ) * 20);
      //double angleY = Math.Atan2(x, -y).ToDegrees();
      //line4.Text = "Degrees  XY: " + angleX.ToString("###.#") + " X-Y: " + angleY.ToString("###.#");

      //angleX = Math.Atan2(-x, y).ToDegrees();
      //angleY = Math.Atan2(-x, -y).ToDegrees();
      //line5.Text = "alt  -XY: " + angleX.ToString("###.#") + " -X-Y: " + angleY.ToString("###.#");

    }

  }


}
