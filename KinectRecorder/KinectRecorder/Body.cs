using LightBuzz.Vitruvius;
using Microsoft.Kinect;
using Rug.Osc;
using System;
using System.Collections.Generic;
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

    private bool bUse, bHead, bTorsoUpper, bTorsoLower, bShoulderLeft, bShoulderRight, bElbowLeft, bElbowright, bHandLeft, bHandRight, bHipLeft, bHipRight, bKneeLeft, bKneeRight, bFootLeft, bFootRight; 

    static OscSender osc = null;
    static IPAddress address = IPAddress.Parse("127.0.0.1");
    static int port = 34567;

    public Body()
    {
      if(osc == null)
      {
        osc = new OscSender(address, port);
        osc.Connect();
      }
    }

    public void SetRotations(TimedFrame frame, bool sendRotations = false)
    {
      int parentAngleX;
      int parentAngleY;

      int torsoAngleX;
      int torsoAngleY;

      double x = 0, y = 0, z = 0;

      // set used parts
      bUse = frame.Use;
      bHead = frame.Head;
      bTorsoUpper = frame.TorsoUpper;
      bTorsoLower = frame.TorsoLower;
      bShoulderLeft = frame.ShoulderLeft;
      bShoulderRight = frame.ShoulderRight;
      bElbowLeft = frame.ElbowLeft;
      bElbowright = frame.ElbowRight;
      bHandLeft = frame.HandLeft;
      bHandRight = frame.HandRight;
      bHipLeft = frame.HipLeft;
      bHipRight = frame.HipRight;
      bKneeLeft = frame.KneeLeft;
      bKneeRight = frame.KneeRight;
      bFootLeft = frame.FootLeft;
      bFootRight = frame.FootRight;

      {
        // lower torso
        frame.getOffset(JointType.SpineMid, JointType.SpineBase, ref x, ref y, ref z);

        TorsoLower.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) - Constants.PI_2).ToDegrees() / 180 * 127));
        TorsoLower.y = -clampRotation(Convert.ToInt32((Math.Atan2(z, y)).ToDegrees() / 180 * 127));
        TorsoLower.z = 0;

        torsoAngleX = TorsoLower.x;
        torsoAngleY = TorsoLower.y;
      }

      {
        // upper torso
        frame.getOffset(JointType.SpineShoulder, JointType.SpineMid, ref x, ref y, ref z);

        TorsoUpper.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) - Constants.PI_2).ToDegrees() / 180 * 127)) + torsoAngleX;
        TorsoUpper.y = -clampRotation(Convert.ToInt32((Math.Atan2(z, y)).ToDegrees() / 180 * 127)) + torsoAngleY;
        TorsoUpper.z = 0;

        torsoAngleX += TorsoUpper.x;
        torsoAngleY += TorsoUpper.y;
      }

      {
        // head
        frame.getOffset(JointType.Head, JointType.Neck, ref x, ref y, ref z);

        Head.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) - Constants.PI_2).ToDegrees() / 180 * 127)) + torsoAngleX;
        Head.y = -clampRotation(Convert.ToInt32((Math.Atan2(z, y)).ToDegrees() / 180 * 127)) + torsoAngleY;
        Head.z = 0;
      }

      {
        // left shoulder
        frame.getOffset(JointType.ElbowLeft, JointType.ShoulderLeft, ref x, ref y, ref z);

        if(x < 0)
        {
          LeftShoulder.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 + Math.Atan2(x, y)).ToDegrees() / 180 * 127));
        } else
        {
          LeftShoulder.x = clampRotation(Convert.ToInt32(clampRadians(Constants.PI_2 - Math.Atan2(x, y)).ToDegrees() / 180 * 127));
        }
        
        LeftShoulder.y = clampRotation(Convert.ToInt32(clampRadians(Constants.PI + Math.Atan2(z, x)).ToDegrees() / 180 * 127));
        LeftShoulder.z = 0;

        

        LeftShoulder.x -= torsoAngleX;

        parentAngleX = torsoAngleX + LeftShoulder.x;
        parentAngleY = LeftShoulder.y;
      }

      {
        // left elbow
        frame.getOffset(JointType.WristLeft, JointType.ElbowLeft, ref x, ref y, ref z);

        LeftElbow.x = clampRotation(Convert.ToInt32((Constants.PI_2 + Math.Atan2(x, y)).ToDegrees() / 180 * 127)) - parentAngleX;
        LeftElbow.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, x)).ToDegrees() / 180 * 127)) - parentAngleY;
        LeftElbow.z = 0;

        parentAngleX += LeftElbow.x;
        parentAngleY += LeftElbow.y;
      }

      {
        // left hand
        frame.getOffset(JointType.HandLeft, JointType.WristLeft, ref x, ref y, ref z);

        LeftHand.x = clampRotation(Convert.ToInt32((Constants.PI_2 + Math.Atan2(x, y)).ToDegrees() / 180 * 127)) - parentAngleX;
        LeftHand.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, x)).ToDegrees() / 180 * 127)) - parentAngleY;
        LeftHand.z = 0;
      }

      {
        // right shoulder
        frame.getOffset(JointType.ElbowRight, JointType.ShoulderRight, ref x, ref y, ref z);

        RightShoulder.x = clampRotation(-Convert.ToInt32(clampRadians(Math.Atan2(x, y) - Constants.PI_2).ToDegrees() / 180 * 127)) - torsoAngleX;
        RightShoulder.y = clampRotation(-Convert.ToInt32((Math.Atan2(z, x)).ToDegrees() / 180 * 127));
        RightShoulder.z = 0;

        parentAngleX = torsoAngleX + RightShoulder.x;
        parentAngleY = RightShoulder.y;
      }

      {
        // right elbow
        frame.getOffset(JointType.WristRight, JointType.ElbowRight, ref x, ref y, ref z);

        RightElbow.x = -clampRotation(Convert.ToInt32((Math.Atan2(x, y) - Constants.PI_2).ToDegrees() / 180 * 127)) - parentAngleX;
        RightElbow.y = -clampRotation(Convert.ToInt32((Math.Atan2(z, x)).ToDegrees() / 180 * 127));
        RightElbow.z = 0;

        parentAngleX += RightElbow.x;
        parentAngleY += RightElbow.y;
      }

      {
        // right hand
        frame.getOffset(JointType.HandRight, JointType.WristRight, ref x, ref y, ref z);

        RightHand.x = -clampRotation(Convert.ToInt32((Math.Atan2(x, y) - Constants.PI_2).ToDegrees() / 180 * 127)) - parentAngleX;
        RightHand.y = -clampRotation(Convert.ToInt32((Math.Atan2(z, x)).ToDegrees() / 180 * 127));
        RightHand.z = 0;
      }

      {
        // left Leg Upper
        frame.getOffset(JointType.KneeLeft, JointType.HipLeft, ref x, ref y, ref z);

        LeftHip.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2).ToDegrees() / 180 * 127));
        LeftHip.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, y)).ToDegrees() / 180 * 127));
        LeftHip.z = 0;

        parentAngleX = LeftHip.x;
        parentAngleY = LeftHip.y;
      }

      {
        // left Leg Lower
        frame.getOffset(JointType.AnkleLeft, JointType.KneeLeft, ref x, ref y, ref z);

        LeftKnee.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2).ToDegrees() / 180 * 127) - parentAngleX);
        LeftKnee.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, y)).ToDegrees() / 180 * 127) - parentAngleY);
        LeftKnee.z = 0;

        parentAngleX += LeftKnee.x;
        parentAngleY += LeftKnee.y;
      }

      {
        // left Foot
        frame.getOffset(JointType.FootLeft, JointType.AnkleLeft, ref x, ref y, ref z);

        LeftFoot.x = -clampRotation(Convert.ToInt32((Math.Atan2(z, x) + Constants.PI_2).ToDegrees() / 180 * 127));
        LeftFoot.y = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2 + Constants.PI_4).ToDegrees() / 180 * 127));
        LeftFoot.z = 0;
      }

      {
        // Right Leg Upper
        frame.getOffset(JointType.KneeRight, JointType.HipRight, ref x, ref y, ref z);

        RightHip.x = clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2).ToDegrees() / 180 * 127));
        RightHip.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, y)).ToDegrees() / 180 * 127));
        RightHip.z = 0;

        parentAngleX = RightHip.x;
        parentAngleY = RightHip.y;
      }

      {
        // right Leg Lower
        frame.getOffset(JointType.AnkleRight, JointType.KneeRight, ref x, ref y, ref z);

        RightKnee.x = -clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_2).ToDegrees() / 180 * 127) - parentAngleX);
        RightKnee.y = clampRotation(Convert.ToInt32((Constants.PI + Math.Atan2(z, y)).ToDegrees() / 180 * 127) - parentAngleY);
        RightKnee.z = 0;

        parentAngleX = RightKnee.x;
        parentAngleY = RightKnee.y;
      }

      {
        // right Foot
        frame.getOffset(JointType.FootRight, JointType.AnkleRight, ref x, ref y, ref z);

        RightFoot.x = clampRotation(Convert.ToInt32((Math.Atan2(z, x) + Constants.PI_2).ToDegrees() / 180 * 127));
        RightFoot.y = clampRotation(Convert.ToInt32((Math.Atan2(y, x) + Constants.PI_4).ToDegrees() / 180 * 127));
        RightFoot.z = 0;
      }

      if(sendRotations)
      {
        send(10);
      }
    }

    public void send(float speed)
    {
      if (!bUse) return;
      if(bTorsoLower) sendMessage("torsoLower", TorsoLower, speed);
      if(bTorsoUpper) sendMessage("torsoUpper", TorsoUpper, speed);
      if(bHead) sendMessage("head", Head, speed);
      if(bShoulderLeft) sendMessage("armLeftUpper", LeftShoulder, speed);
      if(bElbowLeft) sendMessage("armLeftLower", LeftElbow, speed);
      if(bHandLeft) sendMessage("handLeft", LeftHand, speed);
      if(bShoulderRight) sendMessage("armRightUpper", RightShoulder, speed);
      if(bElbowright) sendMessage("armRightLower", RightElbow, speed);
      if(bHandRight) sendMessage("handRight", RightHand, speed);
      if(bHipLeft) sendMessage("legLeftUpper", LeftHip, speed);
      if(bKneeLeft) sendMessage("legLeftLower", LeftKnee, speed);
      if(bFootLeft) sendMessage("footLeft", LeftFoot, speed);
      if(bHipRight) sendMessage("legRightUpper", RightHip, speed);
      if(bKneeRight) sendMessage("legRightLower", RightKnee, speed);
      if(bFootRight) sendMessage("footRight", RightFoot, speed);
    }

    public void sendMessage(String part, VecI rot, float speed)
    {
      osc.Send(new OscMessage("/a", "Vir1", "relrotate", part, 127 + rot.x, 127 + rot.y, 127 + rot.z, speed));
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
  }
}
