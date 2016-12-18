/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_107228632_INCLUDED
#define BINARYDATA_H_107228632_INCLUDED

namespace BinaryData
{
    extern const char*   led_off_png;
    const int            led_off_pngSize = 1087;

    extern const char*   led_on_png;
    const int            led_on_pngSize = 1502;

    extern const char*   cog_png;
    const int            cog_pngSize = 1268;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 3;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
