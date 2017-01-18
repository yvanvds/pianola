using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace KinectRecorder
{
  /// <summary>
  /// Interaction logic for Editor.xaml
  /// </summary>
  public partial class Editor : Window
  {
    RecordingPage parent = null;

    public Editor()
    {
      
      InitializeComponent();
      Style = (Style)FindResource(typeof(Window));
      Closing += OnClose;
      
      dataGrid.ItemsSource = FrameRecorder.frames;
      dataGrid.CurrentCellChanged += CurrentCellChanged;
      dataGrid.SelectionChanged += OnSelectionChanged;

      checkbox_loop.IsChecked = FrameRecorder.Looping;
      FrameRecorder.LinkEditor(this);
    }

    ~Editor()
    {
      FrameRecorder.LinkEditor(null);
    }

    public void SetParent(RecordingPage page)
    {
      parent = page;
    }

    public void SetSelected(int index)
    {
      dataGrid.SelectedIndex = index;
    }

    private void CurrentCellChanged(object sender, EventArgs e)
    {
      dataGrid.CommitEdit(DataGridEditingUnit.Row, true);
    }

    public void OnClose(object sender, CancelEventArgs e)
    {
      dataGrid.CommitEdit(DataGridEditingUnit.Row, true);
    }

    private void OnSelectionChanged(object sender, SelectionChangedEventArgs e)
    {
      if(parent != null && dataGrid.SelectedItems.Count > 0)
      {
        FrameRecorder.body.SetRotations((TimedFrame)dataGrid.SelectedItem, true);
        parent.debugWindow.setFrame((TimedFrame)dataGrid.SelectedItem);
      }
    }

    private void Row_DoubleClick(object sender, MouseButtonEventArgs e)
    {
      DataGridRow row = sender as DataGridRow;
      FrameDetail detail = new FrameDetail(row.GetIndex());
      
      detail.Show();
    }

    private void btnDeleteSelectedClick(object sender, RoutedEventArgs e)
    {
      while(dataGrid.SelectedItems.Count > 0)
      {
        FrameRecorder.frames.Remove((TimedFrame)dataGrid.SelectedItem);
      } 
    }

    private void btnRemoveOffset(object sender, RoutedEventArgs e)
    {
      FrameRecorder.RemoveOffset();
    }

    private void button_play_Click(object sender, RoutedEventArgs e)
    {
      if (FrameRecorder.GetStatus() == FrameRecorder.Status.IDLE)
      {
        FrameRecorder.StartPlaying(false);
        button_play.Content = "Playing...";
        button_play.Background = new SolidColorBrush(Color.FromRgb(83, 219, 99));
      }
      else
      {
        FrameRecorder.StopPlaying();
        button_play.Content = "Play";
        button_play.Background = new SolidColorBrush(Color.FromRgb(60, 60, 60));
      }
    }

    private void checkbox_loop_Click(object sender, RoutedEventArgs e)
    {
      System.Windows.Controls.CheckBox box = sender as System.Windows.Controls.CheckBox;
      FrameRecorder.Looping = box.IsChecked.Value;
    }
  }
}
