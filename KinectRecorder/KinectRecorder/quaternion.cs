using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KinectRecorder
{
  class Quaternion : Vec4
  {
    public Quaternion(Vec4 v) : base(v) {}

    public Quaternion(Vec axis, double angle)
    {
      double sin = Math.Sin(angle * -0.5);
      base.w = Math.Cos(angle * -0.5);
      base.x = axis.x * sin;
      base.y = axis.y * sin;
      base.z = axis.z * sin;
    }

    public static Quaternion RotationBetweenVectors(Vec start, Vec dest)
    {
      start.normalize();
      dest.normalize();

      double cosTheta = Vec.Dot(start, dest);
      Vec rotationAxis;

      if(cosTheta < -1 + 0.001f)
      {
        rotationAxis = Vec.Cross(new Vec(0.0, 0.0, 1.0), start);
        if(rotationAxis.length2() < 0.01)
        {
          rotationAxis = Vec.Cross(new KinectRecorder.Vec(1.0, 0.0, 0.0), start);
        }

        rotationAxis.normalize();

        return new Quaternion(rotationAxis, 180.0);
      }

      rotationAxis = Vec.Cross(start, dest);
      double s = Math.Sqrt((1 + cosTheta) * 2);
      double invs = 1 / s;

      return new Quaternion(new Vec4(rotationAxis.x * invs, rotationAxis.y * invs, rotationAxis.z * invs, s * 0.5));
    }
  }
}
