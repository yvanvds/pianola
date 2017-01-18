using Microsoft.Kinect;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

static class Constants
{
  public const double PI2 = 6.282;
  public const double PI = 3.1415926535897932; // 180 degrees
  public const double PI_2 = 1.5707963267948966; // 90 degrees
  public const double PI_3 = 1.0471975511965977; // 90 degrees
  public const double PI_4 = 0.7853981633974483; // 45 degrees
  public const double PI_6 = 0.5235987755982988; // 30 degrees
}



namespace KinectRecorder
{
  class Vec
  {
    public double x, y, z;

    public Vec() { x = y = z = 0; }
    public Vec(double x, double y, double z) { this.x = x; this.y = y; this.z = z; }
    public Vec(CameraSpacePoint point) { x = point.X; y = point.Y; z = point.Z; }

    public void set(double x, double y, double z)
    {
      this.x = x;
      this.y = y;
      this.z = z;
    }

    public static Vec operator-(Vec a, Vec b)
    {
      return new KinectRecorder.Vec(a.x - b.x, a.y - b.y, a.z - b.z);
    }

    public static double Dot(Vec a, Vec b)
    {
      return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    public static Vec Cross(Vec a, Vec b)
    {
      return new KinectRecorder.Vec(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
    }

    public double length2()
    {
      return x * x + y * y + z * z;
    }

    public double normalize()
    {
      double l = length2();
      if(l != 0) {
        l = Math.Sqrt(l);
        x /= l; y /= l; z /= l;
        return l;
      }
      return 0;
    }

  }

  class Vec4
  {
    public double x, y, z, w;

    public Vec4(double x, double y, double z, double w)
    {
      this.x = x; this.y = y; this.z = z; this.w = w;
    } 

    public Vec4(Vec4 v)
    {
      this.x = v.x;
      this.y = v.y;
      this.z = v.z;
      this.w = v.w;
    }

    public Vec4()
    {
      this.x = this.y = this.z = this.w = 0;
    }
  }

  class VecI
  {
    public int x, y, z;

    public VecI() { x = y = z = 0; }
    public VecI(int x, int y, int z) { this.x = x; this.y = y; this.z = z; }
    public VecI(CameraSpacePoint point) { x = (int)point.X; y = (int)point.Y; z = (int)point.Z; }

    public void set(int x, int y, int z)
    {
      this.x = x;
      this.y = y;
      this.z = z;
    }

    public static VecI operator -(VecI a, VecI b)
    {
      return new KinectRecorder.VecI(a.x - b.x, a.y - b.y, a.z - b.z);
    }
  }

  public class Vec2
  {
    public double x, y;

    public static double Dot(Vec2 A, Vec2 B)
    {
      return A.x * B.x + A.y * B.y;
    }

    public static double Cross(Vec2 A, Vec2 B)
    {
      return A.x * B.y - A.y * B.x;
    }

    public static double GetAngle(Vec2 A, Vec2 B)
    {
      return Math.Atan2(Cross(A, B), Dot(A, B));
    }
  }
}
