#include <stdio.h>
#include "encode.h"
#include "types.h"
#include "string.h"
#include "decode.h"


int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Error: Insufficient arguments.\n");
	printf("Usage:\nFor Encoding:./a.out -e beautiful.bmp secret.txt [stegano.bmp]\nFor Decoding:./a.out -d stegano.bmp [data.txt]\n");
        return 1;
    } 

    int res = check_operation_type(argv);
    EncodeInfo E1;
    DecodeInfo D1;
    

    if(res == e_encode)
    {
	if(argc < 4)
	{
	    printf("Error: Insufficient arguments for encoding.\n");
            printf("Usage: ./a.out -e beautiful.bmp secret.txt [stegano.bmp]\n");
            return 1;
	}
	printf("INFO : Selected Encoding\n");
	//read and validate
	if(read_and_validate_encode_args(argv, &E1) == e_success)
	{
           printf("INFO : Read and Validate encode args is success\n");
           if(do_encoding(&E1) == e_success)
	   {
               printf("INFO : --------------Encoding is success-------------\n");
	   }
	   else
	   {
	       printf("ERROR : Failed to Encode\n");
	       return 2;
	   }
	}
	else
	{
           printf("ERROR : Read and Validate encode args is failure\n");
	   return 1;
	}	

    }

    else if(res == e_decode)
    {
	printf("INFO : Selected Decoding\n");
	if(read_and_validate_decode_args(argv, &D1) == e_success)
	{
	    printf("INFO : Read and Validate args are success\n");
	    if(do_decoding(&D1) == e_success)
	    {
		 printf("INFO : --------------Decoding is success-------------\n");
	    }
	    else
	    {
                 printf("ERROR : Failed to decode\n");
		 return 2;
	    }
	}
	else
	{
	    printf("INFO : Read and validate args are failure\n");
	    return 1;
	}
    }
    else
    {
	printf("Invalid option\nUsage:\nFor Encoding:./a.out -e beautiful.bmp secret.txt [stegano.bmp]\nFor Decoding:./a.out -d stegano.bmp [data.txt]\n");
    }

    return 0;
}

OperationType check_operation_type(char *argv[])
{
    if(strcmp(argv[1] , "-e") == 0)
    {
        return e_encode;
    }
    else if(strcmp(argv[1] ,"-d") == 0)
    {
        return e_decode;
    }
    else
    {
	return e_unsupported;
    }
}
