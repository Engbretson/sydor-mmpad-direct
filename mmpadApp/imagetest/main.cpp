
//#include "stdlib.h"

#include "ttiff/include/tinytiffwriter.h"

#include <cstdio>
#include <cstdint>
#define MAX_WIDTH 512
#define MAX_HEIGHT 512
//    const long MMPAD_HEADER_BYTES = 256; 
//    const long MMPAD_FOOTER_BYTES = 2048-256; 
// or ???
     const long MMPAD_HEADER_BYTES = 0; 
    const long MMPAD_FOOTER_BYTES = 2048; 
   
    uint32_t mImageBuffer[MAX_HEIGHT][MAX_WIDTH]; 


#define asynSuccess 0
#define asynError 1
#define asynOverflow 2


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
    read_size = fread(mImageBuffer, sizeof(uint32_t), MAX_HEIGHT * MAX_WIDTH, imageFile); // Read the actual data

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
fp = fopen("geocalarray_background_100.raw","r+");
for (int i = 1; i <= 100; i++) {
status = readRawFrame(fp);
//printf("Status is %d %d \n",i,status);
strcpy(filename,"data/myfile");
add_number_and_extension_to_filename(filename, i, extension);

   tif=TinyTIFFWriter_open(filename, 32, TinyTIFFWriter_Int, 1, 512, 512, TinyTIFFWriter_GreyscaleAndAlpha);
   if (tif) {
//           printf("Add data to file. \n");
           TinyTIFFWriter_writeImage(tif, mImageBuffer);
           }
       TinyTIFFWriter_close(tif);
 strcpy(filename,"data/myfile");      
 
 add_number_and_extension_to_filename(filename, i, extension2);
fo = fopen(filename,"wb");
fwrite( mImageBuffer, 1, sizeof(mImageBuffer), fo); 
fclose(fo);

}
fclose(fp);

}

