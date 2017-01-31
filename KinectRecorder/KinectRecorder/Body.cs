using LightBuzz.Vitruvius;
using Microsoft.Kinect;
using Rug.Osc;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace KinectRecorder
{
  class Body
  {
    public VecI Head = new VecI();
    public VecI TorsoUpper = new VecI();
    public VecI TorsoLower = new VecI();
    public VecI LeftShoulder = new VecI();
    public VecI RightShoulder = new VecI();
    public VecI LeftElbow = new VecI();
    public VecI RightElbow = new VecI();
    public VecI LeftHand = new VecI();
    public VecI RightHand = new VecI();
    public VecI LeftHip = new VecI();
    public VecI RightHip = new VecI();
    public VecI LeftKnee = new VecI();
    public VecI RightKnee = new VecI();
    public VecI LeftFoot = new VecI();
    public VecI RightFoot = new VecI();

    private enum BODYPART
    {
      HEAD,
      TORSO_UPPER,
      TORSO_LOWER,
      ARMLU,
      ARMLL,
      HANDL,
      ARMRU,
      ARMRL,
      HANDR,
      LEGLU,
      LEGLL,
      FOOTL,
      LEGRU,
      LEGRL,
      FOOTR,
      INVALID,
      NUM,
    };

    private bool bUse, bHead, bTorsoUpper, bTorsoLower, bShoulderLeft, bShoulderRight, bElbowLeft, bElbowRight, bHandLeft, bHandRight, bHipLeft, bHipRight, bKneeLeft, bKneeRight, bFootLeft, bFootRight;

    static OscSender osc = null;
    static IPAddress address;
    static int port = 34567;

    DebugWindow debug = null;

    public Body()
    {

    }

    public bool SetIP(string value)
    {
      if(osc == null)
      {
        address = IPAddress.Parse(value);
        osc = new OscSender(address, port);
        osc.Connect();
        return true;
      }
      return false;
    }

    public void setDebug(DebugWindow window) { debug = window; }

    public void SetRotations(TimedFrame frame, bool sendRotations = false)
    {
      // set used parts
      bUse = frame.Use;
      bHead = frame.Head; bTorsoUpper = frame.TorsoUpper; bTorsoLower = frame.TorsoLower;
      bShoulderLeft = frame.ShoulderLeft; bElbowLeft = frame.ElbowLeft; bHandLeft = frame.HandLeft;
      bShoulderRight = frame.ShoulderRight; bElbowRight = frame.ElbowRight; bHandRight = frame.HandRight;
      bHipLeft = frame.HipLeft; bKneeLeft = frame.KneeLeft; bFootLeft = frame.FootLeft;
      bHipRight = frame.HipRight; bKneeRight = frame.KneeRight; bFootRight = frame.FootRight;

      calcLowerTorso(frame); calcUpperTorso(frame); calcHead(frame);
      calcLeftShoulder(frame); calcLeftElbow(frame); calcLeftHand(frame);
      calcRightShoulder(frame); calcRightElbow(frame); calcRightHand(frame);
      calcLeftHip(frame); calcLeftKnee(frame); calcLeftFoot(frame);
      calcRightHip(frame); calcRightKnee(frame); calcRightFoot(frame);

      if (sendRotations) send(10);
    }

    private void calcLowerTorso(TimedFrame frame) {
      // lower torso
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.SpineMid, JointType.SpineBase, ref x, ref y, ref z);

      TorsoLower.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) - Constants.PI_2).ToDegrees() / 180 * 127));
      TorsoLower.y = -clampRotation(Convert.ToInt32((Math.Atan2(z, y)).ToDegrees() / 180 * 127));
      TorsoLower.z = 0;
    }

    private void calcUpperTorso(TimedFrame frame) {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.SpineShoulder, JointType.SpineMid, ref x, ref y, ref z);

      TorsoUpper.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) - Constants.PI_2).ToDegrees() / 180 * 127)) + TorsoLower.x;
      TorsoUpper.y = -clampRotation(Convert.ToInt32((Math.Atan2(z, y)).ToDegrees() / 180 * 127)) + TorsoLower.y;
      TorsoUpper.z = 0;
    }

    private void calcHead(TimedFrame frame) {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.Head, JointType.Neck, ref x, ref y, ref z);

      Head.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) - Constants.PI_2).ToDegrees() / 180 * 127)) + TorsoLower.x + TorsoUpper.x;
      Head.y = -clampRotation(Convert.ToInt32((Math.Atan2(z, y)).ToDegrees() / 180 * 127)) + TorsoLower.y + TorsoUpper.y;
      Head.z = 0;
    }

    private void calcLeftShoulder(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.ElbowLeft, JointType.ShoulderLeft, ref x, ref y, ref z);

      if (x < 0)
      {
        LeftShoulder.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 + Math.Atan2(x, y)).ToDegrees() / 180 * 127));
      }
      else
      {
        LeftShoulder.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 - Math.Atan2(x, y)).ToDegrees() / 180 * 127));
      }

      LeftShoulder.y = clampRotation(Convert.ToInt32(clampRadians(Constants.PI + Math.Atan2(z, x)).ToDegrees() / 180 * 127));
      LeftShoulder.z = 0;

      LeftShoulder.x -= (TorsoUpper.x + TorsoLower.x);
    }

    private void calcRightShoulder(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.ElbowRight, JointType.ShoulderRight, ref x, ref y, ref z);

      if (x > 0)
      {
        RightShoulder.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 + Math.Atan2(-x, y)).ToDegrees() / 180 * 127));
      }
      else
      {
        RightShoulder.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 - Math.Atan2(-x, y)).ToDegrees() / 180 * 127));
      }

      RightShoulder.y = clampRotation(-Convert.ToInt32((Math.Atan2(z, x)).ToDegrees() / 180 * 127));
      RightShoulder.z = 0;

      RightShoulder.x -= (TorsoLower.x + TorsoUpper.x);

      if (debug != null && debug.jointID == 6)
      {
        setDebugXYZ(x, y, z);
        setDebugRotation(RightShoulder);
      }
    }

    private void calcLeftElbow(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.WristLeft, JointType.ElbowLeft, ref x, ref y, ref z);

      if (x < 0)
      {
        LeftElbow.x = clampRotation(Convert.ToInt32((Constants.PI_2 + Math.Atan2(x, y)).ToDegrees() / 180 * 127));
      } else
      {
        LeftElbow.x = clampRotation(Convert.ToInt32((Constants.PI_2 - Math.Atan2(x, y)).ToDegrees() / 180 * 127));
      }
      LeftElbow.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, x)).ToDegrees() / 180 * 127));
      LeftElbow.z = 0;

      LeftElbow.x -= (TorsoUpper.x + TorsoLower.x + LeftShoulder.x);
      LeftElbow.y -= (LeftShoulder.y);

      if (debug != null && debug.jointID == 4)
      {
        setDebugXYZ(x, y, z);
        setDebugRotation(LeftElbow);
      }
    }

    private void calcRightElbow(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.WristRight, JointType.ElbowRight, ref x, ref y, ref z);

      if (x > 0)
      {
        RightElbow.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 + Math.Atan2(-x, y)).ToDegrees() / 180 * 127));
      }
      else
      {
        RightElbow.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 - Math.Atan2(-x, y)).ToDegrees() / 180 * 127));
      }

      RightElbow.y = clampRotation(-Convert.ToInt32((Math.Atan2(z, x)).ToDegrees() / 180 * 127));
      RightElbow.z = 0;

      RightElbow.x -= (TorsoLower.x + TorsoUpper.x + RightShoulder.x);
      RightElbow.y -= (RightShoulder.y);
    }

    private void calcLeftHand(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.HandLeft, JointType.WristLeft, ref x, ref y, ref z);

      if (x < 0)
      {
        LeftHand.x = clampRotation(Convert.ToInt32((Constants.PI_2 + Math.Atan2(x, y)).ToDegrees() / 180 * 127));
      } else
      {
        LeftHand.x = clampRotation(Convert.ToInt32((Constants.PI_2 - Math.Atan2(x, y)).ToDegrees() / 180 * 127));
      }
      LeftHand.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, x)).ToDegrees() / 180 * 127));
      LeftHand.z = 0;

      LeftHand.x -= (TorsoUpper.x + TorsoLower.x + LeftShoulder.x + LeftElbow.x);
      LeftHand.y -= (LeftShoulder.y + LeftElbow.y);
    }

    private void calcRightHand(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.HandRight, JointType.WristRight, ref x, ref y, ref z);

      if (x > 0)
      {
        RightHand.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 + Math.Atan2(-x, y)).ToDegrees() / 180 * 127));
      }
      else
      {
        RightHand.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 - Math.Atan2(-x, y)).ToDegrees() / 180 * 127));
      }

      RightHand.y = clampRotation(-Convert.ToInt32((Math.Atan2(z, x)).ToDegrees() / 180 * 127));

      RightHand.z = 0;

      RightHand.x -= (RightElbow.x + RightShoulder.x + TorsoUpper.x + TorsoLower.x);
      RightHand.y -= (RightElbow.y + RightShoulder.y);
    }

    private void calcLeftHip(TimedFrame frame) {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.KneeLeft, JointType.HipLeft, ref x, ref y, ref z);

      LeftHip.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2).ToDegrees() / 180 * 127));
      LeftHip.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, y)).ToDegrees() / 180 * 127));
      LeftHip.z = 0;
    }

    private void calcLeftKnee(TimedFrame frame) {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.AnkleLeft, JointType.KneeLeft, ref x, ref y, ref z);

      LeftKnee.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2).ToDegrees() / 180 * 127));
      LeftKnee.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, y)).ToDegrees() / 180 * 127));
      LeftKnee.z = 0;

      LeftKnee.x -= LeftHip.x;
      LeftKnee.y -= LeftHip.y;
    }

    private void calcLeftFoot(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.FootLeft, JointType.AnkleLeft, ref x, ref y, ref z);

      LeftFoot.x = -clampRotation(Convert.ToInt32((Math.Atan2(z, x) + Constants.PI_2).ToDegrees() / 180 * 127));
      LeftFoot.y = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2 + Constants.PI_4).ToDegrees() / 180 * 127));
      LeftFoot.z = 0;
    }

    private void calcRightHip(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.KneeRight, JointType.HipRight, ref x, ref y, ref z);

      RightHip.x = clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2).ToDegrees() / 180 * 127));
      RightHip.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, y)).ToDegrees() / 180 * 127));
      RightHip.z = 0;
    }

    private void calcRightKnee(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.AnkleRight, JointType.KneeRight, ref x, ref y, ref z);

      RightKnee.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2).ToDegrees() / 180 * 127));
      RightKnee.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, y)).ToDegrees() / 180 * 127));
      RightKnee.z = 0;

      RightKnee.x -= RightHip.x;
      RightKnee.y -= RightHip.y;
    }

    private void calcRightFoot(TimedFrame frame)
    {
      double x = 0, y = 0, z = 0;
      frame.getOffset(JointType.FootRight, JointType.AnkleRight, ref x, ref y, ref z);

      RightFoot.x = clampRotation(Convert.ToInt32((Math.Atan2(z, x) + Constants.PI_2).ToDegrees() / 180 * 127));
      RightFoot.y = clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_4).ToDegrees() / 180 * 127));
      RightFoot.z = 0;
    }

    public void send(float speed)
    {
      if (!bUse) return;
      if (bTorsoLower) sendMessage("torsoLower", TorsoLower, speed);
      if (bTorsoUpper) sendMessage("torsoUpper", TorsoUpper, speed);
      if (bHead) sendMessage("head", Head, speed);
      if (bShoulderLeft) sendMessage("armLeftUpper", LeftShoulder, speed);
      if (bElbowLeft) sendMessage("armLeftLower", LeftElbow, speed);
      if (bHandLeft) sendMessage("handLeft", LeftHand, speed);
      if (bShoulderRight) sendMessage("armRightUpper", RightShoulder, speed);
      if (bElbowRight) sendMessage("armRightLower", RightElbow, speed);
      if (bHandRight) sendMessage("handRight", RightHand, speed);
      if (bHipLeft) sendMessage("legLeftUpper", LeftHip, speed);
      if (bKneeLeft) sendMessage("legLeftLower", LeftKnee, speed);
      if (bFootLeft) sendMessage("footLeft", LeftFoot, speed);
      if (bHipRight) sendMessage("legRightUpper", RightHip, speed);
      if (bKneeRight) sendMessage("legRightLower", RightKnee, speed);
      if (bFootRight) sendMessage("footRight", RightFoot, speed);
    }

    public void export(BinaryWriter writer)
    {
      if (bHead         ) { writer.Write((int)BODYPART.HEAD       ); writer.Write(Head.x         ); writer.Write(Head.y         ); writer.Write(Head.z         ); }
      if (bTorsoUpper   ) { writer.Write((int)BODYPART.TORSO_UPPER); writer.Write(TorsoUpper.x   ); writer.Write(TorsoUpper.y   ); writer.Write(TorsoUpper.z   ); }
      if (bTorsoLower   ) { writer.Write((int)BODYPART.TORSO_LOWER); writer.Write(TorsoLower.x   ); writer.Write(TorsoLower.y   ); writer.Write(TorsoLower.z   ); }
      if (bShoulderLeft ) { writer.Write((int)BODYPART.ARMLU      ); writer.Write(LeftShoulder.x ); writer.Write(LeftShoulder.y ); writer.Write(LeftShoulder.z ); }
      if (bElbowLeft    ) { writer.Write((int)BODYPART.ARMLL      ); writer.Write(LeftElbow.x    ); writer.Write(LeftElbow.y    ); writer.Write(LeftElbow.z    ); }
      if (bHandLeft     ) { writer.Write((int)BODYPART.HANDL      ); writer.Write(LeftHand.x     ); writer.Write(LeftHand.y     ); writer.Write(LeftHand.z     ); }
      if (bShoulderRight) { writer.Write((int)BODYPART.ARMRU      ); writer.Write(RightShoulder.x); writer.Write(RightShoulder.y); writer.Write(RightShoulder.z); }
      if (bElbowRight   ) { writer.Write((int)BODYPART.ARMRL      ); writer.Write(RightElbow.x   ); writer.Write(RightElbow.y   ); writer.Write(RightElbow.z   ); }
      if (bHandRight    ) { writer.Write((int)BODYPART.HANDR      ); writer.Write(RightHand.x    ); writer.Write(RightHand.y    ); writer.Write(RightHand.z    ); }
      if (bHipLeft      ) { writer.Write((int)BODYPART.LEGLU      ); writer.Write(LeftHip.x      ); writer.Write(LeftHip.y      ); writer.Write(LeftHip.z      ); }
      if (bKneeLeft     ) { writer.Write((int)BODYPART.LEGLL      ); writer.Write(LeftKnee.x     ); writer.Write(LeftKnee.y     ); writer.Write(LeftKnee.z     ); }
      if (bFootLeft     ) { writer.Write((int)BODYPART.FOOTL      ); writer.Write(LeftFoot.x     ); writer.Write(LeftFoot.y     ); writer.Write(LeftFoot.z     ); }
      if (bHipRight     ) { writer.Write((int)BODYPART.LEGRU      ); writer.Write(RightHip.x     ); writer.Write(RightHip.y     ); writer.Write(RightHip.z     ); }
      if (bKneeRight    ) { writer.Write((int)BODYPART.LEGRL      ); writer.Write(RightKnee.x    ); writer.Write(RightKnee.y    ); writer.Write(RightKnee.z    ); }
      if (bFootRight    ) { writer.Write((int)BODYPART.FOOTR      ); writer.Write(RightFoot.x    ); writer.Write(RightFoot.y    ); writer.Write(RightFoot.z    ); }
      writer.Write((int)BODYPART.INVALID);
    }

    public void sendMessage(String part, VecI rot, float speed)
    {
      if(osc != null) osc.Send(new OscMessage("/a", "Vir1", "relrotate", part, 127 + rot.x, 127 + rot.y, 127 + rot.z, speed));
    }

    private static int clampRotation(int rot)
    {
      while (rot > 127) rot -= 255;
      while (rot < -127) rot += 255;
      return rot;
    }

    public static double clampRadians(double value)
    {
      while (value > Constants.PI) value -= Constants.PI2;
      while (value < -Constants.PI) value += Constants.PI2;
      return value;
    }

    private void setDebugXYZ(double x, double y, double z)
    {
      debug.clear();
      debug.setLine1("Offset   X: " + x.ToString("0.###") + " Y: " + y.ToString("0.###") + " Z: " + z.ToString("0.###"));

      debug.setBlueDot1(x * 100, y * 100);
      debug.setBlueDot2(x * 100, z * 100);
    }

    private void setDebugRotation(VecI rot)
    {
      debug.setLine2("Rot X: " + rot.x.ToString() + " Y: " + rot.y.ToString());
    }
  }
}
