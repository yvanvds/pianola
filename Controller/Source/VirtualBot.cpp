/*
  ==============================================================================

    virtualBot.cpp
    Created: 18 Sep 2016 4:24:11pm
    Author:  yvan

  ==============================================================================
*/

#include "VirtualBot.h"
#include "JuceHeader.h"
#include "Defines.h"
#include "MonitorWindow.h"
#include "../../Shared/Messages.h"
#include "Vector.h"

VirtualBot::VirtualBot() {

}

void VirtualBot::handleMessage(const OSCMessage & message) {
	if (message[1].getString().compareIgnoreCase("rotate") == 0) {
		if (message.size() != 7) {
			ToLog("Invalid bone rotation");
		}
		else {
			// bone rotation needs 5 bytes and a float
			// message - bone - move x - move y - move z - speed

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::JOINTROTATE);

			BODYPART part = getBodyPart(message[2].getString());
			if (part == BODYPART::INVALID) {
				ToLog("Invalid body part: " + message[2].getString());
			}
			else {
				out.writeByte((unsigned char)part);
        out.writeByte((unsigned char)message[3].getInt32());
        out.writeByte((unsigned char)message[4].getInt32());
        out.writeByte((unsigned char)message[5].getInt32());
				
				float time = message[6].getFloat32();
				out.writeFloat(time);

				send(out.getData(), out.getDataSize());
			}
		}
	}
	else if (message[1].getString().compareIgnoreCase("relrotate") == 0) {
		if (message.size() != 7) {
			ToLog("Invalid bone rotation");
		}
		else {
			// bone rotation needs 5 bytes and a float
			// message - bone - move x - move y - move z - speed

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::JOINTRELROTATE);

			BODYPART part = getBodyPart(message[2].getString());
			if (part == BODYPART::INVALID) {
				ToLog("Invalid body part: " + message[2].getString());
			}
			else {
				out.writeByte((unsigned char)part);
        out.writeByte((unsigned char)message[3].getInt32());
        out.writeByte((unsigned char)message[4].getInt32());
        out.writeByte((unsigned char)message[5].getInt32());
       
				float time = message[6].getFloat32();
				out.writeFloat(time);

				send(out.getData(), out.getDataSize());
			}
		}
	}
  else if (message[1].getString().compareIgnoreCase("kinectrotate") == 0) {
    if (message.size() != 7) {
      ToLog("Invalid kinect rotation");
    }
    else {
      // bone rotation needs 5 bytes and a float
      // message - bone - move x - move y - move z - speed

      MemoryOutputStream out;
      out.writeByte((unsigned char)MESSAGE::KINECTROTATE);

      BODYPART part = getBodyPart(message[2].getString());
      if (part == BODYPART::INVALID) {
        ToLog("Invalid body part: " + message[2].getString());
      }
      else {
        out.writeByte((unsigned char)part);
        out.writeByte((unsigned char)message[3].getInt32());
        out.writeByte((unsigned char)message[4].getInt32());
        out.writeByte((unsigned char)message[5].getInt32());
        //Vec coord;
        //coord.x = message[3].getInt32() - 127;
        //coord.y = message[4].getInt32() - 127;
        //coord.z = message[5].getInt32() - 127;
        //ConvertVecToRotation(coord, part);
        //out.writeByte((unsigned char)(coord.y + 127));
        //out.writeByte((unsigned char)(coord.z + 127));
        //out.writeByte((unsigned char)(coord.x + 127));

        float time = message[6].getFloat32();
        out.writeFloat(time);

        send(out.getData(), out.getDataSize());
      }
    }
  }
	else if (message[1].getString().compareIgnoreCase("offset") == 0) {
		if (message.size() != 7) {
			ToLog("Invalid bone offset");
		}
		else {
			// bone rotation needs 5 bytes and a float
			// message - bone - move x - move y - move z - speed

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::JOINTOFFSET);

			BODYPART part = getBodyPart(message[2].getString());
			if (part == BODYPART::INVALID) {
				ToLog("Invalid body part: " + message[2].getString());
			}
			else {
				out.writeByte((unsigned char)part);
				out.writeByte((unsigned char)message[3].getInt32());
				out.writeByte((unsigned char)message[4].getInt32());
				out.writeByte((unsigned char)message[5].getInt32());
				out.writeFloat(message[6].getFloat32());

				send(out.getData(), out.getDataSize());
			}
		}
	}
	else if (message[1].getString().compareIgnoreCase("scale") == 0) {
		if (message.size() != 5) {
			ToLog("Invalid bone scaling");
		}
		else {
			// bone scale needs 3 bytes and a float
			// message - bone - scale - speed

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::JOINTOFFSET);

			BODYPART part = getBodyPart(message[2].getString());
			if (part == BODYPART::INVALID) {
				ToLog("Invalid body part: " + message[2].getString());
			}
			else {
				out.writeByte((unsigned char)part);
				out.writeByte((unsigned char)message[3].getInt32());
				out.writeFloat(message[4].getFloat32());

				send(out.getData(), out.getDataSize());
			}
		}
	}
	else if (message[1].getString().compareIgnoreCase("constraint") == 0) {
		if (message.size() != 4) {
			ToLog("Invalid bone constraint");
		}
		else {
			// bone rotation needs 5 bytes and a float
			// message - bone - constraint multiplier

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::CONSTRAIN);

			BODYPART part = getBodyPart(message[2].getString());
			if (part == BODYPART::INVALID) {
				ToLog("Invalid body part: " + message[2].getString());
			}
			else {
				out.writeByte((unsigned char)part);
				out.writeFloat(message[3].getFloat32());

				send(out.getData(), out.getDataSize());
			}
		}
	}
	else if (message[1].getString().compareIgnoreCase("brown") == 0) {
		if (message.size() != 5) {
			ToLog("Invalid brown factor");
		}
		else {
			// brown factor needs 5 bytes and a float
			// message - bone - constraint multiplier

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::BROWN);

			BODYPART part = getBodyPart(message[2].getString());
			if (part == BODYPART::INVALID) {
				ToLog("Invalid body part: " + message[2].getString());
			}
			else {
				out.writeByte((unsigned char)part);
				out.writeByte((unsigned char)message[3].getInt32());
				out.writeFloat(message[4].getFloat32());

				send(out.getData(), out.getDataSize());
			}
		}
	}
	else if (message[1].getString().compareIgnoreCase("show") == 0) {
		if (message.size() != 4) {
			ToLog("Invalid bone show message");
		}
		else {
			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::JOINTSHOW);

			BODYPART part = getBodyPart(message[2].getString());
			if (part == BODYPART::INVALID) {
				ToLog("Invalid body part: " + message[2].getString());
			}
			else {
				out.writeByte((unsigned char)part);
				out.writeBool(message[3].getInt32());

				send(out.getData(), out.getDataSize());
			}
		}
	}
	else if (message[1].getString().compareIgnoreCase("camFrom") == 0) {
		if (message.size() != 6) {
			ToLog("Invalid camera position");
		}
		else {

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::CAM_FROM);

			// write vector
			out.writeByte((unsigned char)message[2].getInt32());
			out.writeByte((unsigned char)message[3].getInt32());
			out.writeByte((unsigned char)message[4].getInt32());

			// write time
			out.writeFloat(message[5].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}
	else if (message[1].getString().compareIgnoreCase("camAt") == 0) {
		if (message.size() != 6) {
			ToLog("Invalid camera target");
		}
		else {

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::CAM_AT);

			// write vector
			out.writeByte((unsigned char)message[2].getInt32());
			out.writeByte((unsigned char)message[3].getInt32());
			out.writeByte((unsigned char)message[4].getInt32());

			// write time
			out.writeFloat(message[5].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}
	else if (message[1].getString().compareIgnoreCase("camRoll") == 0) {
		if (message.size() != 4) {
			ToLog("Invalid camera roll");
		}
		else {

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::CAM_ROLL);

			// write value
			out.writeByte((unsigned char)message[2].getInt32());

			// write time
			out.writeFloat(message[3].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("dof") == 0) {
		if (message.size() != 4) {
			ToLog("Invalid depth of field");
		}
		else {

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::CAM_DOF);

			// write range
			out.writeFloat(message[2].getFloat32());

			// write speed
			out.writeFloat(message[3].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("ambient") == 0) {
		if (message.size() != 6) {
			ToLog("Invalid depth of field");
		}
		else {
			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::CAM_AMBIENT);

			// write color
			out.writeByte((unsigned char)message[2].getInt32());
			out.writeByte((unsigned char)message[3].getInt32());
			out.writeByte((unsigned char)message[4].getInt32());

			// write speed
			out.writeFloat(message[5].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("camspotlight") == 0) {
		if (message.size() != 6) {
			ToLog("Invalid Camera Spotlight Color");
		}
		else {
			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::CAM_SPOTCOLOR);

			// write color
			out.writeByte((unsigned char)message[2].getInt32());
			out.writeByte((unsigned char)message[3].getInt32());
			out.writeByte((unsigned char)message[4].getInt32());

			// write speed
			out.writeFloat(message[5].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("camspotpower") == 0) {
		if (message.size() != 4) {
			ToLog("Invalid Camera spotlight power");
		}
		else {

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::CAM_SPOTPOWER);

			// write power
			out.writeFloat(message[2].getFloat32());

			// write speed
			out.writeFloat(message[3].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("spot1pos") == 0) {
		if (message.size() != 6) {
			ToLog("Invalid Spot 1 position");
		}
		else {
			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::SPOT1_POS);

			// write position
			out.writeByte((unsigned char)message[2].getInt32());
			out.writeByte((unsigned char)message[3].getInt32());
			out.writeByte((unsigned char)message[4].getInt32());

			// write speed
			out.writeFloat(message[5].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("spot1color") == 0) {
		if (message.size() != 6) {
			ToLog("Invalid Spotlight  1 Color");
		}
		else {
			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::SPOT1_COLOR);

			// write color
			out.writeByte((unsigned char)message[2].getInt32());
			out.writeByte((unsigned char)message[3].getInt32());
			out.writeByte((unsigned char)message[4].getInt32());

			// write speed
			out.writeFloat(message[5].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("spot1power") == 0) {
		if (message.size() != 4) {
			ToLog("Invalid spotlight 1 power");
		}
		else {

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::SPOT1_POWER);

			// write power
			out.writeFloat(message[2].getFloat32());

			// write speed
			out.writeFloat(message[3].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("spot2pos") == 0) {
		if (message.size() != 6) {
			ToLog("Invalid Spot 2 position");
		}
		else {
			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::SPOT2_POS);

			// write position
			out.writeByte((unsigned char)message[2].getInt32());
			out.writeByte((unsigned char)message[3].getInt32());
			out.writeByte((unsigned char)message[4].getInt32());

			// write speed
			out.writeFloat(message[5].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("spot2color") == 0) {
		if (message.size() != 6) {
			ToLog("Invalid Spotlight 2 Color");
		}
		else {
			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::SPOT2_COLOR);

			// write color
			out.writeByte((unsigned char)message[2].getInt32());
			out.writeByte((unsigned char)message[3].getInt32());
			out.writeByte((unsigned char)message[4].getInt32());

			// write speed
			out.writeFloat(message[5].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("spot2power") == 0) {
		if (message.size() != 4) {
			ToLog("Invalid spotlight 2 power");
		}
		else {

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::SPOT2_POWER);

			// write power
			out.writeFloat(message[2].getFloat32());

			// write speed
			out.writeFloat(message[3].getFloat32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("background") == 0) {
		if (message.size() != 3) {
			ToLog("Invalid Background Message");
		}
		else {

			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::BACKGROUND);

			// write background ID
			out.writeByte((unsigned char)message[2].getInt32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("foreground") == 0) {
		if (message.size() != 4) {
			ToLog("Invalid Foreground Message");
		}
		else {
			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::FOREGROUND);

			// write foreground ID and alpha
			out.writeByte((unsigned char)message[2].getInt32());
			out.writeByte((unsigned char)message[3].getInt32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else if (message[1].getString().compareIgnoreCase("textMessage") == 0) {
		if (message.size() != 4) {
			ToLog("Invalid Text Message");
		}
		else {
			MemoryOutputStream out;
			out.writeByte((unsigned char)MESSAGE::MESSAGE);

			// write foreground ID and alpha
			String msg = message[2].getString();
			const char * bytes = msg.getCharPointer();
			int size = msg.getNumBytesAsUTF8();
			out.writeInt(size);
			for (int i = 0; i < size; i++) {
				out.writeByte(bytes[i]);
			}

			out.writeByte(message[3].getInt32());

			// send it
			send(out.getData(), out.getDataSize());
		}
	}

	else {
		ToLog(message);
	}
}

void VirtualBot::initialize() {

}

BODYPART VirtualBot::getBodyPart(const String & name) {
	if (name.equalsIgnoreCase("head"         )) return BODYPART::HEAD;
	if (name.equalsIgnoreCase("torsoUpper"   )) return BODYPART::TORSO_UPPER;
	if (name.equalsIgnoreCase("torsoLower"   )) return BODYPART::TORSO_LOWER;
	if (name.equalsIgnoreCase("armLeftUpper" )) return BODYPART::ARMLU;
	if (name.equalsIgnoreCase("armLeftLower" )) return BODYPART::ARMLL;
	if (name.equalsIgnoreCase("handLeft"     )) return BODYPART::HANDL;
	if (name.equalsIgnoreCase("armRightUpper")) return BODYPART::ARMRU;
	if (name.equalsIgnoreCase("armRightLower")) return BODYPART::ARMRL;
	if (name.equalsIgnoreCase("handRight"    )) return BODYPART::HANDR;
	if (name.equalsIgnoreCase("legLeftUpper" )) return BODYPART::LEGLU;
	if (name.equalsIgnoreCase("legLeftLower" )) return BODYPART::LEGLL;
	if (name.equalsIgnoreCase("footLeft"     )) return BODYPART::FOOTL;
	if (name.equalsIgnoreCase("legRightUpper")) return BODYPART::LEGRU;
	if (name.equalsIgnoreCase("legRightLower")) return BODYPART::LEGRL;
	if (name.equalsIgnoreCase("footRight"    )) return BODYPART::FOOTR;
	return BODYPART::INVALID;
}