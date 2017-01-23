using LightBuzz.Vitruvius;
using Microsoft.Kinect;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace KinectRecorder
{
  public class TimedFrame : INotifyPropertyChanged
  {
    public event PropertyChangedEventHandler PropertyChanged;
    private void OnPropertyChanged(string prop)
    {
      if(PropertyChanged != null)
      {
        PropertyChanged(this, new PropertyChangedEventArgs(prop));
      }
    }

    public bool Use { get; set; }

    private long time;
    public long Time { get { return time; } set { if(time != value) { time = value; OnPropertyChanged("Time"); } } }

    public bool Head { get; set; }
    public bool TorsoUpper { get; set; }
    public bool TorsoLower { get; set; }

    public bool ShoulderLeft { get; set; }
    public bool ElbowLeft { get; set; }
    public bool HandLeft { get; set; }

    public bool ShoulderRight { get; set; }
    public bool ElbowRight { get; set; }
    public bool HandRight { get; set; }

    public bool HipLeft { get; set; }
    public bool KneeLeft { get; set; }
    public bool FootLeft { get; set; }

    public bool HipRight { get; set; }
    public bool KneeRight { get; set; }
    public bool FootRight { get; set; }

    public double HeadX { get { return Joints[JointType.Head].X; } set { replaceX(JointType.Head, value); OnPropertyChanged("HeadX"); } }
    public double HeadY { get { return Joints[JointType.Head].Y; } set { replaceY(JointType.Head, value); OnPropertyChanged("HeadY"); } }
    public double HeadZ { get { return Joints[JointType.Head].Z; } set { replaceZ(JointType.Head, value); OnPropertyChanged("HeadZ"); } }

    public double NeckX { get { return Joints[JointType.Neck].X; } set { replaceX(JointType.Neck, value); OnPropertyChanged("NeckX"); } }
    public double NeckY { get { return Joints[JointType.Neck].Y; } set { replaceY(JointType.Neck, value); OnPropertyChanged("NeckY"); } }
    public double NeckZ { get { return Joints[JointType.Neck].Z; } set { replaceZ(JointType.Neck, value); OnPropertyChanged("NeckZ"); } }

    public double SpineShoulderX { get { return Joints[JointType.SpineShoulder].X; } set { replaceX(JointType.SpineShoulder, value); OnPropertyChanged("SpineShoulderX"); } }
    public double SpineShoulderY { get { return Joints[JointType.SpineShoulder].Y; } set { replaceY(JointType.SpineShoulder, value); OnPropertyChanged("SpineShoulderY"); } }
    public double SpineShoulderZ { get { return Joints[JointType.SpineShoulder].Z; } set { replaceZ(JointType.SpineShoulder, value); OnPropertyChanged("SpineShoulderZ"); } }

    public double SpineMidX { get { return Joints[JointType.SpineMid].X; } set { replaceX(JointType.SpineMid, value); OnPropertyChanged("SpineMidX"); } }
    public double SpineMidY { get { return Joints[JointType.SpineMid].Y; } set { replaceY(JointType.SpineMid, value); OnPropertyChanged("SpineMidY"); } }
    public double SpineMidZ { get { return Joints[JointType.SpineMid].Z; } set { replaceZ(JointType.SpineMid, value); OnPropertyChanged("SpineMidZ"); } }

    public double SpineBaseX { get { return Joints[JointType.SpineBase].X; } set { replaceX(JointType.SpineBase, value); OnPropertyChanged("SpineBaseX"); } }
    public double SpineBaseY { get { return Joints[JointType.SpineBase].Y; } set { replaceY(JointType.SpineBase, value); OnPropertyChanged("SpineBaseY"); } }
    public double SpineBaseZ { get { return Joints[JointType.SpineBase].Z; } set { replaceZ(JointType.SpineBase, value); OnPropertyChanged("SpineBaseZ"); } }

    public double LeftShoulderX { get { return Joints[JointType.ShoulderLeft].X; } set { replaceX(JointType.ShoulderLeft, value); OnPropertyChanged("LeftShoulderX"); } }
    public double LeftShoulderY { get { return Joints[JointType.ShoulderLeft].Y; } set { replaceY(JointType.ShoulderLeft, value); OnPropertyChanged("LeftShoulderY"); } }
    public double LeftShoulderZ { get { return Joints[JointType.ShoulderLeft].Z; } set { replaceZ(JointType.ShoulderLeft, value); OnPropertyChanged("LeftShoulderZ"); } }

    public double LeftElbowX { get { return Joints[JointType.ElbowLeft].X; } set { replaceX(JointType.ElbowLeft, value); OnPropertyChanged("LeftElbowX"); } }
    public double LeftElbowY { get { return Joints[JointType.ElbowLeft].Y; } set { replaceY(JointType.ElbowLeft, value); OnPropertyChanged("LeftElbowY"); } }
    public double LeftElbowZ { get { return Joints[JointType.ElbowLeft].Z; } set { replaceZ(JointType.ElbowLeft, value); OnPropertyChanged("LeftElbowZ"); } }

    public double LeftWristX { get { return Joints[JointType.WristLeft].X; } set { replaceX(JointType.WristLeft, value); OnPropertyChanged("LeftWristX"); } }
    public double LeftWristY { get { return Joints[JointType.WristLeft].Y; } set { replaceY(JointType.WristLeft, value); OnPropertyChanged("LeftWristY"); } }
    public double LeftWristZ { get { return Joints[JointType.WristLeft].Z; } set { replaceZ(JointType.WristLeft, value); OnPropertyChanged("LeftWristZ"); } }

    public double LeftHandX { get { return Joints[JointType.HandLeft].X; } set { replaceX(JointType.HandLeft, value); OnPropertyChanged("LeftHandX"); } }
    public double LeftHandY { get { return Joints[JointType.HandLeft].Y; } set { replaceY(JointType.HandLeft, value); OnPropertyChanged("LeftHandY"); } }
    public double LeftHandZ { get { return Joints[JointType.HandLeft].Z; } set { replaceZ(JointType.HandLeft, value); OnPropertyChanged("LeftHandZ"); } }

    public double RightShoulderX { get { return Joints[JointType.ShoulderRight].X; } set { replaceX(JointType.ShoulderRight, value); OnPropertyChanged("RightShoulderX"); } }
    public double RightShoulderY { get { return Joints[JointType.ShoulderRight].Y; } set { replaceY(JointType.ShoulderRight, value); OnPropertyChanged("RightShoulderY"); } }
    public double RightShoulderZ { get { return Joints[JointType.ShoulderRight].Z; } set { replaceZ(JointType.ShoulderRight, value); OnPropertyChanged("RightShoulderZ"); } }

    public double RightElbowX { get { return Joints[JointType.ElbowRight].X; } set { replaceX(JointType.ElbowRight, value); OnPropertyChanged("RightElbowX"); } }
    public double RightElbowY { get { return Joints[JointType.ElbowRight].Y; } set { replaceY(JointType.ElbowRight, value); OnPropertyChanged("RightElbowY"); } }
    public double RightElbowZ { get { return Joints[JointType.ElbowRight].Z; } set { replaceZ(JointType.ElbowRight, value); OnPropertyChanged("RightElbowZ"); } }

    public double RightWristX { get { return Joints[JointType.WristRight].X; } set { replaceX(JointType.WristRight, value); OnPropertyChanged("RightWristX"); } }
    public double RightWristY { get { return Joints[JointType.WristRight].Y; } set { replaceY(JointType.WristRight, value); OnPropertyChanged("RightWristY"); } }
    public double RightWristZ { get { return Joints[JointType.WristRight].Z; } set { replaceZ(JointType.WristRight, value); OnPropertyChanged("RightWristZ"); } }

    public double RightHandX { get { return Joints[JointType.HandRight].X; } set { replaceX(JointType.HandRight, value); OnPropertyChanged("RightHandX"); } }
    public double RightHandY { get { return Joints[JointType.HandRight].Y; } set { replaceY(JointType.HandRight, value); OnPropertyChanged("RightHandY"); } }
    public double RightHandZ { get { return Joints[JointType.HandRight].Z; } set { replaceZ(JointType.HandRight, value); OnPropertyChanged("RightHandZ"); } }

    public double LeftHipX { get { return Joints[JointType.HipLeft].X; } set { replaceX(JointType.HipLeft, value); OnPropertyChanged("LeftHipX"); } }
    public double LeftHipY { get { return Joints[JointType.HipLeft].Y; } set { replaceY(JointType.HipLeft, value); OnPropertyChanged("LeftHipY"); } }
    public double LeftHipZ { get { return Joints[JointType.HipLeft].Z; } set { replaceZ(JointType.HipLeft, value); OnPropertyChanged("LeftHipZ"); } }

    public double LeftKneeX { get { return Joints[JointType.KneeLeft].X; } set { replaceX(JointType.KneeLeft, value); OnPropertyChanged("LeftKneeX"); } }
    public double LeftKneeY { get { return Joints[JointType.KneeLeft].Y; } set { replaceY(JointType.KneeLeft, value); OnPropertyChanged("LeftKneeY"); } }
    public double LeftKneeZ { get { return Joints[JointType.KneeLeft].Z; } set { replaceZ(JointType.KneeLeft, value); OnPropertyChanged("LeftKneeZ"); } }

    public double LeftAnkleX { get { return Joints[JointType.AnkleLeft].X; } set { replaceX(JointType.AnkleLeft, value); OnPropertyChanged("LeftAnkleX"); } }
    public double LeftAnkleY { get { return Joints[JointType.AnkleLeft].Y; } set { replaceY(JointType.AnkleLeft, value); OnPropertyChanged("LeftAnkleY"); } }
    public double LeftAnkleZ { get { return Joints[JointType.AnkleLeft].Z; } set { replaceZ(JointType.AnkleLeft, value); OnPropertyChanged("LeftAnkleZ"); } }

    public double LeftFootX { get { return Joints[JointType.FootLeft].X; } set { replaceX(JointType.FootLeft, value); OnPropertyChanged("LeftFootX"); } }
    public double LeftFootY { get { return Joints[JointType.FootLeft].Y; } set { replaceY(JointType.FootLeft, value); OnPropertyChanged("LeftFootY"); } }
    public double LeftFootZ { get { return Joints[JointType.FootLeft].Z; } set { replaceZ(JointType.FootLeft, value); OnPropertyChanged("LeftFootZ"); } }

    public double RightHipX { get { return Joints[JointType.HipRight].X; } set { replaceX(JointType.HipRight, value); OnPropertyChanged("RightHipX"); } }
    public double RightHipY { get { return Joints[JointType.HipRight].Y; } set { replaceY(JointType.HipRight, value); OnPropertyChanged("RightHipY"); } }
    public double RightHipZ { get { return Joints[JointType.HipRight].Z; } set { replaceZ(JointType.HipRight, value); OnPropertyChanged("RightHipZ"); } }

    public double RightKneeX { get { return Joints[JointType.KneeRight].X; } set { replaceX(JointType.KneeRight, value); OnPropertyChanged("RightKneeX"); } }
    public double RightKneeY { get { return Joints[JointType.KneeRight].Y; } set { replaceY(JointType.KneeRight, value); OnPropertyChanged("RightKneeY"); } }
    public double RightKneeZ { get { return Joints[JointType.KneeRight].Z; } set { replaceZ(JointType.KneeRight, value); OnPropertyChanged("RightKneeZ"); } }

    public double RightAnkleX { get { return Joints[JointType.AnkleRight].X; } set { replaceX(JointType.AnkleRight, value); OnPropertyChanged("RightAnkleX"); } }
    public double RightAnkleY { get { return Joints[JointType.AnkleRight].Y; } set { replaceY(JointType.AnkleRight, value); OnPropertyChanged("RightAnkleY"); } }
    public double RightAnkleZ { get { return Joints[JointType.AnkleRight].Z; } set { replaceZ(JointType.AnkleRight, value); OnPropertyChanged("RightAnkleZ"); } }

    public double RightFootX { get { return Joints[JointType.FootRight].X; } set { replaceX(JointType.FootRight, value); OnPropertyChanged("RightFootX"); } }
    public double RightFootY { get { return Joints[JointType.FootRight].Y; } set { replaceY(JointType.FootRight, value); OnPropertyChanged("RightFootY"); } }
    public double RightFootZ { get { return Joints[JointType.FootRight].Z; } set { replaceZ(JointType.FootRight, value); OnPropertyChanged("RightFootZ"); } }


    public IDictionary<JointType, Vector3> Joints;

    // used to indicate what type of data to expect next
    private enum FilePart
    {
      Time,
      Joints,
      Uses,
      End,
    }

    public TimedFrame()
    {
      Use = true;
      Head = TorsoUpper = TorsoLower = true;
      ShoulderLeft = ElbowLeft = HandLeft = true;
      ShoulderRight = ElbowRight = HandRight = true;
      HipLeft = KneeLeft = FootLeft = true;
      HipRight = KneeRight = FootRight = true;

      Joints = new Dictionary<JointType, Vector3>();
      Joints.Add(JointType.Head, new Vector3());
      Joints.Add(JointType.Neck, new Vector3());
      Joints.Add(JointType.SpineShoulder, new Vector3());
      Joints.Add(JointType.SpineMid, new Vector3());
      Joints.Add(JointType.SpineBase, new Vector3());

      Joints.Add(JointType.ShoulderLeft, new Vector3());
      Joints.Add(JointType.ElbowLeft, new Vector3());
      Joints.Add(JointType.WristLeft, new Vector3());
      Joints.Add(JointType.HandLeft, new Vector3());

      Joints.Add(JointType.ShoulderRight, new Vector3());
      Joints.Add(JointType.ElbowRight, new Vector3());
      Joints.Add(JointType.WristRight, new Vector3());
      Joints.Add(JointType.HandRight, new Vector3());

      Joints.Add(JointType.HipLeft, new Vector3());
      Joints.Add(JointType.KneeLeft, new Vector3());
      Joints.Add(JointType.AnkleLeft, new Vector3());
      Joints.Add(JointType.FootLeft, new Vector3());

      Joints.Add(JointType.HipRight, new Vector3());
      Joints.Add(JointType.KneeRight, new Vector3());
      Joints.Add(JointType.AnkleRight, new Vector3());
      Joints.Add(JointType.FootRight, new Vector3());
    }

    public TimedFrame(Microsoft.Kinect.Body body) : this()
    {
      set(body);
    }

    public void set(Microsoft.Kinect.Body body) 
    {
      addJointFromBody(JointType.Head, body.Joints[JointType.Head]);
      addJointFromBody(JointType.Neck, body.Joints[JointType.Neck]);
      addJointFromBody(JointType.SpineShoulder, body.Joints[JointType.SpineShoulder]);
      addJointFromBody(JointType.SpineMid, body.Joints[JointType.SpineMid]);
      addJointFromBody(JointType.SpineBase, body.Joints[JointType.SpineBase]);
      addJointFromBody(JointType.ShoulderLeft, body.Joints[JointType.ShoulderLeft]);
      addJointFromBody(JointType.ElbowLeft, body.Joints[JointType.ElbowLeft]);
      addJointFromBody(JointType.WristLeft, body.Joints[JointType.WristLeft]);
      addJointFromBody(JointType.HandLeft, body.Joints[JointType.HandLeft]);
      addJointFromBody(JointType.ShoulderRight, body.Joints[JointType.ShoulderRight]);
      addJointFromBody(JointType.ElbowRight, body.Joints[JointType.ElbowRight]);
      addJointFromBody(JointType.WristRight, body.Joints[JointType.WristRight]);
      addJointFromBody(JointType.HandRight, body.Joints[JointType.HandRight]);
      addJointFromBody(JointType.HipLeft, body.Joints[JointType.HipLeft]);
      addJointFromBody(JointType.KneeLeft, body.Joints[JointType.KneeLeft]);
      addJointFromBody(JointType.AnkleLeft, body.Joints[JointType.AnkleLeft]);
      addJointFromBody(JointType.FootLeft, body.Joints[JointType.FootLeft]);
      addJointFromBody(JointType.HipRight, body.Joints[JointType.HipRight]);
      addJointFromBody(JointType.KneeRight, body.Joints[JointType.KneeRight]);
      addJointFromBody(JointType.AnkleRight, body.Joints[JointType.AnkleRight]);
      addJointFromBody(JointType.FootRight, body.Joints[JointType.FootRight]);
    }

    public TimedFrame(BinaryReader reader) : this()
    {
      set(reader);
    }

    public void set(BinaryReader reader)
    {
      while (true)
      {
        FilePart part = (FilePart)reader.ReadInt32();
        switch (part)
        {
          case FilePart.Time: Time = reader.ReadInt64(); break;
          case FilePart.Joints: readJoints(reader); break;
          case FilePart.Uses: readUses(reader); break;
          case FilePart.End: return;
        }
      }
    }
      
    private void readUses(BinaryReader reader) { 
      Use = reader.ReadBoolean();
      Head = reader.ReadBoolean(); TorsoUpper = reader.ReadBoolean(); TorsoLower = reader.ReadBoolean();
      ShoulderLeft = reader.ReadBoolean(); ElbowLeft = reader.ReadBoolean(); HandLeft = reader.ReadBoolean(); ;
      ShoulderRight = reader.ReadBoolean(); ElbowRight = reader.ReadBoolean(); HandRight = reader.ReadBoolean();
      HipLeft = reader.ReadBoolean(); KneeLeft = reader.ReadBoolean(); FootLeft = reader.ReadBoolean();
      HipRight = reader.ReadBoolean(); KneeRight = reader.ReadBoolean(); FootRight = reader.ReadBoolean();
    }

    private void readJoints(BinaryReader reader)
    {
      addJointFromReader(reader, JointType.Head);
      addJointFromReader(reader, JointType.Neck);
      addJointFromReader(reader, JointType.SpineShoulder);
      addJointFromReader(reader, JointType.SpineMid);
      addJointFromReader(reader, JointType.SpineBase);

      addJointFromReader(reader, JointType.ShoulderLeft);
      addJointFromReader(reader, JointType.ElbowLeft);
      addJointFromReader(reader, JointType.WristLeft);
      addJointFromReader(reader, JointType.HandLeft);

      addJointFromReader(reader, JointType.ShoulderRight);
      addJointFromReader(reader, JointType.ElbowRight);
      addJointFromReader(reader, JointType.WristRight);
      addJointFromReader(reader, JointType.HandRight);

      addJointFromReader(reader, JointType.HipLeft);
      addJointFromReader(reader, JointType.KneeLeft);
      addJointFromReader(reader, JointType.AnkleLeft);
      addJointFromReader(reader, JointType.FootLeft);

      addJointFromReader(reader, JointType.HipRight);
      addJointFromReader(reader, JointType.KneeRight);
      addJointFromReader(reader, JointType.AnkleRight);
      addJointFromReader(reader, JointType.FootRight);
    }

    public TimedFrame(TimedFrame other) :this()
    {
      set(other);
    }

    public void set(TimedFrame other)
    {
      Time = other.Time;

      copyJoint(JointType.Head, other);
      copyJoint(JointType.Neck, other);
      copyJoint(JointType.SpineShoulder, other);
      copyJoint(JointType.SpineMid, other);
      copyJoint(JointType.SpineBase, other);

      copyJoint(JointType.ShoulderLeft, other);
      copyJoint(JointType.ElbowLeft, other);
      copyJoint(JointType.WristLeft, other);
      copyJoint(JointType.HandLeft, other);

      copyJoint(JointType.ShoulderRight, other);
      copyJoint(JointType.ElbowRight, other);
      copyJoint(JointType.WristRight, other);
      copyJoint(JointType.HandRight, other);

      copyJoint(JointType.HipLeft, other);
      copyJoint(JointType.KneeLeft, other);
      copyJoint(JointType.AnkleLeft, other);
      copyJoint(JointType.FootLeft, other);

      copyJoint(JointType.HipRight, other);
      copyJoint(JointType.KneeRight, other);
      copyJoint(JointType.AnkleRight, other);
      copyJoint(JointType.FootRight, other);

      Use = other.Use;
      Head = other.Head;
      TorsoUpper = other.TorsoUpper;
      TorsoLower = other.TorsoLower;
      ShoulderLeft = other.ShoulderLeft;
      ElbowLeft = other.ElbowLeft;
      HandLeft = other.HandLeft;
      ShoulderRight = other.ShoulderRight;
      ElbowRight = other.ElbowRight;
      HandRight = other.HandRight;
      HipLeft = other.HipLeft;
      KneeLeft = other.KneeLeft;
      FootLeft = other.FootLeft;
      HipRight = other.HipRight;
      KneeRight = other.KneeRight;
      FootRight = other.FootRight;
    }

    public void save(BinaryWriter writer)
    {
      saveTime(writer);
      saveJoints(writer);
      saveUsage(writer);
      saveEnd(writer);
    }

    public void saveTime(BinaryWriter writer)
    {
      writer.Write((int)FilePart.Time);
      writer.Write(Convert.ToInt64(Time));
    }

    public void writeJointHeader(BinaryWriter writer)
    {
      writer.Write((int)FilePart.Joints);
    }

    private void saveJoints(BinaryWriter writer)
    {
      writer.Write((int)FilePart.Joints);
      saveJoint(writer, JointType.Head);
      saveJoint(writer, JointType.Neck);
      saveJoint(writer, JointType.SpineShoulder);
      saveJoint(writer, JointType.SpineMid);
      saveJoint(writer, JointType.SpineBase);

      saveJoint(writer, JointType.ShoulderLeft);
      saveJoint(writer, JointType.ElbowLeft);
      saveJoint(writer, JointType.WristLeft);
      saveJoint(writer, JointType.HandLeft);

      saveJoint(writer, JointType.ShoulderRight);
      saveJoint(writer, JointType.ElbowRight);
      saveJoint(writer, JointType.WristRight);
      saveJoint(writer, JointType.HandRight);

      saveJoint(writer, JointType.HipLeft);
      saveJoint(writer, JointType.KneeLeft);
      saveJoint(writer, JointType.AnkleLeft);
      saveJoint(writer, JointType.FootLeft);

      saveJoint(writer, JointType.HipRight);
      saveJoint(writer, JointType.KneeRight);
      saveJoint(writer, JointType.AnkleRight);
      saveJoint(writer, JointType.FootRight);
    }

    private void saveUsage(BinaryWriter writer)
    {
      writer.Write((int)FilePart.Uses);
      writer.Write(Use);
      writer.Write(Head); writer.Write(TorsoUpper); writer.Write(TorsoLower);
      writer.Write(ShoulderLeft); writer.Write(ElbowLeft); writer.Write(HandLeft);
      writer.Write(ShoulderRight); writer.Write(ElbowRight); writer.Write(HandRight);
      writer.Write(HipLeft); writer.Write(KneeLeft); writer.Write(FootLeft);
      writer.Write(HipRight); writer.Write(KneeRight); writer.Write(FootRight);
    }
    
    public void saveEnd(BinaryWriter writer)
    {
      writer.Write((int)FilePart.End);
    }

    void addJointFromReader(BinaryReader reader, JointType type)
    {
      
      Vector3 point = new Vector3();
      point.X = reader.ReadDouble();
      point.Y = reader.ReadDouble();
      point.Z = reader.ReadDouble();

      Joints[type] = point;
    }

    void addJointFromBody(JointType type, Joint joint)
    {
      Vector3 point = new Vector3();
      point.X = joint.Position.X;
      point.Y = joint.Position.Y;
      point.Z = joint.Position.Z;
      Joints[type] = point;
    }

    void copyJoint(JointType type, TimedFrame other)
    {
      Joints[type] = other.Joints[type];
    }

    void saveJoint(BinaryWriter writer, JointType type)
    {
      writer.Write(Joints[type].X);
      writer.Write(Joints[type].Y);
      writer.Write(Joints[type].Z);
    }

    public void getOffset(JointType joint, JointType parent, ref double x, ref double y, ref double z)
    {
      Vector3 j = Joints[joint];
      Vector3 p = Joints[parent];
      x = j.X - p.X; y = j.Y - p.Y; z = j.Z - p.Z;
    }

    public Vec2 getXY(JointType joint)
    {
      Vec2 result = new Vec2();
      result.x = Joints[joint].X;
      result.y = Joints[joint].Y;
      return result;
    }

    public Vec2 getXZ(JointType joint)
    {
      Vec2 result = new Vec2();
      result.x = Joints[joint].X;
      result.y = Joints[joint].Z;
      return result;
    }


    void replaceX(JointType type, double x)
    {
      Vector3 v = Joints[type];
      v.X = x;
      Joints[type] = v;
    }

    void replaceY(JointType type, double y)
    {
      Vector3 v = Joints[type];
      v.Y = y;
      Joints[type] = v;
    }

    void replaceZ(JointType type, double z)
    {
      Vector3 v = Joints[type];
      v.Z = z;
      Joints[type] = v;
    }
  }
}
