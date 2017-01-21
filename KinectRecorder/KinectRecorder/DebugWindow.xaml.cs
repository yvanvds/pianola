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
    public int jointID { get; set; }

    public DebugWindow()
    {
      InitializeComponent();
      jointID = 0;
    }

    private void onComboBoxChange(object sender, EventArgs e)
    {
      jointID = comboBox.SelectedIndex;
    }

    public void clear()
    {
      line1.Text = "";
      line2.Text = "";
      line3.Text = "";
      line4.Text = "";
      line5.Text = "";
      line6.Text = "";
    }

    public void setLine1(string value) { line1.Text = value; }
    public void setLine2(string value) { line2.Text = value; }
    public void setLine3(string value) { line3.Text = value; }
    public void setLine4(string value) { line4.Text = value; }
    public void setLine5(string value) { line5.Text = value; }
    public void setLine6(string value) { line6.Text = value; }

    public void setBlueDot1(double x, double y)
    {
      ellipse1Blue.SetValue(Canvas.LeftProperty, 40 + x);
      ellipse1Blue.SetValue(Canvas.TopProperty , 40 + y);
    }

    public void setBlueDot2(double x, double y)
    {
      ellipse2Blue.SetValue(Canvas.LeftProperty, 40 + x);
      ellipse2Blue.SetValue(Canvas.TopProperty , 40 + y);
    }

    public void setRedDot1(double x, double y)
    {
      ellipse1Red.SetValue(Canvas.LeftProperty, 40 + x);
      ellipse1Red.SetValue(Canvas.TopProperty , 40 + y);
    }

    public void setRedDot2(double x, double y)
    {
      ellipse2Red.SetValue(Canvas.LeftProperty, 40 + x);
      ellipse2Red.SetValue(Canvas.TopProperty , 40 + y);
    }

    public void setGreenDot1(double x, double y)
    {
      ellipse1Green.SetValue(Canvas.LeftProperty, 40 + x);
      ellipse1Green.SetValue(Canvas.TopProperty , 40 + y);
    }

    public void setGreenDot2(double x, double y)
    {
      ellipse2Green.SetValue(Canvas.LeftProperty, 40 + x);
      ellipse2Green.SetValue(Canvas.TopProperty , 40 + y);
    }
  }


}
