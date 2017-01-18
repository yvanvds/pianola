using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KinectRecorder
{
  class Matrix3
  {
    public Vec x = new Vec();
    public Vec y = new Vec();
    public Vec z = new Vec();

    public Matrix3() { }

    public Matrix3(Matrix3 source)
    {
      x = source.x;
      y = source.y;
      z = source.z;
    }

    public Vec angles()
    {
      Vec O = new KinectRecorder.Vec();
      Matrix3 temp = new Matrix3(this);
      

      return O;
    } 

    public Matrix3 setRotateX(double angle)
    {
      double s, c;
      s = Math.Sin(angle);
      c = Math.Cos(angle);
      x.set(1, 0, 0);
      y.set(0, c, s);
      z.set(0, -s, c);
      return this;
    }

    public Matrix3 setRotateY(double angle)
    {
      double s, c;
      s = Math.Sin(angle);
      c = Math.Cos(angle);
      x.set(c, 0, -s);
      y.set(0, 1, 0);
      z.set(s, 0, c);
      return this;
    }

    public Matrix3 setRotateZ(double angle)
    {
      double s, c;
      s = Math.Sin(angle);
      c = Math.Cos(angle);
      x.set(c, s, 0);
      y.set(-s, c, 0);
      z.set(0, 0, 1);
      return this;
    }

    internal void mul(Matrix3 m, Matrix3 dest)
    {
      double x, y, z;
      if(Object.ReferenceEquals(m, dest))
      {
        x = m.x.x; y = m.y.x; z = m.z.x;
        dest.x.x = x * this.x.x + y * this.x.y + z * this.x.z;
        dest.y.x = x * this.y.x + y * this.y.y + z * this.y.z;
        dest.z.x = x * this.z.x + y * this.z.y + z * this.z.z;

        x = m.x.y; y = m.y.y; z = m.z.y;
        dest.x.y = x * this.x.x + y * this.x.y + z * this.x.z;
        dest.y.y = x * this.y.x + y * this.y.y + z * this.y.z;
        dest.z.y = x * this.z.x + y * this.z.y + z * this.z.z;

        x = m.x.z; y = m.y.z; z = m.z.z;
        dest.x.z = x * this.x.x + y * this.x.y + z * this.x.z;
        dest.y.z = x * this.y.x + y * this.y.y + z * this.y.z;
        dest.z.z = x * this.z.x + y * this.z.y + z * this.z.z;
      } else
      {
        x = this.x.x; y = this.x.y; z = this.x.z;
        dest.x.x = x * m.x.x + y * m.y.x + z * m.z.x;
        dest.x.y = x * m.x.y + y * m.y.y + z * m.z.y;
        dest.x.z = x * m.x.z + y * m.y.z + z * m.z.z;

        x = this.y.x; y = this.y.y; z = this.y.z;
        dest.y.x = x * m.x.x + y * m.y.x + z * m.z.x;
        dest.y.y = x * m.x.y + y * m.y.y + z * m.z.y;
        dest.y.z = x * m.x.z + y * m.y.z + z * m.z.z;

        x = this.z.x; y = this.z.y; z = this.z.z;
        dest.z.x = x * m.x.x + y * m.y.x + z * m.z.x;
        dest.z.y = x * m.x.y + y * m.y.y + z * m.z.y;
        dest.z.z = x * m.x.z + y * m.y.z + z * m.z.z;
      }
    }
  }

  class Matrix : Matrix3
  {
    public Vec pos = new Vec();

    public void mul(Matrix3 m, Matrix dest)
    {
      double x = pos.x;
      double y = pos.y;
      double z = pos.z;

      dest.pos.x = x * m.x.x + y * m.y.x + z * m.z.x;
      dest.pos.y = x * m.x.y + y * m.y.y + z * m.z.y;
      dest.pos.z = x * m.x.z + y * m.y.z + z * m.z.z;

      base.mul(m, dest.orn());
    }

    public Matrix mul(Matrix3 matrix)
    {
      mul(matrix, this);
      return this;
    }

    public Matrix3 orn() { return this; }

    public void multiply(Matrix3 m) { mul(m); }

    public void rotateX(double angle)
    {
      if (angle != 0)
      {
        Matrix3 m = new KinectRecorder.Matrix3();
        m.setRotateX(angle);
        multiply(m);
      }
    }

    public void rotateY(double angle)
    {
      if (angle != 0)
      {
        Matrix3 m = new KinectRecorder.Matrix3();
        m.setRotateY(angle);
        multiply(m);
      }
    }

    public void rotateZ(double angle)
    {
      if (angle != 0)
      {
        Matrix3 m = new KinectRecorder.Matrix3();
        m.setRotateZ(angle);
        multiply(m);
      }
    }
  }
}
