
//#include "stdlib.h"

#include "ttiff/include/tinytiffwriter.h"

#include <cstdio>
#include <cstdint>
#define MAX_WIDTH 512
#define MAX_HEIGHT 512
//    const long MMPAD_HEADER_BYTES = 256; 
//    const long MMPAD_FOOTER_BYTES = 2048-256; 
// or ???
//    const long MMPAD_HEADER_BYTES = 0; 
//    const long MMPAD_FOOTER_BYTES = 2048; 
// or 
     const long MMPAD_HEADER_BYTES = 512; // per Valerie Fleischauer 4/26/2023
    const long MMPAD_FOOTER_BYTES = 2048; 
   
    uint32_t mImageBuffer[MAX_HEIGHT][MAX_WIDTH]; 
   uint32_t mImageBuffer1[MAX_HEIGHT][MAX_WIDTH]; 


#define asynSuccess 0
#define asynError 1
#define asynOverflow 2

// I can't actually do anything with this data, I think that it isn't what they say that it is
// i.e. if I tell ImageJ that the number is only 16-bit, I actually see some representation that
// matches the pictures of what it should be. So adding a test routine to pop off bits.
//
// Most of the data has nothing at all in the other 16-bits, so might just spike them if it helps

// this 24-bit, makes no difference, try 16-bit. And that generates a more reasonable image.

// so is this actually just an endian issue ? not if my code is correct.

// Lets try fliiping 32-bits down to 16-bits and see what happens, this works
// 24-bit shows some of the artifacts, but the artifacts swamp out everything else.
// what do we get if we just take the top 16-bits? sam sort of crap
// for now, just use the lower 16-bit


void convert_to_big_endian(uint32_t *array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = ((array[i] >> 24) & 0xff) | ((array[i] << 8) & 0xff0000) | ((array[i] >> 8) & 0xff00) | ((array[i] << 24) & 0xff000000);
    }
}


void convert_buffer32to24( uint32_t *buffer,  uint32_t *result, size_t buffer_size) {
    for (size_t i = 0; i < buffer_size; i++) {

//        int32_t value = buffer[i] >> 8;
//        if (value >= 0x800000) {
//            value |= 0xFF000000;
         int32_t value = buffer[i] & 0xFFFF; // only this generates 'seeable' data, 
//         int32_t value = buffer[i] & 0xFFFFFF; // only 24-bits shows articats correctly, no data
//         int32_t value = buffer[i] & 0xFFFF0000; //only upper 16-bit = crap

        result[i] = value;
    }
}

int readRawFrame(FILE *imageFile)
{
    int rtn;
    size_t read_size;

    // Advance past the header
    rtn = fseek(imageFile, MMPAD_HEADER_BYTES, SEEK_CUR);
    if (rtn)
    {
        return asynError;       // Something bad happend
    }

    //-=-= XXX This assumes a little-endian machine
    read_size = fread(mImageBuffer, sizeof(int32_t), MAX_HEIGHT * MAX_WIDTH, imageFile); // Read the actual data

    if (read_size < (MAX_HEIGHT * MAX_WIDTH)) // Didn't read all the data
    {
        return asynOverflow;
    }

    // Skip the footer
    rtn = fseek(imageFile, MMPAD_FOOTER_BYTES, SEEK_CUR);
    if (rtn)
    {
        return asynError;       // Something bad happened
    }

    return asynSuccess;
}

void add_number_and_extension_to_filename(char *filename, int num, char *extension) {
    // Determine the length of the filename
    int filename_len = strlen(filename);

    // Determine the length of the number when converted to a string
    int num_len = snprintf(NULL, 0, "%d", num);

    // Determine the length of the extension
    int extension_len = strlen(extension);

    // Allocate memory for the new filename
    char *new_filename = (char *) malloc((filename_len + num_len + extension_len + 3) * sizeof(char));
    if (new_filename == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for new filename.\n");
        exit(EXIT_FAILURE);
    }

    // Copy the filename into the new filename
    strncpy(new_filename, filename, filename_len);

    // Add the number and extension to the new filename
    snprintf(new_filename + filename_len, num_len + extension_len + 3, "_%d%s", num, extension);

    // Replace the old filename with the new filename
    strncpy(filename, new_filename, filename_len + num_len + extension_len + 3);

    // Free the memory allocated for the new filename
    free(new_filename);
}


int main () 
{
FILE *fp;
FILE *fo;
TinyTIFFWriterFile* tif;
char filename[60];
char extension[] = ".tif";
char extension2[] = ".raw";
int status;

size_t buffer_size = (sizeof(mImageBuffer) / 4);

fp = fopen("geocalarray_foreground_100.raw","r+");
for (int i = 1; i <= 100; i++) {
status = readRawFrame(fp);
//printf("Status is %d %d \n",i,status);
strcpy(filename,"data/myfile");
add_number_and_extension_to_filename(filename, i, extension);

   tif=TinyTIFFWriter_open(filename, 32, TinyTIFFWriter_Int, 1, 512, 512, TinyTIFFWriter_GreyscaleAndAlpha);
   if (tif) {
//           printf("Add data to file. \n");
           convert_buffer32to24((uint32_t *) mImageBuffer,(uint32_t *) mImageBuffer1,buffer_size);
//           convert_to_big_endian((uint32_t *)mImageBuffer,100);
           TinyTIFFWriter_writeImage(tif, mImageBuffer1);
           }
       TinyTIFFWriter_close(tif);
 strcpy(filename,"data/myfile");      
 
 add_number_and_extension_to_filename(filename, i, extension2);
fo = fopen(filename,"wb");
fwrite( mImageBuffer1, 1, sizeof(mImageBuffer1), fo); 
fclose(fo);

}
fclose(fp);

}

