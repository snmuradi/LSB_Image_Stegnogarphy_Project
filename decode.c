#include <stdio.h>
#include <string.h>
#include "types.h"
#include "common.h"
#include "decode.h"

/*Function Definitions*/
d_Status files_open(DecodeInfo *decInfo)
{
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");
    // Do error handling
    if (decInfo->fptr_stego_image == NULL)
    {
        perror("fopen");
        fprintf(stderr, "INFO : ERROR : Unable to open file %s\n", decInfo->stego_image_fname);

        return d_failure;
    }

    decInfo->fptr_secret_data = fopen(decInfo->secret_data_fname, "w");
    // Do error handling
    if (decInfo->fptr_secret_data == NULL)
    {
        perror("fopen");
        fprintf(stderr, "INFO : ERROR : Unable to open file %s\n", decInfo->secret_data_fname);

        return d_failure;
    }
    return d_success;
}

d_Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    if (strcmp(strstr(argv[2], ".bmp"), ".bmp") == 0)
    {
        decInfo->stego_image_fname = argv[2];
    }
    else
    {
        return d_failure;
    }
    if (argv[3] != NULL)
    {
        decInfo->secret_data_fname = argv[3];
    }
    else
    {
        decInfo->secret_data_fname = "default.txt";
    }
    return d_success;
}

d_Status decode_image_to_data(DecodeInfo *decInfo)
{
    for (int i = 0; i < 8; i++)
    {
        decInfo->decode_data[0] |= (decInfo->str[i] & 1) << i;
    }
    return d_success;
}

d_Status decode_magic_string(DecodeInfo *decInfo)
{
    fseek(decInfo->fptr_stego_image, 54, SEEK_SET);
    for (int i = 0; i < strlen(MAGIC_STRING); i++)
    {
        fread(decInfo->str, 8, 1, decInfo->fptr_stego_image);
        decInfo->decode_data[0] = 0;

        decode_image_to_data(decInfo);

        if (decInfo->decode_data[0] == MAGIC_STRING[i])
        {
            continue;
        }
        else
        {
            return d_failure;
        }
    }
    return d_success;
}

d_Status decode_size_to_data(DecodeInfo *decInfo)
{
    fread(decInfo->secret_file_size, 32, 1, decInfo->fptr_stego_image);
    decInfo->image_data_size = 0;
    for(int i = 0; i < 32; i++)
    {
	 decInfo->image_data_size |= (decInfo->secret_file_size[i] & 1) << i;
    }
    return d_success;
}


d_Status decode_secret_file_extn_size(DecodeInfo *decInfo)
{
    decode_size_to_data(decInfo);
    return d_success;
}

d_Status decode_secret_file_extn(DecodeInfo *decInfo)
{
   for(int i = 0; i < decInfo->image_data_size; i++)
   {
	fread(decInfo->str, 8, 1, decInfo->fptr_stego_image);
	decInfo->decode_data[0] = 0;

	decode_image_to_data(decInfo);
   }
   //printf("INFO : File pointer is %d\n", ftell(decInfo->fptr_stego_image));
   return d_success;
}

d_Status decode_secret_file_size(DecodeInfo *decInfo)
{
    decode_size_to_data(decInfo);
    return d_success;
}

d_Status decode_secret_file_data(DecodeInfo *decInfo)
{
    for(int i = 0; i < decInfo->image_data_size; i++)
    {
	 fread(decInfo->str, 8, 1, decInfo->fptr_stego_image);
	 decInfo->decode_data[0] = 0;

	 decode_image_to_data(decInfo);

//	 printf("%c", decInfo->decode_data[0]);

	 fputc(decInfo->decode_data[0], decInfo->fptr_secret_data);
    }
    //printf("INFO : FIle pointer is %d\n", ftell(decInfo->fptr_stego_image));
    return d_success;
}

d_Status do_decoding(DecodeInfo *decInfo)
{
    if (files_open(decInfo) == d_success)
    {
        printf("INFO : Files opened successfully\n");
	if(decode_magic_string(decInfo) == d_success)
	{
	   printf("INFO : Magic string decoded successfully\n");
	   if(decode_secret_file_extn_size(decInfo) == d_success)
	   {
		printf("INFO : Secret file extension size decoded successfully\n");
		if(decode_secret_file_extn(decInfo) == d_success)
		{
		     printf("INFO : Secret file extension decoded successfully\n");
                     if(decode_secret_file_size(decInfo) == d_success)
		     {
			  printf("INFO : Secret file size decoded successfully\n");
			  if(decode_secret_file_data(decInfo) == d_success)
			  {
			      printf("INFO : Secret file data decoded successfully\n");
			  }
			  else
			  {
			      printf("ERROR : Failed to decode secret file data\n");
			      return d_failure;
			  }
		     }
		     else
		     {
			  printf("ERROR : Failed to decode secret file size\n");
			  return d_failure;
		     }
		}
		else
		{
		     printf("ERROR : Failed to decode file extension\n");
		     return d_failure;
		}
	   }
	   else
	   {
		printf("ERROR : Failed to decode secret file extension size\n");
                return d_failure;
	   }
	}
	else
	{
	    printf("ERROR : Failed to decode magic string\n");
            return d_failure;
	}

    }
    else
    {
        printf("INFO : ERROR : Failed to open files\n");
        return d_failure;
    }

    return d_success;
}































