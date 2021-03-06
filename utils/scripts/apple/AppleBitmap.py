"""
 * Copyright (c) 2018 Anthony Beaucamp.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented * you must not
 *   claim that you wrote the original software. If you use this software in a
 *   product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not
 *   be misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any distribution.
 *
 *   4. The names of this software and/or it's copyright holders may not be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
"""

from AppleHires import *
from PIL import Image
import io, sys

mode = sys.argv[1]
input = sys.argv[2]
output = sys.argv[3]

try:
    ###################
    # Read source file
    img1 = Image.open(input)
    rawdata = list(img1.getdata())
    colors = max(rawdata)

    # Prepare data lists
    main = [chr(0)]*8192
    if mode == 'double':
        aux = [chr(0)]*8192

    # Convert bitmap
    for i in range(192):
        for j in range(0,140,7):
            pixels = rawdata[i*140+j:i*140+j+7]
            if mode == 'single':
                # Reduce palette?
                if colors > 6:
                    pixels = RemapDHR2SHR(pixels)
                res = AssignColorGroup(pixels)    
                pixels = res[0]; block = res[1]
                
                # Process in blocks of 7 pixels, to be packed into 2 bytes
                for k in range(7):
                    SetSHRColor(block, k, pixels[k])
                main[HiresLines[i]+(j*2)/7+0] = (chr(block[0]))
                main[HiresLines[i]+(j*2)/7+1] = (chr(block[1]))
                
            else:
                # Process in blocks of 7 pixels, to be packed into 4 bytes
                block = [0,0,0,0]
                for k in range(7):
                    SetDHRColor(block, k, pixels[k])
                aux [HiresLines[i]+(j*2)/7+0] = (chr(block[0]))
                main[HiresLines[i]+(j*2)/7+0] = (chr(block[1]))
                aux [HiresLines[i]+(j*2)/7+1] = (chr(block[2]))
                main[HiresLines[i]+(j*2)/7+1] = (chr(block[3]))

    # Write to file
    f2 = io.open(output, 'wb')
    if mode == 'double':
        f2.write(''.join(aux))
    f2.write(''.join(main))
    f2.close()

except:
    print "Error: cannot convert " + input + "... (is it a 140x192 PNG file with 6 or 16 color palette?)"
